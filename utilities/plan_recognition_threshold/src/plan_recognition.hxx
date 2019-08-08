#ifndef PLAN_RECOGNITION_H
#define PLAN_RECOGNITION_H

#include <strips_prob.hxx>
#include <action.hxx>
#include <fwd_search_prob.hxx>

using aptk::agnostic::Fwd_Search_Problem;

namespace pr {

  class PlanRecognitionEngine
  {

  public:
    PlanRecognitionEngine(const aptk::STRIPS_Problem * problem, std::vector< std::vector<unsigned int> > candidate_goal_set,
        std::vector<double> goal_set_priors, bool approximate_pr, bool negated_as_neutral,
        bool variable_beta, bool verbose)
      : m_s_problem(problem), m_candidate_goal_set(candidate_goal_set), m_goal_set_priors(goal_set_priors),
      m_approximate_pr(approximate_pr), m_negated_as_neutral(negated_as_neutral),
      m_variable_beta(variable_beta), m_verbose(verbose)
    {
    }
      ;

    virtual ~PlanRecognitionEngine(){};

    std::vector<double> plan_recognition(std::vector<unsigned int> observations, aptk::Fluent_Vec& initial_state,
        float initial_beta);
    std::vector<int> find_delta_values(std::vector<unsigned int> observations, aptk::Fluent_Vec& initial_state);
    std::vector<double> delta_values_to_probabilities(std::vector<int> delta_values, float beta);

    void set_verbose(float verbose){ m_verbose = verbose; }
    void set_approximate_pr(bool a_pr){ m_approximate_pr = a_pr; }
    void set_negated_as_neutral(bool n_a_n){ m_negated_as_neutral = n_a_n; }
    void set_variable_beta(bool v_b){ m_variable_beta = v_b; }
    void set_goal_set(std::vector<std::vector<unsigned int>> g){m_candidate_goal_set = g;}

    std::vector<std::vector<unsigned int>> goal_set(){return m_candidate_goal_set;}

    void do_pr_search(Fwd_Search_Problem& search_prob,  std::vector< aptk::Action_Idx >& plan, float& cost);
    void heuristic_estimate(Fwd_Search_Problem& search_prob, float& cost,
        std::vector<aptk::Action_Idx>& relaxed_plan, std::vector<unsigned>& observations);
  private:
    void translate_problem(const aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& trans_prob, aptk::Fluent_Vec& w_observation,
        aptk::Fluent_Vec& wo_observation, std::map<std::string, unsigned int>& idx_to_trans_idx, std::vector<unsigned>& observations,
        std::vector<unsigned int> init_state);
    void translate_problem_approx_pos(const aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& trans_prob,
        std::vector<unsigned>& observations, std::vector<unsigned> init_state);
    float approximation_wo_delete_relax_break_sequence(aptk::STRIPS_Problem& trans_prob_neg,
        std::vector<unsigned> observations, bool verbose = false);
    float find_new_beta(std::vector<int> deltas, float initial_beta);

    template<
        typename T,
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
      >
    std::vector<double> normalize_vector(std::vector<T> v){
      std::vector<double> n_v;
      double sum =  (double) std::accumulate(v.begin(), v.end(), (T) 0);

      for(T e : v){
        n_v.push_back( ((double) e) / sum);
      }

      return n_v;
    }

    template<class T>
    void print_vector(std::vector<T> v){
      for (unsigned int i = 0; i <  v.size(); i++){
        std::cout << i << ": " << std::to_string(v[i]) << std::endl;
      }
    }

    void print_plan_to_cout(std::vector< int >& plan, Fwd_Search_Problem& search_prob){
      for ( unsigned k = 0; k < plan.size(); k++ ) {
        const aptk::Action& a = *(search_prob.task().actions()[ plan[k] ]);
        std::cout  << a.signature() << ": ";
        for (auto f: a.prec_vec()){
          std::cout << search_prob.task().fluents()[f]->signature() << ", ";
        }

        std::cout << std::endl;
      }
    }


  private:
    const aptk::STRIPS_Problem * m_s_problem;
    std::vector< std::vector<unsigned int> > m_candidate_goal_set;
    std::vector<double> m_goal_set_priors;

    bool m_approximate_pr;
    bool m_negated_as_neutral;
    bool m_variable_beta;
    bool m_verbose;
  };

}

#endif /* PLAN_RECOGNITION_H */
