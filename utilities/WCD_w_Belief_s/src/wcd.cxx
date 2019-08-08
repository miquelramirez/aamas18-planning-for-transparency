#include <iostream>
#include <fstream>
#include <map>
#include "wcd.hxx"

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
#include <h_2.hxx>

#include <aptk/open_list.hxx>
#include <aptk/string_conversions.hxx>
#include <aptk/at_bfs.hxx>

#include <fstream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

using	aptk::STRIPS_Problem;

using	aptk::agnostic::Fwd_Search_Problem;
using	aptk::Action;

using 	aptk::agnostic::H1_Heuristic;
using 	aptk::agnostic::H2_Heuristic;
using	aptk::agnostic::H_Add_Evaluation_Function;
using	aptk::agnostic::H_Max_Evaluation_Function;

using 	aptk::search::Open_List;
using	aptk::search::bfs::AT_BFS_SQ_SH;
using	aptk::search::Node_Comparer;

typedef	aptk::search::bfs::Node< aptk::State >	Search_Node;
typedef	Node_Comparer< Search_Node >	Tie_Breaking_Algorithm;
typedef	Open_List< Tie_Breaking_Algorithm, Search_Node >	BFS_Open_List;

typedef	H1_Heuristic<Fwd_Search_Problem, H_Max_Evaluation_Function>	H_Max_Fwd;
typedef	H2_Heuristic<Fwd_Search_Problem>	H2_FWD;
typedef	AT_BFS_SQ_SH< Fwd_Search_Problem, H_Max_Fwd, BFS_Open_List >		BFS_H_Max_Fwd;

using	aptk::agnostic::Relaxed_Plan_Heuristic;

typedef	H1_Heuristic<Fwd_Search_Problem, H_Add_Evaluation_Function>	H_Add_Fwd;
typedef	Relaxed_Plan_Heuristic< Fwd_Search_Problem, H_Add_Fwd >		H_Add_Rp_Fwd;

typedef AT_BFS_SQ_SH<Fwd_Search_Problem, H_Add_Rp_Fwd, BFS_Open_List> BFS_H_RP_Fwd;

void print_wcd_plan_to_cout(std::vector< aptk::Action_Idx >& plan, Fwd_Search_Problem& search_prob);

void do_wcd_search(  Fwd_Search_Problem& search_prob,  std::vector< aptk::Action_Idx >& plan, float& cost, std::string plan_filename,  bool anytime, bool delayed, bool greedy  ) {
    cost = infty;
    BFS_H_Max_Fwd engine( search_prob );
    engine.start();
    engine.find_solution( cost, plan );

    //print_wcd_plan_to_cout(plan, search_prob);

    //H_Add_Rp_Fwd h_ff(search_prob);
    //Search_Node* root = new Search_Node( search_prob.init(), 0.0f,-1, NULL );
    //std::vector<aptk::Action_Idx> pref_ops;
    //h_ff.eval(*(root->state()), cost, pref_ops, plan);

}

void translate_problem_latest_split(aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& trans_prob, std::map<std::string, unsigned int>& idx_to_trans_idx, float epsilon){

	aptk::Fluent_Vec init_trans;

	unsigned int index_0 = 0;
	unsigned int index_1 = 1;

	aptk::Fluent_Ptr_Vec f = prob.fluents();
	aptk::Fluent_Vec init = prob.init();
	aptk::Action_Ptr_Vec as = prob.actions();

	trans_prob.set_domain_name(prob.domain_name());
	trans_prob.set_problem_name(prob.problem_name());

	// Transformed fluent set vector contains two fluents for every one in the original. One for each goal.
	// Also contains the split and done_0 fluents.
 	for (unsigned int i = 0; i < prob.num_fluents(); i++){

		trans_prob.add_fluent(trans_prob, (*f[i]).signature() + "_0");
		idx_to_trans_idx.insert(std::pair<std::string, unsigned int>(std::to_string((*f[i]).index()) + "_0",index_0));

		trans_prob.add_fluent(trans_prob, (*f[i]).signature() + "_1");
		idx_to_trans_idx.insert(std::pair<std::string, unsigned int>(std::to_string((*f[i]).index()) + "_1",index_1));

		index_0 += 2;
		index_1 += 2;
	}

	trans_prob.add_fluent(trans_prob, "split");
	idx_to_trans_idx.insert(std::pair<std::string, unsigned int>("split", index_0++));
	trans_prob.add_fluent(trans_prob, "not_split");
	idx_to_trans_idx.insert(std::pair<std::string, unsigned int>("not_split", index_0++));
	trans_prob.add_fluent(trans_prob, "done_0");
	idx_to_trans_idx.insert(std::pair<std::string, unsigned int>("done_0", index_0++));
	trans_prob.add_fluent(trans_prob, "not_done_0");
	idx_to_trans_idx.insert(std::pair<std::string, unsigned int>("not_done_0", index_0++));

	for (unsigned int i = 0; i < init.size(); i++){
	// Transformed initial state vector contains two fluents for every one in the original. One for each goal.
		init_trans.push_back(idx_to_trans_idx[std::to_string(init[i]) + "_0"]);
		init_trans.push_back(idx_to_trans_idx[std::to_string(init[i]) + "_1"]);
	}
	init_trans.push_back(idx_to_trans_idx["not_split"]);
	init_trans.push_back(idx_to_trans_idx["not_done_0"]);

	trans_prob.set_init(trans_prob, init_trans);

	// Transformed action set vector contains three actions for every one in the original.
	// One for each goal and one for both.
	// Also contains the DoSplit and Done_0 actions.

	aptk::Fluent_Vec dosplit_pre;
	aptk::Fluent_Vec dosplit_add;
	aptk::Fluent_Vec dosplit_del;
	aptk::Fluent_Vec done_0_pre;
	aptk::Fluent_Vec done_0_add;
	aptk::Fluent_Vec done_0_del;

	// Conditional effects to be added later
	aptk::Conditional_Effect_Vec cond_eff;

	for (unsigned int i = 0; i < prob.num_actions(); i++){

		aptk::Action a = *as[i];
		aptk::Fluent_Vec pre_0;
		aptk::Fluent_Vec pre_1;
		aptk::Fluent_Vec pre_01;
		aptk::Fluent_Vec add_0;
		aptk::Fluent_Vec add_1;
		aptk::Fluent_Vec add_01;
		aptk::Fluent_Vec del_0;
		aptk::Fluent_Vec del_1;
		aptk::Fluent_Vec del_01;

	// Adds transformed fluents to the preconditions vector
		for (unsigned int i = 0; i < a.prec_vec().size(); i++){
			pre_0.push_back(idx_to_trans_idx[std::to_string(a.prec_vec()[i]) + "_0"]);
			pre_1.push_back(idx_to_trans_idx[std::to_string(a.prec_vec()[i]) + "_1"]);
			pre_01.push_back(idx_to_trans_idx[std::to_string(a.prec_vec()[i]) + "_0"]);
			pre_01.push_back(idx_to_trans_idx[std::to_string(a.prec_vec()[i]) + "_1"]);
		}

		pre_01.push_back(idx_to_trans_idx["not_split"]);
		pre_0.push_back(idx_to_trans_idx["split"]);
		pre_0.push_back(idx_to_trans_idx["not_done_0"]);
		pre_1.push_back(idx_to_trans_idx["split"]);
		pre_1.push_back(idx_to_trans_idx["done_0"]);

	// Adds transformed fluents to the add vector
		for (unsigned int i = 0; i < a.add_vec().size(); i++){
			add_0.push_back(idx_to_trans_idx[std::to_string(a.add_vec()[i]) + "_0"]);
			add_1.push_back(idx_to_trans_idx[std::to_string(a.add_vec()[i]) + "_1"]);
			add_01.push_back(idx_to_trans_idx[std::to_string(a.add_vec()[i]) + "_0"]);
			add_01.push_back(idx_to_trans_idx[std::to_string(a.add_vec()[i]) + "_1"]);
		}



	// Adds transformed fluents to the del vector
		for (unsigned int i = 0; i < a.del_vec().size(); i++){
			del_0.push_back(idx_to_trans_idx[std::to_string(a.del_vec()[i]) + "_0"]);
			del_1.push_back(idx_to_trans_idx[std::to_string(a.del_vec()[i]) + "_1"]);
			del_01.push_back(idx_to_trans_idx[std::to_string(a.del_vec()[i]) + "_0"]);
			del_01.push_back(idx_to_trans_idx[std::to_string(a.del_vec()[i]) + "_1"]);
		}

		trans_prob.add_action(trans_prob, a.signature() + "_0", pre_0, add_0, del_0, cond_eff, a.cost());
		trans_prob.add_action(trans_prob, a.signature() + "_1", pre_1, add_1, del_1, cond_eff, a.cost());
		trans_prob.add_action(trans_prob, a.signature() + "_01", pre_01, add_01, del_01, cond_eff, 2*a.cost() - epsilon);

	}

	done_0_pre.push_back(idx_to_trans_idx["split"]);
	dosplit_add.push_back(idx_to_trans_idx["split"]);
	done_0_add.push_back(idx_to_trans_idx["done_0"]);
	dosplit_del.push_back(idx_to_trans_idx["not_split"]);
	done_0_del.push_back(idx_to_trans_idx["not_done_0"]);

	trans_prob.add_action(trans_prob, "DoSplit", dosplit_pre, dosplit_add, dosplit_del, cond_eff, 0);
	trans_prob.add_action(trans_prob, "Done_0", done_0_pre, done_0_add, done_0_del, cond_eff, 0);

	trans_prob.make_action_tables();

}

void translate_goals(aptk::Fluent_Vec& g0, aptk::Fluent_Vec& g1, std::map<std::string, unsigned int>& idx_to_trans_idx, aptk::Fluent_Vec& trans_goal){

	// Adds transformed goals
	for (unsigned int i = 0; i < g0.size(); i++){
		trans_goal.push_back(idx_to_trans_idx[std::to_string(g0[i]) + "_0"]);
	}

	for (unsigned int i = 0; i < g1.size(); i++){
		trans_goal.push_back(idx_to_trans_idx[std::to_string(g1[i]) + "_1"]);
	}
}

void fluent_combinations(unsigned int offset, unsigned int arity, aptk::Fluent_Ptr_Vec& f, aptk::Fluent_Vec& curr_comb, std::vector<aptk::Fluent_Vec>& goal_set, H2_FWD& h2){
	if (arity == 0) {
		if (h2.eval(curr_comb) != infty)
			goal_set.push_back(curr_comb);
		return;
	}
	for (unsigned int i = offset; i <= f.size() - arity; ++i) {
		curr_comb.push_back((*f[i]).index());
		fluent_combinations(i + 1, arity - 1, f, curr_comb, goal_set, h2);
		curr_comb.pop_back();
	}
}

void print_goal_set(std::vector<aptk::Fluent_Vec>& goal_set, aptk::STRIPS_Problem& prob){
	for (unsigned int i = 0; i < goal_set.size(); i++){
		for (unsigned int j = 0; j < goal_set[i].size(); j++){
			std::cout << (*prob.fluents()[goal_set[i][j]]).signature() << " ";
		}
		std::cout << std::endl;
	}
}

void print_wcd_plan_to_cout(std::vector< aptk::Action_Idx >& plan, Fwd_Search_Problem& search_prob){
	for ( unsigned k = 0; k < plan.size(); k++ ) {
		const aptk::Action& a = *(search_prob.task().actions()[ plan[k] ]);
		std::cout  << a.signature() << ",";
	}
	std::cout  << std::endl;
}

void generate_goal_set(aptk::STRIPS_Problem& prob, int goal_arity, std::vector<aptk::Fluent_Vec>& goal_set){
	aptk::Fluent_Vec empty_temp;
	Fwd_Search_Problem fw(&prob);
	H2_FWD h2(fw);
	h2.compute_edeletes(prob);

	for (unsigned int i = goal_arity; i > 0; i--){
		fluent_combinations(0, i, prob.fluents(), empty_temp, goal_set, h2);
	}
}

int count_plan_until_split(std::vector< aptk::Action_Idx>& plan, Fwd_Search_Problem& search_prob){
	int count = 0;
	for ( unsigned int k = 0; k < plan.size(); k++ ) {
		const aptk::Action& a = *(search_prob.task().actions()[ plan[k] ]);
		if (a.signature() == "DoSplit")
			return count;
		else
			count++;
	}
	return count;
}

float wcd(aptk::STRIPS_Problem& prob, std::vector<aptk::Fluent_Vec>& goal_set, float epsilon){

	// This function implements the latest_split method for determing the WCD of a problem.
	// Keren, S., Gal, A., and Karpas, E.: ‘Goal recognition design’, International Conference on Automated Planning and Scheduling (ICAPS), 2014

	aptk::STRIPS_Problem trans_prob;
	std::map<std::string, unsigned int> idx_to_trans_idx;
	aptk::Fluent_Vec trans_goal;

  Fwd_Search_Problem	search_prob( &prob );
  float opt_cost = infty;
  std::vector< aptk::Action_Idx > plan;
  BFS_H_Max_Fwd engine( search_prob );
  engine.start();
  engine.find_solution( opt_cost, plan );


	translate_problem_latest_split(prob, trans_prob, idx_to_trans_idx, epsilon);

	unsigned int max = 0;

	for (unsigned int i = 0; i < goal_set.size(); i++){
		unsigned int wcd_g_val = wcd_g(trans_prob, idx_to_trans_idx, goal_set[i], goal_set, epsilon);
		max = (wcd_g_val > max) ? wcd_g_val : max;

		// So two goals are not compared twice
		goal_set.erase (goal_set.begin()+i);
	}

	return (float)( max + 1 ) / (float)opt_cost;
}

unsigned int wcd_g(aptk::STRIPS_Problem& trans_prob, std::map<std::string, unsigned int>& idx_to_trans_idx, aptk::Fluent_Vec& r_goal, std::vector<aptk::Fluent_Vec>& goal_set, float epsilon){

	// This function implements the latest_split method for determing the WCD of a problem with reguards to a single goal.
	// Keren, S., Gal, A., and Karpas, E.: ‘Goal recognition design’, International Conference on Automated Planning and Scheduling (ICAPS), 2014

	aptk::Fluent_Vec trans_goal;
	unsigned int max = 0;

	for (unsigned int i = 0; i < goal_set.size(); i++){
			if (goal_set[i] != r_goal) {

  				aptk::Fluent_Vec trans_goal;
				std::vector< aptk::Action_Idx > plan;
				float cost = 0;

				translate_goals(goal_set[i], r_goal, idx_to_trans_idx, trans_goal);
				trans_prob.set_goal(trans_prob, trans_goal);

				Fwd_Search_Problem	search_prob( &trans_prob );
				do_wcd_search(search_prob, plan, cost, "plan.ipc" ,  0, 0, 0 );

        //for(unsigned int i = 0; i < search_prob.task().fluents().size(); i++){
          //std::cout << search_prob.task().fluents()[i]->signature() << std::endl;
        //}
        //for(unsigned int i = 0; i < search_prob.task().actions().size(); i++){
          //std::cout << search_prob.task().actions()[i]->signature() << std::endl;
        //}

				unsigned int until_split = count_plan_until_split(plan, search_prob);
				max = (until_split > max) ? until_split : max;
			}
	}

	return max;
}
