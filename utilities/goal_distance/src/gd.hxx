#ifndef GD_H
#define GD_H

#include <map>
#include <vector>

#include <strips_prob.hxx>
#include <h_1.hxx>
#include <fwd_search_prob.hxx>

#include "utility.hxx"

namespace gd{

using Action_Idx = int;
using Fluent_Idx = int;
using Landmark = std::vector<Action_Idx>;
using Goal = std::vector<unsigned int>;

  class goal_distance_calculator
  {
    private:
      aptk::STRIPS_Problem& m_prob;
      std::vector<Goal> m_goal_set;
      std::map<Goal, std::vector<Landmark>> m_goal_landmarks;
      double landmark_distance(Landmark g1, Landmark g2);

    public:
      goal_distance_calculator(aptk::STRIPS_Problem& p, std::vector<Goal> goal_set);
      virtual ~goal_distance_calculator(){};

      double goal_distance(Goal g1, Goal g2);
      double complete_goal_distance();
  };

}

#endif /* GD_H */
