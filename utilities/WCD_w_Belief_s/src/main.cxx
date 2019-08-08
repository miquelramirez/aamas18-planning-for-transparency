/*
Lightweight Automated Planning Toolkit
Copyright (C) 2012
Miquel Ramirez <miquel.ramirez@rmit.edu.au>
Nir Lipovetzky <nirlipo@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <fstream>

#include <ff_to_aptk.hxx>
#include <strips_prob.hxx>
#include <fluent.hxx>
#include <action.hxx>
#include <cond_eff.hxx>
#include <strips_state.hxx>
#include <fwd_search_prob.hxx>

#include <h_1.hxx>

#include <aptk/open_list.hxx>
#include <aptk/string_conversions.hxx>
#include <aptk/at_bfs.hxx>

#include <fstream>

#include <boost/program_options.hpp>

#include "wcd.hxx"
#include "goal_set_parse.hxx"


namespace po = boost::program_options;

using	aptk::STRIPS_Problem;

using	aptk::agnostic::Fwd_Search_Problem;
using	aptk::Action;


using 	aptk::agnostic::H1_Heuristic;
using	aptk::agnostic::H_Add_Evaluation_Function;
using	aptk::agnostic::H_Max_Evaluation_Function;

using 	aptk::search::Open_List;
using	aptk::search::bfs::AT_BFS_SQ_SH;
using	aptk::search::Node_Comparer;



//NIR: We start defining the type of nodes for our planner
typedef		aptk::search::bfs::Node< aptk::State >	Search_Node;

//NIR: Then we define the type of the tie-breaking algorithm
// for the open list we are going to use
typedef		Node_Comparer< Search_Node >					Tie_Breaking_Algorithm;


//NIR: Now we define the Open List type by combining the types we have defined before
typedef		Open_List< Tie_Breaking_Algorithm, Search_Node >		BFS_Open_List;


//NIR: Now we define the heuristics

typedef 	H1_Heuristic<Fwd_Search_Problem, H_Max_Evaluation_Function>	H_Max_Fwd;

//NIR: Now we're ready to define the BFS algorithm we're going to use
typedef		AT_BFS_SQ_SH< Fwd_Search_Problem, H_Max_Fwd, BFS_Open_List >		BFS_H_Max_Fwd;



float do_search(  Fwd_Search_Problem& search_prob,  std::vector< aptk::Action_Idx >& plan, float& cost, std::string plan_filename,  std::vector<aptk::Fluent_Vec>& goal_set, bool anytime, bool delayed, bool greedy  ) {

	cost = infty;

	float ref = aptk::time_used();
	float t0 = aptk::time_used();

	BFS_H_Max_Fwd engine( search_prob);
	engine.set_greedy( greedy );
	engine.set_delay_eval( delayed );
	engine.start();

	unsigned expanded_0 = engine.expanded();
	unsigned generated_0 = engine.generated();

	while ( engine.find_solution( cost, plan ) ) {
		if ( !plan.empty() ) {

			if( anytime ) std::cout << "Plan found with cost: " << cost << std::endl;
			std::ofstream plan_stream( plan_filename.c_str() );
			for ( unsigned k = 0; k < plan.size(); k++ ) {
				const aptk::Action& a = *(search_prob.task().actions()[ plan[k] ]);
				plan_stream << a.signature() << std::endl;
			}
			plan_stream.close();
		}
		float tf = aptk::time_used();
		unsigned expanded_f = engine.expanded();
		unsigned generated_f = engine.generated();
		if(anytime){
			std::cout << "Time: " << tf - t0 << std::endl;
			std::cout << "Generated: " << generated_f - generated_0 << std::endl;
			std::cout << "Expanded: " << expanded_f - expanded_0 << std::endl << std::endl;
		}
		t0 = tf;
		expanded_0 = expanded_f;
		generated_0 = generated_f;

		if(!anytime) break;
		plan.clear();

	}

	float total_time = aptk::time_used() - ref;
	std::cout << "Total time: " << total_time << std::endl;
	std::cout << "Nodes generated during search: " << engine.generated() << std::endl;
	std::cout << "Nodes expanded during search: " << engine.expanded() << std::endl;
	std::cout << "Nodes pruned by bound: " << engine.pruned_by_bound() << std::endl;
	std::cout  << "Dead-end nodes: " << engine.dead_ends() << std::endl;
	std::cout << "Plan found with cost: " << cost << std::endl;

	return total_time;


}

void process_command_line_options( int ac, char** av, po::variables_map& vm) {
	po::options_description desc( "Options:" );

	desc.add_options()
		( "domain,d", po::value<std::string>(), "Input PDDL domain description" )
		( "problem,p", po::value<std::string>(), "Input PDDL problem description" )
		( "goalset,g", po::value<std::string>(), "Input PDDL goal-set description\n" )

		( "epsilon", po::value<float>()->default_value(1.0f), "Let epsilon be a constant discount value which premotes working together" )

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

void print_plan_to_cout(std::vector< aptk::Action_Idx >& plan, Fwd_Search_Problem& search_prob){
	for ( unsigned k = 0; k < plan.size(); k++ ) {
		const aptk::Action& a = *(search_prob.task().actions()[ plan[k] ]);
		std::cout  << a.signature() << std::endl;
	}
}

void human_add_fluents(aptk::STRIPS_Problem&  prob, aptk::Fluent_Vec& fluent_vec){
		int fluent_index;
		prob.print_fluents(std::cout);

		do {
			std::cout << "Index of fluent to add (\"-1\" to continue): " << std::endl;
			std::cin >> fluent_index;

			if (fluent_index > 0){
				fluent_vec.push_back((unsigned int) (fluent_index - 1));
			}
		} while (fluent_index > 0);

}

void human_get_goal_set(aptk::STRIPS_Problem& prob, std::vector<aptk::Fluent_Vec>& goal_set){

	bool add_to_goal_set = 0;
	std::cout << "Add a goal to goal set (1/0)?" << std::endl;
	std::cin >> add_to_goal_set;

	while(add_to_goal_set){
		aptk::Fluent_Vec goal_vec;
		human_add_fluents(prob, goal_vec);
		goal_set.push_back(goal_vec);
		std::cout << "Add another goal to goal set (1/0)?" << std::endl;
		std::cin >> add_to_goal_set;
	}

}

void print_grid(std::vector<std::vector<std::string>> & g){
	for (unsigned int i = 0; i < g.size(); i++){
		for (unsigned int j = 0; j < g[i].size(); j++) {
			std::cout << g[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

template <typename T>
std::vector<T> flatten(const std::vector<std::vector<T>>& v) {
    std::size_t total_size = 0;

    for (const auto& sub : v)
        total_size += sub.size();

	std::vector<T> result;
    result.reserve(total_size);

	for (const auto& sub : v)
        result.insert(result.end(), sub.begin(), sub.end());

	return result;
}


int main( int argc, char** argv ) {

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
  float epsilon= vm["epsilon"].as<float >();

	aptk::STRIPS_Problem	prob;
	aptk::FF_Parser::get_problem_description( vm["domain"].as<std::string>(), vm["problem"].as<std::string>(), prob );
	std::vector<aptk::Fluent_Vec> goal_set = goal_set_parsing(goal_set_name, prob);

  unsigned int goal_index = 0;
  std::vector<unsigned> true_goal_v = prob.goal();
  std::set<unsigned> true_goal(true_goal_v.begin(), true_goal_v.end());
  for (unsigned int i = 0; i < goal_set.size(); i++){
    std::vector<unsigned> cand_goal_v = goal_set[i];
    std::set<unsigned> cand_goal (cand_goal_v.begin(), cand_goal_v.end());
    if (cand_goal == true_goal)
      goal_index = i;

  }


  float wcd_v = wcd(prob, goal_set, epsilon);
  std::cout  << std::endl;
  std::cout << wcd_v << std::endl;

	//std::cout << "Make goal set:" <<std::endl;
	//std::vector<aptk::Fluent_Vec> goal_set;
  //aptk::Fluent_Vec temp_1;
  //temp_1.push_back(14);
  //goal_set.push_back(temp_1);
	//human_get_goal_set(prob, goal_set);
	//aptk::Fluent_Vec flattened_goal_set = flatten(goal_set);

	//std::cout << "Select goal:" << std::endl;
	//aptk::Fluent_Vec r_goal;
  //r_goal.push_back(25);
	//human_add_fluents(prob, r_goal);

	//std::vector<std::vector<std::string>> grid;

	//for (unsigned int j = 1; j <= m; j++){
		//std::vector<std::string> row;
		//unsigned int index;
		//for (unsigned int i = 1; i <= n; i++){
			//aptk::Fluent_Vec init;
			//for (unsigned int k = 0; k < prob.fluents().size(); k++){
				//if ((*prob.fluents()[k]).signature() == "(POS P" + std::to_string((j-1)*n + i) + ")"){
					//index = (*prob.fluents()[k]).index();
					//std::cout << (*prob.fluents()[k]).signature() << std::endl;
					//init.push_back((*prob.fluents()[k]).index());
					//break;
				//}
			//}
			//prob.set_init(prob, init);
			//aptk::STRIPS_Problem trans_prob;
			//std::map<std::string, unsigned int> idx_to_trans_idx;
			//translate_problem_latest_split(prob,  trans_prob,  idx_to_trans_idx, epsilon);
			//unsigned int wcd_g_val = wcd_g(trans_prob, idx_to_trans_idx, r_goal, goal_set, epsilon);

			//if (std::find(r_goal.begin(), r_goal.end(), index) != r_goal.end())
				//row.push_back(std::to_string(wcd_g_val) + "\"");
			//else if (std::find(flattened_goal_set.begin(), flattened_goal_set.end(), index) != flattened_goal_set.end())
				//row.push_back(std::to_string(wcd_g_val) + "\'");
			//else
				//row.push_back(std::to_string(wcd_g_val));
		//}
		//grid.push_back(row);
	//}

	//print_grid(grid);

}
