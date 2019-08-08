#ifndef __GOAL_SET_PARSE__
#define __GOAL_SET_PARSE__

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
#include <rp_heuristic.hxx>
#include <aptk/open_list.hxx>

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <aptk/string_conversions.hxx>

using aptk::agnostic::Fwd_Search_Problem;

// Process Observation File
std::vector<unsigned int> observations_parsing(std::string obs_name, aptk::STRIPS_Problem& prob){
  std::string line;
  std::ifstream obs_file(obs_name);
  std::vector<unsigned int> obs_set;

  if(obs_file.is_open())
    while (std::getline(obs_file,line)){
      boost::to_upper(line);

      for(auto a : prob.actions()){
        if(a->signature() == line){
          obs_set.push_back(a->index());
          break;
        }
      }

    }
  else
    std::cout << "Unable to open observations file!" << std::endl;

  return obs_set;
}

// Process the goal candidate set file
std::vector<unsigned int> process_goal_set_line(std::string s, aptk::STRIPS_Problem& prob){
  std::string delimiter = ",";
	size_t pos = 0;
	std::string token;
  std::vector<unsigned int> goal_vector;
  aptk::Fluent_Ptr_Vec fs = prob.fluents();

	while ((pos = s.find(delimiter)) != std::string::npos || !s.empty()) {
			token = s.substr(0, pos);

      //std::transform(token.begin(), token.end(), token.begin(), toupper);
      boost::to_upper(token);
      boost::algorithm::trim(token);
			for (unsigned int i = 0 ; i < fs.size(); i++){
        //std::cout << "fs" << i << ": |" << fs[i]->signature() << "| token = |" << token << "|"<< std::endl;
        if (fs[i]->signature() == token){
          goal_vector.push_back(fs[i]->index());
          //std::cout << "Chosen: " << fs[i]->signature() << ", \n";
          break;
        }
      }
      //std::cout << "sB = " << s << std::endl;

      if((pos = s.find(delimiter)) != std::string::npos)
        s.erase(0, pos + delimiter.length());
      else
        s.clear();

      //std::cout << "sA = " << s << std::endl;
	}

  boost::to_upper(s);
  for (unsigned int i = 0 ; i < fs.size(); i++){
    if (fs[i]->signature() == s){
      //std::cout << fs[i]->signature() << ", ";
      goal_vector.push_back(fs[i]->index());
    }
  }

  //std::cout << std::endl;

  std::sort(goal_vector.begin(), goal_vector.end());
  return goal_vector;
}

// Parses each line of the goal candidate set file
std::vector<aptk::Fluent_Vec> goal_set_parsing(std::string goal_set_file_name, aptk::STRIPS_Problem& prob){
  std::string line;
  std::ifstream goal_set_file(goal_set_file_name);
	std::vector<aptk::Fluent_Vec> goal_set;
  //unsigned int ln_n = 0;

  //std::cout << "Goal-Set: " << std::endl;

  if(goal_set_file.is_open())
    while (std::getline(goal_set_file,line)){
      //std::cout << ln_n++ << ": " << std::endl;
      std::vector<unsigned int> goal = process_goal_set_line(line, prob);
      if (!goal.empty())
        goal_set.push_back(goal);
    }
  else
    std::cout << "Unable to open Goal-Set file!" << std::endl;

  //std::cout << std::endl;

  return goal_set;
}

void remove_hidden_actions(std::vector<aptk::Action_Idx> plan, Fwd_Search_Problem& search_prob, std::vector<aptk::Action_Idx>& plan_woh){
  std::string hidden = "(HIDDEN";
  for ( unsigned k = 0; k < plan.size(); k++ ) {
    const aptk::Action& a = *(search_prob.task().actions()[ plan[k] ]);
    std::string name = a.signature();
    boost::to_upper(name);

    auto res = std::mismatch(hidden.begin(), hidden.end(), name.begin());
    if (res.first != hidden.end()){
      plan_woh.push_back(plan[k]);
    }

  }
}


// Process the goal candidate set file
std::vector<unsigned int> process_hype_line(std::string s, aptk::STRIPS_Problem& prob){
  std::string delimiter = ",";
	size_t pos = 0;
	std::string token;
  std::vector<unsigned int> hype_vector;
  auto fs = prob.actions();

	while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);

      boost::to_upper(token);
			for (unsigned int i = 0 ; i < fs.size(); i++){
        //std::cout << "fs" << i << ": " << fs[i]->signature() << " token = " << token << std::endl;
        if (fs[i]->signature() == token){
          hype_vector.push_back(fs[i]->index());
        //std::cout << fs[i]->signature() << ", ";
        }
      }

			s.erase(0, pos + delimiter.length());
	}

  boost::to_upper(s);
  for (unsigned int i = 0 ; i < fs.size(); i++){
    if (fs[i]->signature() == s){
      //std::cout << fs[i]->signature() << ", ";
      hype_vector.push_back(fs[i]->index());
    }
  }

  //std::cout << std::endl;

  return hype_vector;
}

// Parses each line of the goal candidate set file
std::vector<unsigned int> hype_set_parsing(std::string hype_set_file_name, aptk::STRIPS_Problem& prob){
  std::string line;
  std::ifstream hype_set_file(hype_set_file_name);
	std::vector<unsigned int> hype_set;
  //unsigned int ln_n = 0;

  //std::cout << "Goal-Set: " << std::endl;

  if(hype_set_file.is_open())
    while (std::getline(hype_set_file,line)){
      //std::cout << ln_n++ << ": " << std::endl;
      std::vector<unsigned int> hype = process_hype_line(line, prob);
      hype_set.insert(hype_set.end(), hype.begin(), hype.end());
    }
  else
    std::cout << "Unable to open Goal-Set file!" << std::endl;

  //std::cout << std::endl;

  return hype_set;
}
#endif
