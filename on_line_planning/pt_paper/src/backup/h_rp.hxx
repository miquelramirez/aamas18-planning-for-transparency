/*
 *Project: Planning for Recognizability
 *Author: Aleck MacNally
 *-------------------------------------
 */

#ifndef __H_RP__
#define __H_RP__

#include <aptk/search_prob.hxx>
#include <aptk/heuristic.hxx>
#include <strips_state.hxx>
#include <strips_prob.hxx>
#include "plan_recognition.hxx"

using namespace pr;

namespace aptk {

namespace agnostic {

template < typename Search_Model >
class	Plan_Recognition_Heuristic : public Heuristic<State> {
public:

	Plan_Recognition_Heuristic( const Search_Model& prob)
	: Heuristic<State>( prob ), m_strips_model( prob.task() ), m_index(0){

    /*
    *Find the index of the goal of the search model in the set of goals
    */
    std::vector<unsigned> true_goal_v = m_strips_model.goal();
    std::set<unsigned> true_goal(true_goal_v.begin(), true_goal_v.end());
    for (unsigned int i = 0; i < m_strips_model.goal_set(m_strips_model).size(); i++){

      std::vector<unsigned> cand_goal_v = m_strips_model.goal_set(m_strips_model)[i];
      std::set<unsigned> cand_goal (cand_goal_v.begin(), cand_goal_v.end());
      if (cand_goal == true_goal){
        m_index = i;
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

    std::vector<aptk::Fluent_Vec> goal_set = m_strips_model.goal_set(m_strips_model);
    std::vector<double> priors = m_strips_model.priors(m_strips_model);
    float beta = m_strips_model.beta(m_strips_model);
    aptk::Fluent_Vec init = m_strips_model.init();
    std::vector<unsigned int> observations = m_strips_model.m_top_level_observations;

    bool negated_as_neutral = m_strips_model.m_negated_as_neutral;
    bool variable_beta = m_strips_model.m_variable_beta;
    bool pr_verbose = m_strips_model.m_pr_verbose;
    bool approximate_pr = !m_strips_model.m_optimal;

    //if (n->parent() == NULL){
      //float ambiguity  = -1 * quantify_prob_distribution(posteriors, observations.size());
      //float round_ambiguity = round( ambiguity  * pow(10, m_strips_model.m_precision) );

      //h_val = round_ambiguity;

      ////h_val = goal_set.size() + (1 - priors[m_index]);
      ////std::cout << "Rank: " << h_val << std::endl;
      ////if (bu_approx){
        ////n->set_og(priors);
      ////}
      //return;
    //}

    /*
    *Get observations, set priors if necessary.
    */
    //if (bu_approx){
      //observations.push_back(n->action());
      //priors = n->parent()->og();
    //}else

    get_observations<Search_Node>(n, observations);

    /*
     *std::cout << "Observations: " << std::endl;
     *for (unsigned int i = 0; i < observations.size(); i++){
     *  std::cout << observations[i] << ": " << m_strips_model.actions()[observations[i]]->signature() << std::endl;
     *}
     */

    /*
    *Do plan recognition to produce posteriors
    */
    //if (bu_approx){

      //if (h_approx)
        //posteriors =  plan_recognition_approx(m_strips_model, goal_set, priors, observations, \
            //n->parent()->state()->fluent_vec(), beta, h_approx, diff_plan_rec, verbose);
      //else
        //posteriors =  plan_recognition(m_strips_model, goal_set, priors, observations, \
            //n->parent()->state()->fluent_vec(), beta,true, diff_plan_rec, verbose);

      //n->set_og(posteriors);
    //} else
    //{
    //if (h_approx)
      //posteriors =  plan_recognition_approx(m_strips_model, goal_set, priors, observations, init, beta, h_approx,diff_plan_rec, verbose);
    //else
      //posteriors =  plan_recognition(m_strips_model, goal_set, priors, observations, init, beta,true, diff_plan_rec, verbose);
    //}


    /* Markovian Limitation */
    if(prob.m_markov){
      std::vector<unsigned int> o = {observations.back()};







    }
    /*----------------------*/

    PlanRecognitionEngine pr(&m_strips_model, goal_set, priors, approximate_pr, negated_as_neutral, variable_beta, pr_verbose, total_delta);

    std::vector<double> posteriors = pr.plan_recognition(observations, init, beta);

/*
 *    bool diff_plan_rec =false;
 *    bool verbose =true;
 *    bool optimal =false;
 *    bool true_optimal = true;
 *    int approx = 3;
 *    std::pair<std::vector<double>, std::vector<int>> posteriors_pair;
 *    std::vector<int> adj_diff_cost;
 *    if(observations.size() > 0){
 *      [> CHANGING BETA BASED UPON RATIONALITY <]
 *      if(optimal)
 *        posteriors_pair =  plan_rec_helper(m_strips_model, goal_set, priors, observations, init, beta, true_optimal, diff_plan_rec, verbose);
 *      else
 *        posteriors_pair =  plan_rec_helper_approx(m_strips_model, goal_set, priors, observations, init, beta, approx, diff_plan_rec, verbose);
 *
 *      adj_diff_cost = posteriors_pair.second;
 *    }else{
 *      for(auto i : priors)
 *        adj_diff_cost.push_back(0);
 *    }
 *
 *
 *
 *    int min_ele = *std::min_element( adj_diff_cost.begin(), adj_diff_cost.end() );
 *
 *    if(min_ele > 0){
 *      n->m_beta = n->m_beta / min_ele;
 *    }
 *
 *    float sum = 0;
 *    std::vector<double> goal_cost_change;
 *
 *    for(unsigned i = 0; i < adj_diff_cost.size(); i++){
 *
 *      // Calculate liklihood
 *      const float pOGin = 1.0f*(n->m_beta)*(adj_diff_cost[i]);
 *      const float pOGinexp = exp(pOGin);
 *      const float pOG = 1.0f/(1.0f + pOGinexp);
 *      const float pOGpG = pOG*priors[i];
 *
 *      if(verbose){
 *        std::cout << i << ":\tprior: " << priors[i] << std::endl;
 *        std::cout <<  " \tpogin: " << pOGin << std::endl;
 *        std::cout <<  " \tpoginexp: " << pOGinexp << std::endl;
 *        std::cout <<  " \tpog: " << pOG << std::endl;
 *        std::cout <<  " \tpogpg: " << pOGpG << std::endl;
 *      }
 *
 *      sum += pOGpG;
 *
 *      goal_cost_change.push_back(pOGpG);
 *    }
 *
 *
 *    std::vector<double> normv;
 *
 *    if (sum != 0){
 *      normv = normalize_vector(goal_cost_change);
 *
 *      if(verbose){
 *        print_vector(normv);
 *      }
 *
 *    }else {
 *        for (unsigned i = 0; i < priors.size(); i++)
 *          normv.push_back(priors[i]);
 *    }
 *
 *    std::vector<double> posteriors = normv;
 *
 *    // -----------------------------------------------------------------------------------
 */


    float ambiguity  = -1 * quantify_prob_distribution(posteriors, observations.size());
    float average_ambiguity;
    float round_ambiguity = round( ambiguity  * pow(10, m_strips_model.m_precision) );

    if (!n->parent())
      average_ambiguity = round_ambiguity;
    else{
      average_ambiguity = round( (( n->parent()->m_h2 * n->parent()->m_g ) + round_ambiguity) / n->m_g );
    }

    //odds(posteriors);

    //std::cout << "Posteriors: " << std::endl;
    //print_vector(posteriors);

    /*
    *Count the number of goals with greater posterior than the goal
    */

    //rank = modified_ranking_strategy(m_index, posteriors);
    //rank = binary_ranking_strategy(m_index, posteriors);

    //std::cout << "Rank: " << rank << std::endl << std::endl;
    //std::cout << "Length: " << observations.size() << std::endl;

    /*
    *Set heuristic value.
    */
    //h_val = 1 - posteriors[m_index];
    h_val = average_ambiguity;// + (1 - posteriors[m_index]);
    //std::cout << "\t\tActions: ";

    //for (unsigned int i = 0; i < observations.size(); i++){
      //std::cout << m_strips_model.actions()[observations[i]]->signature() << ",";
    //}

    //std::cout << " AvAmbiguity: " << h_val << ", CurAmbiguity: " << ambiguity << ", Beta: " << n->m_beta  << std::endl;
    //n->m_g += rank; //binary_ranking_strategy(m_index, posteriors);

  }

protected:

	const STRIPS_Problem&	m_strips_model;
	unsigned int m_index;
  std::vector<double> m_perfect_dist;

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

  int modified_ranking_strategy(int index, std::vector<double> posteriors){
    int rank = 1;
    for (unsigned int i = 0; i < posteriors.size(); i++){
      if (index != i)
        if (posteriors[i] >= posteriors[index])
          rank++;
    }

    return rank;
  }

  int binary_ranking_strategy(int index, std::vector<double> posteriors){
    int rank = 0;

    for (unsigned int i = 0; i < posteriors.size(); i++){
      if (index != i){
        if(posteriors[i] > posteriors[index]){
          rank = infty;
          break;
        } else if (posteriors[i] == posteriors[index]){
          rank = 1;
          break;
        }
      }
    }

    return rank;
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
