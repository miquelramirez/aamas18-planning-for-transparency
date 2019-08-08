#ifndef __UTILITY_FILE_H__
#define __UTILITY_FILE_H__

/* Purpose: Utility file, such as printing fluent vectors */
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

std::string print_fluent_vec(const aptk::STRIPS_Problem& prob, std::vector<unsigned int> f_v);
std::string print_action_vec(const aptk::STRIPS_Problem& prob, std::vector<int> a_v);
//std::string print_action_vec(aptk::STRIPS_Problem& prob, std::vector<unsigned int> a_v);

template<class T>
bool element_of(T e, std::vector<T> es){
  return std::find(es.begin(), es.end(), e) != es.end();
}

template<class T>
void print_vector(std::vector<T> v){
  for (unsigned int i = 0; i <  v.size(); i++){
    std::cout << i << ": " << std::to_string(v[i]) << std::endl;
  }
}

template<class T>
std::string vector_as_string(std::vector<T> v, std::string del){

  std::stringstream s;

  for (unsigned int i = 0; i <  v.size(); i++){
    if(i != v.size()-1)
      s << std::to_string(v[i]) << del;
    else
      s << std::to_string(v[i]);
  }

  return s.str();
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
std::vector<double> normalize_vector(std::vector<T> v){
	std::vector<double> n_v;
	double sum =  (double) std::accumulate(v.begin(), v.end(), (T) 0);

  if(sum == 0){
    for (unsigned i = 0; i < v.size(); i++)
      n_v.push_back((double) 1.0f / ((double) v.size()));
  }else{

    for(T e : v){
      n_v.push_back( ((double) e) / sum);
    }
  }

	return n_v;

}

void clone_problem(const aptk::STRIPS_Problem& prob, aptk::STRIPS_Problem& trans_prob, std::vector<unsigned> init_state);


#endif //UTILITY_FILE_H_
