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

using	aptk::agnostic::Fwd_Search_Problem;

std::vector<double> plan_recognition(const aptk::STRIPS_Problem& prob, std::vector<aptk::Fluent_Vec>& goal_set, std::vector<double> priors, std::vector<unsigned>& observations, aptk::Fluent_Vec& init, float beta, bool optimal);

std::vector<double> plan_recognition_approx(const aptk::STRIPS_Problem& prob, std::vector<aptk::Fluent_Vec>& goal_set, std::vector<double> priors, std::vector<unsigned>& observations, aptk::Fluent_Vec& init, float beta, unsigned approx_type);

std::vector<double> simulate_plan_for_recog(std::vector<aptk::Action_Idx>& plan, aptk::STRIPS_Problem& prob, std::vector<aptk::Fluent_Vec>& goal_set, std::vector<double>& priors, float beta);

#ifndef __PLANREC_H__
#define __PLANREC_H__

template<class T>
void print_vector(std::vector<T> v){
	for (unsigned int i = 0; i <  v.size(); i++){
		std::cout << i << ": " << std::to_string(v[i]) << std::endl;
	}
}

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


#endif
