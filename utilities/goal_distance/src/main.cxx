
#include <iostream>
#include <fstream>
#include <map>
#include <ctype.h>
#include <climits>

#include <strips_prob.hxx>
#include <ff_to_aptk.hxx>
#include <fluent.hxx>
#include <action.hxx>
#include <cond_eff.hxx>
#include <strips_state.hxx>
#include <fwd_search_prob.hxx>
#include <rp_heuristic.hxx>
#include <aptk/open_list.hxx>

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <aptk/string_conversions.hxx>
#include <aptk/at_bfs.hxx>
#include <aptk/closed_list.hxx>

#include "utility.hxx"
#include "goal_set_parse.hxx"
#include "dalandmarks.hxx"
#include "gd.hxx"

namespace po = boost::program_options;

using	aptk::STRIPS_Problem;
using	aptk::Action;
using	aptk::agnostic::Fwd_Search_Problem;
using namespace gd;

void process_command_line_options( int ac, char** av, po::variables_map& vm) {
	po::options_description desc( "Additional Options" );

	desc.add_options()
		( "domain,d", po::value<std::string>(), "Input PDDL domain description" )
		( "problem,p", po::value<std::string>(), "Input PDDL problem description" )
		( "goalset,g", po::value<std::string>(), "Input PDDL goal-set description\n" )

		( "max-nodes,m", po::value<unsigned int>()->default_value(100), "The maximum amount of nodes in earch MCTS tree." )
		( "max-simulate-nodes,s", po::value<unsigned int>(), "The maximum amount of nodes to be simulated in the rollout policy.\n" )

		( "beta,b", po::value<float>()->default_value(1), "Value determining how rational an observer believes the agent to be." )
		( "theta,t", po::value<double>()->default_value(1.0f), "Threshold for goal filtering" )
		( "discount-factor,D", po::value<double>()->default_value(1.0f), "The amount by which transparent plans are penalised by their distance." )
		( "precision,P", po::value<int>()->default_value(2), "The precision to which the belief state is stored as within the state.\n" )


		( "landmark,L", po::bool_switch()->default_value(false), "Use landmark plan recognition." )
		( "filter,f", po::bool_switch()->default_value(false), "Use goal filtering with plan recognition." )

		( "optimal,o", po::bool_switch()->default_value(false), "Use optimal plan recognition." )
		( "nan,n", po::bool_switch()->default_value(false), "Approximate C(G, ~O) as c(G) in approximate plan recognition." )
		( "static-beta,S", po::bool_switch()->default_value(false), "Keep beta value static in search." )
    ( "diff-plan-rec,r", po::bool_switch()->default_value(false), "Use difference based plan recognition." )
    ( "closed-list-tree,l", po::bool_switch()->default_value(false), "Use a closed list in the tree policy of the MCTS.\n" )

		( "verbose,v", po::bool_switch()->default_value(false), "Verbose results." )
		( "pr-verbose,V", po::bool_switch()->default_value(false), "Verbose plan recognition results." )
		( "continue,c", po::bool_switch()->default_value(false), "Continue actions without pause." )
		( "one-action,O", po::bool_switch()->default_value(false), "Finish program after one action." )
		( "help,h", "Show help message" )
	;
  po::positional_options_description positionalOptions;
  positionalOptions.add("domain", 1);
  positionalOptions.add("problem", 1);
  positionalOptions.add("goalset", 1);

	try {
    po::store(po::command_line_parser(ac, av).options(desc).positional(positionalOptions).run(), vm);
		//po::store( po::parse_command_line( ac, av, desc ), vm);
		po::notify( vm );
	}
	catch ( std::exception& e ) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(1);
	}
	catch ( ... ) {
		std::cerr << "Exception of unknown type!" << std::endl;
		std::exit(1);
	}

	if ( vm.count("help") ) {
    std::cout << "Author: Aleck MacNally\n";
    std::cout << "Purpose: This program is an AI planner for classical planning domains.\n\
It differs from other AI planners in that it's objective is to find the plan which\n\
which is most obviously attempting to achieve it's goal to an observer.\n\n";
    std::cout << "Usage: PFT DOMAIN PROBLEM GOALSET [OPTIONS]" << std::endl << std::endl;
		std::cout << desc << std::endl;
		std::exit(0);
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
  float beta = vm["beta"].as<float>();
  bool optimal = vm["optimal"].as<bool>();
  double discount_factor = vm["discount-factor"].as<double>();
  unsigned int max_nodes = vm["max-nodes"].as<unsigned int>();
  bool diff_plan_rec = vm["diff-plan-rec"].as<bool>();
  bool closed_list_tree = vm["closed-list-tree"].as<bool>();
  bool verbose = vm["verbose"].as<bool>();
  bool continue_pause = vm["continue"].as<bool>();
  bool one_action = vm["one-action"].as<bool>();
  bool negated_as_neutral = vm["nan"].as<bool>();
  bool variable_beta = !vm["static-beta"].as<bool>();
  bool pr_verbose = vm["pr-verbose"].as<bool>();
  double theta = vm["theta"].as<double>();
  bool landmark = vm["landmark"].as<bool>();
  bool filter = vm["filter"].as<bool>();

  unsigned int max_simulate_nodes;
  if(!vm.count("max-simulate-nodes")){
    max_simulate_nodes = INT_MAX;
  }else{
    max_simulate_nodes = vm["max-simulate-nodes"].as<unsigned int>();
  }

  unsigned int precision;
  if(!vm.count("precision")){
    precision = -1;
  }else{
    precision = vm["precision"].as<int>();
  }


	aptk::STRIPS_Problem	prob;
	aptk::FF_Parser::get_problem_description( vm["domain"].as<std::string>(), vm["problem"].as<std::string>(), prob );
	std::vector<aptk::Fluent_Vec> goal_set = goal_set_parsing(goal_set_name, prob);

  std::vector<double> priors;
  for (unsigned int i = 0; i < goal_set.size(); i++){
    priors.push_back(0.5);
  }

  priors = normalize_vector(priors);

  unsigned int goal_index = 0;
  std::vector<unsigned> true_goal_v = prob.goal();
  std::set<unsigned> true_goal(true_goal_v.begin(), true_goal_v.end());
  for (unsigned int i = 0; i < goal_set.size(); i++){
    std::vector<unsigned> cand_goal_v = goal_set[i];
    std::set<unsigned> cand_goal (cand_goal_v.begin(), cand_goal_v.end());
    if (cand_goal == true_goal)
      goal_index = i;

  }

  prob.set_goal_set(goal_set);
  prob.set_priors(priors);
  prob.set_beta(beta);
  prob.set_df(discount_factor);
  prob.set_precision(precision);
  prob.set_pr_verbose(pr_verbose);
  prob.set_nan(negated_as_neutral);
  prob.set_v_beta(variable_beta);
  prob.set_optimal(optimal);
  prob.set_true_init(prob.init());
  prob.set_theta(theta);
  prob.set_filter(filter);
  prob.set_landmark(landmark);

  std::cout << std::endl;

  goal_distance_calculator gd(prob, goal_set);

  double distance = gd.complete_goal_distance();
  std::cout << "Goal Distance: " << distance << std::endl;



}
