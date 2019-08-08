
#ifndef __BFWS_PR_MCTS__
#define __BFWS_PR_MCTS__

#include "mcts.hxx"
#include "h_rplm.hxx"
#include "plan_recognition.hxx"

#include <utility>
#include <novelty.hxx>
#include <strips_prob.hxx>
#include <aptk/open_list.hxx>
#include <aptk/closed_list.hxx>
#include <h_1.hxx>
#include <rp_heuristic.hxx>

#include <iostream>
#include <fstream>
#include <map>
#include <ctype.h>

#include <fwd_search_prob.hxx>
#include "bfws/src/new_node_comparer.hxx"
#include "bfws/src/dynamic_novelty_partition.hxx"
#include "bfws/src/novelty_partition.hxx"
#include "bfws/src/recursive_novelty_partition.hxx"
#include "bfws/src/pc_gbfs_2h.hxx"

#include <novelty.hxx>
#include "bfws/src/iw.hxx"
#include <aptk/string_conversions.hxx>


using aptk::agnostic::Fwd_Search_Problem;
using aptk::search::Open_List;
using aptk::agnostic::Dynamic_Novelty_Partition;
using aptk::agnostic::Novelty_Partition;
using	aptk::search::Node_Comparer_2H;
using	aptk::search::gbfs_2h::AT_GBFS_2H;
using aptk::agnostic::Novelty;
using	aptk::search::brfs::IW;

using aptk::agnostic::H1_Heuristic;
using	aptk::agnostic::H_Max_Evaluation_Function;
using	aptk::agnostic::H_Add_Evaluation_Function;
using	aptk::agnostic::Relaxed_Plan_Heuristic;

typedef		aptk::search::gbfs_2h::Node< Fwd_Search_Problem, aptk::State >	Search_Node_gbfs;
typedef		Node_Comparer_2H< Search_Node_gbfs >	Tie_Breaking_Algorithm_gbfs;
typedef		Open_List< Tie_Breaking_Algorithm_gbfs, Search_Node_gbfs > BFS_Open_List_gbfs;

typedef   Dynamic_Novelty_Partition<Fwd_Search_Problem, Search_Node_gbfs> H_Dyn_Novel_Fwd;
typedef   Novelty_Partition<Fwd_Search_Problem, Search_Node_gbfs> H_Novel_Partition_Fwd;


using	aptk::search::bfs::AT_BFS_SQ_SH;
using	aptk::search::Node_Comparer;

typedef	aptk::search::bfs::Node< aptk::State >	Search_Node_bfs;
typedef	Node_Comparer< Search_Node_bfs >	Tie_Breaking_Algorithm_bfs;
typedef	Open_List< Tie_Breaking_Algorithm_bfs, Search_Node_bfs >	BFS_Open_List_bfs;

typedef	H1_Heuristic<Fwd_Search_Problem, H_Add_Evaluation_Function>	H_Add_Fwd;
typedef	Relaxed_Plan_Heuristic< Fwd_Search_Problem, H_Add_Fwd >		H_Add_Rp_Fwd;

typedef AT_BFS_SQ_SH<Fwd_Search_Problem, H_Add_Rp_Fwd, BFS_Open_List_bfs> BFS_H_RP_Fwd;
//typedef AT_GBFS_SQ_SH<Fwd_Search_Problem, H_Add_Rp_Fwd, BFS_Open_List_gbfs> GBFS_H_RP_Fwd;

// Optimal


template <typename Search_Model>
class BFWS_PR_MCTS: public MCTS<Search_Model>{

public:

  typedef typename Search_Model::State_Type State;
  typedef Node<State> Search_Node;
  typedef aptk::search::Closed_List<Search_Node> Closed_List_Type;
  typedef aptk::agnostic::Plan_Recognition_Heuristic<Fwd_Search_Problem> 	H_PR;
  typedef AT_GBFS_2H< Fwd_Search_Problem, H_Dyn_Novel_Fwd, H_PR, BFS_Open_List_gbfs > BWFS_Dynamic_Novel_H_PR_Fwd;

  typedef	H1_Heuristic<Fwd_Search_Problem, H_Add_Evaluation_Function>	H_Add_Fwd;
  typedef	Relaxed_Plan_Heuristic< Fwd_Search_Problem, H_Add_Fwd >		H_Add_Rp_Fwd;


	 BFWS_PR_MCTS( 	const Search_Model& search_problem, const std::vector<std::vector<unsigned>> goal_set,
	  const std::vector<double> priors, unsigned goal_index, std::vector<unsigned> observations,
	  std::vector<unsigned int> init, bool has_closed_list, double discount_factor,
	  float beta, bool optimal, bool diff_plan_rec, bool verbose, unsigned int max_simulate_nodes,
	  int precision, int counter, Closed_List_Type * closed_list, double& threshold
	  )
	  : MCTS<Search_Model>(search_problem, has_closed_list, verbose, closed_list),
	  m_goal_set(goal_set), m_priors(priors), m_index(goal_index),
	  m_top_level_observations(observations),
	  m_best_transparency(-infty), m_init(init), m_discount_factor(discount_factor),
	  m_beta(beta), m_optimal(optimal), m_diff_plan_rec(diff_plan_rec),
    m_max_simulate_nodes(max_simulate_nodes), m_precision(precision),
    m_bfws(search_problem), m_counter(counter), m_threshold_met(false)
	{
    for (unsigned int i = 0; i < goal_set.size(); i++)
      if (i == goal_index)
        m_perfect_dist.push_back(1.0);
      else
        m_perfect_dist.push_back(0.0);


    float prior_sum = 0;
    float max_other = 0;
    for(unsigned i = 0; i < m_priors.size(); i++){
      if(i != goal_index){
        prior_sum += m_priors[i];

        if(max_other < m_priors[i])
          max_other = m_priors[i];
      }
    }



    m_priors_av = prior_sum / ((float) m_priors.size() - 1) + (m_priors[goal_index] - max_other);
    threshold = m_priors_av;

    //std::cout << "Theshold: " << m_priors_av << std::endl;

    m_bfws.start();
    m_best_node = this->m_root;
	}

   ~BFWS_PR_MCTS(){
     //std::cout << this->m_problem.task().fluents()[ m_best_node->state()->fluent_vec()[0] ]->signature() << ": " << m_best_node->m_true_reward << ", " << m_best_node->m_g << std::endl;
     //print_m_tree_to_dot(this->m_tree, this->m_root);
   }

   std::vector<double> belief_state(){
     return m_end_belief;
   }

protected:

  virtual Search_Node * select( Search_Node * root ){
    if(m_threshold_met)
      return NULL;

    Search_Node_gbfs * child = m_bfws.next_node();

    if(!child){
      return NULL;
    }

    State * succ = child->state();
    unsigned int a = child->action();
    Search_Node * n;
    Search_Node * parent;

    if(child->parent()){
      parent = m_node_conversion[child->parent()];
      n = new Search_Node( succ, this->m_problem.cost( *(parent->state()), a ), a, parent );
      n->m_deltas = child->m_total_delta;
    }else{
      n = root;
      n->m_deltas = 0.0f;
    }

    m_node_conversion[child] = n;

    if(parent != NULL){
      this->m_tree[parent].push_back(n);
    }

    n->reward() = -1*((int)child->m_h2);
    n->m_delta_sum = child->m_total_delta;
    n->m_t_delta_sum = child->m_total_delta;

    // Thresholding
    {
      float max_prob = 0;
      for(unsigned i = 0; i < child->m_post.size(); i++){
        if(i != child->m_goal_index){
          if (child->m_post[i] > max_prob){
            max_prob = child->m_post[i];
          }
        }

      }


      if (max_prob < child->m_post[child->m_goal_index] - (m_priors_av)){
        //std::cout << "MaxProb: " << max_prob << ", GoalProb: " << child->m_post[child->m_goal_index] << ", YES";
        if(a != -1)
        {
          m_threshold_met = true;
        }

      }
      else{
        //std::cout << "MaxProb: " << max_prob << ", GoalProb: " << child->m_post[child->m_goal_index] << ", NO";
      }

    }

    return n;
  }

  std::vector<Search_Node *> expand(Search_Node * parent){
    std::vector<Search_Node * > heads;
    heads.push_back(parent);
    return heads;
  }

  double simulate(Search_Node * n, unsigned int max_actions){

    // Find MCTS Observations
    Search_Node * child = n;
    std::vector<unsigned> observations(m_top_level_observations);

    std::vector<unsigned> mcts_observations;
    while(child){
      if (child->action() == -1)
        break;

      mcts_observations.push_back(child->action());
      child = child->parent();
    }
    std::reverse(mcts_observations.begin(), mcts_observations.end());
    observations.insert( observations.end(), mcts_observations.begin(), mcts_observations.end()  );

    //// Perform Plan Recognition on MCTS Observations
    //std::vector<double> posteriors;
    //if(m_optimal)
    //{
      //posteriors = plan_recognition(this->m_problem.task(),
          //m_goal_set, m_priors, observations, m_init, m_beta, true, m_diff_plan_rec, false);
    //}else{
      //posteriors = plan_recognition_approx(this->m_problem.task(),
          //m_goal_set, m_priors, observations, m_init, m_beta,3,m_diff_plan_rec,false);
    //}

    //double ambiguity = quantify_prob_distribution(posteriors,   mcts_observations.size());

    ////double transparency_no_discount = quantify_prob_distribution(posteriors, 0);
    ////n->reward() = transparency;
    ////n->m_true_reward = transparency;
    ////n->m_reward_no_discount = transparency_no_discount;

    //float average_ambiguity;

    //if (!n->parent())
      //average_ambiguity = ambiguity;
    //else
      //average_ambiguity = (( n->parent()->reward() * n->parent()->m_g ) + ambiguity) / n->m_g;

    if(this->m_verbose){
      float beta = (n->m_deltas == 0 ? this->m_problem.task().m_beta : this->m_problem.task().m_beta / n->m_deltas);


      std::cout << "Top: " << m_top_level_observations.size() << ", MCTS: " << mcts_observations.size()
        << " Reward: " << n->reward() << ", Plan: ";

      for (auto i : mcts_observations){
        std::cout << this->m_problem.task().actions()[i]->signature() << ", ";
      }
      std::cout << "Beta: " <<  beta << std::endl;
    }

    //n->reward() = average_ambiguity;
    //n->m_true_reward = average_ambiguity;

    //if( m_best_transparency < average_ambiguity ){
      //m_best_transparency = average_ambiguity;
      //m_best_node = n;
    //}

    float cost_estimate = 0;

    H_Add_Rp_Fwd h_ff(this->m_problem);
    std::vector<aptk::Action_Idx> pref_ops;
    std::vector<aptk::Action_Idx> relaxed_plan;
    h_ff.eval(*(n->state()), cost_estimate, pref_ops, relaxed_plan);

    n->m_ce = cost_estimate;

    return n->reward(); // average_ambiguity;
  }

  Search_Node * tie_break_action(std::vector<Search_Node * > children){

    double best_reward = infty;
    std::vector<Search_Node *> max_children = children;

    bool h_verbose = this->m_problem.task().m_h_verbose;

    //if(h_verbose)
    //{
      //std::cout << "\t----------------------\n";
      //std::cout << "\tSmallest Distance to Goal:" << std::endl;
    //}

    //for (unsigned int i = 0; i < children.size(); i++){
      //Search_Node * child = children[i];

      //if(h_verbose)
        //std::cout << "\t" << this->m_problem.task().actions()[child->action()]->signature() << ": " << child->m_ce << std::endl;

      //if(child->m_ce < best_reward){
        //best_reward = child->m_ce;
        //max_children.clear();
        //max_children.push_back(child);
      //} else if (child->m_ce == best_reward){
        //max_children.push_back(child);
      //}
    //}

    //assert(max_children.size() > 0);

    //float small_delta_sum = infty;
    //std::vector<Search_Node *> beta_children;

    //if(h_verbose)
    //{
      //std::cout << "\t\t----------------------\n";
      //std::cout << "\t\tSmallest Delta Sum Value:" << std::endl;
    //}

    //for (unsigned int i = 0; i < max_children.size(); i++){
      //Search_Node * child = max_children[i];

      //if(h_verbose)
        //std::cout << "\t\t" << this->m_problem.task().actions()[child->action()]->signature() << ": " << child->m_delta_sum << std::endl;

      //if(child->m_delta_sum < small_delta_sum){
        //small_delta_sum = child->m_delta_sum;
        //beta_children.clear();
        //beta_children.push_back(child);
      //} else if (child->m_delta_sum == small_delta_sum){
        //beta_children.push_back(child);
      //}
    //}

    //if(h_verbose)
    //{
      //std::cout << "\t\t----------------------\n";
      //std::cout << "\t\t\tSmallest Action Delta Sum Value:" << std::endl;
    //}

    //float t_small_delta_sum = infty;
    //std::vector<Search_Node *> t_beta_children;

    //for (unsigned int i = 0; i < beta_children.size(); i++){
      //Search_Node * child = beta_children[i];

      //if(h_verbose)
        //std::cout << "\t\t\t" << this->m_problem.task().actions()[child->action()]->signature() << ": " << child->m_t_delta_sum << std::endl;

      //if(child->m_t_delta_sum < t_small_delta_sum){
        //t_small_delta_sum = child->m_t_delta_sum;
        //t_beta_children.clear();
        //t_beta_children.push_back(child);
      //} else if (child->m_t_delta_sum == t_small_delta_sum){
        //t_beta_children.push_back(child);
      //}
    //}

    //for (auto i : t_beta_children){
      //std::cout << "\t\t\t\t"<< i->m_ce << std::endl;
    //}


		if(children.size() == 1)
    {
      m_end_belief = children[0]->state()->belief_state();
      return children[0];
    }
    else{
      aptk::STRIPS_Problem * n = new aptk::STRIPS_Problem();
      (*n).set_domain_name(this->m_problem.task().domain_name());
      (*n).set_problem_name(this->m_problem.task().problem_name());

      for(auto f : this->m_problem.task().fluents()){
        (*n).add_fluent((*n), f->signature());
      }

      unsigned next_index = n->add_fluent(*n, "NEXT");

      for(auto a : this->m_problem.task().actions()){

        bool inchoice = false;
        for(auto c : children){
          if(c->action() == a->index()){
            inchoice = true;
            break;
          }
        }

        if ( inchoice ){
          auto av = a->add_vec();
          av.push_back(next_index);
          auto ap = a->prec_vec();
          auto ad = a->del_vec();
          n->add_action(*n, a->signature(), ap, av, ad, a->ceff_vec(), a->cost());

          //if(h_verbose){
            //std::cout << "InChild Action:\n";
            //std::cout << "Adds: " << print_fluent_vec(*n, av) << std::endl;
            //std::cout << "Precs: " << print_fluent_vec(*n, ap) << std::endl;
          //}
        }else{
          auto av = a->add_vec();
          auto ap = a->prec_vec();
          ap.push_back(next_index);
          auto ad = a->del_vec();
          n->add_action(*n, a->signature(), ap, av, ad, a->ceff_vec(), a->cost());
          //if(h_verbose){
            //std::cout << "NormalAction:\n";
            //std::cout << "Adds: " << print_fluent_vec(*n, av) << std::endl;
            //std::cout << "Precs: " << print_fluent_vec(*n, ap) << std::endl;
          //}
        }

      }

      (*n).set_goal((*n), m_goal_set[m_index]);
      (*n).set_init((*n), children[0]->m_parent->state()->fluent_vec());
      if(h_verbose){
        std::cout << "\tInit: " << print_fluent_vec(*n, n->init()) << std::endl;
        std::cout << "\tGoal: " << print_fluent_vec(*n, n->goal()) << std::endl;
      }
      n->make_action_tables();

      Fwd_Search_Problem search_prob(n);

      float cost = infty;
      std::vector<aptk::Action_Idx> plan;
      BFS_H_RP_Fwd engine( search_prob );
      engine.start();
      if(engine.find_solution( cost, plan )){
        if(plan.size() < 1){
          m_end_belief = children[children.size()-1]->state()->belief_state();
          return children[children.size()-1];
        }
        if(h_verbose)
          std::cout << "\tTieBreakPlan: " << print_action_vec(*n, plan) << std::endl;

        for(auto c : children){
          if (c->action() == plan[0])
          {
            m_end_belief = c->state()->belief_state();
            return c;
          }
        }
      }else{
        m_end_belief = children[children.size()-1]->state()->belief_state();
        return children[children.size()-1];
      }

    }

		//unsigned int chosen_child = beta_children.size() - 1;
		//return beta_children[chosen_child];

  }




private:

  double quantify_prob_distribution(std::vector<double> posteriors, unsigned int length){
    double discount_factor;
    double distance;

    if (m_discount_factor == 0){
      if (length == 0){
        discount_factor = 1;
      } else {
        discount_factor = infty;
      }
    } else {
      discount_factor = pow(1/m_discount_factor, length);
    }

    distance = hellinger_distance(m_perfect_dist, posteriors);

    return discount_factor*distance;
  }

  double hellinger_distance(const std::vector<double> P, const std::vector<double> Q){
    assert(P.size() == Q.size());

    double h_d_2 = 0.0;

    for (unsigned int i = 0; i < P.size(); i++)
    {
      double p_q_i = P[i] - Q[i];
      h_d_2 += p_q_i*p_q_i;
    }

    return -1*sqrt(h_d_2);
  }

  void print_m_tree_to_dot(std::map<const Search_Node *, std::vector<Search_Node *>> root_tree, Search_Node * root_node){

    std::stringstream rv;
    rv << "digraph G{\n";

    std::string c_r_v = print_m_tree_rec(root_tree, root_node);

    rv << c_r_v << "}";

    std::stringstream filename;
    filename << m_counter << ".dot";

    std::ofstream outputFile;
    outputFile.open(filename.str());
    outputFile << rv.str();
    outputFile.close();

    std::stringstream graph_file_name;
    graph_file_name << "graph/" << m_counter << ".ps";

    std::stringstream cmd;
    cmd << "dot -Tps " << filename.str() << " -o " << graph_file_name.str();

    system(cmd.str().c_str());
    std::remove(filename.str().c_str());
  }

  std::string print_m_tree_rec(std::map<const Search_Node *, std::vector<Search_Node *>> root_tree, Search_Node * node){
    std::stringstream rv;

    std::string a;
    if (node->action() > 0)
      a = this->m_problem.task().actions()[node->action()]->signature();
    else
      a = "Root";

    std::string fluent_full = this->m_problem.task().fluents()[node->state()->fluent_vec()[0]]->signature();
    std::stringstream fluent;
    fluent << "\"" << fluent_full << "\"";

    std::stringstream sf;

    sf << "\"" << fluent_full << ", " << a << ", " << node->m_reward << ", " << node->m_g
      << "\"";

    std::string f = sf.str();

    //rv << "\t" << fluent.str() << " [label=" << f << "]\n";

    for(unsigned i = 0; i < root_tree[node].size(); i++){
      Search_Node * child = root_tree[node][i];
      std::string fluent_child_full = this->m_problem.task().fluents()[child->state()->fluent_vec()[0]]->signature();

      std::stringstream csf;
      csf << "\"" << fluent_child_full << ", " << this->m_problem.task().actions()[child->action()]->signature() << ", " << child->m_reward  << ", " << child->m_g
        << "\"";

      rv << "\t" << f  << " -> " << csf.str() << ";\n";

      std::string child_return_value = print_m_tree_rec( root_tree, child );

      rv << child_return_value;
    }

    std::string return_value = rv.str();

    return return_value;
  }


public:
  BWFS_Dynamic_Novel_H_PR_Fwd m_bfws;

protected:
  std::vector<std::vector<unsigned int>> m_goal_set;
  std::vector<double> m_priors;
  unsigned int m_index;
  std::vector<unsigned int> m_top_level_observations;
  std::vector<unsigned> m_init;
  double m_discount_factor;
  float m_beta;
  bool m_optimal;
  bool m_diff_plan_rec;
  unsigned int m_max_simulate_nodes;
  int m_precision;
  std::vector<double> m_perfect_dist;
  std::map<Search_Node_gbfs *, Search_Node *> m_node_conversion;

private:
  double m_best_transparency;
  Search_Node * m_best_node;
  int m_counter;
  bool m_threshold_met;
  float m_priors_av;
  std::vector<double> m_end_belief;


};

#endif
