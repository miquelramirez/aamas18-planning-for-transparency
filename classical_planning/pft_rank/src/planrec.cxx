#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include "planrec.hxx"
#include "a_h_1_rp.hxx"

#include <ff_to_aptk.hxx>
#include <strips_prob.hxx>
#include <fluent.hxx>
#include <action.hxx>
#include <cond_eff.hxx>
#include <strips_state.hxx>
#include <fwd_search_prob.hxx>
#include <mutex_set.hxx>

#include <h_1.hxx>
#include <rp_heuristic.hxx>

#include <aptk/open_list.hxx>
#include <aptk/string_conversions.hxx>
#include <aptk/at_bfs.hxx>
#include <aptk/at_gbfs.hxx>

#include <fstream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

using	aptk::STRIPS_Problem;

using	aptk::agnostic::Fwd_Search_Problem;
using	aptk::Action;

using aptk::agnostic::H1_Heuristic;
using	aptk::agnostic::H_Max_Evaluation_Function;

using	aptk::agnostic::H_Add_Evaluation_Function;
using	aptk::agnostic::Relaxed_Plan_Heuristic;

using aptk::agnostic::recog::RP_H1_Heuristic;

using aptk::search::Open_List;
using	aptk::search::bfs::AT_BFS_SQ_SH;
using aptk::search::bfs::AT_GBFS_SQ_SH;
using	aptk::search::Node_Comparer;

typedef	aptk::search::bfs::Node< aptk::State >	Search_Node;
typedef	Node_Comparer< Search_Node >	Tie_Breaking_Algorithm;
typedef	Open_List< Tie_Breaking_Algorithm, Search_Node >	BFS_Open_List;

typedef	H1_Heuristic<Fwd_Search_Problem, H_Max_Evaluation_Function>	H_Max_Fwd;
typedef	AT_BFS_SQ_SH< Fwd_Search_Problem, H_Max_Fwd, BFS_Open_List >	BFS_H_Max_Fwd;

typedef	H1_Heuristic<Fwd_Search_Problem, H_Add_Evaluation_Function>	H_Add_Fwd;
typedef	Relaxed_Plan_Heuristic< Fwd_Search_Problem, H_Add_Fwd >		H_Add_Rp_Fwd;

typedef AT_BFS_SQ_SH<Fwd_Search_Problem,H_Add_Rp_Fwd, BFS_Open_List> BFS_H_RP_Fwd;
typedef AT_GBFS_SQ_SH<Fwd_Search_Problem, H_Add_Rp_Fwd, BFS_Open_List> GBFS_H_RP_Fwd;

typedef RP_H1_Heuristic<Fwd_Search_Problem, H_Max_Evaluation_Function> H_A_MAX_Fwd;

// Greedy Best First Seach and Novelty, Nir's Code
// ----------------------------------------------------------------------

#include "gbfs_f_local/src/new_node_comparer.hxx"
#include "gbfs_f_local/src/dynamic_novelty_partition.hxx"
#include "gbfs_f_local/src/novelty_partition.hxx"
#include "gbfs_f_local/src/novelty_partition_2.hxx"
#include "gbfs_f_local/src/recursive_novelty_partition.hxx"
#include "gbfs_f_local/src/at_gbfs_2h.hxx"

#include "gbfs_f_local/src/at_gbfs_3h.hxx"
#include "gbfs_f_local/src/at_gbfs_alternate.hxx"
#include "gbfs_f_local/src/at_gbfs_2h_exp.hxx"
#include "gbfs_f_local/src/2h_exp_node.hxx"

#include <novelty.hxx>
#include "gbfs_f_local/src/iw.hxx"

using 	aptk::agnostic::Dynamic_Novelty_Partition;
using 	aptk::agnostic::Novelty_Partition;
using 	aptk::agnostic::Recursive_Novelty_Partition;
using 	aptk::agnostic::Novelty_Partition_2;

using	aptk::search::Node_Comparer_2H;
using	aptk::search::Node_Comparer_2H_ehc;
using	aptk::search::Node_Comparer_Second;
using	aptk::search::Node_Comparer_Third;
using	aptk::search::Node_Comparer_3H_FN;
using	aptk::search::gbfs_2h::AT_GBFS_2H;
using	aptk::search::gbfs_3h::AT_GBFS_3H;
using	aptk::search::gbfs_alternate::AT_GBFS_Alternate;
using	aptk::search::gbfs_2h_exp::AT_GBFS_2H_EXP;

using aptk::agnostic::Novelty;
using	aptk::search::brfs::IW;

typedef		aptk::search::gbfs_2h::Node< Fwd_Search_Problem, aptk::State >	Search_Node_gbfs;
typedef		Node_Comparer_2H< Search_Node_gbfs >					Tie_Breaking_Algorithm_gbfs;
typedef		Open_List< Tie_Breaking_Algorithm_gbfs, Search_Node_gbfs >		   BFS_Open_List_gbfs;

typedef   Dynamic_Novelty_Partition<Fwd_Search_Problem, Search_Node_gbfs> H_Dyn_Novel_Fwd;
typedef   Novelty_Partition<Fwd_Search_Problem, Search_Node_gbfs> H_Novel_Partition_Fwd;

typedef   AT_GBFS_2H< Fwd_Search_Problem, H_Dyn_Novel_Fwd, H_Add_Rp_Fwd, BFS_Open_List_gbfs > BWFS_Dynamic_Novel_HRP_Fwd;


// ----------------------------------------------------------------------

void print_plan_to_cout(std::vector< int >& plan, Fwd_Search_Problem& search_prob){
	for ( unsigned k = 0; k < plan.size(); k++ ) {
		const aptk::Action& a = *(search_prob.task().actions()[ plan[k] ]);
		std::cout  << a.signature() << ": ";
    for (auto f: a.prec_vec()){
      std::cout << search_prob.task().fluents()[f]->signature() << ", ";
    }


    std::cout << std::endl;
	}
}

// Do search for plan recognition
void do_pr_search(  Fwd_Search_Problem& search_prob,  std::vector< aptk::Action_Idx >& plan, float& cost,  bool anytime, bool delayed, bool greedy, bool optimal  ) {

  cost = infty;
  anytime = false;

  if (optimal){
    BFS_H_Max_Fwd engine( search_prob );
    engine.set_greedy( greedy );
    engine.set_delay_eval( delayed );
    engine.start();
    engine.find_solution( cost, plan );
    //unsigned h_init = 0;
    //BWFS_Dynamic_Novel_HRP_Fwd engine (search_prob);
    //engine.set_arity(0,h_init);
    //engine.start();
    //engine.find_solution(cost, plan);

  }else {
    GBFS_H_RP_Fwd engine( search_prob );
    engine.start();
    engine.find_solution( cost, plan );
  }
}

void do_heuristic(Fwd_Search_Problem& search_prob, float& cost, std::vector<aptk::Action_Idx>& relaxed_plan, std::vector<unsigned>& observations){

  H_Add_Rp_Fwd h_ff(search_prob);
  //H_A_MAX_Fwd h_amax(search_prob, observations);

  Search_Node* root = new Search_Node( search_prob.init(), 0.0f,-1, NULL );
  std::vector<aptk::Action_Idx> pref_ops;
  h_ff.eval(*(root->state()), cost, pref_ops, relaxed_plan);
  //h_amax.eval(*(root->state()), cost);
}

// Translate the problem to a plan recognition problem
void translate_problem(const aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& trans_prob, aptk::Fluent_Vec& w_observation, aptk::Fluent_Vec& wo_observation, std::map<std::string, unsigned int>& idx_to_trans_idx, std::vector<unsigned>& observations, std::vector<unsigned> init_state){

	const std::vector<const aptk::Fluent*> f = prob.fluents();
	const std::vector<const aptk::Action*> as = prob.actions();
	aptk::Fluent_Vec init = init_state;
	aptk::Fluent_Vec goal = prob.goal();
	unsigned index = 0;

	// Add each fluent to transformed problem
	for (unsigned int i = 0; i < prob.num_fluents(); i++){
		trans_prob.add_fluent(trans_prob, (*f[i]).signature());
		idx_to_trans_idx.insert(std::pair<std::string, unsigned int>(std::to_string((*f[i]).index()),index++));

	}

	// Add fluents for each observed action
 	for (unsigned int i = 0; i < observations.size(); i++){
		std::string name = "pa" + std::to_string(observations[i]);
		std::string name_neg = "npa" + std::to_string(observations[i]);

		trans_prob.add_fluent(trans_prob, name);
		idx_to_trans_idx.insert(std::pair<std::string, unsigned int>(name ,index++));

		trans_prob.add_fluent(trans_prob, name_neg);
		idx_to_trans_idx.insert(std::pair<std::string, unsigned int>(name_neg ,index++));

		w_observation.push_back(idx_to_trans_idx[name]);
		wo_observation.push_back(idx_to_trans_idx[name_neg]);
		init.push_back(idx_to_trans_idx[name_neg]);

	}

	// Add actions to translated problem
	for (const aptk::Action * a : as){

		auto address = std::find(observations.begin(), observations.end(), a->index());
		int index = std::distance(observations.begin(), address);

		// The actions corrosponding to the first observation adds the corrosponding fluent unconditionally
		if ( address == observations.begin()){
			aptk::Fluent_Vec add = a->add_vec();
			aptk::Fluent_Vec del = a->del_vec();

			add.push_back(idx_to_trans_idx["pa" + std::to_string(observations[0])]);
			del.push_back(idx_to_trans_idx["npa" + std::to_string(observations[0])]);

			trans_prob.add_action(trans_prob, a->signature(), a->prec_vec(), add, del, a->ceff_vec(), a->cost());

		// Any actions corrosponding to any other observation add the corrospoding fluent only if the fluent corrosponding
		// to the observation immediately prior to this one has already been added.
		 } else if (address != observations.end() ){
			aptk::Fluent_Vec ce_add;
			aptk::Fluent_Vec ce_del;
			aptk::Fluent_Vec ce_prec;
			aptk::Conditional_Effect_Vec ceffs( a->ceff_vec() );
			aptk::Conditional_Effect * ceff = new aptk::Conditional_Effect(trans_prob);

			int prev_obs = idx_to_trans_idx["pa" + std::to_string(observations[index - 1])];
			int curr_obs = idx_to_trans_idx["pa" + std::to_string(a->index())];
			int neg_curr_obs = idx_to_trans_idx["npa" + std::to_string(a->index())];

			ce_prec.push_back(prev_obs);
			ce_add.push_back(curr_obs);
			ce_del.push_back(neg_curr_obs);

			ceff->define(ce_prec, ce_add, ce_del);

			ceffs.push_back(ceff);

			trans_prob.add_action(trans_prob, a->signature(), a->prec_vec(), a->add_vec(), a->del_vec(), ceffs, a->cost());

		// Unobserved action is added as is.
		}else
			trans_prob.add_action(trans_prob, a->signature(), a->prec_vec(), a->add_vec(), a->del_vec(), a->ceff_vec(), a->cost());
	}

	// Set names and initial and goal states the same as
	trans_prob.set_domain_name(prob.domain_name());
	trans_prob.set_problem_name(prob.problem_name());
	trans_prob.set_init(trans_prob, init);
	trans_prob.set_goal(trans_prob, goal);

	trans_prob.make_action_tables();
  unsigned int w_back = w_observation.back();
  unsigned int wo_back = wo_observation.back();
	w_observation.clear();
	wo_observation.clear();
	w_observation.push_back((w_back));
	wo_observation.push_back((wo_back));
  //std::cout << "w_observation: " << trans_prob.fluents()[w_observation[0]]->signature() << "\n";
  //std::cout << "wo_observation: " << trans_prob.fluents()[wo_observation[0]]->signature() << "\n";
}

// Main function for plan recognition
std::vector<double> plan_recognition(const aptk::STRIPS_Problem& prob, std::vector<aptk::Fluent_Vec>& goal_set, std::vector<double> priors, std::vector<unsigned>& observations, aptk::Fluent_Vec& init, float beta, bool optimal) {

	aptk::STRIPS_Problem trans_prob;
	aptk::Fluent_Vec w_observation;
	aptk::Fluent_Vec wo_observation;
	std::map<std::string, unsigned int> idx_to_trans_idx;
  std::vector<float> goal_cost_change;
  float sum (0);

	// Translate problem
	translate_problem(prob, trans_prob, w_observation, wo_observation, idx_to_trans_idx, observations, init);

  // For each goal candidate perform two searches:
  // One where observed actions must be used
  // One where observed actions must not be used
	for (unsigned i = 0; i < goal_set.size(); i++){

    //std::cout << "\nGoal No.: " << i << " / " << goal_set.size() << "\n";
		// Set goal to candidate goal and that observations have occured
		aptk::Fluent_Vec g = goal_set[i];
		aptk::Fluent_Vec pos_goal(g);
		pos_goal.insert(pos_goal.end(), w_observation.begin(), w_observation.end());
		trans_prob.set_goal(trans_prob, pos_goal);

		Fwd_Search_Problem pos_search_prob(&trans_prob);
		std::vector< aptk::Action_Idx > plan;
		float pos_cost(0);

    // Perform search with observations
    do_pr_search(pos_search_prob, plan, pos_cost, false, false, false, optimal);

    //std::cout << "Pos Plan: \n";
    //print_plan_to_cout(plan, pos_search_prob);
    //std::cout << std::endl;
    //print_vector(plan);
    plan.clear();

		// Set goal to candidate goal and that observations must not occur
		aptk::Fluent_Vec neg_goal(g);
		neg_goal.insert(neg_goal.end(), wo_observation.begin(), wo_observation.end());
    /*
     *if (observations == obs){
     *  std::cout << "Goals of PICKUP S and STACK S A:" << std::endl;
     *  for (unsigned int i : neg_goal){
     *    std::cout << (*trans_prob.fluents()[i]).signature() << std::endl;
     *  }
     *}
     */
		trans_prob.set_goal(trans_prob, neg_goal);

		Fwd_Search_Problem neg_search_prob(&trans_prob);
		float neg_cost(0);

    // Perform search without observations
    do_pr_search(neg_search_prob, plan, neg_cost, false, false, false, optimal);

    /*
     *std::cout << "Neg Plan: \n";
     *print_plan_to_cout(plan, neg_search_prob);
     *print_vector(plan);
     */
    plan.clear();

    // Calculate liklihood
		const float pOGin = -1.0f*beta*(neg_cost - pos_cost);
		const float pOGinexp = exp(pOGin);
		const float pOG = 1.0f/(1.0f + pOGinexp);
		const float pOGpG = pOG*priors[i];

    //std::cout << i << ":\tprior: " << priors[i] << std::endl;
    //std::cout <<  "\tneg - pos: " << neg_cost << " - " << pos_cost << std::endl;
    //std::cout <<  " \tpogin: " << pOGin << std::endl;
    //std::cout <<  " \tpoginexp: " << pOGinexp << std::endl;
    //std::cout <<  " \tpog: " << pOG << std::endl;
    //std::cout <<  " \tpogpg: " << pOGpG << std::endl;

		sum += pOGpG;

		goal_cost_change.push_back(pOGpG);
	}
  if (sum != 0){
    auto normv = normalize_vector(goal_cost_change);
    return normv;
  }else {
    std::vector<double> new_priors;
    for (unsigned i = 0; i < priors.size(); i++)
      new_priors.push_back(priors[i]);

    return new_priors;
  }
}

void clone_problem(const aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& trans_prob, std::vector<unsigned>& observations, float cost, std::vector<unsigned> init_state){

	const std::vector<const aptk::Fluent*> f = prob.fluents();
	const std::vector<const aptk::Action*> as = prob.actions();
	aptk::Fluent_Vec init = init_state;
	aptk::Fluent_Vec goal = prob.goal();

	// Add each fluent to transformed problem
	for (unsigned int i = 0; i < prob.num_fluents(); i++){
		trans_prob.add_fluent(trans_prob, (*f[i]).signature());
	}

	// Add actions to translated problem
	for (const aptk::Action * a : as){

		auto address = std::find(observations.begin(), observations.end(), a->index());

		// The actions corrosponding to the observations are given cost "cost", all other actions are the same.
    float a_cost = a->cost();
    //if (address != observations.end() )
      //a_cost = cost;
    //else
      //a_cost = a->cost();

    trans_prob.add_action(trans_prob, a->signature(), a->prec_vec(), a->add_vec(), a->del_vec(), a->ceff_vec(),a_cost);

	}

	// Set names and initial and goal states the same as
	trans_prob.set_domain_name(prob.domain_name());
	trans_prob.set_problem_name(prob.problem_name());
	trans_prob.set_init(trans_prob, init);
	trans_prob.set_goal(trans_prob, goal);

	trans_prob.make_action_tables();

}

void translate_problem_approx_pos(const aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& trans_prob, std::vector<unsigned>& observations, std::vector<unsigned> init_state){

	const std::vector<const aptk::Fluent*> f = prob.fluents();
	const std::vector<const aptk::Action*> as = prob.actions();
	aptk::Fluent_Vec init = init_state;
	aptk::Fluent_Vec goal = prob.goal();

	// Add each fluent to transformed problem
	for (unsigned int i = 0; i < prob.num_fluents(); i++){
		trans_prob.add_fluent(trans_prob, (*f[i]).signature());

	}

	// Add actions to translated problem
	for (const aptk::Action * a : as){

		auto address = std::find(observations.begin(), observations.end(), a->index());

		// The effects of the actions corrosponding to the observations are made true in the initial state,
		// the number of observations is then added to the length of the relaxed plan.
    if (address != observations.end() ){
      for (unsigned int i = 0; i < a->add_vec().size(); i++ ){
        init.push_back(a->add_vec()[i]);
      }
    }
    trans_prob.add_action(trans_prob, a->signature(), a->prec_vec(), a->add_vec(), a->del_vec(), a->ceff_vec(), a->cost());

	}

	// Set names and initial and goal states the same as
	trans_prob.set_domain_name(prob.domain_name());
	trans_prob.set_problem_name(prob.problem_name());
	trans_prob.set_init(trans_prob, init);
	trans_prob.set_goal(trans_prob, goal);

	trans_prob.make_action_tables();

}

// Purpose: Approximate a planning problem which requires that a certain action sequence may not be
// satisfied. This is acheived by taking the root value of a delete relaxed heuristic. In order for
// the solution to not satisfy the action sequence the heuristic is run once for each action in the
// sequence. The action being considered is then disallowed. The minimum value over these runs is
// taken as the approximate cost of optimal path for the given planning problem without satisfying
// the actions sequence. This should always be lesser or equal to the  approximation_wo_delete_relax_break_sequence
// method.
// Arguments:
//  trans_prob_neg: This is the planning problem to be solved.
//  observations: This is the sequence of actions which must not be satisfied.
// Return:
//  The approximate cost of an optimal path which solves the problem.
float approximation_wo_delete_relax_disallow_action(aptk::STRIPS_Problem& trans_prob_neg, std::vector<unsigned> observations){
  float min(infty);

  // For each action in the observation sequence set its cost to infinity in turn
  for (unsigned o: observations){
    aptk::Action * a = trans_prob_neg.actions()[o];
    float temp_a_cost = a->cost();
    a->set_cost(infty);

		// The heuristic at the root node is taken the approximate cost of an optimal plan
		// which does not use the considered action
		Fwd_Search_Problem neg_search_prob(&trans_prob_neg);
		float neg_cost(0);
    std::vector<aptk::Action_Idx> plan;
    do_heuristic(neg_search_prob, neg_cost, plan, observations);
    plan.clear();

    if (min > neg_cost){
      min = neg_cost;
    }

    a->set_cost(temp_a_cost);
  }

  return min;
}

// Purpose: Approximate a planning problem which requires that a certain action sequence may not be
// satisfied. This is acheived by taking the root value of a delete relaxed heuristic. In order for
// the solution to not satisfy the action sequence the heuristic is run once for each action in the
// sequence. The action being considered is then disallowed until another action in the sequence is
// used. The initial state is then advanced through the action being considered and its cost is added
// to every following run. The minimum value over these runs is taken as an approximate optimal path
// for the given planning problem without satisfying the actions sequence.
// Arguments:
//  trans_prob_neg: This is the planning problem to be solved.
//  observations: This is the sequence of actions which must not be satisfied.
// Return:
//  The approximate cost of an optimal path which solves the problem.
float approximation_wo_delete_relax_break_sequence(aptk::STRIPS_Problem& trans_prob_neg, std::vector<unsigned> observations){

  float min(infty);

  // The "NEXT" fluent is used to determine if the current action may be taken.
  unsigned next_index = trans_prob_neg.add_fluent(trans_prob_neg, "NEXT");

  // The true inial state is stored to reconstruct the problem
  auto true_init  (trans_prob_neg.init());

  // At present the code only allows for uniform cost actions
  // So the amount of observatons seen so far is added to the cost of the plan.
  int obs_count = 0;

  // The "NEXT" fluent is added to the add lists of all actions in the observation sequence.
  for (auto o: observations){
    auto a = trans_prob_neg.actions()[o];
    a->add_vec().push_back(next_index);
  }

  // For each observation a heurisitic value is taken and the minimum is returned.
  for (unsigned o: observations){
    aptk::Action * a = trans_prob_neg.actions()[o];

    // The observation currently considered has the "NEXT" fluent added to its preconditions
    // This means that it may be used only after another observation.
    a->prec_vec().push_back(next_index);

		// The heuristic value of the problem is found
		Fwd_Search_Problem neg_search_prob(&trans_prob_neg);
		float neg_cost(0);
    std::vector<aptk::Action_Idx> plan;
    do_heuristic(neg_search_prob, neg_cost, plan, observations);
    plan.clear();

    // The action cost of the previous observations is added to the cost
    neg_cost += obs_count;

    if (min > neg_cost){
      min = neg_cost;
    }

    // The "NEXT" fluent is removed as a precondition and an effect
    a->prec_vec().pop_back();
    a->add_vec().pop_back();

    // The initial state is progressed through the considered action
    aptk::State root( trans_prob_neg);
    root.set(trans_prob_neg.init() );

    aptk::State* next_root = root.progress_through(*a);
    STRIPS_Problem::set_init(trans_prob_neg, next_root->fluent_vec());

    // The cost is incremented to reflect the changing initial state
    // TODO: This will need to be changed to:
    obs_count += a->cost();
    //obs_count++;
  }

  // The initial state of the problem is reset
  STRIPS_Problem::set_init(trans_prob_neg,true_init);

  return min;
}

std::vector<double> plan_recognition_approx(const aptk::STRIPS_Problem& prob, std::vector<aptk::Fluent_Vec>& goal_set, std::vector<double> priors, std::vector<unsigned>& observations, aptk::Fluent_Vec& init, float beta = 1, unsigned approx_type = 1) {

	aptk::STRIPS_Problem trans_prob_pos;
	aptk::STRIPS_Problem trans_prob_neg;
  std::vector<float> goal_cost_change;
  float sum (0);
  clone_problem(prob, trans_prob_neg, observations, infty, init);
  translate_problem_approx_pos(prob, trans_prob_pos, observations, init);

  // For each goal candidate perform two searches:
  // One where observed actions must be used
  // One where observed actions must not be used
	for (unsigned i = 0; i < goal_set.size(); i++){

    //std::cout << "\nGoal No.: " << i << " / " << goal_set.size() << "\n";

		// Set goal to candidate goal and that observations have occured
		aptk::Fluent_Vec g = goal_set[i];
		aptk::Fluent_Vec pos_goal(g);
		trans_prob_pos.set_goal(trans_prob_pos, pos_goal);

		Fwd_Search_Problem pos_search_prob(&trans_prob_pos);
		float pos_cost(0);
    std::vector<aptk::Action_Idx> plan;

    // Perform search with observations
    do_heuristic(pos_search_prob, pos_cost, plan, observations);
    pos_cost += observations.size();

    //std::cout << "Relaxed Pos Plan: \n";
    //print_plan_to_cout(plan, pos_search_prob);
    plan.clear();

		// Set goal to candidate goal and that observations must not occur
		aptk::Fluent_Vec neg_goal(g);
		trans_prob_neg.set_goal(trans_prob_neg, neg_goal);
    float neg_cost(0);

		if (approx_type == 1){
      Fwd_Search_Problem neg_search_prob(&trans_prob_neg);

      // Perform search without observations
      do_heuristic(neg_search_prob, neg_cost, plan, observations);

      //std::cout << "Relaxed Neg Plan: \n";
      //print_plan_to_cout(plan, pos_search_prob);
      plan.clear();
    } else if (approx_type == 2) {
      neg_cost = approximation_wo_delete_relax_disallow_action(trans_prob_neg, observations);
    } else {
      neg_cost = approximation_wo_delete_relax_break_sequence(trans_prob_neg, observations);
    }


    // Calculate liklihood
		const float pOGin = -1.0f*beta*(neg_cost - pos_cost);
		const float pOGinexp = exp(pOGin);
		const float pOG = 1.0f/(1.0f + pOGinexp);
		const float pOGpG = pOG*priors[i];

    //std::cout << i << ":\tPrior: " << priors[i] << std::endl;
    //std::cout <<  "\tPos - Neg: " << pos_cost << " - " << neg_cost << std::endl;
    //std::cout <<  " \tpOGin: " << pOGin << std::endl;
    //std::cout <<  " \tpOGinexp: " << pOGinexp << std::endl;
    //std::cout <<  " \tpOG: " << pOG << std::endl;
    //std::cout <<  " \tpOGpG: " << pOGpG << std::endl;

		sum += pOGpG;

		goal_cost_change.push_back(pOGpG);
	}

	return normalize_vector(goal_cost_change);
}

std::vector<double> simulate_plan_for_recog(std::vector<aptk::Action_Idx>& plan, aptk::STRIPS_Problem& prob, std::vector<aptk::Fluent_Vec>& goal_set, std::vector<double>& priors, float beta){

  std::vector<unsigned int> observations;
  std::vector<double> probability;

  int index = 0;
  std::set<unsigned> true_goal(prob.goal().begin(), prob.goal().end());
  for (unsigned int i = 0; i < goal_set.size(); i++){
    std::set<unsigned> cand_goal(goal_set[i].begin(),goal_set[i].end());
    if (true_goal == cand_goal)
      index = i;
  }


  for (unsigned int i = 0; i < plan.size(); i++){
    observations.push_back(plan[i]);
    double h_val;
    /*
     *std::cout << "Observations: " << std::endl;
     *for (unsigned int i = 0; i < observations.size(); i++){
     *  std::cout << observations[i] << ": " << prob.actions()[observations[i]]->signature() << std::endl;
     *}
     */
    std::vector<double> belief_probs_at_i = plan_recognition(prob, goal_set, priors, observations, prob.init(), beta, true);

    // Count the number of goals with greater posterior than the goal
    float rank = 1;
    for (unsigned int i = 0; i < belief_probs_at_i.size(); i++){
      if (index != i)
        if (belief_probs_at_i[i] >= belief_probs_at_i[index])
          rank++;
    }

    //h_val = (1 - belief_probs_at_i[index]);
    h_val = rank + (1 - belief_probs_at_i[index]);

    probability.push_back(h_val);
  }

  return probability;
}
