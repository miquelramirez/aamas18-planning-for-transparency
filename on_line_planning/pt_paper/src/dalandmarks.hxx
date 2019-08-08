#ifndef DALANDMARKS_H
#define DALANDMARKS_H

/* Purpose: Generator for LM-Cut disjunctive action landmarks */
#include <map>
#include <vector>

#include <strips_prob.hxx>
#include <h_1.hxx>
#include <fwd_search_prob.hxx>

#include "utility.hxx"

using	aptk::agnostic::Fwd_Search_Problem;

using aptk::agnostic::H1_Heuristic;
using	aptk::agnostic::H_Max_Evaluation_Function;

typedef	H1_Heuristic<Fwd_Search_Problem, H_Max_Evaluation_Function>	H_Max;

using Action_Idx = int;
using Fluent_Idx = int;
using Landmark = std::vector<Action_Idx>;

namespace dalm{
  class DALandmarkGenerator
  {

    public:

      DALandmarkGenerator(aptk::STRIPS_Problem * s_p, const std::vector<unsigned int> goal)
      {
        m_strips_model = new aptk::STRIPS_Problem();
        clone_problem(*s_p, *m_strips_model, s_p->init());
        aptk::STRIPS_Problem::set_goal(*m_strips_model, goal);

        Fwd_Search_Problem search_prob(m_strips_model);

        m_h_max = new H_Max(search_prob);
        construct_justified_graph();
        extract_landmarks();
      }

      virtual ~DALandmarkGenerator(){
        delete m_h_max;
        delete m_strips_model;
      };

      void construct_justified_graph();
      void extract_landmarks();
      std::vector<Landmark> extract_landmarks_helper(std::vector<Fluent_Idx> gs, float cost_accumulation);
      std::vector<std::vector<Action_Idx>> landmarks(){return m_landmark_vector;}
      void print_landmarks();

    private:
      std::map<Fluent_Idx, std::vector<Fluent_Idx>> m_just_graph;
      std::map<std::pair<Fluent_Idx, Fluent_Idx>,Action_Idx> m_edge_action;
      std::map<Action_Idx, Fluent_Idx> m_a_best_p;
      Fluent_Idx m_relaxed_goal;
      std::vector<Landmark> m_landmark_vector;
      aptk::STRIPS_Problem * m_strips_model;
      H_Max * m_h_max;
      float m_init_h;

  };
}

#endif /* DALANDMARKS_H */
