
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
#include "lm_plan_recognition.hxx"

namespace po = boost::program_options;

using namespace pr_lm;

using	aptk::STRIPS_Problem;
using	aptk::Action;
using	aptk::agnostic::Fwd_Search_Problem;

void process_command_line_options( int ac, char** av, po::variables_map& vm) {
	po::options_description desc( "Additional Options" );

	desc.add_options()
		( "domain,d", po::value<std::string>(), "Input PDDL domain description" )
		( "problem,p", po::value<std::string>(), "Input PDDL problem description" )
		( "goalset,g", po::value<std::string>(), "Input PDDL goal-set description\n" )
		( "hypset,H", po::value<std::string>(), "Input PDDL hyp-set description\n" )

		( "theta,t", po::value<double>()->default_value(.20), "Threshold for filtering goals" )
		( "precision,P", po::value<int>()->default_value(2), "The precision to which the belief state is stored as within the state.\n" )
		( "static-beta,S", po::bool_switch()->default_value(false), "Keep beta value static in search." )

		( "verbose,v", po::bool_switch()->default_value(false), "Verbose results." )
		( "help,h", "Show help message" )
	;
  po::positional_options_description positionalOptions;
  positionalOptions.add("domain", 1);
  positionalOptions.add("problem", 1);
  positionalOptions.add("goalset", 1);
  positionalOptions.add("hypset", 1);

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

	if ( !vm.count( "hypset" ) ) {
		std::cerr << "No Hyp Set file was specified!" << std::endl;
		std::exit(1);
	}

  std::string goal_set_name = vm["goalset"].as<std::string>();
  std::string hyp_set_name = vm["hypset"].as<std::string>();
  bool verbose = vm["verbose"].as<bool>();
  bool variable_beta = !vm["static-beta"].as<bool>();
  double theta = vm["theta"].as<double>();

  unsigned int precision;
  if(!vm.count("precision")){
    precision = -1;
  }else{
    precision = vm["precision"].as<int>();
  }


	aptk::STRIPS_Problem	prob;
	aptk::FF_Parser::get_problem_description( vm["domain"].as<std::string>(), vm["problem"].as<std::string>(), prob );
	std::vector<aptk::Fluent_Vec> goal_set = goal_set_parsing(goal_set_name, prob);
	std::vector<unsigned int> observations = hype_set_parsing(hyp_set_name, prob);

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
  prob.set_precision(precision);
  prob.set_v_beta(variable_beta);
  prob.set_true_init(prob.init());

  PlanRecognitionEngine_LM engine(&prob, goal_set,theta, verbose);

  auto percents = engine.plan_recognition(observations);

  std::cout << std::endl;
  std::cout << "Probabilities: " << std::endl;
  for (unsigned int i = 0 ; i <  percents.size(); i++){
    for (auto f : goal_set[i]){
      std::cout << prob.fluents()[f]->signature() << ",";
    }
    std::cout << "; ";
    std::cout << percents[i] << std::endl;
  }



  std::cout << std::endl;

}
