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



float do_search(  Fwd_Search_Problem& search_prob,  std::vector< aptk::Action_Idx >& plan, float& cost, std::string plan_filename,  bool anytime, bool delayed, bool greedy  ) {

	cost = infty;

	float ref = aptk::time_used();
	float t0 = aptk::time_used();

	BFS_H_Max_Fwd engine( search_prob );
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

void process_command_line_options( int ac, char** av, po::variables_map& vars ) {
	po::options_description desc( "Options:" );

	desc.add_options()
		( "help", "Show help message" )
		( "domain", po::value<std::string>(), "Input PDDL domain description" )
		( "problem", po::value<std::string>(), "Input PDDL problem description" )
		( "greedy", po::value<bool>()->default_value(false), "Greedy (default False)" )
		( "delayed", po::value<bool>()->default_value(false), "Delayed Evaluation (default False)" )
		( "anytime", po::value<bool>()->default_value(false), "Anytime (default False)" )
		( "output", po::value<std::string>(), "Output file for plan" )
		( "lambda", po::value<float>()->default_value(0.5), "Scaling unit for human involvement" )
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

bool human_action_information(aptk::Action_Ptr_Vec& human_actions, aptk::STRIPS_Problem&  prob, int cost){
	bool human_accept;

 	// Show actions to human
	std::cout << "Human Actions:" << std::endl;
	if (human_actions.size() > 0){
		for (unsigned i = 0; i < human_actions.size(); i++) {
		aptk::Action& a = *(human_actions[i]);
		std::cout << a.index() << ". " << a.signature() << std::endl;
		}
	} else if (cost == infty) {
		std::cout << "No Plan Was Found" << std::endl;
	} else {
		std::cout << "No Human Actions" << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Do you acccept? (1/0)" << std::endl;
	std::cin >> human_accept;

	if (!human_accept){
		// Ask for actions to delete and then set their cost to infinity
		aptk::Action_Idx ai;
		do{
			std::cout << std::endl;
			std::cout << "Index of action to remove (\"-1\" to continue): " << std::endl;
			std::cin >> ai;
			if (ai != -1){
				aptk::Action& delete_a= *(prob.actions()[ai]);
				delete_a.set_cost(infty);
			}
		} while(ai != -1);

		// Ask for new actions to add to action pool
		bool newaction;
		std::cout << std::endl;
		std::cout << "Do you wish to add a new human action? (1/0) " << std::endl;
		std::cin >> newaction;

		while (newaction){
			int cost;
			std::string	action_sig;
			aptk::Fluent_Vec add;
			aptk::Fluent_Vec del;
			aptk::Fluent_Vec pre;
			aptk::Conditional_Effect_Vec cond_eff;

			std::cout << std::endl;
			std::cout << "Name: " << std::endl;
			std::cin >> action_sig;

			std::cout << std::endl;
			std::cout << "Preconditions: " << std::endl;
			human_add_fluents(prob, pre);

			std::cout << std::endl;
			std::cout << "Adds: " << std::endl;
			human_add_fluents(prob, add);

			std::cout << std::endl;
			std::cout << "Deletes: " << std::endl;
			human_add_fluents(prob, del);

			std::cout << std::endl;
			std::cout << "Cost:" << std::endl;
			std::cin >> cost;

			prob.add_action(prob, "HUMAN_ACTION_" + action_sig, pre, add, del, cond_eff, cost);
			prob.print_actions(std::cout);

			std::cout << "Do you wish to add a new human action? (1/0) " << std::endl;
			std::cin >> newaction;

		}
	}

	return human_accept;
}

void instantiate_human_actions(aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& augment_prob, float ha_cost){

	aptk::Fluent_Ptr_Vec& fs = prob.fluents();

	for (unsigned int i = 0; i < prob.num_fluents(); i++){

		aptk::Fluent& f = *fs[i];
		aptk::Fluent_Vec pre;
		aptk::Conditional_Effect_Vec cond_eff;

		std::string action_name = "HUMAN_ACTION" + f.signature();
		aptk::Fluent_Vec add;
		aptk::Fluent_Vec del;
		add.push_back(i);

		std::string neg_action_name = "HUMAN_ACTION_NEG" + f.signature();
		aptk::Fluent_Vec add_neg;
		aptk::Fluent_Vec del_neg;
		del_neg.push_back(i);

		augment_prob.add_fluent(augment_prob,f.signature());

		prob.add_action(augment_prob, action_name, pre, add, del, cond_eff, ha_cost);
		prob.add_action(augment_prob, neg_action_name, pre, add_neg, del_neg, cond_eff, ha_cost);
	}

	aptk::Action_Ptr_Vec& as = prob.actions();
	for (unsigned int i = 0; i < prob.num_actions(); i++) {
		aptk::Action& a = *as[i];
		augment_prob.add_action(augment_prob, a.signature(), a.prec_vec(), a.add_vec(), a.del_vec(), a.ceff_vec(), a.cost());
	}

	augment_prob.make_action_tables();

	augment_prob.set_init(augment_prob, prob.init());
	augment_prob.set_goal(augment_prob, prob.goal());
	augment_prob.set_domain_name(prob.domain_name());
	augment_prob.set_problem_name(prob.problem_name());

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

	std::string plan_filename;
	if ( !vm.count( "output" ) ) {
		std::cerr << "No output plan file specified, defaulting to 'plan.ipc'" << std::endl;
		plan_filename = "plan.ipc";
	}
	else
		plan_filename = vm["output"].as<std::string>();

	bool anytime = vm["anytime"].as<bool>();
	bool delayed = vm["delayed"].as<bool>();
	bool greedy =  vm["greedy"].as<bool>();

	aptk::STRIPS_Problem	prob;
	aptk::FF_Parser::get_problem_description( vm["domain"].as<std::string>(), vm["problem"].as<std::string>(), prob );


	float lambda = vm["lambda"].as<float>();
	float ha_cost = lambda*prob.num_actions();
	aptk::STRIPS_Problem augment_prob;

	instantiate_human_actions(prob, augment_prob, ha_cost);


	Fwd_Search_Problem	search_prob( &augment_prob );
	std::vector< aptk::Action_Idx > plan;

	bool human_accept;

	do{

		float cost = 0;
		plan.clear();
		float at_search_t = do_search(search_prob, plan, cost, plan_filename,  anytime, delayed, greedy );
		std::cout << "Time taken: " << at_search_t << std::endl;

 		aptk::Action_Ptr_Vec human_actions;
		for (unsigned k = 0; k < plan.size(); k++) {
			aptk::Action& a = *(search_prob.task().actions()[ plan[k] ]);

			if (a.signature().find("HUMAN_ACTION") != std::string::npos) {
				human_actions.push_back(&a);
			}
		}

		human_accept = human_action_information(human_actions, augment_prob, cost);
		augment_prob.make_action_tables();

	} while (!human_accept);

}
