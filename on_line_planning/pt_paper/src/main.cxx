
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
#include "bfws_pr_avamb_mcts.hxx"
#include "goal_set_parse.hxx"
#include "plan_recognition.hxx"
#include "lm_plan_recognition.hxx"
#include "dalandmarks.hxx"

namespace po = boost::program_options;

using	aptk::STRIPS_Problem;
using	aptk::Action;
using	aptk::agnostic::Fwd_Search_Problem;
using namespace pr;
using namespace pr_lm;

typedef	Node< aptk::State >	Search_Node;
typedef aptk::search::Closed_List<Search_Node> Closed_List_Type;
typedef BFWS_PR_MCTS<Fwd_Search_Problem> BFWS_MCTS_SEARCH;

void progress_pr_though_action(aptk::STRIPS_Problem& prob, std::vector<aptk::Fluent_Vec> goal_set,
    float beta, float& delta_value,
    std::vector<double>& priors, std::vector<std::vector<int>>& min_relaxed_plan,
    std::vector<std::vector<unsigned int>>& min_obs, std::vector<float>& min_neg_cost,
    std::vector<unsigned int> full_observations,
    int a){

  PlanRecognitionEngine pr(&prob, goal_set, priors, true, false, true, false);
  std::vector<double> posteriors;
  std::vector<unsigned int> actions;
  actions.push_back(a);


  posteriors = pr.plan_recognition(actions, prob.init(), beta, delta_value,
      min_relaxed_plan, min_obs, min_neg_cost, full_observations);

  std::vector<double> rounded_post;
  for (double p : posteriors){
    double rounded_p = round(p * pow(10, prob.m_precision)) / pow(10, prob.m_precision);
    rounded_post.push_back(rounded_p);
  }


  priors = rounded_post;


}

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
  float beta, bool landmark, double theta, bool variable_beta
  ){

  std::vector<double> perfect_dist;
  for (unsigned int i = 0; i < goal_set.size(); i++)
    if (i == goal_index)
      perfect_dist.push_back(1.0);
    else
      perfect_dist.push_back(0.0);

  bool approx = false;
  bool negated_as_neutral = false;
  bool verbose =false;

  //if(beta != 1)
    //approx = false;

  std::vector<double> posteriors;
  PlanRecognitionEngine pr(&prob, goal_set, priors, approx, negated_as_neutral,
      variable_beta, verbose);
  float dummy_deltas = 0;
  std::vector<std::vector<int>> dummy_rel;
  std::vector<std::vector<unsigned int>> dummy_obs;
  std::vector<unsigned int> dummy_f_obs;
  std::vector<float> dummy_min_cost;

  for(auto a : priors){
    dummy_min_cost.push_back(infty);
    dummy_rel.push_back({});
    dummy_obs.push_back({});
    dummy_f_obs.push_back(1);
  }

  if(!landmark)
  {
    posteriors = pr.plan_recognition(observations, init, beta, dummy_deltas,
        dummy_rel, dummy_obs, dummy_min_cost, dummy_f_obs);
  }else{
    PlanRecognitionEngine_LM prlm(&prob, goal_set, theta,verbose,priors);
    posteriors = prlm.plan_recognition(observations);
  }


  std::pair<double,std::vector<double>> reward;
  reward.first = euclidean_distance(perfect_dist, posteriors);
  reward.second = posteriors;

  return reward;

}

void do_search(aptk::STRIPS_Problem& prob, std::vector<aptk::Fluent_Vec> goal_set,
  std::vector<double> true_priors, unsigned int goal_index, bool closed_list_tree,
  double discount_factor, int max_nodes,
  float beta, bool optimal, bool diff_plan_rec,
  bool verbose, unsigned int max_simulate_nodes,
  bool continue_pause, int precision, bool one_action,
  bool landmark_eval, float beta_eval, double theta_eval, bool prob_trace
  ){

  std::vector<unsigned> observations;
  std::vector<std::vector<double>> observations_prob;
  std::vector<double> observations_eval;
  std::vector<unsigned int> init = prob.init();
  int counter = 0;
  Closed_List_Type * closed_list = new Closed_List_Type;
  std::vector<double> action_comp_time;
  std::vector<unsigned int> obs = {430,595,598,787};


  std::vector<double> priors = true_priors;
  float delta_value = 0;
  std::vector<std::vector<int>> min_relaxed_plan;
  std::vector<std::vector<unsigned int>> min_obs;
  std::vector<float> min_neg_cost;
  auto true_goal = prob.goal();
  double threshold = 0;


  for(auto a : true_priors){
    min_neg_cost.push_back(infty);
    std::vector<unsigned int> tempt_ui;
    std::vector<int> tempt_i;

    min_obs.push_back(tempt_ui);
    min_relaxed_plan.push_back(tempt_i);
  }

  PlanRecognitionEngine pr(&prob, goal_set, priors,false,false,
      false,false);
  Fwd_Search_Problem search_prob_o(&prob);
  //float optimal_cost = 0;
  //std::vector<int> plan;
  //pr.heuristic_estimate(search_prob_o, optimal_cost, plan, obs);

  float priors_sum = 0;
  for(unsigned i = 0; i < priors.size(); i++){
    if(i != goal_index){
      priors_sum += priors[i];
    }
  }

  float priors_av = priors_sum / ((float) true_priors.size() -1 );

  bool thresh_b1_met = false;
  bool thresh_v_beta = false;
  bool thresh_binf_met = false;
  bool thresh_lm_met = false;

  float cost_b1 = 0;
  float cost_binf = 0;
  float cost_lm = 0;
  float cost_vb = 0;

  unsigned int countdown = 30;


  while(true){

    clock_t begin = clock();
    //for( unsigned i = 0; i < prob.actions().size(); i++){
      //auto a = *(prob.actions()[i]);
      //std::cout << a.index() << ". " << a.signature() << std::endl;
    //}
    //exit(0);

    prob.set_priors(priors);

    Fwd_Search_Problem search_prob(&prob);
    BFWS_MCTS_SEARCH  engine( search_prob, goal_set, priors, goal_index, observations,
        init, true , discount_factor,
        beta, optimal, diff_plan_rec, verbose,
        max_simulate_nodes, precision, counter, closed_list, threshold
        );
    int act = engine.pick_next_action(max_nodes);

    //if(obs.size() == 0)
      //break;

    //int act = (obs.back());
    //obs.pop_back();

    if(act == -1)
      break;

    aptk::Action * a = prob.actions()[act];

    observations.push_back(act);

    std::pair<double, std::vector<double>> reward_b1 = call_plan_rec(prob, init, goal_set, observations,  true_priors, goal_index, 1, false, theta_eval,false);
    std::pair<double, std::vector<double>> reward_binf = call_plan_rec(prob, init, goal_set, observations,  true_priors, goal_index, infty, false, theta_eval,false);
    std::pair<double, std::vector<double>> reward_vb = call_plan_rec(prob, init, goal_set, observations,  true_priors, goal_index, 1, false, theta_eval,true);
    std::pair<double, std::vector<double>> reward_lm = call_plan_rec(prob, init, goal_set, observations,  true_priors, goal_index, beta_eval, true, theta_eval,true);
    prob.set_goal(prob,true_goal);


    if(!one_action)
    if(!continue_pause && !one_action)
      std::cout << a->signature() << ": " << reward_b1.first << std::endl;

    //observations_eval.push_back(reward_lm.first);
    observations_prob.push_back(reward_b1.second);


    aptk::State root(prob);
    root.set(prob.init());

    aptk::State * next_root_state = root.progress_through(*a);

    std::vector<double> false_priors(priors);

    progress_pr_though_action(prob, goal_set, beta, delta_value, false_priors, min_relaxed_plan, min_obs, min_neg_cost, observations, act);
    priors = engine.belief_state();

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    action_comp_time.push_back(elapsed_secs);

    if(search_prob.goal( *next_root_state )) {
      break;
    }

    aptk::STRIPS_Problem::set_init(prob, next_root_state->fluent_vec());
    prob.set_observations(observations);

    //counter++;
    //if(counter > 2*optimal_cost){
      //break;
    //}

    float max_prob_beta1 = 0;
    for(unsigned i = 0; i < reward_b1.second.size(); i++){
      if(i != goal_index){
        if (reward_b1.second[i] > max_prob_beta1){
          max_prob_beta1 = reward_b1.second[i];
        }
      }
    }

    if (max_prob_beta1 < reward_b1.second[goal_index] - (priors_av) && !thresh_b1_met)
    {
      thresh_b1_met = true;
      cost_b1 += a->cost();
    }

    float max_prob_betainf = 0;
    for(unsigned i = 0; i < reward_binf.second.size(); i++){
      if(i != goal_index){
        if (reward_binf.second[i] > max_prob_betainf){
          max_prob_betainf = reward_binf.second[i];
        }
      }
    }
    if (max_prob_betainf < reward_binf.second[goal_index] - (priors_av) && !thresh_binf_met)
    {
      thresh_binf_met = true;
      cost_binf += a->cost();
    }

    float max_prob_vb = 0;
    for(unsigned i = 0; i < reward_vb.second.size(); i++){
      if(i != goal_index){
        if (reward_vb.second[i] > max_prob_vb){
          max_prob_vb = reward_vb.second[i];
        }
      }
    }
    if (max_prob_vb < reward_vb.second[goal_index] - (priors_av) && !thresh_v_beta)
    {
      thresh_v_beta= true;
      cost_vb += a->cost();
    }

    float max_prob_lm = 0;
    for(unsigned i = 0; i < reward_lm.second.size(); i++){
      if(i != goal_index){
        if (reward_lm.second[i] > max_prob_lm){
          max_prob_lm = reward_lm.second[i];
        }
      }
    }
    if (max_prob_lm < reward_lm.second[goal_index] - (priors_av) && !thresh_lm_met)
    {
      cost_lm += a->cost();
      thresh_lm_met = true;
    }

    if(thresh_b1_met || thresh_lm_met || thresh_v_beta || thresh_binf_met ){
      countdown--;
    }

    if(!thresh_b1_met)
      cost_b1 += a->cost();
    if(!thresh_binf_met)
      cost_binf += a->cost();
    if(!thresh_lm_met)
      cost_lm += a->cost();
    if(!thresh_v_beta)
      cost_vb += a->cost();

    //if(cost_lm >= 2+cost_b1 && !thresh_lm_met){
      //thresh_lm_met = true;
      //cost_lm = optimal_cost;
    //}

    if(countdown == 0){
      if(!thresh_b1_met)
        cost_b1 = infty;
      if(!thresh_binf_met)
        cost_binf = infty;
      if(!thresh_lm_met)
        cost_lm = infty;
      if(!thresh_v_beta)
        cost_vb = infty;

      break;
    }



    if(thresh_b1_met && thresh_lm_met && thresh_binf_met && thresh_v_beta)
      break;

    if(one_action)
      break;

    if(!continue_pause)
    {
      auto cha = std::cin.get();
      if (cha == 'n')
        break;
    }
  }


  std::cout << std::endl;
  for(auto i : observations){
    std::cout << prob.actions()[i]->signature() << ",";
  }

  std::cout << std::endl;
  for(auto i : action_comp_time){
    std::cout << i  << ",";
  }
  std::cout << std::endl;

  //for(auto i : observations_eval){
    //i = -1*i;
    //std::cout << i << ",";
  //}
  //std::cout << std::endl;

  if(prob_trace){
    for(unsigned i = 0; i < goal_set.size(); i++)
    {
      for(unsigned j = 0 ; j < observations_prob.size(); j++){
        std::cout << observations_prob[j][i] << ",";
      }
      std::cout << std::endl;
    }
  }
  //std::cout << goal_index << std::endl;
  std::cout << prob.fluents().size() << std::endl;
  std::cout << std::endl;

  std::cout << cost_b1 << std::endl;
  std::cout << cost_binf << std::endl;
  std::cout << cost_vb << std::endl;
  std::cout << cost_lm  << std::endl;
  //std::cout << optimal_cost << std::endl;


}

void process_command_line_options( int ac, char** av, po::variables_map& vm) {
	po::options_description desc( "Additional Options" );

	desc.add_options()
		( "domain,d", po::value<std::string>(), "Input PDDL domain description" )
		( "problem,p", po::value<std::string>(), "Input PDDL problem description" )
		( "goalset,g", po::value<std::string>(), "Input PDDL goal-set description\n" )

		( "max-nodes,M", po::value<unsigned int>()->default_value(100), "The maximum amount of nodes in earch MCTS tree." )
		( "max-simulate-nodes,s", po::value<unsigned int>(), "The maximum amount of nodes to be simulated in the rollout policy.\n" )
		( "prob-trace,T", po::bool_switch()->default_value(false), "Show probability trace.")

		( "beta,b", po::value<float>()->default_value(1), "Value determining how rational an observer believes the agent to be." )
		( "theta,t", po::value<double>()->default_value(0.2f), "Threshold for goal filtering" )
		( "discount-factor,D", po::value<double>()->default_value(1.0f), "The amount by which transparent plans are penalised by their distance." )
		( "precision,P", po::value<int>()->default_value(2), "The precision to which the belief state stored as within the state.\n" )

		( "landmark,L", po::bool_switch()->default_value(false), "Use POM17 landmark plan recognition." )
		( "filter,f", po::bool_switch()->default_value(false), "Use goal filtering with plan recognition." )

		( "optimal,o", po::bool_switch()->default_value(false), "Use optimal plan recognition." )
		( "markovian,m", po::bool_switch()->default_value(false), "Use markovian limited plan recognition." )
		( "nan,n", po::bool_switch()->default_value(false), "Approximate C(G, ~O) as c(G) in approximate plan recognition." )
		( "static-beta,S", po::bool_switch()->default_value(false), "Keep beta value static in search." )
    ( "diff-plan-rec,r", po::bool_switch()->default_value(false), "Use difference based plan recognition." )
    ( "closed-list-tree,l", po::bool_switch()->default_value(false), "Use a closed list in the tree policy of the MCTS.\n" )

		( "verbose,v", po::bool_switch()->default_value(false), "BFWS Verbose results, Use H instead." )
		( "pr-verbose,V", po::bool_switch()->default_value(false), "Verbose plan recognition results." )
		( "h-verbose,H", po::bool_switch()->default_value(false), "Verbose heuristic results." )
		( "continue,c", po::bool_switch()->default_value(false), "Continue actions without pause." )
		( "one-action,O", po::bool_switch()->default_value(false), "Finish program after one action." )


		// Ignore these
		( "landmark-eval,z", po::bool_switch()->default_value(false), "Use landmark for evaluation." )
		( "beta-eval,y", po::value<float>()->default_value(1), "Value determining how rational an observer believes the agent to be for evaluation." )
		( "theta-eval,x", po::value<double>()->default_value(0.2f), "Threshold for goal filtering for evaluation" )


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
  bool h_verbose = vm["h-verbose"].as<bool>();
  double theta = vm["theta"].as<double>();
  bool landmark = vm["landmark"].as<bool>();
  bool filter = vm["filter"].as<bool>();
  bool markovian = vm["markovian"].as<bool>();
  bool prob_trace = vm["prob-trace"].as<bool>();

  bool landmark_eval = vm["landmark-eval"].as<bool>();
  double theta_eval = vm["theta-eval"].as<double>();
  float beta_eval = vm["beta-eval"].as<float>();

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

  //for(auto i : goal_set){
    //std::cout << print_fluent_vec(prob, i) << std::endl;
    //std::cout << std::endl;
  //}
  //std::cout << print_fluent_vec(prob, prob.goal()) << std::endl;

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

  //std::cout << "Goal Set: \n";
  //for(auto i : goal_set){
    //std::cout << print_fluent_vec(prob, i) << std::endl;
  //}

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
  prob.set_markov(markovian);
  prob.set_h_verbose(h_verbose);

  std::cout << std::endl;

  do_search(prob, goal_set, priors, goal_index, closed_list_tree,
      discount_factor, max_nodes, beta, optimal, diff_plan_rec,
      verbose, max_simulate_nodes, continue_pause, precision, one_action,
      landmark_eval, beta_eval, theta_eval, prob_trace);

}
