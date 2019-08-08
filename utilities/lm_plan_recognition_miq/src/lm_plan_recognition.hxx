
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
using aptk::agnostic::Landmarks_Graph_Manager;

namespace pr_lm {

  class PlanRecognitionEngine_LM {

  public:
    typedef aptk::agnostic::Landmarks_Graph_Manager<Fwd_Search_Problem> Landmarks_Graph_Manager;
    typedef aptk::agnostic::Landmarks_Graph Landmarks_Graph;

    PlanRecognitionEngine_LM(aptk::STRIPS_Problem * s_prob, Goal_set goal_set, double theta, bool verbose);
    PlanRecognitionEngine_LM(aptk::STRIPS_Problem const * s_prob, Goal_set goal_set, double theta, bool verbose);
    virtual ~PlanRecognitionEngine_LM();

    std::vector<double> plan_recognition(std::vector<unsigned int> observations);
    std::map<Goal, double> heuristic(std::vector<unsigned int> observations);
    Goal_set goal_set(){return m_goal_set;}

  //private:
    std::map<Goal, double> goal_filtering(std::vector<unsigned int> observations);
    double percentage_complete_lm(Goal g, unsigned int f, std::vector<unsigned int> observations);
    std::vector<unsigned int> extract_landmarks(aptk::STRIPS_Problem& s_prob, Goal& g, bool verbose);
    std::tuple<std::vector<unsigned int>, std::vector<unsigned int>, std::vector<unsigned int>>
      partition_facts(aptk::STRIPS_Problem& s_prob, std::vector<unsigned int>& land_marks);
    std::vector<unsigned int> extract_fluents_from_graph(Landmarks_Graph& lm);
    void update_graph(std::vector<unsigned int> observations);
    void generate_landmarks_graphs();

    template<class T>
    std::vector<T> instersection(std::vector<T> &v1, std::vector<T> &v2){

        std::vector<T> v3;

        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());

        std::set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));

        return v3;
    }


  private:
    aptk::STRIPS_Problem * m_strips_model;
    Goal_set m_goal_set;
    std::map<Goal, Landmarks_Graph_Manager * > m_lgm_v;

    double m_theta;
    bool m_verbose;

  };
}

#endif /* LM_PLAN_RECOGNITION_H */
