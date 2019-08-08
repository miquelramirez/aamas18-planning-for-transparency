/**
 * Author: Aleck MacNally
 * Institution: University of Melbourne
 * Date: 20/02/2017
 * Purpose: Monte Carlo Tree Search
 */

#ifndef __MCTS__
#define __MCTS__

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <map>

#include <aptk/search_prob.hxx>
#include <aptk/resources_control.hxx>
#include <aptk/closed_list.hxx>
#include <aptk/ext_math.hxx>
#include <action.hxx>

template <typename State>
class Node;

// Class for MONTE-CARLO TREE SEARCH algorithm implemented
// ontop of the LAPKT planning framework
template <typename Search_Model>
class MCTS{

public:

  typedef typename Search_Model::State_Type State;
  typedef Node<State> Search_Node;
  typedef aptk::search::Closed_List<Search_Node> Closed_List_Type;

	MCTS(const Search_Model& search_problem, bool has_closed_list, bool verbose, Closed_List_Type * closed_list)
	  : m_problem( search_problem ), m_has_closed_list(has_closed_list),
	  m_verbose(verbose)
	{
    m_root = new Search_Node( m_problem.init(), 0.0f, aptk::no_op, NULL );
    m_closed_top_level = * closed_list;
	}

  virtual ~MCTS(){
    // Delete MONTE-CARLO SEARCH TREE
    // delete_m_tree(m_root);
  }

  int  pick_next_action(unsigned int max_nodes){

    int counter = 0;
    Search_Node * root = m_root;
    Search_Node * head;
    std::vector<Search_Node * > children;

    while( counter < max_nodes ){

      head = select(root);
      if (head == NULL){
        break;
      }
      children = expand(head);
      simulate_nodes(children, 20);
      back_propagate_nodes(children);

      counter += children.size();
    }

    Search_Node * next = best_child(m_tree[root]);

    if (next == NULL){
      return -1;
    }

    unsigned int a_id = next->action();

    return a_id;

  }

protected:

  // Returns the best Search Node in a vector of Search Nodes
  // based on some criteria.
  // Used to pick the best action to take from the root node.
  virtual Search_Node * best_child(std::vector<Search_Node *> children){
    // Implemented here is returning the child with best reward
    // however returning the most simulated child may also be useful

    double best_reward = -1*infty;
    std::vector<Search_Node *> max_children;

    for (unsigned int i = 0; i < children.size(); i++){
      Search_Node * child = children[i];

      if(m_problem.task().m_h_verbose)
        std::cout << "\t" << m_problem.task().actions()[child->action()]->signature() << ": " << child->reward() << std::endl;

      if(child->reward() > best_reward){
        best_reward = child->reward();
        max_children.clear();
        max_children.push_back(child);
      } else if (child->reward() == best_reward){
        max_children.push_back(child);
      }
    }

    return tie_break_action(max_children);
  }

  // Tie-break policy for choosing the best action to take from root node
  virtual Search_Node * tie_break_action(std::vector<Search_Node * > children){
		// Break Ties Randomly
		unsigned int chosen_child = 0;
		return children[chosen_child];
  }

  // Tie-break policy for choosing next state in the select step of the
  // MONTE-CARLO TREE SEARCH.
  virtual Search_Node * tie_break_tree_policy(std::vector<Search_Node * > children){
		// Break Ties Randomly
		unsigned int chosen_child = 0;
		return children[chosen_child];
  }

  // Select step of the MONTE-CARLO TREE SEARCH
  virtual Search_Node * select( Search_Node * root ){

    // If we are at the goal no more expanding
    if(m_problem.goal(*(root->state()))){
      return NULL;
    }

    if (root->m_has_children == false){
      return NULL;
    }

    // Recursively applies the select function on the
    // children of the selected child node, until
    // no children exist
    if (m_tree[root].empty()){
      return root;
    }

    // Finds the set of maximum children of the Search_Node root
    // based up the function tree_func
    std::vector<Search_Node *> children = m_tree[root];
    while(!children.empty()){

      std::vector<Search_Node * > max_children;
      float max_tree_func = -1*infty;

      for(unsigned int i = 0; i < children.size(); i++){
        Search_Node * child = children[i];
        float child_tree_func = tree_func(child);
        if( child_tree_func > max_tree_func ){
          max_tree_func = child_tree_func;
          max_children.clear();
          max_children.push_back(child);
        } else if (child_tree_func == max_tree_func){
          max_children.push_back(child);
        }
      }

      Search_Node * selected = NULL;

      while(selected == NULL && !max_children.empty()){
        Search_Node * best_child = tie_break_tree_policy(max_children);
        selected = select(best_child);
        if (selected == NULL){
          max_children.erase(std::remove(max_children.begin(), max_children.end(), best_child), max_children.end());
          children.erase(std::remove(children.begin(), children.end(), best_child), children.end());
        }else{
          return selected;
        }
      }

    }

    return NULL;

    //if(max_children.empty()){
      //return NULL;
    //} else {
      //return selected;
    //}

  }


  // Adds the children of the selected node 'parent' to the search
  // tree. Chooses one of these children at random to simulate
  virtual std::vector<Search_Node *> expand(Search_Node * parent){
    // TODO HOW TO DELETE STATES AS SEEM TO BE SHARED EVERYWHERE
		std::vector< aptk::Action_Idx > app_set;
		m_problem.applicable_set_v2( *(parent->state()), app_set );

		for (unsigned i = 0; i < app_set.size(); ++i ) {

			int a = app_set[i];
			State *succ = m_problem.next( *(parent->state()), a );

			Search_Node* n = new Search_Node( succ, m_problem.cost( *(parent->state()), a ), a, parent );

      if(m_has_closed_list)
        if (is_closed(n)){
          delete n;
          continue;
        }

      m_tree[parent].push_back(n);

      if(m_has_closed_list)
        close(n);

		}

    //parent->m_reward = -1*infty;

    if(m_tree[parent].empty()){
      parent->m_has_children = false;
    }

		return m_tree[parent];

		//unsigned int chosen_child = rand() % app_set.size();
		//return m_tree[parent][chosen_child];

  }

  void simulate_nodes(std::vector<Search_Node * > children, unsigned max_nodes){
    for (unsigned i = 0; i < children.size(); i++)
      children[i]->reward() = simulate(children[i], max_nodes);
  }

  // The simulation/rollout policy must be defined separately
  virtual double simulate(Search_Node * selected, unsigned int max_actions) = 0;

  // This is the update function which updates the rewards of all the nodes
  // on the path from the root to the node child.
  virtual void back_propagate(Search_Node * child){

    child->m_play_count++;

    if (child->m_parent == NULL){
      return;
    }

    Search_Node * parent = child->m_parent;
    parent->reward() = combine_reward(parent, child);

    //TODO:

    back_propagate(parent);

  }

  // This function determines how the reward of the child node updates
  // the reward of the parent node.
  virtual double combine_reward(Search_Node * parent, Search_Node * child){
    // Implemented here is the "max" function which returns the larger reward
    // of the two search nodes

    if (parent->reward() < child->reward()){
      // TODO Reconsider
      //parent->gn() = child->gn();
      parent->m_delta_sum = child->m_delta_sum;
      return child->reward();
    } else{
      return parent->reward();
    }
  }

  // This is the function which represents the tree policy
  virtual double tree_func(Search_Node * head){
    // Implemented here is the UCB1 tree policy

    double exploration_constant = 1/sqrt(2);

    if (head->m_play_count == 0)
      return infty;
    else
    {
      double reward_term = head->m_reward;
      double non_reward_term = exploration_constant*sqrt((log(head->m_parent->m_play_count))/head->m_play_count);
      double result = reward_term + non_reward_term;

      //std::cout << "\t\tReward: " << reward_term << ", Non-Reward: " << non_reward_term << std::endl;

      return result;
    }
  }

protected:

	void close( Search_Node* n ) 	{
	  m_closed.put(n);
	  m_closed_top_level.put(n);
	}

	bool is_closed( Search_Node* n ) 	{
		Search_Node * n2 = m_closed.retrieve(n);
		Search_Node * n3 = m_closed_top_level.retrieve(n);

		if ( n2 != NULL || n3 != NULL){

      //std::cout << "Terminated: ";
      //for (auto i : n->state()->belief_state()){
        //std::cout << i << ", ";
      //}
      //std::cout << std::endl;
      //for (auto i : n2->state()->belief_state()){
        //std::cout << i << ", ";
      //}
      //std::cout << std::endl;

			return true;
    }
		else
      return false;
  }

private:

  // Deletes each node in the tree recursively
  void delete_m_tree(Search_Node * parent){
    std::vector<Search_Node * > children = m_tree[parent];

    for (Search_Node * child : children){
      delete_m_tree(child);
    }

    delete parent;
  }


  std::string fluent_vector_to_string(std::vector<unsigned> v){
    std::string s("{");
    for (unsigned int i: v){
      s = s + (m_problem.task().fluents()[i]->signature()) + ", ";
    }
    s = s + "}";
    return s;
  }

  void back_propagate_nodes(std::vector<Search_Node * > children){
    for (unsigned i = 0; i < children.size(); i++)
      back_propagate(children[i]);
  }


public:

	const Search_Model& m_problem;
	bool m_has_closed_list;
	Search_Node*  m_root;
	bool m_verbose;

protected:

  // This is the MCTS Tree
  std::map<const Search_Node *, std::vector<Search_Node *>>  m_tree;
	Closed_List_Type		m_closed;
	Closed_List_Type    m_closed_top_level;

};


template <typename State>
class Node {
public:

	typedef State State_Type;

	Node( State* s, float cost, aptk::Action_Idx action, Node<State>* parent )
	: m_state( s ), m_parent( parent ), m_action(action), m_g( 0 ), m_reward( -1*infty ),
	m_play_count(0), m_has_children(true){
		m_g = ( parent ? parent->m_g + cost : 0.0f);
	}

	virtual ~Node() {
    if ( m_state != NULL ) delete m_state;
	}

	float&			gn()		{ return m_g; }
	float			gn() const 	{ return m_g; }
	float&  reward() { return m_reward; }
  float  reward() const {return m_reward;}
	Node<State>*		parent()   	{ return m_parent; }
  aptk::Action_Idx		action() const 	{ return m_action; }
	State*			state()		{ return m_state; }
	const State&		state() const 	{ return *m_state; }
	void			set_state( State* s )	{ m_state = s; }
	bool			has_state() const	{ return m_state != NULL; }
	void			print( std::ostream& os ) const {
		os << "{@ = " << this << ", s = " << m_state << ", parent = " << m_parent << ", g(n) = " << m_g << "}";
	}

	bool   	operator==( const Node<State>& o ) const {

		if( &(o.state()) != NULL && &(state()) != NULL)
			return (const State&)(o.state()) == (const State&)(state());
		/**
		 * Lazy
		 */
		if  ( m_parent == NULL ) {
			if ( o.m_parent == NULL ) return true;
			return false;
		}

		if ( o.m_parent == NULL ) return false;

		return (m_action == o.m_action) && ( *(m_parent->m_state) == *(o.m_parent->m_state) );
	}

	size_t                  hash() const { return m_state->hash(); }



public:

	State*		m_state;
  std::vector<double> m_belief_state;
  Node<State>* m_parent;
  aptk::Action_Idx	m_action;
	float		m_g;
  float   m_reward;
  float m_true_reward;
  float m_reward_no_discount;
  unsigned int m_play_count;
	bool m_has_children;
	float m_ce;
	float m_delta_sum;
	float m_t_delta_sum;

	float m_deltas;


};
#endif

