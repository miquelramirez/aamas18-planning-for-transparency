#ifndef __UTILITY_FILE__
#define __UTILITY_FILE__

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

template<class T>
void print_vector(std::vector<T> v){
	for (unsigned int i = 0; i <  v.size(); i++){
		std::cout << i << ": " << std::to_string(v[i]) << std::endl;
	}
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
std::vector<double> normalize_vector(std::vector<T> v){
	std::vector<double> n_v;
	double sum =  (double) std::accumulate(v.begin(), v.end(), (T) 0);

	for(T e : v){
		n_v.push_back( ((double) e) / sum);
	}

	return n_v;

}


#endif
