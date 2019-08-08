
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
using aptk::agnostic::Landmarks_Graph_Generator;
using aptk::agnostic::Landmarks_Graph;

typedef         Landmarks_Graph_Generator<Fwd_Search_Problem>     Gen_Lms_Fwd;
typedef         Landmarks_Graph::Node Search_Node;

namespace pr_lm{

  PlanRecognitionEngine_LM::PlanRecognitionEngine_LM(aptk::STRIPS_Problem * s_prob, Goal_set goal_set,
      double theta, bool verbose)
  : m_strips_model(s_prob), m_goal_set(goal_set), m_theta(theta),m_verbose(verbose)
  {
    generate_landmarks_graphs();
  }

  PlanRecognitionEngine_LM::PlanRecognitionEngine_LM(aptk::STRIPS_Problem const * s_prob, Goal_set goal_set,
      double theta, bool verbose)
  : m_strips_model(NULL), m_goal_set(goal_set), m_theta(theta),m_verbose(verbose)
  {
    aptk::STRIPS_Problem * n = new aptk::STRIPS_Problem(*s_prob);
	  m_strips_model = n;
	  generate_landmarks_graphs();
  }

  void PlanRecognitionEngine_LM::generate_landmarks_graphs(){

    for(unsigned int i = 0; i < m_goal_set.size(); i++){

      m_strips_model->set_goal(*m_strips_model, m_goal_set[i]);

      Fwd_Search_Problem search_prob (m_strips_model);
      Gen_Lms_Fwd    gen_lms( search_prob );
      Landmarks_Graph * graph = new Landmarks_Graph( *m_strips_model );
      gen_lms.compute_lm_graph_set_additive( *graph );

      bool verbose = false;
      if (verbose){
        std::cout << "For Goal: ";
        for (auto f : m_goal_set[i]){
          std::cout << m_strips_model->fluents()[f]->signature() << ",";
        }
        std::cout << std::endl;
        std::cout << "\tLandmarks found are: ";
        auto e = extract_fluents_from_graph(*graph);
        for(auto f : e){
          std::cout << m_strips_model->fluents()[f]->signature() << ",";
        }
        std::cout << std::endl;
      }

      Landmarks_Graph_Manager * lm = new Landmarks_Graph_Manager(search_prob, graph);
      m_lgm_v[m_goal_set[i]] = lm;

    }


  }

  PlanRecognitionEngine_LM::~PlanRecognitionEngine_LM(){
    //for(Goal g : m_goal_set){
      //delete m_lgm_v[g];
    //}

  }

	void PlanRecognitionEngine_LM::update_graph(std::vector<unsigned int> observations){

	  auto init = m_strips_model->init();

	  for( auto g : m_goal_set ){
	    auto i = m_lgm_v[g];
      i->reset_graph();
      i->apply_state(init);

      aptk::State * root = new aptk::State(*m_strips_model);
      root->set(init);

      for(unsigned j = 0; j < observations.size(); j++){
        aptk::State* next_root_state = root->progress_through( *(m_strips_model->actions()[observations[j]])  );
        i->apply_action( next_root_state, observations[j]);
        root = next_root_state;
      }
    }
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
    std::vector<aptk::agnostic::Landmarks_Graph::Node*> m_lm = lm.m_lm_graph;

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

  double PlanRecognitionEngine_LM::percentage_complete_lm(Goal g, unsigned int f, std::vector<unsigned int> observations){

    auto lmg = m_lgm_v[g];
    std::vector<unsigned int> lms;
    lmg->graph()->preceding(f, lms);

    if(lms.size() == 0){
      return 0;
    }

    std::set<unsigned int> g_a_lm;
    double percentage_complete;

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

    //std::vector<unsigned int> output(g_a_lm.begin(), g_a_lm.end());
    //std::cout << print_fluent_vec(*m_strips_model, output) << std::endl;


    percentage_complete = (double) g_a_lm.size() / (double) lms.size();

    return percentage_complete;

  }

  std::map<Goal, double> PlanRecognitionEngine_LM::goal_filtering(
      std::vector<unsigned int> observations){

    std::map<Goal, double> map_goal_percent;
    double max = 0;

    for( unsigned int k = 0 ; k < m_goal_set.size(); k++ ){
      Goal g = m_goal_set[k];

      std::vector<unsigned int> land_marks_g = extract_fluents_from_graph(*(m_lgm_v[g]->graph()));
      std::tuple<std::vector<unsigned int>,
        std::vector<unsigned int>, std::vector<unsigned int>> fact_partition;

      fact_partition = partition_facts(*m_strips_model, land_marks_g);

      auto f_strictly_activating = std::get<0>(fact_partition);
      auto f_unstable_activating = std::get<1>(fact_partition);
      auto f_strictly_terminal = std::get<2>(fact_partition);


      if(m_verbose){
        std::cout << "Strictly Activating: " << f_strictly_activating.size() << std::endl;
        std::cout << "Unstable Activating: " << f_unstable_activating.size() << std::endl;
        std::cout << "Strictly Terminal: " << f_strictly_terminal.size() << std::endl;
      }

      std::vector<unsigned int> int_fsa_init;
      auto init =  m_strips_model->init();
      sort(f_strictly_activating.begin(), f_strictly_activating.end());
      sort(init.begin(), init.end());

      std::set_intersection(f_strictly_activating.begin(),f_strictly_activating.end(),
          init.begin(),init.end(),back_inserter(int_fsa_init));

      // TODO: CLARIFY THIS
      if (int_fsa_init.empty() && f_strictly_activating.size() != 0){
        //std::cout << "\tLandmarks found are: ";
        //for(auto f : land_marks_fluents){
          //std::cout << m_strips_model.fluents()[f]->signature() << ",";
        //}
        map_goal_percent[g] = -1;
        continue;
      }

      std::set<unsigned int> achieved_landmarks_g;
      bool discardg = false;

      for(unsigned int o : observations){
        auto a = m_strips_model->actions()[o];

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
          map_goal_percent[g] = -1;
          break;
        }

        if(m_verbose){
          std::cout << "\t\t\tLandmarks in Observation " << a->signature() << ": ";
        }
        for ( auto l : land_marks_g ){
          if (prec_adds.count(l)) {
            if(m_verbose){
              std::cout << m_strips_model->fluents()[l]->signature() << ",";
            }
            achieved_landmarks_g.insert(l);
          }
        }
        if(m_verbose)
          std::cout << std::endl;
      }

      if(discardg)
        break;

      auto g1 = g;
      double percentage = (double) achieved_landmarks_g.size() / (double)land_marks_g.size();
      if(percentage > max){
        max = percentage;
      }

      map_goal_percent[g] = percentage;

      if(m_verbose){
        std::cout  << std::endl;
      }
    }

    for(std::map<Goal,double>::iterator iter = map_goal_percent.begin();
        iter != map_goal_percent.end(); ++iter){

      if(iter->second < max - m_theta)
        map_goal_percent[iter->first] = -1;
    }

    return map_goal_percent;
  }

  std::map<Goal,double> PlanRecognitionEngine_LM::heuristic(std::vector<unsigned int> observations){
    auto goal = m_strips_model->goal();

    auto A_g = goal_filtering(observations);
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
        int a = percentage_complete_lm(G,g,observations);
        sum += a;
      }

     heuristic[G] = sum / (double) G.size();
     heuristic[G] = (double) iter->second / (double) G.size();
    }

    m_strips_model->set_goal(*m_strips_model, goal);

    return heuristic;

  }

  //std::vector<double> PlanRecognitionEngine_LM::plan_recognition(
      //std::vector<unsigned int> observations){


    //auto h = heuristic(observations);
    //std::vector<double> probs;

    //for (auto G : m_goal_set){
      //if(h[G] == -1)
        //probs.push_back(0);
      //else
        //probs.push_back(h[G]);

    //}

    //float sum = 0;
    //for(auto i : probs){
      //sum += i;
    //}


    //std::vector<double> priors;

    //if (sum != 0)
      //probs = normalize_vector(probs);
    //else
    //{
      //for (unsigned int i = 0; i < m_goal_set.size(); i++){
        //priors.push_back(0.5);
      //}
      //probs = normalize_vector(priors);
    //}

    //return probs;

  //}
  std::vector<double> PlanRecognitionEngine_LM::plan_recognition(
      std::vector<unsigned int> observations){

    std::map<Goal,std::vector<unsigned int>> land_marks_g;

    for (Goal g : m_goal_set){
      land_marks_g[g] = extract_fluents_from_graph(*(m_lgm_v[g]->graph()));
    }


	  auto init = m_strips_model->init();
    std::set<unsigned int> observation_landmarks;
    for(auto o : observations){
      auto a = m_strips_model->actions()[o];
      auto adds = a->add_vec();
      auto precs = a->prec_vec();

      for (auto a : adds){
        if (std::find(init.begin(), init.end(),a) == init.end())
          observation_landmarks.insert(a);
      }
      for (auto a : precs){
        if (std::find(init.begin(), init.end(),a) == init.end())
          observation_landmarks.insert(a);
      }
    }

    std::vector<unsigned int> obs_lms(observation_landmarks.begin(),observation_landmarks.end());


    std::vector<double> liklihoods;
    for(Goal G : m_goal_set){
      double counter = 0;
      for(Goal g : m_goal_set){
        auto int_l = instersection<unsigned int>(land_marks_g[G],land_marks_g[g]);

        if(!int_l.empty())
          counter++;
      }


      auto obs_int = instersection<unsigned int>(land_marks_g[G], obs_lms);

      double liklihood = ((double) obs_int.size()) / (counter);
      liklihoods.push_back(liklihood);
    }

    auto normalize_liklihoods = normalize_vector(liklihoods);
    print_vector(normalize_liklihoods);

    std::vector<double> pOGpG;
    for (unsigned int i = 0 ; i < normalize_liklihoods.size() ; i++){
      pOGpG.push_back(normalize_liklihoods[i]*(m_strips_model->m_priors[i]));
    }

    return normalize_vector(pOGpG);
  }


}

