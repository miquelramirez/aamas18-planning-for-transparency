
#include <map>
#include <set>
#include <limits>
#include <algorithm>

#include <strips_prob.hxx>
#include <fluent.hxx>
#include <action.hxx>
#include <cond_eff.hxx>
#include <fwd_search_prob.hxx>
#include <landmark_graph.hxx>
#include <landmark_graph_manager.hxx>
#include <landmark_graph_generator.hxx>

#include "lm_plan_recognition.hxx"
#include "utility.hxx"

using	aptk::agnostic::Fwd_Search_Problem;
using Goal_set = std::vector<std::vector<unsigned int>>;
using Goal = std::vector<unsigned int>;
using aptk::agnostic::Landmarks_Graph;
using aptk::agnostic::Landmarks_Graph_Generator;

typedef         Landmarks_Graph_Generator<Fwd_Search_Problem>     Gen_Lms_Fwd;

namespace pr_lm{

  PlanRecognitionEngine_LM::PlanRecognitionEngine_LM(aptk::STRIPS_Problem * s_prob, Goal_set goal_set,
      double theta, bool verbose)
  : m_strips_model(s_prob), m_goal_set(goal_set), m_theta(theta),m_verbose(verbose)
  {

  }

  std::vector<unsigned int> PlanRecognitionEngine_LM::extract_landmarks(aptk::STRIPS_Problem& s_prob, Goal& g, bool verbose){

    s_prob.set_goal(s_prob, g);

    Fwd_Search_Problem search_prob (&s_prob);

		Gen_Lms_Fwd    gen_lms( search_prob );
		Landmarks_Graph graph( s_prob );
		gen_lms.compute_lm_graph_set_additive( graph );

    std::vector<unsigned int> land_marks_fluents = extract_fluents_from_graph(graph);

    if (verbose){
      std::cout << "For Goal: ";
      for (auto f : g){
        std::cout << s_prob.fluents()[f]->signature() << ",";
      }
      std::cout << std::endl;
      std::cout << "\tLandmarks found are: ";
      for(auto f : land_marks_fluents){
        std::cout << s_prob.fluents()[f]->signature() << ",";
      }
    }

    return land_marks_fluents;
  }

  std::vector<unsigned int> PlanRecognitionEngine_LM::extract_fluents_from_graph(Landmarks_Graph& lm){

    std::vector<unsigned int> land_marks;
    auto m_lm = lm.m_lm_graph;

    for ( unsigned k = 0; k < m_lm.size(); k++ ) {

      auto n = m_lm[k];

      land_marks.push_back(n->fluent());
    }

    return land_marks;
  }

  std::tuple<std::vector<unsigned int>,std::vector<unsigned int>, std::vector<unsigned int>>
      PlanRecognitionEngine_LM::partition_facts( aptk::STRIPS_Problem& s_prob,
      std::vector<unsigned int>& land_marks)
  {
    std::vector<unsigned int> f_strictly_activating;
    std::vector<unsigned int> f_strictly_terminal;
    std::vector<unsigned int> f_unstable_activating;

    auto init = s_prob.init();


    for (unsigned int f : land_marks){


      // Is f in the initial State
      bool f_init_state = false;
      if(std::find(init.begin(), init.end(), f) != init.end()) {
        f_init_state = true;
      }

      bool not_in_any_adds = true;
      bool not_in_any_dels = true;
      bool not_in_any_precs = true;
      bool exists_a_f_as_prec = false;
      bool exists_a_f_as_del = false;
      bool exists_a_f_as_add = false;

      for( auto a_p : s_prob.actions() ){
        auto adds = a_p->add_vec();
        auto dels = a_p->del_vec();
        auto precs = a_p->prec_vec();

        if(std::find(adds.begin(), adds.end(), f) != adds.end()) {
          not_in_any_adds = false;
          exists_a_f_as_add = true;
        }

        if(std::find(dels.begin(), dels.end(), f) != dels.end()) {
          not_in_any_dels = false;
          exists_a_f_as_del = true;
        }

        if(std::find(precs.begin(), precs.end(), f) != precs.end()) {
          not_in_any_precs = false;
          exists_a_f_as_prec = true;
        }
      }

      if (f_init_state && not_in_any_adds && not_in_any_dels && exists_a_f_as_prec)
        f_strictly_activating.push_back(f);

      if(f_init_state && not_in_any_adds && exists_a_f_as_prec && exists_a_f_as_del)
        f_unstable_activating.push_back(f);

      if(exists_a_f_as_add && not_in_any_precs && not_in_any_dels)
        f_strictly_terminal.push_back(f);

    }

    std::tuple<std::vector<unsigned int>,std::vector<unsigned int>, std::vector<unsigned int>> t(
        f_strictly_activating, f_unstable_activating, f_strictly_terminal
        );

    return t;
  }

  std::map<Goal, double> PlanRecognitionEngine_LM::goal_percent_complete_lm(
      aptk::STRIPS_Problem& s_prob, Goal_set& goal_set, std::vector<unsigned int> observations,
      double theta){

    std::map<Goal, double> map_goal_percent;
    double max = 0;

    for( Goal g : goal_set ){

      std::vector<unsigned int> land_marks_g =  extract_landmarks(s_prob, g, m_verbose);
      std::tuple<std::vector<unsigned int>,
        std::vector<unsigned int>, std::vector<unsigned int>> fact_partition;

      fact_partition = partition_facts(s_prob, land_marks_g);

      auto f_strictly_activating = std::get<0>(fact_partition);
      auto f_unstable_activating = std::get<1>(fact_partition);
      auto f_strictly_terminal = std::get<2>(fact_partition);

      std::cout << f_strictly_activating.size() << f_unstable_activating.size() << f_strictly_terminal.size()
        << std::endl;

      std::vector<unsigned int> int_fsa_init;
      auto init =  s_prob.init();
      sort(f_strictly_activating.begin(), f_strictly_activating.end());
      sort(init.begin(), init.end());

      std::set_intersection(f_strictly_activating.begin(),f_strictly_activating.end(),
          init.begin(),init.end(),back_inserter(int_fsa_init));

      // TODO: CLARIFY THIS
      if (int_fsa_init.empty() && f_strictly_activating.size() != 0){
        //std::cout << "\tLandmarks found are: ";
        //for(auto f : land_marks_fluents){
          //std::cout << s_prob.fluents()[f]->signature() << ",";
        //}
        continue;
      }

      std::set<unsigned int> achieved_landmarks_g;
      bool discardg = false;

      for(unsigned int o : observations){
        auto a = s_prob.actions()[o];

        auto adds_v = a->add_vec();
        std::set<unsigned int> adds(adds_v.begin(), adds_v.end());
        auto prec_v = a->prec_vec();
        std::set<unsigned int> precs(prec_v.begin(), prec_v.end());
        auto del_v = a->del_vec();
        std::set<unsigned int> dels(del_v.begin(), del_v.end());

        std::set<unsigned int> prec_adds;
        std::set<unsigned int> prec_adds_dels;
        std::set_union(adds.begin(), adds.end(),
            precs.begin(), precs.end(),
            std::inserter(prec_adds, prec_adds.begin()));
        std::set_union(prec_adds.begin(), prec_adds.end(),
            dels.begin(), dels.end(),
            std::inserter(prec_adds_dels, prec_adds_dels.begin()));

        std::set<unsigned int> fua_fst;
        std::set_union(f_unstable_activating.begin(), f_unstable_activating.end(),
            f_strictly_terminal.begin(), f_strictly_terminal.end(),
            std::inserter(fua_fst, fua_fst.begin()));

        std::set<unsigned int> intersect;
        std::set_intersection(fua_fst.begin(),fua_fst.end(),prec_adds_dels.begin(),
            prec_adds_dels.end(), std::inserter(intersect, intersect.begin()));

        if(intersect.empty() && fua_fst.size() != 0){
          discardg = true;
          break;
        }

        if(m_verbose){
          std::cout << "\t\t\tLandmarks in Observation " << a->signature() << ": ";
        }
        for ( auto l : land_marks_g ){
          if (prec_adds.count(l)) {
            if(m_verbose){
              std::cout << s_prob.fluents()[l]->signature() << ",";
            }
            achieved_landmarks_g.insert(l);
          }
        }
        std::cout << std::endl;
      }

      if(discardg)
        break;

      auto g1 = g;
      double percentage = (double) achieved_landmarks_g.size() / (double)land_marks_g.size();
      if(percentage > max){
        max = percentage;
      }

      if(percentage >=  max - theta)
        map_goal_percent[g] = percentage;
      else
        map_goal_percent[g] = -1;

      if(m_verbose){
        std::cout  << std::endl;
      }
    }

    for(std::map<Goal,double>::iterator iter = map_goal_percent.begin();
        iter != map_goal_percent.end(); ++iter){
      if(iter->second < max - theta)
        map_goal_percent[iter->first] = -1;
    }

    return map_goal_percent;
  }

  std::map<Goal,double> PlanRecognitionEngine_LM::heuristic(std::vector<unsigned int> observations){
    auto goal = m_strips_model->goal();

    auto A_g = this->goal_percent_complete_lm(*m_strips_model, m_goal_set, observations, m_theta);
    std::map<Goal, double> heuristic;

    for(std::map<Goal,double>::iterator iter = A_g.begin();
        iter != A_g.end(); ++iter){
      Goal G = iter->first;
      double sum = 0;

      if(iter->second == -1){
        heuristic[G] = -1;
        continue;
      }


      for(unsigned int g : G){
        std::vector<unsigned int> g_v = {g};
        auto lms = extract_landmarks(*m_strips_model, g_v, false);
        std::set<unsigned int> g_a_lm;


        for(auto o : observations){
          auto a = m_strips_model->actions()[o];
          auto adds = a->add_vec();
          auto precs = a->prec_vec();

          for ( auto l : lms ){

            if ( std::find(adds.begin(), adds.end(),l) != adds.end() ){
              g_a_lm.insert(l);
              continue;
            }

            if ( std::find(precs.begin(), precs.end(),l) != precs.end() ){
              g_a_lm.insert(l);
              continue;
            }

          }
        }

        sum += (double) g_a_lm.size() / (double) lms.size();

      }

     heuristic[G] = sum / (double) G.size();
    }

    m_strips_model->set_goal(*m_strips_model, goal);

    return heuristic;

  }

  std::vector<double> PlanRecognitionEngine_LM::plan_recognition(
      std::vector<unsigned int> observations){

    auto h = heuristic(observations);
    std::vector<double> probs;

    for (auto G : m_goal_set){
      if(h[G] == -1)
        probs.push_back(0);
      else
        probs.push_back(h[G]);
    }

    float sum = 0;
    for(auto i : probs){
      sum += i;
    }


    std::vector<double> priors;

    if (sum != 0)
      probs = normalize_vector(probs);
    else
    {
      for (unsigned int i = 0; i < m_goal_set.size(); i++){
        priors.push_back(0.5);
      }
      probs = normalize_vector(priors);
    }


    return probs;

  }

}

