
#include <map>
#include <algorithm>

#include <strips_prob.hxx>
#include <fluent.hxx>
#include <action.hxx>
#include <cond_eff.hxx>

#include "gd.hxx"
#include "dalandmarks.hxx"
#include "utility.hxx"

using namespace dalm;

namespace gd{

  goal_distance_calculator::goal_distance_calculator(aptk::STRIPS_Problem& p,
      std::vector<Goal> goal_set): m_prob(p), m_goal_set(goal_set) {

    for(unsigned int i = 0; i < m_goal_set.size(); i++){
      DALandmarkGenerator d_g(&m_prob, m_goal_set[i]);
      m_goal_landmarks[m_goal_set[i]] = d_g.landmarks();
    }
  }

  double goal_distance_calculator::goal_distance(Goal g1, Goal g2){

    double sum = 0;


    for(unsigned int i = 0; i < m_goal_landmarks[g1].size(); i++){

      double min_distance = infty;

      for(unsigned j = 0; j < m_goal_landmarks[g2].size(); j++){

        double current_lm_dist_fw = landmark_distance(m_goal_landmarks[g1][i], m_goal_landmarks[g2][j]);
        double current_lm_dist_bw = landmark_distance(m_goal_landmarks[g2][j], m_goal_landmarks[g1][i]);
        double current_lm_dist = (current_lm_dist_bw + current_lm_dist_fw) / 2;

        if(current_lm_dist < min_distance){
          min_distance = current_lm_dist;
        }

      }

      sum += min_distance;
    }

    return sum / ((double) m_goal_landmarks[g1].size() + m_goal_landmarks[g2].size());
  }

  double goal_distance_calculator::landmark_distance(Landmark l1, Landmark l2){

    sort(l1.begin(), l1.end());
    sort(l2.begin(), l2.end());

    Landmark l_s_d;
    set_symmetric_difference(l1.begin(), l1.end(),
                             l2.begin(), l2.end(), std::back_inserter(l_s_d));

    double sum = 0;

    for(auto a_i : l_s_d){
      auto a = m_prob.actions()[a_i];
      sum += a->cost();
    }

    sum = sum / ((double) l1.size() + l2.size());

    return sum;

  }

  double goal_distance_calculator::complete_goal_distance(){

    std::vector<double> goal_distances;

    for(unsigned int i = 0; i < m_goal_set.size(); i++){
      for(unsigned int j = 0; j < m_goal_set.size(); j++){
        if(i > j){
          double d = goal_distance(m_goal_set[i], m_goal_set[j]);
          goal_distances.push_back(d);

          for (auto a : m_goal_set[i]){
            std::cout << m_prob.fluents()[a]->signature()  << ", ";
          }
          std::cout << " --- ";
          for (auto a : m_goal_set[j]){
            std::cout << m_prob.fluents()[a]->signature()  << ", ";
          }
          std::cout << ": " << d << std::endl;
        }


      }

    }

    double average = ((double)std::accumulate(goal_distances.begin(), goal_distances.end(), 0.0f)) / ((double)goal_distances.size());

    return average;
  }

}
