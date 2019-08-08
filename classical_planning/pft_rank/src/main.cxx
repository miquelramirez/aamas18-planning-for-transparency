#include <iostream>
#include <fstream>
#include <map>
#include <ctype.h>

#include <strips_prob.hxx>
#include <ff_to_aptk.hxx>
#include <fluent.hxx>
#include <action.hxx>
#include <cond_eff.hxx>
#include <strips_state.hxx>
#include <fwd_search_prob.hxx>
#include <rp_heuristic.hxx>
#include "h_rp.hxx"

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <string>

#include <aptk/open_list.hxx>
#include <aptk/string_conversions.hxx>
#include <aptk/at_bfs_recog.hxx>

namespace po = boost::program_options;

using	aptk::STRIPS_Problem;
using	aptk::Action;
using	aptk::agnostic::Fwd_Search_Problem;

using aptk::agnostic::Plan_Recognition_Heuristic;
using aptk::agnostic::H1_Heuristic;
using	aptk::agnostic::H_Max_Evaluation_Function;

using	aptk::agnostic::H_Add_Evaluation_Function;
using	aptk::agnostic::Relaxed_Plan_Heuristic;

using aptk::search::Open_List;
using	aptk::search::rbfs::AT_BFS_SQ_SH;
using	aptk::search::Node_Comparer;

// Plan Rec heuristic, Not baysian update
typedef Plan_Recognition_Heuristic<Fwd_Search_Problem, false, 0>	H_PR;
typedef Plan_Recognition_Heuristic<Fwd_Search_Problem, false, 1>	H_A1_PR;
typedef Plan_Recognition_Heuristic<Fwd_Search_Problem, false, 2>	H_A2_PR;
typedef Plan_Recognition_Heuristic<Fwd_Search_Problem, false, 3>	H_A3_PR;

// Plan Rec heuristic, Baysian Update
typedef Plan_Recognition_Heuristic<Fwd_Search_Problem, true, 0>	H_BU_PR;
typedef Plan_Recognition_Heuristic<Fwd_Search_Problem, true, 1>	H_A1_BU_PR;
typedef Plan_Recognition_Heuristic<Fwd_Search_Problem, true, 2>	H_A2_BU_PR;
typedef Plan_Recognition_Heuristic<Fwd_Search_Problem, true, 3>	H_A3_BU_PR;

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

typedef   AT_GBFS_2H< Fwd_Search_Problem, H_Dyn_Novel_Fwd, H_PR, BFS_Open_List_gbfs > BWFS_Dynamic_Novel_H_PR_Fwd;
typedef   AT_GBFS_2H< Fwd_Search_Problem, H_Dyn_Novel_Fwd, H_BU_PR, BFS_Open_List_gbfs > BWFS_Dynamic_Novel_H_BU_PR_Fwd;
typedef   AT_GBFS_2H< Fwd_Search_Problem, H_Dyn_Novel_Fwd, H_A1_PR, BFS_Open_List_gbfs > BWFS_Dynamic_Novel_H_A1_PR_Fwd;
typedef   AT_GBFS_2H< Fwd_Search_Problem, H_Dyn_Novel_Fwd, H_A2_PR, BFS_Open_List_gbfs > BWFS_Dynamic_Novel_H_A2_PR_Fwd;
typedef   AT_GBFS_2H< Fwd_Search_Problem, H_Dyn_Novel_Fwd, H_A1_BU_PR, BFS_Open_List_gbfs > BWFS_Dynamic_Novel_H_BU_A1_PR_Fwd;
typedef   AT_GBFS_2H< Fwd_Search_Problem, H_Dyn_Novel_Fwd, H_A2_BU_PR, BFS_Open_List_gbfs > BWFS_Dynamic_Novel_H_BU_A2_PR_Fwd;


// ----------------------------------------------------------------------

typedef	aptk::search::rbfs::Node< aptk::State >	Search_Node;
typedef	Node_Comparer< Search_Node >	Tie_Breaking_Algorithm;
typedef	Open_List< Tie_Breaking_Algorithm, Search_Node >	BFS_Open_List;

// A*
typedef	AT_BFS_SQ_SH< Fwd_Search_Problem, H_PR, BFS_Open_List >		BFS_H_PR_Fwd;
typedef	AT_BFS_SQ_SH< Fwd_Search_Problem, H_A1_PR, BFS_Open_List >		BFS_H_A1_PR_Fwd;
typedef	AT_BFS_SQ_SH< Fwd_Search_Problem, H_A2_PR, BFS_Open_List >		BFS_H_A2_PR_Fwd;
typedef	AT_BFS_SQ_SH< Fwd_Search_Problem, H_A3_PR, BFS_Open_List >		BFS_H_A3_PR_Fwd;
typedef	AT_BFS_SQ_SH< Fwd_Search_Problem, H_BU_PR, BFS_Open_List >		BFS_H_BU_PR_Fwd;
typedef	AT_BFS_SQ_SH< Fwd_Search_Problem, H_A1_BU_PR, BFS_Open_List >		BFS_H_A1_BU_PR_Fwd;
typedef	AT_BFS_SQ_SH< Fwd_Search_Problem, H_A2_BU_PR, BFS_Open_List >		BFS_H_A2_BU_PR_Fwd;
typedef	AT_BFS_SQ_SH< Fwd_Search_Problem, H_A3_BU_PR, BFS_Open_List >		BFS_H_A3_BU_PR_Fwd;

typedef	H1_Heuristic<Fwd_Search_Problem, H_Add_Evaluation_Function>	H_Add_Fwd;
typedef	Relaxed_Plan_Heuristic< Fwd_Search_Problem, H_Add_Fwd >		H_Add_Rp_Fwd;

typedef AT_BFS_SQ_SH<Fwd_Search_Problem,H_Add_Rp_Fwd, BFS_Open_List> BFS_H_RP_Fwd;

// Search functions
void do_search(  Fwd_Search_Problem& search_prob,  std::vector< aptk::Action_Idx >& plan, float& cost, std::vector<double>& prob_vector, unsigned approx, bool condin , bool greedy ) {

	cost = infty;
  bool delayed = false;

/*
 *  typedef Plan_Recognition_Heuristic<Fwd_Search_Problem, condin, approx>	H_PR;
 *  typedef	AT_BFS_SQ_SH< Fwd_Search_Problem, H_PR, BFS_Open_List >		BFS_H_PR_Fwd;
 *
 *  BFS_H_PR_Fwd engine( search_prob);
 *  engine.set_greedy( greedy );
 *  engine.set_delay_eval( delayed);
 *  engine.start();
 *  engine.find_solution(cost, plan, prob_vector);
 */

    /*
     *BFS_H_RP_Fwd engine( search_prob );
     *engine.set_greedy( greedy );
     *engine.set_delay_eval( delayed );
     *engine.start();
     *engine.find_solution( cost, plan );
     */

  unsigned h_init = 0;

  if (condin){
    if (approx == 1){
      BFS_H_A1_BU_PR_Fwd engine( search_prob );
      engine.set_greedy( greedy );
      engine.set_delay_eval( delayed);
      engine.start();
      engine.find_solution(cost,plan,prob_vector);
      //BWFS_Dynamic_Novel_H_BU_A1_PR_Fwd engine( search_prob );
      //engine.set_arity(1,h_init);
      //engine.set_ignore_novelty(1);
      //engine.start();
      //engine.find_solution(cost, plan);
    } else if (approx == 2){
      BFS_H_A2_BU_PR_Fwd engine( search_prob );
      engine.set_greedy( greedy );
      engine.set_delay_eval( delayed);
      engine.start();
      engine.find_solution(cost,plan,prob_vector);
      //BWFS_Dynamic_Novel_H_BU_A2_PR_Fwd engine( search_prob );
      //engine.set_arity(1,h_init);
      //engine.set_ignore_novelty(1);
      //engine.start();
      //engine.find_solution(cost, plan);
    } else if (approx == 3){
      BFS_H_A3_BU_PR_Fwd engine( search_prob );
      engine.set_greedy( greedy );
      engine.set_delay_eval( delayed);
      engine.start();
      engine.find_solution(cost,plan,prob_vector);
      //BWFS_Dynamic_Novel_H_BU_A2_PR_Fwd engine( search_prob );
      //engine.set_arity(1,h_init);
      //engine.set_ignore_novelty(1);
      //engine.start();
      //engine.find_solution(cost, plan);
    }else{
      BFS_H_BU_PR_Fwd engine( search_prob );
      engine.set_greedy( greedy );
      engine.set_delay_eval( delayed);
      engine.start();
      engine.find_solution(cost,plan,prob_vector);
      //BWFS_Dynamic_Novel_H_BU_PR_Fwd engine ( search_prob );
      //engine.set_arity(1,h_init);
      //engine.set_ignore_novelty(1);
      //engine.start();
      //engine.find_solution(cost, plan);
    }
  }else{
    if (approx == 1){
      BFS_H_A1_PR_Fwd engine( search_prob);
      engine.set_greedy( greedy );
      engine.set_delay_eval( delayed);
      engine.start();
      engine.find_solution(cost,plan,prob_vector);
      //BWFS_Dynamic_Novel_H_A1_PR_Fwd engine (search_prob);
      //engine.set_arity(1,h_init);
      //engine.set_ignore_novelty(1);
      //engine.start();
      //engine.find_solution(cost, plan);
    } else if (approx == 2){
      BFS_H_A2_PR_Fwd engine( search_prob);
      engine.set_greedy( greedy );
      engine.set_delay_eval( delayed);
      engine.start();
      engine.find_solution(cost,plan,prob_vector);
      //BWFS_Dynamic_Novel_H_A2_PR_Fwd engine (search_prob);
      //engine.set_arity(1,h_init);
      //engine.set_ignore_novelty(1);
      //engine.start();
      //engine.find_solution(cost, plan);
    } else if (approx == 3){
      BFS_H_A3_PR_Fwd engine( search_prob);
      engine.set_greedy( greedy );
      engine.set_delay_eval( delayed);
      engine.start();
      engine.find_solution(cost,plan,prob_vector);
      //BWFS_Dynamic_Novel_H_A2_PR_Fwd engine (search_prob);
      //engine.set_arity(1,h_init);
      //engine.set_ignore_novelty(1);
      //engine.start();
      //engine.find_solution(cost, plan);
    }else{
      BFS_H_PR_Fwd engine( search_prob);
      engine.set_greedy( greedy );
      engine.set_delay_eval( delayed);
      engine.start();
      engine.find_solution(cost,plan,prob_vector);
      //BWFS_Dynamic_Novel_H_PR_Fwd engine ( search_prob );
      //engine.set_arity(1,h_init);
      //engine.set_ignore_novelty(1);
      //engine.start();
      //engine.find_solution(cost, plan);
    }

  }
}

void print_action_plan_to_cout(std::vector< int >& plan, Fwd_Search_Problem& search_prob){
  for ( unsigned k = 0; k < plan.size(); k++ ) {
    const aptk::Action& a = *(search_prob.task().actions()[ plan[k] ]);
    //std::cout << a.index() << ": " << a.signature() << "\t";
    std::cout << a.signature() << "\t";
  }
  std::cout << std::endl;
}

void process_command_line_options( int ac, char** av, po::variables_map& vars ) {
	po::options_description desc( "Options:" );

	desc.add_options()
		( "help", "Show help message" )
		( "domain", po::value<std::string>(), "Input PDDL domain description" )
		( "problem", po::value<std::string>(), "Input PDDL problem description" )
		( "goalset", po::value<std::string>(), "Input PDDL goal-set description" )
		( "approx", po::value<unsigned>()->default_value(0), "Use approximate plan recognition" )
		( "condin", po::value<bool>()->default_value(false), "Use assumption of conditional independence of observations" )
		( "greedy", po::value<bool>()->default_value(false), "Use greedy best first search" )
		( "beta", po::value<int>()->default_value(1), "Beta" )
	;

	try {
		po::store( po::parse_command_line( ac, av, desc ), vars );
		po::notify( vars );
	}
	catch ( std::exception& e ) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(1);
	}
	catch ( ... ) {
		std::cerr << "Exception of unknown type!" << std::endl;
		std::exit(1);
	}

	if ( vars.count("help") ) {
		std::cout << desc << std::endl;
		std::exit(0);
	}

}

// Process the goal candidate set file
std::vector<unsigned int> process_goal_set_line(std::string s, aptk::STRIPS_Problem& prob){
  std::string delimiter = ",";
	size_t pos = 0;
	std::string token;
  std::vector<unsigned int> goal_vector;
  aptk::Fluent_Ptr_Vec fs = prob.fluents();

	while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);

      //std::cout << token;
      //std::transform(token.begin(), token.end(), token.begin(), toupper);
      //std::cout << token << std::endl;
			for (unsigned int i = 0 ; i < fs.size(); i++){
        //std::cout << "fs" << i << ": " << fs[i]->signature() << " token = " << token << std::endl;
        if (fs[i]->signature() == token){
          goal_vector.push_back(fs[i]->index());
        //std::cout << fs[i]->signature() << ", ";
        }
      }

			s.erase(0, pos + delimiter.length());
	}

  boost::to_upper(s);
  for (unsigned int i = 0 ; i < fs.size(); i++){
    if (fs[i]->signature() == s){
      //std::cout << fs[i]->signature() << ", ";
      goal_vector.push_back(fs[i]->index());
    }
  }

  //std::cout << std::endl;

  return goal_vector;
}

// Parses each line of the goal candidate set file
std::vector<aptk::Fluent_Vec> goal_set_parsing(std::string goal_set_file_name, aptk::STRIPS_Problem& prob){
  std::string line;
  std::ifstream goal_set_file(goal_set_file_name);
	std::vector<aptk::Fluent_Vec> goal_set;
  //unsigned int ln_n = 0;

  //std::cout << "Goal-Set: " << std::endl;

  if(goal_set_file.is_open())
    while (std::getline(goal_set_file,line)){
      //std::cout << ln_n++ << ": " << std::endl;
      std::vector<unsigned int> goal = process_goal_set_line(line, prob);
      goal_set.push_back(goal);
    }
  else
    std::cout << "Unable to open Goal-Set file!" << std::endl;

  //std::cout << std::endl;

  return goal_set;
}

void remove_hidden_actions(std::vector<aptk::Action_Idx> plan, Fwd_Search_Problem& search_prob, std::vector<aptk::Action_Idx>& plan_woh){
  std::string hidden = "(HIDDEN";
  for ( unsigned k = 0; k < plan.size(); k++ ) {
    const aptk::Action& a = *(search_prob.task().actions()[ plan[k] ]);
    std::string name = a.signature();
    boost::to_upper(name);

    auto res = std::mismatch(hidden.begin(), hidden.end(), name.begin());
    if (res.first != hidden.end()){
      plan_woh.push_back(plan[k]);
    }

  }
}

int main( int argc, char** argv){

	po::variables_map vm;
	process_command_line_options( argc, argv, vm );

	if ( !vm.count( "domain" ) ) {
		std::cerr << "No PDDL domain was specified!" << std::endl;
		std::exit(1);
	}

	if ( !vm.count( "problem" ) ) {
		std::cerr << "No PDDL problem was specified!" << std::endl;
		std::exit(1);
	}

	if ( !vm.count( "goalset" ) ) {
		std::cerr << "No Goal Set file was specified!" << std::endl;
		std::exit(1);
	}

  std::string goal_set_name = vm["goalset"].as<std::string>();
  int beta = vm["beta"].as<int>();
  unsigned approx = vm["approx"].as<unsigned>();
  bool condin= vm["condin"].as<bool>();
  bool greedy= vm["greedy"].as<bool>();

	aptk::STRIPS_Problem	prob;
	aptk::FF_Parser::get_problem_description( vm["domain"].as<std::string>(), vm["problem"].as<std::string>(), prob );
	std::vector<aptk::Fluent_Vec> goal_set = goal_set_parsing(goal_set_name, prob);

  // Print out goal set.
  /*
   *for (unsigned i = 0; i < goal_set.size(); i++){
   *  std::cout << std::endl << i << ":  ";
   *  for (unsigned j = 0; j < goal_set[i].size(); j++){
   *    std::cout << goal_set[i][j] << ", ";
   *  }
   *  std::cout << std::endl;
   *}
   */

  prob.set_goal_set(goal_set);

  std::vector<double> priors;
  // Sets the priors to be uniform (//TODO put these in the goal candidate set file)
  for (unsigned int i = 0; i < goal_set.size(); i++){
    priors.push_back(0.5);
  }
  priors = normalize_vector(priors);
  prob.set_priors(priors);

  prob.set_beta(beta);

  float cost = 0;
  std::vector<double> prob_vector;
  std::vector< aptk::Action_Idx > plan_wh;

  // Do search using h_rp heuristic
  Fwd_Search_Problem search_prob(&prob);
  do_search(search_prob, plan_wh, cost, prob_vector, approx, condin, greedy);
  std::cout << "Cost: " << cost << std::endl;
  std::cout << "Action Cost: " << plan_wh.size() << std::endl;

  std::vector<aptk::Action_Idx> plan;
  remove_hidden_actions(plan_wh, search_prob, plan);
  //print_action_plan_to_cout(plan,search_prob);

  /*
  *Find the index of the goal of the search model in the set of goals
  */
  unsigned int goal_index;
  std::vector<unsigned> true_goal_v = prob.goal();
  std::set<unsigned> true_goal(true_goal_v.begin(), true_goal_v.end());
  for (unsigned int i = 0; i < prob.goal_set(prob).size(); i++){
    std::vector<unsigned> cand_goal_v = prob.goal_set(prob)[i];
    std::set<unsigned> cand_goal (cand_goal_v.begin(), cand_goal_v.end());
    if (cand_goal == true_goal)
      goal_index = i;

  }

  //std::cout << std::endl;
  //std::cout << prob.domain_name() << "\n";
  //std::cout << prob.problem_name() << "\n";
  //print_action_plan_to_cout(plan, search_prob);
  //std::cout << goal_index << "\n";

  //std::vector<unsigned> ordered_half_plan;
  //std::vector<unsigned> unordered_half_plan;

  //for (unsigned i = 0; i < plan.size()*0.65; i++)
    //ordered_half_plan.push_back(plan[i]);

  //std::vector<unsigned> numbers;
  //std::vector<unsigned> numbesr75;
  //for (unsigned i = 0; i < plan.size(); i++){
    //numbers.push_back(i);
  //}
  //std::random_shuffle(numbers.begin(), numbers.end());
  //for (unsigned i = 0; i < numbers.size()*0.65; i++){
    //numbesr75.push_back(numbers[i]);
  //}

  //for (unsigned i = 0; i < plan.size(); i++)
    //if (std::find(numbesr75.begin(), numbesr75.end(), i) != numbesr75.end())
      //unordered_half_plan.push_back(plan[i]);

  //std::vector<unsigned> half_unordered_half_plan;
  //std::vector<unsigned> half_numbers;
  //std::vector<unsigned> half_numbers_frac;
  //for (unsigned i = 0; i < plan.size()/2; i++){
    //half_numbers.push_back(i);
  //}

  //std::random_shuffle(half_numbers.begin(), half_numbers.end());
  //for (unsigned i = 0; i < half_numbers.size()*0.65; i++){
    //half_numbers_frac.push_back(half_numbers[i]);
  //}

  //for (unsigned i = 0; i < plan.size(); i++)
    //if (std::find(half_numbers_frac.begin(), half_numbers_frac.end(), i) != half_numbers_frac.end())
      //half_unordered_half_plan.push_back(plan[i]);

  //std::vector<double> optimal_ohp_p =  plan_recognition(prob, goal_set, priors, ordered_half_plan, prob.init(), beta, true);
  //std::vector<double> optimal_uohp_p =  plan_recognition(prob, goal_set, priors, unordered_half_plan, prob.init(), beta, true);

  //std::vector<double> sat_ohp_p =  plan_recognition(prob, goal_set, priors, ordered_half_plan, prob.init(), beta, false);
  //std::vector<double> sat_uohp_p =  plan_recognition(prob, goal_set, priors, unordered_half_plan, prob.init(), beta, false);

  //std::vector<double> optimal_hohp_p = plan_recognition(prob, goal_set, priors, half_unordered_half_plan, prob.init(), beta, true);
  //std::vector<double> sat_hohp_p = plan_recognition(prob, goal_set, priors, half_unordered_half_plan, prob.init(), beta, false);

  //for (unsigned i = 0; i < optimal_ohp_p.size(); i++)
    //std::cout << optimal_ohp_p[i] << "\t";
  //std::cout << std::endl;

  //std::cout << "Optimal Randomized: ";
  //for (unsigned i = 0; i < unordered_half_plan.size(); i++)
    //std::cout << unordered_half_plan[i] << "\t";
  //std::cout << std::endl;
  //for (unsigned i = 0; i < optimal_uohp_p.size(); i++)
    //std::cout << optimal_uohp_p[i] << "\t";
  //std::cout << std::endl;

  //for (unsigned i = 0; i < sat_ohp_p.size(); i++)
    //std::cout << sat_ohp_p[i] << "\t";
  //std::cout << std::endl;

  //for (unsigned i = 0; i < sat_uohp_p.size(); i++)
    //std::cout << sat_uohp_p[i] << "\t";
  //std::cout << std::endl;

  //for (unsigned i = 0; i < optimal_hohp_p.size(); i++)
    //std::cout << optimal_hohp_p[i] << "\t";
  //std::cout << std::endl;

  //for (unsigned i = 0; i < sat_hohp_p.size(); i++)
    //std::cout << sat_hohp_p[i] << "\t";
  //std::cout << std::endl;

  std::cout << std::endl << std::endl << "Plan Finished" << std::endl;
  print_action_plan_to_cout(plan, search_prob);
  std::cout << std::endl;
  std::cout << "Cost to Recognizability:" << std::endl;
  print_vector(prob_vector);

  double sum_of_elems = 0.0f;

  for (double n : prob_vector)
    sum_of_elems += n;
  std::cout << "Total Cost: " << sum_of_elems << std::endl;

  // Before using this ensure that the cost function is the same in both h_rp.hxx and the simulate_plan_for_recog function in planrec.cxx.
  //std::vector<double> exact_probabilities = simulate_plan_for_recog(plan_wh, prob, goal_set, priors, beta);

  //std::cout << std::endl << "Exact Cost to Recognizability:" << std::endl;
  //print_vector(exact_probabilities);

  //sum_of_elems = 0.0f;

  //for (double n : exact_probabilities)
    //sum_of_elems += n;
  //std::cout << "Total Cost: " << sum_of_elems << std::endl;

}
