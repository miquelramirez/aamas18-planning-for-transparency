
#include <map>
#include <limits>

#include <strips_prob.hxx>
#include <fluent.hxx>
#include <action.hxx>
#include <cond_eff.hxx>
#include <fwd_search_prob.hxx>

#include <h_1.hxx>
#include <rp_heuristic.hxx>

#include <aptk/open_list.hxx>
#include <aptk/at_bfs.hxx>
#include <aptk/at_gbfs.hxx>

#include "plan_recognition.hxx"
#include "utility.hxx"

using	aptk::STRIPS_Problem;
using	aptk::agnostic::Fwd_Search_Problem;

using aptk::agnostic::H1_Heuristic;
using	aptk::agnostic::H_Max_Evaluation_Function;
using	aptk::agnostic::H_Add_Evaluation_Function;
using	aptk::agnostic::Relaxed_Plan_Heuristic;

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

typedef AT_BFS_SQ_SH<Fwd_Search_Problem, H_Add_Rp_Fwd, BFS_Open_List> BFS_H_RP_Fwd;
typedef AT_GBFS_SQ_SH<Fwd_Search_Problem, H_Add_Rp_Fwd, BFS_Open_List> GBFS_H_RP_Fwd;

namespace pr {

  std::vector<double> PlanRecognitionEngine::plan_recognition(std::vector<unsigned int> observations, aptk::Fluent_Vec& initial_state,
      float initial_beta){

    if(m_verbose){
      if(!m_approximate_pr){
        std::cout << "\tPlan Recognition:" << std::endl;
        std::cout << "\t------------------" << std::endl;
      }else{
        std::cout << "\tApproximate Plan Recognition:" << std::endl;
        std::cout << "\t-----------------------------" << std::endl;
      }
      std::cout << "\t\tObservations: ";
      for(auto i : observations)
        std::cout << (*m_s_problem).actions()[i]->signature() << ",";
      std::cout << std::endl << std::endl;
    }

    std::vector<int> delta_values = find_delta_values(observations, initial_state);

    float beta = initial_beta;
    if(m_variable_beta){
      beta = find_new_beta(delta_values, initial_beta);
    }
    if(m_verbose){
      std::cout << "\t\tBeta: " << beta  << std::endl << std::endl;
    }

    std::vector<double> posteriors = delta_values_to_probabilities(delta_values, beta);

    if(m_verbose){
      if(!m_approximate_pr){
        std::cout << "\t-----------------" << std::endl << std::endl;
      }else{
        std::cout << "\t-----------------------------" << std::endl;
      }
    }

    return posteriors;
  }

  std::vector<int> PlanRecognitionEngine::find_delta_values(std::vector<unsigned int> observations, aptk::Fluent_Vec& initial_state){

    // Transform problem in order to perform plan recognition
    aptk::STRIPS_Problem transformed_s_problem_positive;
    aptk::STRIPS_Problem transformed_s_problem_negative;

    std::map<std::string, unsigned int> idx_to_trans_idx;
    aptk::Fluent_Vec observation_fluents;
    aptk::Fluent_Vec negated_observation_fluents;

    if(!m_approximate_pr){
      translate_problem(* m_s_problem, transformed_s_problem_positive, observation_fluents,
          negated_observation_fluents, idx_to_trans_idx, observations, m_s_problem->m_true_init);
      clone_problem(transformed_s_problem_positive, transformed_s_problem_negative, transformed_s_problem_positive.init());
    }else{
      translate_problem_approx_pos(* m_s_problem, transformed_s_problem_positive, observations, initial_state);
      clone_problem(* m_s_problem, transformed_s_problem_negative, m_s_problem->m_true_init);
    }

    //std::cout << "\t\tM_SInitial State: ";
    //for(auto i : m_s_problem->init()){
      //std::cout << m_s_problem->fluents()[i]->signature() << ",";
    //}
    //std::cout << std::endl;
    //std::cout << "\t\tPOSInitial State: ";
    //for(auto i : transformed_s_problem_positive.init()){
      //std::cout << transformed_s_problem_positive.fluents()[i]->signature() << ",";
    //}
    //std::cout << std::endl;
    //std::cout << "\t\tNEGInitial State: ";
    //for(auto i : transformed_s_problem_negative.init()){
      //std::cout << transformed_s_problem_negative.fluents()[i]->signature() << ",";
    //}
    //std::cout << std::endl;

    // For each goal candidate perform two searches:
    // One where observed actions must be used
    // One where observed actions must not be used
    std::vector<int> delta_values;
    for (unsigned i = 0; i < m_candidate_goal_set.size(); i++){

      if(m_verbose){
        std::cout << "\t\tGoal: ";
        auto g = m_candidate_goal_set[i];
        for(unsigned int j = 0; j < g.size(); j++)
          std::cout << m_s_problem->fluents()[g[j]]->signature() << ",";
        std::cout << std::endl;

      }

      /*
      * Set goal to candidate goal and that observations have occured
      */
      aptk::Fluent_Vec g = m_candidate_goal_set[i];
      aptk::Fluent_Vec goal_with_observation_fluents = g;
      goal_with_observation_fluents.insert(goal_with_observation_fluents.end(),
          observation_fluents.begin(), observation_fluents.end());

      transformed_s_problem_positive.set_goal(transformed_s_problem_positive, goal_with_observation_fluents);

      Fwd_Search_Problem pos_search_prob(&transformed_s_problem_positive);
      std::vector< aptk::Action_Idx > plan;
      float cost_of_goal_w_observations = 0;

      // Perform search with observations
      if(!m_approximate_pr){
        do_pr_search(pos_search_prob, plan, cost_of_goal_w_observations);
      }else{
        //do_pr_search(pos_search_prob, plan, cost_of_goal_w_observations);
        heuristic_estimate(pos_search_prob, cost_of_goal_w_observations, plan, observations);
        cost_of_goal_w_observations += observations.size();
      }

      if(m_verbose){
        std::cout << "\t\t\tPlan With Observations: ";
        if(!m_approximate_pr){
          for(unsigned int j = 0; j < plan.size(); j++)
            std::cout << m_s_problem->actions()[plan[j]]->signature() << ",";
          std::cout << std::endl;
        }else{
          for(unsigned j = 0; j < observations.size(); j++)
            std::cout << m_s_problem->actions()[observations[j]]->signature() << ",";
          std::cout << " | ";
          for(unsigned j = 0; j < plan.size(); j++)
            std::cout << m_s_problem->actions()[plan[j]]->signature() << ",";
          std::cout << std::endl;
        }
        std::cout << "\t\t\tTotal Cost With Observations: " << cost_of_goal_w_observations << std::endl;
        std::cout << std::endl;
      }
      plan.clear();

      /*
      * Set goal to candidate goal and that observations must not occur
      */
      aptk::Fluent_Vec goal_without_observation_fluents = g;
      goal_without_observation_fluents.insert(goal_without_observation_fluents.end(),
          negated_observation_fluents.begin(), negated_observation_fluents.end());

      transformed_s_problem_negative.set_goal(transformed_s_problem_negative, goal_without_observation_fluents);

      Fwd_Search_Problem neg_search_prob(&transformed_s_problem_negative);
      float cost_of_goal_wo_observations = 0;

      // Perform search without observations
      if(!m_approximate_pr){
        do_pr_search(neg_search_prob, plan, cost_of_goal_wo_observations);
      }else{

        if(!m_negated_as_neutral){
          cost_of_goal_wo_observations = approximation_wo_delete_relax_break_sequence(transformed_s_problem_negative, observations, m_verbose);
        }else{
          heuristic_estimate(neg_search_prob, cost_of_goal_wo_observations, plan, observations);
        }
      }

      if(m_verbose && (!m_approximate_pr || m_negated_as_neutral)){
        std::cout << "\t\t\tPlan Without Observations: ";
        for(unsigned int j = 0; j < plan.size(); j++)
          std::cout << m_s_problem->actions()[plan[j]]->signature() << ",";
        std::cout << std::endl;
        std::cout << "\t\t\tTotal Cost Without Observations: " << cost_of_goal_wo_observations << std::endl;
        std::cout << std::endl;
      }
      plan.clear();

      if(m_verbose){
        std::cout << "\t\t\t[Delta Value: " << cost_of_goal_w_observations - cost_of_goal_wo_observations << "]"
          << std::endl << std::endl;
      }


      // Convert float infinity to int
      int cost_of_goal_w_observations_i;
      int cost_of_goal_wo_observations_i;
      if(cost_of_goal_w_observations == infty){
        cost_of_goal_w_observations_i = std::numeric_limits<int>::max();
      }else{
        cost_of_goal_w_observations_i = (int) cost_of_goal_w_observations;
      }
      if(cost_of_goal_wo_observations == infty){
        cost_of_goal_wo_observations_i = std::numeric_limits<int>::max();
      }else{
        cost_of_goal_wo_observations_i = (int) cost_of_goal_wo_observations;
      }

      delta_values.push_back(cost_of_goal_w_observations_i - cost_of_goal_wo_observations_i );
    }

    return delta_values;

  }

  std::vector<double> PlanRecognitionEngine::delta_values_to_probabilities( std::vector<int> delta_values, float beta ){

    std::vector<double> goal_cost_change;
    float sum = 0.0f;

    for(unsigned i = 0; i < delta_values.size(); i++){

      // Calculate liklihood
      double pOGin = 1.0f*beta*(delta_values[i]);
      double pOGinexp = exp(pOGin);
      double pOG = 1.0f/(1.0f + pOGinexp);
      double pOGpG = pOG*m_goal_set_priors[i];

      //if(m_verbose){
        //std::cout << i << ":\tprior: " << m_goal_set_priors[i] << std::endl;
        //std::cout <<  " \tpogin: " << pOGin << std::endl;
        //std::cout <<  " \tpoginexp: " << pOGinexp << std::endl;
        //std::cout <<  " \tpog: " << pOG << std::endl;
        //std::cout <<  " \tpogpg: " << pOGpG << std::endl;
      //}

      sum += pOGpG;

      goal_cost_change.push_back(pOGpG);
    }

    std::vector<double> posterior_probabilities;

    if (sum != 0){
      posterior_probabilities = normalize_vector(goal_cost_change);
    }else {
      for (unsigned i = 0; i < m_goal_set_priors.size(); i++)
        posterior_probabilities.push_back(m_goal_set_priors[i]);
    }

    if(m_verbose){
      for(unsigned int j = 0; j < posterior_probabilities.size(); j++){
        auto g = m_candidate_goal_set[j];
        for(unsigned k = 0; k < g.size(); k++){
          std::cout << "\t\t" << m_s_problem->fluents()[g[k]]->signature() << ",";
        }
        std::cout << ": ";
        std::cout << posterior_probabilities[j] << std::endl;
      }
      std::cout << std::endl;

    }

    return posterior_probabilities;
  }

 float PlanRecognitionEngine::find_new_beta(std::vector<int> delta_values, float initial_beta){
     int min_ele = *std::min_element( delta_values.begin(), delta_values.end() );

     if(min_ele > 0){
       return initial_beta / (1+min_ele);
       //return 0;
     } else {
       return initial_beta;
     }

  }

  void PlanRecognitionEngine::translate_problem(const aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& trans_prob,
      aptk::Fluent_Vec& w_observation, aptk::Fluent_Vec& wo_observation, std::map<std::string, unsigned int>& idx_to_trans_idx,
      std::vector<unsigned>& observations, std::vector<unsigned> init_state){

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
      if ( address == observations.begin() && observations.size() > 0){
        aptk::Fluent_Vec add = a->add_vec();
        aptk::Fluent_Vec del = a->del_vec();

        add.push_back(idx_to_trans_idx["pa" + std::to_string(observations[0])]);
        del.push_back(idx_to_trans_idx["npa" + std::to_string(observations[0])]);

        trans_prob.add_action(trans_prob, a->signature(), a->prec_vec(), add, del, a->ceff_vec(), a->cost());

      // Any actions corrosponding to any other observation add the corrospoding fluent only if the fluent corrosponding
      // to the observation immediately prior to this one has already been added.
      } else if (address != observations.end() && observations.size() > 0 ){
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

    if(observations.size() > 0){
      unsigned int w_back = w_observation.back();
      unsigned int wo_back = wo_observation.back();
      w_observation.clear();
      wo_observation.clear();
      w_observation.push_back((w_back));
      wo_observation.push_back((wo_back));
    }
    //std::cout << "w_observation: " << trans_prob.fluents()[w_observation[0]]->signature() << "\n";
    //std::cout << "wo_observation: " << trans_prob.fluents()[wo_observation[0]]->signature() << "\n";
  }

  void PlanRecognitionEngine::do_pr_search( Fwd_Search_Problem& search_prob,  std::vector< aptk::Action_Idx >& plan, float& cost) {

    //std::cout << "\t\tInitial State: ";
    //for(auto i : search_prob.init()->fluent_vec()){
      //std::cout << search_prob.task().fluents()[i]->signature() << ",";
    //}
    //std::cout << " | ";
    //for(auto i : search_prob.task().goal()){
      //std::cout << search_prob.task().fluents()[i]->signature() << ",";
    //}
    //std::cout << "\t\tActions: ";
    //for(auto i : search_prob.task().actions()){
      //std::cout << i->signature() << ",";
    //}
    //std::cout << std::endl;

    cost = infty;
    BFS_H_Max_Fwd engine( search_prob );
    engine.start();
    engine.find_solution( cost, plan );

  }

  void PlanRecognitionEngine::heuristic_estimate(Fwd_Search_Problem& search_prob,
      float& cost, std::vector<aptk::Action_Idx>& relaxed_plan, std::vector<unsigned>& observations){

    //std::cout << "\t\tInitial State: ";
    //for(auto i : search_prob.init()->fluent_vec()){
      //std::cout << m_s_problem->fluents()[i]->signature() << ",";
    //}
    //std::cout << " | ";
    //for(auto i : search_prob.task().goal()){
      //std::cout << m_s_problem->fluents()[i]->signature() << ",";
    //}
    //std::cout << "\t\tActions: ";
    //for(auto i : search_prob.task().actions()){
      //std::cout << i->signature() << ",";
    //}
    //std::cout << std::endl;


    //std::cout << std::endl;


    H_Add_Rp_Fwd h_ff(search_prob);
    //H_A_MAX_Fwd h_amax(search_prob, observations);

    Search_Node* root = new Search_Node( search_prob.init(), 0.0f,-1, NULL );
    std::vector<aptk::Action_Idx> pref_ops;
    h_ff.eval(*(root->state()), cost, pref_ops, relaxed_plan);
    //h_amax.eval(*(root->state()), cost);
  }

  void PlanRecognitionEngine::translate_problem_approx_pos(const aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& trans_prob,
      std::vector<unsigned>& observations, std::vector<unsigned> init_state){

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
      trans_prob.add_action(trans_prob, a->signature(), a->prec_vec(), a->add_vec(), a->del_vec(), a->ceff_vec(), a->cost());
    }

    // The effects of the actions corrosponding to the observations are made true in the initial state,
    // the number of observations is then added to the length of the relaxed plan.
    for(auto o : observations){
      const aptk::Action * a = prob.actions()[o];

      for (unsigned int i = 0; i < a->add_vec().size(); i++ ){
        init.push_back(a->add_vec()[i]);
      }
      for (unsigned int i = 0; i < a->del_vec().size(); i++){
        init.erase(std::remove( init.begin(), init.end(),a->del_vec()[i] ), init.end());
      }

    }

    // Set names and initial and goal states the same as
    trans_prob.set_domain_name(prob.domain_name());
    trans_prob.set_problem_name(prob.problem_name());
    trans_prob.set_init(trans_prob, init);
    trans_prob.set_goal(trans_prob, goal);

    trans_prob.make_action_tables();

  }

  float PlanRecognitionEngine::approximation_wo_delete_relax_break_sequence(aptk::STRIPS_Problem& trans_prob_neg,
      std::vector<unsigned> observations, bool verbose){

    float min(infty);
    std::vector<aptk::Action_Idx> min_plan;
    unsigned int min_index = 0;

    // The "NEXT" fluent is used to determine if the current action may be taken.
    unsigned next_index = trans_prob_neg.add_fluent(trans_prob_neg, "NEXT");

    // The true inial state is stored to reconstruct the problem
    auto true_init  (trans_prob_neg.init());

    // At present the code only allows for uniform cost actions
    // So the amount of observatons seen so far is added to the cost of the plan.
    int obs_count = 0;

    // The "NEXT" fluent is added to the add lists of all actions in the observation sequence.
    //for (unsigned o: observations){
      //auto a = trans_prob_neg.actions()[o];
      //a->add_vec().push_back(next_index);
    //}
    for (auto a : trans_prob_neg.actions()){
      a->add_vec().push_back(next_index);
    }

    if(m_verbose){
      std::cout << "\t\t\tPlan Without Observations:\n";
    }

    // For each observation a heurisitic value is taken and the minimum is returned.
    for (unsigned int i = 0; i < observations.size(); i++ ) {
      aptk::Action * a = trans_prob_neg.actions()[observations[i]];

      // The observation currently considered has the "NEXT" fluent added to its preconditions
      // This means that it may be used only after another observation.
      a->prec_vec().push_back(next_index);

      // The heuristic value of the problem is found
      Fwd_Search_Problem neg_search_prob(&trans_prob_neg);
      float neg_cost(0);
      std::vector<aptk::Action_Idx> plan;
      heuristic_estimate(neg_search_prob, neg_cost, plan, observations);
      //do_pr_search(neg_search_prob, plan, neg_cost);

      if (m_verbose){
        std::cout << "\t\t\t\tCost = " << neg_cost << ", Observation Cost = " << obs_count << std::endl;
      }

      // The action cost of the previous observations is added to the cost
      neg_cost += obs_count;

      // Action cost updated
      obs_count += a->cost();

      if (min > neg_cost){
        min = neg_cost;
        min_plan = plan;
        min_index = i;
      }
      plan.clear();

      // The "NEXT" fluent is removed as a precondition and an effect
      a->prec_vec().pop_back();
      //a->add_vec().pop_back();

      // The initial state is progressed through the considered action
      aptk::State root( trans_prob_neg);
      root.set(trans_prob_neg.init() );

      aptk::State* next_root = root.progress_through(*a);
      STRIPS_Problem::set_init(trans_prob_neg, next_root->fluent_vec());

    }

    if (observations.size() == 0){
      Fwd_Search_Problem neg_search_prob(&trans_prob_neg);
      float neg_cost(0);
      std::vector<aptk::Action_Idx> plan;
      heuristic_estimate(neg_search_prob, neg_cost, plan, observations);
      min = neg_cost;
      min_plan = plan;
      min_index = 0;
    }

    if(m_verbose){
      std::cout << "\t\t\t\tRelaxed Plan Found: ";
      for(unsigned j = 0; j < min_index; j++)
        std::cout << m_s_problem->actions()[observations[j]]->signature() << ",";
      std::cout << " | ";
      for(unsigned j = 0; j < min_plan.size(); j++)
        std::cout << m_s_problem->actions()[min_plan[j]]->signature() << ",";
      std::cout << std::endl;
      std::cout << "\t\t\tTotal Cost Without Observations: " << min << std::endl;
      std::cout << std::endl;
    }

    for (auto a : trans_prob_neg.actions()){
      a->add_vec().pop_back();
    }

    // The initial state of the problem is reset
    STRIPS_Problem::set_init(trans_prob_neg,true_init);

    return min;
  }

}
