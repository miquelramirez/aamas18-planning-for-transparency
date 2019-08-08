
#include <map>
#include <algorithm>

#include <strips_prob.hxx>
#include <fluent.hxx>
#include <action.hxx>
#include <cond_eff.hxx>

#include "dalandmarks.hxx"
#include "utility.hxx"

namespace dalm{

  void DALandmarkGenerator::construct_justified_graph(){
    std::vector<aptk::Action * > actions = m_strips_model->actions();

    aptk::State s(*m_strips_model);
    s.set(m_strips_model->init());

    m_h_max->eval(s,m_init_h);

    float max_h_max = 0;
    for (Fluent_Idx f : m_strips_model->goal()){
      if (m_h_max->value(f) >= max_h_max){
        max_h_max = m_h_max->value(f);
        m_relaxed_goal = f;
      }
    }

    for (const aptk::Action * a : actions){

      float max_h_max_prec = 0;
      Fluent_Idx relaxed_prec = -1;
      for (Fluent_Idx f : a->prec_vec()){
        if (m_h_max->value(f) > max_h_max_prec){
          max_h_max_prec = m_h_max->value(f);
          relaxed_prec = f;
        }
      }

      for(Fluent_Idx f : a->add_vec()){
        m_just_graph[f].push_back(relaxed_prec);
        std::pair<Fluent_Idx, Fluent_Idx> ff(relaxed_prec, f);
        m_edge_action[ff] = a->index();
        m_a_best_p[a->index()] = relaxed_prec;
      }

    }
  }

  void DALandmarkGenerator::extract_landmarks(){
    std::vector<Fluent_Idx> rg;
    rg.push_back(m_relaxed_goal);
    m_landmark_vector = extract_landmarks_helper(rg,0);
  }

  std::vector<Landmark> DALandmarkGenerator::extract_landmarks_helper(std::vector<Fluent_Idx> gs, float cost_accumulation){

    if (m_init_h - cost_accumulation <= 0){
      std::vector<Landmark> ls;
      return ls;
    }

    Landmark l;
    for (auto g : gs){
      for(auto p : m_just_graph[g]){
        if ( std::find(gs.begin(), gs.end(), p) == gs.end() ){
          l.push_back(m_edge_action[std::make_pair(p,g)]);
        }
      }
    }

    float cmin = infty;
    for(int a : l){
      float a_cost = m_strips_model->actions()[a]->cost();
      if (a_cost < cmin)
        cmin = a_cost;
    }
    cost_accumulation += cmin;

    std::vector<Action_Idx> zero_actions;
    for(int i : l){
      auto a = m_strips_model->actions()[i];
      if(a->cost() - cmin <= 0){
        a->set_cost(0);
        zero_actions.push_back(i);
      } else {
        a->set_cost(a->cost() - cmin);
      }
    }

    size_t gs_size = gs.size();
    for(Action_Idx a : zero_actions){
      if (!element_of(m_a_best_p[a], gs))
        gs.push_back(m_a_best_p[a]);
    }

    if (gs.size() == gs_size){
      std::cout << "No Solution" << std::endl;
      std::vector<Landmark> ls;
      return ls;
    }

    std::vector<Landmark> ls = extract_landmarks_helper(gs, cost_accumulation);
    ls.push_back(l);

    return ls;

  }

  void DALandmarkGenerator::print_landmarks(){
    for(unsigned int i = 0; i < landmarks().size(); i++){

      auto a = landmarks()[i];
      std::cout << i << "th landmark: ";
      for (auto i : a){
        std::cout << m_strips_model->actions()[i]->signature() << ",";
      }
      std::cout << std::endl;
    }
  }

}
