#include <iostream>
#include <fstream>
#include <map>
#include <ctype.h>

#include <strips_prob.hxx>
#include <fluent.hxx>
#include <action.hxx>
#include <cond_eff.hxx>
#include <strips_state.hxx>
#include <fwd_search_prob.hxx>

#include <boost/algorithm/string.hpp>
#include <string>
#include <aptk/string_conversions.hxx>

#include "utility.hxx"

void clone_problem(const aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& trans_prob, std::vector<unsigned> init_state){

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
    trans_prob.add_action(trans_prob, a->signature(), a->prec_vec(), a->add_vec(), a->del_vec(), a->ceff_vec(),a->cost());
  }

  // Set names and initial and goal states the same as
  trans_prob.set_domain_name(prob.domain_name());
  trans_prob.set_problem_name(prob.problem_name());
  trans_prob.set_init(trans_prob, init);
  trans_prob.set_goal(trans_prob, goal);

  trans_prob.make_action_tables();

}
