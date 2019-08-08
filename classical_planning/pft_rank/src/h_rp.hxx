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
#include "planrec.hxx"

namespace aptk {

namespace agnostic {

template < typename Search_Model, bool bu_approx, unsigned h_approx >
/*
*bu_approx: Baysian Update approximation
*h_approx: Root-Node Heuristic approximation
*/
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

	}

	virtual ~Plan_Recognition_Heuristic() {
	}

  template <typename Search_Node>
  void eval( Search_Node* n, float& h_val) {

    std::vector<aptk::Fluent_Vec> goal_set = m_strips_model.goal_set(m_strips_model);
    std::vector<double> priors = m_strips_model.priors(m_strips_model);
    float beta = m_strips_model.beta(m_strips_model);
    float rank = 1;
    std::vector<double> posteriors;
    aptk::Fluent_Vec init = m_strips_model.init();
    std::vector<unsigned int> observations;

    if (n->parent() == NULL){
      h_val = goal_set.size() + (1 - priors[m_index]);
      //std::cout << "Rank: " << h_val << std::endl;
      if (bu_approx){
        n->set_og(priors);
      }
      return;
    }

    /*
    *Get observations, set priors if necessary.
    */
    if (bu_approx){
      observations.push_back(n->action());
      priors = n->parent()->og();
    }else
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
    if (bu_approx){

      if (h_approx)
        posteriors =  plan_recognition_approx(m_strips_model, goal_set, priors, observations, \
            n->parent()->state()->fluent_vec(), beta, h_approx);
      else
        posteriors =  plan_recognition(m_strips_model, goal_set, priors, observations, \
            n->parent()->state()->fluent_vec(), beta,true);

      n->set_og(posteriors);
    } else
      if (h_approx)
        posteriors =  plan_recognition_approx(m_strips_model, goal_set, priors, observations, init, beta, h_approx);
      else
        posteriors =  plan_recognition(m_strips_model, goal_set, priors, observations, init, beta,true);

    //odds(posteriors);

    //std::cout << "Posteriors: " << std::endl;
    //print_vector(posteriors);

    /*
    *Count the number of goals with greater posterior than the goal
    */

    rank = modified_ranking_strategy(m_index, posteriors);
    //rank = binary_ranking_strategy(m_index, posteriors);

    //std::cout << "Rank: " << rank << std::endl << std::endl;
    //std::cout << "Length: " << observations.size() << std::endl;

    /*
    *Set heuristic value.
    */
    //h_val = 1 - posteriors[m_index];
    h_val = rank + (1 - posteriors[m_index]);
    n->m_g += rank; //binary_ranking_strategy(m_index, posteriors);

  }

protected:

	const STRIPS_Problem&	m_strips_model;
	unsigned int m_index;

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

};

}

}

#endif
