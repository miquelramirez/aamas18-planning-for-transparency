
#ifndef LM_PLAN_RECOGNITION_H
#define LM_PLAN_RECOGNITION_H

#include <strips_prob.hxx>
#include <action.hxx>
#include <landmark_graph.hxx>
#include <landmark_graph_manager.hxx>
#include <landmark_graph_generator.hxx>

#include <tuple>

using aptk::agnostic::Fwd_Search_Problem;
using Goal_set = std::vector<std::vector<unsigned int>>;
using Goal = std::vector<unsigned int>;

using aptk::agnostic::Landmarks_Graph;
using aptk::agnostic::Landmarks_Graph_Generator;

namespace pr_lm {

  class PlanRecognitionEngine_LM {

  public:
    typedef aptk::agnostic::Landmarks_Graph_Manager<Fwd_Search_Problem> Landmarks_Graph_Manager;
    typedef aptk::agnostic::Landmarks_Graph Landmarks_Graph;

    PlanRecognitionEngine_LM(aptk::STRIPS_Problem * s_prob, Goal_set goal_set, double theta, bool verbose);
    virtual ~PlanRecognitionEngine_LM(){}

    std::vector<double> plan_recognition(std::vector<unsigned int> observations);
    std::map<Goal, double> heuristic(std::vector<unsigned int> observations);

  //private:
    std::map<Goal, double> goal_percent_complete_lm(
        aptk::STRIPS_Problem& s_prob, Goal_set& goal_set, std::vector<unsigned int> observations, double theta);
    std::vector<unsigned int> extract_landmarks(aptk::STRIPS_Problem& s_prob, Goal& g, bool verbose);
    std::tuple<std::vector<unsigned int>, std::vector<unsigned int>, std::vector<unsigned int>>
      partition_facts(aptk::STRIPS_Problem& s_prob, std::vector<unsigned int>& land_marks);
    std::vector<unsigned int> extract_fluents_from_graph(Landmarks_Graph& lm);

  private:
    aptk::STRIPS_Problem*     m_strips_model;
    Goal_set                  m_goal_set;
    double m_theta;
    bool m_verbose;

  };
}

#endif /* LM_PLAN_RECOGNITION_H */
