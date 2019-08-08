//#ifndef __MCTS__
//#define __MCTS__

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

template <typename Search_Model, typename Open_List_Type>
class MCTS;

template <typename Search_Model, typename Open_List_Type>
class MCTS{

public:

  typedef typename Search_Model::State_Type State;
  typedef Node<State> Search_Node;

	MCTS( 	const Search_Model& search_problem )
	  : m_problem( search_problem )
	{
	}

	virtual ~MCTS(){}

  void start(){
    m_root = new Search_Node( m_problem.init(), 0.0f, aptk::no_op, NULL );
  }

  int  pick_next_action(unsigned int max_nodes){

    int counter = 0;
    Search_Node * root = m_root;
    Search_Node * head;
    Search_Node * child;

    while( counter < max_nodes ){

      head = select(root);
      child = expand(head);
      child->reward() = simulate(child, 20);
      back_propagate(child);

      counter++;
    }

    Search_Node * next = best_child(m_tree[root]);

    if (next == NULL){
      return -1;
    }

    unsigned int a_id = next->action();

    return a_id;

  }

protected:

  virtual Search_Node * best_child(std::vector<Search_Node *> children){
    // Implemented here is returning the child with best reward
    // however returning the most simulated child may also be useful

    double best_reward = -1;
    double best_child_index = -1;

    for (unsigned int i = 0; i < children.size(); i++){
      Search_Node * child = children[i];
      if(child->reward() > best_reward){
        best_reward = child->reward();
        best_child_index = i;
      }
    }

    if(best_child_index == -1){
      return NULL;
    }

    return children[best_child_index];
  }

  Search_Node * select( Search_Node * root ){
    int  max_index = -1;
    float max_tree_func = -1;

    for(unsigned int i = 0; i < m_tree[root].size(); i++){
      Search_Node * child = m_tree[root][i];
      float child_tree_func = tree_func(child);
      if( child_tree_func > max_tree_func ){
        max_tree_func = child_tree_func;
        max_index = i;
      }
    }

    if (max_index < 0){
      return root;
    } else {
      return select(m_tree[root][max_index]);
    }
  }


  Search_Node * expand(Search_Node * parent){
		std::vector< aptk::Action_Idx > app_set;
		m_problem.applicable_set_v2( *(parent->state()), app_set );

		for (unsigned i = 0; i < app_set.size(); ++i ) {

			int a = app_set[i];
			State *succ = m_problem.next( *(parent->state()), a );
			Search_Node* n = new Search_Node( succ, m_problem.cost( *(parent->state()), a ), a, parent );
			m_tree[parent].push_back(n);

		}

		unsigned int chosen_child = rand() % m_tree[parent].size();
		return m_tree[parent][chosen_child];

  }

  virtual double simulate(Search_Node * selected, unsigned int max_actions){return 0;}

  void back_propagate(Search_Node * child){

    child->m_play_count++;

    if (child->m_parent == NULL){
      return;
    }

    Search_Node * parent = child->m_parent;
    parent->reward() = combine_reward(parent, child);

    back_propagate(parent);

  }

  virtual double combine_reward(Search_Node * parent, Search_Node * child){
    // Implemented here is the "max" function which returns the larger reward
    // of the two search nodes

    if (parent->reward() < child->reward()){
      return child->reward();
    } else{
      return parent->reward();
    }
  }

  virtual double tree_func(Search_Node * head){
    // Implemented here is the UCB1 tree policy

    return head->m_reward + sqrt((2*log(head->m_parent->m_play_count))/head->m_play_count);
  }

protected:

	const Search_Model& m_problem;
	Search_Node*  m_root;
  std::map<const Search_Node *, std::vector<Search_Node *>>  m_tree;

};


template <typename State>
class Node {
public:

	typedef State State_Type;

	Node( State* s, float cost, aptk::Action_Idx action, Node<State>* parent )
	: m_state( s ), m_parent( parent ), m_action(action), m_g( 0 ), m_reward( 0 ),
	m_play_count(0){
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



public:

	State*		m_state;
  Node<State>* m_parent;
  aptk::Action_Idx	m_action;
	float		m_g;
  float   m_reward;
  unsigned int m_play_count;


};
//#endif

