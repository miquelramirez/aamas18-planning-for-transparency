
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
#include "plan_recognition.hxx"
#include "lm_plan_recognition.hxx"

namespace po = boost::program_options;

using	aptk::STRIPS_Problem;
using	aptk::Action;
using	aptk::agnostic::Fwd_Search_Problem;
using namespace pr;
using namespace pr_lm;

double euclidean_distance(const std::vector<double> P, const std::vector<double> Q){
  assert(P.size() == Q.size());

  double h_d_2 = 0.0;

  for (unsigned int i = 0; i < P.size(); i++)
  {
    double p_q_i = P[i] - Q[i];
    h_d_2 += p_q_i*p_q_i;
  }

  return -1*sqrt(h_d_2);
}

std::pair<double, std::vector<double>> call_plan_rec(aptk::STRIPS_Problem& prob, aptk::Fluent_Vec init,  std::vector<aptk::Fluent_Vec> goal_set,
  std::vector<unsigned> observations, std::vector<double> priors, unsigned int goal_index,
  float beta, float theta, bool approx, bool landmark, bool negated_as_neutral, bool variable_beta, bool verbose
  ){

  std::vector<double> perfect_dist;
  for (unsigned int i = 0; i < goal_set.size(); i++)
    if (i == goal_index)
      perfect_dist.push_back(1.0);
    else
      perfect_dist.push_back(0.0);

  // Using traditional plan rec not difference plan rec
  std::vector<double> posteriors;

  if(!landmark)
  {
    PlanRecognitionEngine pr(&prob, goal_set, priors, approx, negated_as_neutral,
        variable_beta, verbose);
    posteriors = pr.plan_recognition(observations, init, beta);
  }else{
    PlanRecognitionEngine_LM prlm(&prob, goal_set, theta, verbose, priors);
    posteriors = prlm.plan_recognition(observations);
  }

  std::pair<double,std::vector<double>> reward;
  reward.first = euclidean_distance(perfect_dist, posteriors);
  reward.second = posteriors;

  return reward;

}

std::vector<float> aggregate_plan_recognition(aptk::STRIPS_Problem& prob, aptk::Fluent_Vec init,  std::vector<aptk::Fluent_Vec> goal_set,
  std::vector<unsigned> observations, std::vector<double> priors, unsigned int goal_index,
  float beta, float theta, bool approx, bool landmark, bool negated_as_neutral, bool variable_beta, bool verbose
  ){

  float thresh_1 = -1*0.367423;
  //float thresh_2 = -1*0.244949;
  //float thresh_3 = -1*0.122471;
  float cost_thresh_1 = 0;
  //float cost_thresh_2 = 0;
  //float cost_thresh_3 = 0;
  bool thresh_1_done = false;
  //bool thresh_3_done = false;
  //bool thresh_2_done = false;

  float prior_sum = 0;
  float priors_av;
  for(unsigned i = 0; i < priors.size(); i++){
    if(i != goal_index){
      prior_sum += priors[i];
    }

  }

  priors_av = prior_sum / ((float) priors.size() - 1);

  PlanRecognitionEngine pr(&prob, goal_set, priors,false,false,
      false,false);
  Fwd_Search_Problem search_prob_o(&prob);
  float optimal_cost;
  std::vector<int> plan;
  std::vector<unsigned int> obs;
  pr.heuristic_estimate(search_prob_o,  optimal_cost, plan, obs);

  std::vector<unsigned int> current_obs;
  for(unsigned int i = 0; i < observations.size(); i++){
    current_obs.push_back(observations[i]);

    auto result = call_plan_rec(prob, prob.init(), goal_set, current_obs,  priors, goal_index,
      beta, theta, approx, landmark, negated_as_neutral, variable_beta, verbose);

    float observations_eval = result.first;
    auto posts = result.second;

    //std::cout << print_action_vec(prob, current_obs) << std::endl;
    //print_vector(posts);
    //std::cout  << std::endl;
    //std::cout  << std::endl;
    //std::cout  << std::endl;
    //std::cout  << std::endl;

    //for (auto i : posts){
      //std::cout << i << std::endl;
    //}

    float max_prob = 0;
    for(unsigned i = 0; i < posts.size(); i++){
      if(i != goal_index){
        if (posts[i] > max_prob){
          max_prob = posts[i];
        }
      }

    }


    if (max_prob < posts[goal_index] - (priors_av)){
      //std::cout << "MaxProb: " << max_prob << ", GoalProb: " << posts[goal_index] << ", YES";
        thresh_1_done= true;

    }
    else{
      //std::cout << "MaxProb: " << max_prob << ", GoalProb: " << posts[goal_index] << ", NO";
    }


    cost_thresh_1 += prob.actions()[observations[i]]->cost();

    //if (observations_eval > thresh_2){
      //thresh_2_done = true;
    //} else if (!thresh_2_done){
      //cost_thresh_2 += prob.actions()[observations[i]]->cost();
    //}

    //if (observations_eval > thresh_3){
      //thresh_3_done = true;
    //} else if (!thresh_3_done){
      //cost_thresh_3 += prob.actions()[observations[i]]->cost();
    //}

    if(thresh_1_done ){//&& thresh_2_done && thresh_3_done){
      break;
    }else{
      //std::cout << observations[i] << std::endl;
    }


  }

  std::vector<float> thress;

  std::cout << cost_thresh_1 << std::endl;
  std::cout << optimal_cost << std::endl;


  //cost_thresh_1 = (cost_thresh_1+1)/optimal_cost > 1 ? 1 : cost_thresh_1/optimal_cost;
  //cost_thresh_2 = (cost_thresh_2+1)/optimal_cost > 1 ? 1 : cost_thresh_2/optimal_cost;
  //cost_thresh_3 = (cost_thresh_3+1)/optimal_cost > 1 ? 1 : cost_thresh_3/optimal_cost;
  //thress.push_back(cost_thresh_1);
  //thress.push_back(cost_thresh_2);
  //thress.push_back(cost_thresh_3);
  return thress;

}


void process_command_line_options( int ac, char** av, po::variables_map& vm) {
	po::options_description desc( "Additional Options" );

	desc.add_options()
		( "domain,d", po::value<std::string>(), "Input PDDL domain description" )
		( "problem,p", po::value<std::string>(), "Input PDDL problem description" )
		( "goalset,g", po::value<std::string>(), "Input goal-set description" )
		( "observations,o", po::value<std::string>(), "Input observation description" )

		( "beta,b", po::value<float>()->default_value(1), "Value determining how rational an observer believes the agent to be." )
		( "landmark,l", po::bool_switch()->default_value(false), "Use landmark plan recognition." )
		( "theta,t", po::value<float>()->default_value(0.2), "Threshold for filtering gaols." )

		( "approx,a", po::bool_switch()->default_value(false), "Use approx plan recognition." )
		( "nan,n", po::bool_switch()->default_value(false), "Approximate C(G, ~O) as c(G) in approximate plan recognition." )
		( "static-beta,S", po::bool_switch()->default_value(false), "Keep beta value static in search." )

		( "verbose,v", po::bool_switch()->default_value(false), "Verbose results." )
		( "help,h", "Show help message" )
	;
  po::positional_options_description positionalOptions;
  positionalOptions.add("domain", 1);
  positionalOptions.add("problem", 1);
  positionalOptions.add("goalset", 1);
  positionalOptions.add("observations", 1);

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

	if ( !vm.count( "observations" ) ) {
		std::cerr << "No Goal Set file was specified!" << std::endl;
		std::exit(1);
	}

  std::string goal_set_name = vm["goalset"].as<std::string>();
  std::string observations_name = vm["observations"].as<std::string>();
  float beta = vm["beta"].as<float>();
  float theta = vm["theta"].as<float>();
  bool optimal = !vm["approx"].as<bool>();
  bool landmark = vm["landmark"].as<bool>();
  bool verbose = vm["verbose"].as<bool>();
  bool negated_as_neutral = vm["nan"].as<bool>();
  bool variable_beta = !vm["static-beta"].as<bool>();
  bool approx = !optimal;

	aptk::STRIPS_Problem	prob;
	aptk::FF_Parser::get_problem_description( vm["domain"].as<std::string>(), vm["problem"].as<std::string>(), prob );
	std::vector<aptk::Fluent_Vec> goal_set = goal_set_parsing(goal_set_name, prob);
  std::vector<unsigned int> observations = observations_parsing(observations_name, prob);

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
  prob.set_true_init(prob.init());

  std::cout << std::endl;

  auto result = aggregate_plan_recognition(prob, prob.init(), goal_set, observations,  priors, goal_index,
    beta, theta, approx, landmark, negated_as_neutral, variable_beta, verbose);

  //std::cout << result[0] << std::endl;
}
