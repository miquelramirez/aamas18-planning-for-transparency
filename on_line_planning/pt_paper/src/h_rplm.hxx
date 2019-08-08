/* Plan recognition heuristic */

#ifndef __H_RP_LM__
#define __H_RP_LM__

#include <aptk/search_prob.hxx>
#include <aptk/heuristic.hxx>
#include <strips_state.hxx>
#include <strips_prob.hxx>
#include "lm_plan_recognition.hxx"
#include "plan_recognition.hxx"

namespace aptk {

namespace agnostic {

template < typename Search_Model >
class	Plan_Recognition_Heuristic : public Heuristic<State> {
public:

	Plan_Recognition_Heuristic( const Search_Model& prob)
	  : Heuristic<State>( prob ), m_strips_model(prob.task()), m_index(0),
	  m_filter(m_strips_model.m_filter), m_landmark(m_strips_model.m_landmark),
    m_pr_lm(&m_strips_model, m_strips_model.goal_set(m_strips_model), m_strips_model.m_theta, m_strips_model.m_pr_verbose, m_strips_model.priors(m_strips_model)),
    m_pr(&m_strips_model, m_strips_model.goal_set(m_strips_model), m_strips_model.priors(m_strips_model),
        !m_strips_model.m_optimal, m_strips_model.m_negated_as_neutral, m_strips_model.m_variable_beta, m_strips_model.m_pr_verbose)
	{
    /*
    *Find the index of the goal of the search model in the set of goals
    */
    std::vector<unsigned> true_goal_v = m_strips_model.goal();
    std::set<unsigned> true_goal(true_goal_v.begin(), true_goal_v.end());
    //std::cout << "True Goal: " << print_fluent_vec(m_strips_model, true_goal_v) << std::endl;
    for (unsigned int i = 0; i < m_strips_model.goal_set(m_strips_model).size(); i++){

      std::vector<unsigned> cand_goal_v = m_strips_model.goal_set(m_strips_model)[i];
      std::set<unsigned> cand_goal (cand_goal_v.begin(), cand_goal_v.end());
      //std::cout << "Candidate Goal: " << print_fluent_vec(m_strips_model, cand_goal_v) << std::endl;
      if (cand_goal == true_goal){
        m_index = i;
        //std::cout << "This One!!!" << std::endl;
        break;
      }

    }

    /*
    * Produce perfect distribution.
    */
    for (unsigned int i = 0; i < m_strips_model.goal_set(m_strips_model).size(); i++)
      if (i == m_index)
        m_perfect_dist.push_back(1.0);
      else
        m_perfect_dist.push_back(0.0);

	}

	virtual ~Plan_Recognition_Heuristic() {
	}

  template <typename Search_Node>
  void eval( Search_Node* n, float& h_val) {

    n->m_goal_index = m_index;

    float beta = m_strips_model.beta(m_strips_model);
    aptk::Fluent_Vec init = m_strips_model.m_true_init;
    std::vector<unsigned int> full_observations = m_strips_model.m_top_level_observations;
    std::vector<unsigned int> observations;

    get_observations<Search_Node>(n, full_observations);

    /*Markovian Limitation:*/
    if(m_strips_model.m_markov){
      if(n->parent()){

        m_pr.set_goal_set_priors(n->parent()->state()->get_bs());
        init = n->parent()->state()->fluent_vec();

        if(n->action() > 0)
        {
          observations = {n->action()};
        }else{
          observations = full_observations;
        }
      }

    }else{
      observations = full_observations;
    }
    /*_____________________*/

    std::vector<double> posteriors;
    if(m_landmark)
      posteriors = m_pr_lm.plan_recognition(observations);
    else if (m_filter){
      std::map<std::vector<unsigned>, double> filter = m_pr_lm.goal_filtering(observations);
      auto old_goal_set = m_pr.goal_set();
      std::vector<std::vector<unsigned>> new_goal_set;
      std::vector<unsigned> filtered_indices;

      for (unsigned int i = 0; i < old_goal_set.size(); i++){
        if(filter[old_goal_set[i]] != -1){
          new_goal_set.push_back(old_goal_set[i]);
        }else{
          filtered_indices.push_back(i);
        }
      }

      m_pr.set_goal_set(new_goal_set);
      posteriors = m_pr.plan_recognition(observations, init, beta, n->m_total_delta,
          n->m_best_negated_obs_rel_plan, n->m_best_negated_obs_plan, n->m_best_negated_obs_cost, full_observations);

      for(unsigned p : filtered_indices){
        posteriors.insert(posteriors.begin() + p, 0.0f);
      }

      m_pr.set_goal_set(old_goal_set);

    } else{
      posteriors = m_pr.plan_recognition(observations, init, beta, n->m_total_delta,
          n->m_best_negated_obs_rel_plan, n->m_best_negated_obs_plan, n->m_best_negated_obs_cost, full_observations);

    }
    // TODO: When do we round posteriors????

    std::vector<double> rounded_post;

    for (double p : posteriors){
      double rounded_p = round(p * pow(10, m_strips_model.m_precision)) / pow(10, m_strips_model.m_precision);
      rounded_post.push_back(rounded_p);
    }

    n->m_post = rounded_post;
    n->state()->set_bs(n->m_post);
    n->state()->update_hash();

    float ambiguity  = -1 * quantify_prob_distribution(rounded_post, observations.size());
    float average_ambiguity;
    float round_ambiguity = round( ambiguity  * pow(10, m_strips_model.m_precision) );
    ambiguity = round_ambiguity;

    if (!n->parent())
      average_ambiguity = round_ambiguity;
    else{
      average_ambiguity = round( (( n->parent()->m_h2 * n->parent()->m_g ) + round_ambiguity) / n->m_g );
    }


    /* Print Out */
    bool heuristic_verbose = m_strips_model.m_h_verbose;
    if(heuristic_verbose){

      std::cout << "C_amb: " <<  ambiguity << ", Av_amb: " << average_ambiguity << ", State: " << n->state() << ", BState: " << vector_as_string(n->state()->belief_state(), ", ")<< " | " << "index: " << n->m_goal_index << " | " ;


      std::cout << "Prior: ";
      for ( int i = 0; i < ( (int)m_pr.m_goal_set_priors.size()  )- 1; i++){
        std::cout << m_pr.m_goal_set_priors[i] << ", ";
      }
      if(m_pr.m_goal_set_priors.size() > 0)
        std::cout << m_pr.m_goal_set_priors.back() << " | ";
      else
        std::cout << " | ";

      if(n->m_total_delta > 0)
        std::cout << "Beta: " << m_strips_model.beta(m_strips_model) / pow(n->m_total_delta+1,1) << " | ";
      else
        std::cout << "Beta: " << m_strips_model.beta(m_strips_model)<< " | ";

      std::cout << " Post: ";
      for ( int i = 0; i < ( (int)n->state()->belief_state().size()  )- 1; i++){
        std::cout << n->state()->belief_state()[i] << ", ";
      }
      if(n->state()->belief_state().size() > 0)
        std::cout << (n->state()->belief_state().back())  << " | ";
      else
        std::cout << " | ";

      for ( int i = 0; i < ( (int)full_observations.size() ) - 1; i++){
        std::cout << m_strips_model.actions()[full_observations[i]]->signature() << ", ";
      }
      if(full_observations.size() > 0)
        std::cout << m_strips_model.actions()[full_observations.back()]->signature() << std::endl;
      else
        std::cout << std::endl;
    }

    /*-----------*/

    h_val = average_ambiguity;

  }

protected:

	const STRIPS_Problem&	m_strips_model;
	unsigned int m_index;
  std::vector<double> m_perfect_dist;
  bool m_filter;
  bool m_landmark;

  pr_lm::PlanRecognitionEngine_LM m_pr_lm;
  pr::PlanRecognitionEngine m_pr;

  /*
  *Recursively pull the observations from a node
  */
  template <typename Search_Node>
  void get_observations(const Search_Node* n, std::vector<unsigned>& acc){
    if(n->parent() == NULL)
      return;
    get_observations(n->parent(), acc);
    acc.push_back(n->action());

  }

  void  odds(std::vector<double>& p){
    for (unsigned i = 0; i < p.size(); i++){
      p[i] = p[i] == 1 ? infty : p[i] / (1 - p[i]);
    }
  }

  double quantify_prob_distribution(std::vector<double> posteriors, unsigned int length){
    double discount_factor;
    double distance;

    if (m_strips_model.get_df()== 0){
      if (length == 0){
        discount_factor = 1;
      } else {
        discount_factor = infty;
      }
    } else {
      discount_factor = pow(1/m_strips_model.get_df(), length);
    }

    distance = hellinger_distance(m_perfect_dist, posteriors);

    return discount_factor*distance;
  }

  double hellinger_distance(const std::vector<double> P, const std::vector<double> Q){
    assert(P.size() == Q.size());

    double h_d_2 = 0.0;

    for (unsigned int i = 0; i < P.size(); i++)
    {
      double p_q_i = P[i] - Q[i];
      h_d_2 += p_q_i*p_q_i;
    }

    // Heuristic is positive because smaller is better
    return -1*sqrt(h_d_2);

}



};
}
}

#endif
