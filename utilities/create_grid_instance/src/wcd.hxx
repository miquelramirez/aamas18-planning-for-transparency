#include <iostream>
#include <fstream>
#include <map>

#include <ff_to_aptk.hxx>
#include <strips_prob.hxx>
#include <fluent.hxx>
#include <action.hxx>
#include <cond_eff.hxx>
#include <strips_state.hxx>
#include <fwd_search_prob.hxx>

#include <h_1.hxx>

#include <aptk/open_list.hxx>
#include <aptk/string_conversions.hxx>
#include <aptk/at_bfs.hxx>

#include <fstream>

#include <boost/program_options.hpp>

int wcd(aptk::STRIPS_Problem& prob, std::vector<aptk::Fluent_Vec>& goal_set, float epsilon);
unsigned int wcd_g(aptk::STRIPS_Problem& trans_prob, std::map<std::string, unsigned int>& idx_to_trans_idx, aptk::Fluent_Vec& r_goal, std::vector<aptk::Fluent_Vec>& goal_set, float epsilon);
void translate_problem_latest_split(aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& trans_prob, std::map<std::string, unsigned int>& idx_to_trans_idx, float epsilon);
