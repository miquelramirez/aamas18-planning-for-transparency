/*
Lightweight Automated Planning Toolkit
Copyright (C) 2012
Miquel Ramirez <miquel.ramirez@rmit.edu.au>
Nir Lipovetzky <nirlipo@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ITERATIVE_WIDTH__
#define __ITERATIVE_WIDTH__

#include <aptk/search_prob.hxx>
#include <aptk/resources_control.hxx>
#include <aptk/closed_list.hxx>
#include "brfs.hxx"
#include <reachability.hxx>
#include <vector>
#include <algorithm>
#include <iostream>
#include "2h_exp_node.hxx"

namespace aptk {

namespace search {

namespace brfs {


template < typename Search_Model, typename Abstract_Novelty, typename Heuristic, typename Open_List_Type >
class IW  {

public:

	typedef		typename Search_Model::State_Type		        State;
        typedef  	aptk::search::gbfs_2h_exp::Node< Search_Model,State >	Search_Node;
	typedef 	Closed_List< Search_Node >			        Closed_List_Type;

	IW( 	const Search_Model& search_problem ) 
		: m_problem( search_problem ), m_global_closed(NULL),  m_exp_count(0), m_gen_count(0), m_cl_count(0), m_max_depth(0),  m_max_expanded( no_such_index ), m_pruned_B_count(0), m_B( infty ), m_verbose( true ), m_init_h( 0 ), m_ignore_novelty(false) {	   
		m_novelty = new Abstract_Novelty( search_problem );
		m_h = new Heuristic( search_problem );
		m_reachability = new aptk::agnostic::Reachability_Test( this->problem().task() );
		m_consistency_test = false;
		m_novelty->init();
	}

	virtual ~IW() {
		delete m_novelty;
		delete m_h;
		delete m_reachability;

		for ( typename Closed_List_Type::iterator i = m_closed.begin();
			i != m_closed.end(); i++ ) {
			delete i->second;
		}
		
		while	(!m_open.empty() ) 
		{	
			Search_Node* n = m_open.pop();
			delete n;
		}
		while	(!m_open2.empty() ) 
		{	
			Search_Node* n = m_open2.pop();
			delete n;
		}
		
		m_closed.clear();
		m_open_hash.clear();
	
	}

	void	set_verbose( bool v ) { m_verbose = v; }
	bool	verbose() const { return m_verbose; }
    	void	set_ignore_novelty( bool v )    { m_ignore_novelty = v; }
	
	void reset() {
		for ( typename Closed_List_Type::iterator i = m_closed.begin();
		      i != m_closed.end(); i++ ) {
			delete i->second;
		}
				

		while	(!m_open.empty() ) 
		{	
			Search_Node* n = m_open.pop();
			delete n;
		}

		while	(!m_open2.empty() ) 
		{	
			Search_Node* n = m_open2.pop();
			delete n;
		}
	
		m_closed.clear();
		m_open_hash.clear();
		m_max_depth=0;
	}
	

	template <typename global_open_list_type>
	void dump_nodes( global_open_list_type& o ){
		if(m_global_closed){
			for ( typename Closed_List_Type::iterator i = m_closed.begin();
			      i != m_closed.end(); i++ ) {
				m_global_closed->put( i->second );
			}
			m_closed.clear();
		}
		while	(!m_open.empty() ) 
		{	
			Search_Node* n = m_open.pop();
			//Goal oriented
			//m_h->eval( *(n->state()), n->h2n() );
			n->h1n() = 1;
			//--
			o.insert(n);
		}
		while	(!m_open2.empty() ) 
		{	
			Search_Node* n = m_open2.pop();
			//Goal oriented
			//m_h->eval( *(n->state()), n->h2n() );
			n->h1n() = 1;
			//--
			o.insert(n);
		}
		m_open_hash.clear();

	}


	void	start(Search_Node* n = NULL) {

		m_exp_count = 0;

		// //Goal oriented stoping
		// m_goals_achieved.clear();
		// m_goal_candidates.clear();
		
		
		// for(Fluent_Vec::const_iterator it =  problem().task().goal().begin(); it != problem().task().goal().end(); it++){
		// 	if(  n->state()->entails( *it ) ){
		// 		m_goals_achieved.push_back( *it );
		// 	}
		// 	else
		// 		m_goal_candidates.push_back( *it );
		// }
		

		
		m_root = n;


		m_pruned_B_count = 0;
		reset();

		m_novelty->init();
		m_h->eval( *(m_root->state()), m_root->h2n() );
		m_root->h1n() = 1;
		m_init_h = m_root->h2n();

		if ( prune( m_root ) )  {
			if ( verbose() ) 
				std::cout<<"Initial State pruned! No Solution found."<<std::endl;
			return;
		}
		
		
#ifdef DEBUG
		if ( verbose() ) {
			std::cout << "Initial search node: ";
			m_root->print(std::cout);
			std::cout << std::endl;
		}
#endif 
		m_open.insert( m_root );
		m_open_hash.put( m_root );
		inc_gen();
	}

	Abstract_Novelty*      			novelty() { return m_novelty; }

	float			bound() const			{ return m_B; }
	void			set_bound( float v ) 		{ 
		m_B = v;
		m_novelty->set_arity( m_B );
	}

	float			arity() 	                { return m_novelty->arity( ); }

	void			inc_pruned_bound() 		{ m_pruned_B_count++; }
	unsigned		pruned_by_bound() const		{ return m_pruned_B_count; }

	
	void			inc_gen()			{ m_gen_count++; }
	unsigned		generated() const		{ return m_gen_count; }
	void			inc_exp()			{ m_exp_count++; }
	unsigned		expanded() const		{ return m_exp_count; }

	void			inc_closed()			{ m_cl_count++; }
	unsigned		pruned_closed() const		{ return m_cl_count; }

	void                    set_max_expanded( unsigned v )  { m_max_expanded = v; }
	
	void 			close( Search_Node* n ) 	{  m_closed.put(n); }
	Closed_List_Type&	closed() 			{ return m_closed; }
        void	                set_global_closed( Closed_List_Type *c ) { m_global_closed = c; }
	Closed_List_Type&	open_hash() 			{ return m_open_hash; }

	const	Search_Model&	problem() const			{ return m_problem; }

	bool 		is_closed( Search_Node* n ) 	{ 
		Search_Node* n2 = this->closed().retrieve(n);

		if ( n2 != NULL ) 
			return true;

		if(m_global_closed){
		    Search_Node* n2 = this->m_global_closed->retrieve(n);

		    if ( n2 != NULL ) 
			return true;
		}

		return false;
	}
	
	bool          search_exhausted(){ return m_open.empty() and m_open2.empty(); }

	virtual bool	find_solution( float& cost, std::vector<Action_Idx>& plan ) {
		Search_Node* end = do_search();
		if ( end == NULL ) return false;
		extract_plan( m_root, end, plan, cost );	
		
		return true;
	}

	virtual Search_Node*	 	do_search() {

		open_one = true;
		Search_Node *head = get_node();

		if ( !head ) return NULL;
		
		if( is_goal( head ) )
			return head;

		
		int counter = 0;
		while(head) {	
			if( ! head->has_state() )
				head->set_state( m_problem.next(*(head->parent()->state()), head->action()) );
			
			Search_Node* goal = process(head);
			inc_exp();			
			close(head);
			if( goal ) {
				if( ! goal->has_state() )
					goal->set_state( m_problem.next(*(goal->parent()->state()), goal->action()) );
				return goal;
			}
			
			if( m_exp_count > m_max_expanded ) return NULL;
			counter++;
			head = get_node();
		}
		return NULL;
	}


protected:

	
	Search_Node* 		get_node() {
		Search_Node *next = NULL;
		if(open_one)
			if(! m_open.empty() ) {
				next = m_open.pop();
				m_open_hash.erase( m_open_hash.retrieve_iterator( next) );
				open_one = false;
			}
			
		if(!open_one or !next){
			if(! m_open2.empty() ) {
				next = m_open2.pop();
				m_open_hash.erase( m_open_hash.retrieve_iterator( next) );
				open_one = true;
			}
			else	if(! m_open.empty() ) {
				next = m_open.pop();
				m_open_hash.erase( m_open_hash.retrieve_iterator( next) );
				open_one = false;
			}
		}
		

		
		return next;
	}

	void	 	open_node( Search_Node *n ) {
		//if(n->h1n() == 1)
		m_open.insert(n);
		//else
		//	m_open2.insert(n);
		
		m_open_hash.put(n);
		
		
		inc_gen();
		if(n->gn() + 1 > m_max_depth){
			//if( m_max_depth == 0 ) std::cout << std::endl;  
			m_max_depth = n->gn() + 1 ;
			if ( verbose() ) 
				std::cout << "[" << m_max_depth  <<"]" << std::flush;			
		}

	}

		
	
	virtual bool 			previously_hashed( Search_Node *n ) {
		Search_Node *previous_copy = m_open_hash.retrieve(n);
		
		if( previous_copy != NULL ){
			
			return true;
		}
		return false;
	}

	Search_Node* root() { return m_root; }
	void	extract_plan( Search_Node* s, Search_Node* t, std::vector<Action_Idx>& plan, float& cost, bool reverse = true ) {
		Search_Node *tmp = t;
		cost = 0.0f;
		while( tmp != s) {
			cost += m_problem.cost( *(tmp->state()), tmp->action() );
			plan.push_back(tmp->action());
			tmp = tmp->parent();
		}
		
		if(reverse)
			std::reverse(plan.begin(), plan.end());		
	}


	void	extract_path( Search_Node* s, Search_Node* t, std::vector<Search_Node*>& plan ) {
		Search_Node* tmp = t;
		while( tmp != s) {
			plan.push_back(tmp);
			tmp = tmp->parent();
		}
		
		std::reverse(plan.begin(), plan.end());				
	}

          

	bool   prune( Search_Node* n ){

		float node_novelty = infty;
		if(!m_ignore_novelty)
			m_novelty->eval( n, node_novelty );
		else
			node_novelty = 1;
		
		if( node_novelty > bound() ) {
			inc_pruned_bound();
			//close(n);				
			return true;
		}	
		return false;
	}

	

	/**
	 * Process with successor generator
	 */

	virtual Search_Node*   	process(  Search_Node *head ) {
		std::vector< aptk::Action_Idx > app_set;
		problem().applicable_set_v2( *(head->state()), app_set );
		
		for (unsigned i = 0; i < app_set.size(); ++i ) {
			int a = app_set[i];

			/**
			 * Prune actions that do not add anything new compared to prev state.
			 * Big impact in del-free tasks, as states grow monotonically
			 */
			//need to check COND EFF TOO!!
			// if( head->state()->entails(problem().task().actions()[a]->add_vec()) )
			// 	continue;
			

			State *succ = problem().next( *(head->state()), a );	       			
                        Search_Node* n = new Search_Node( succ ,problem().task().actions()[ a ]->cost(),  a, head  );

			//Lazy expansion
			//Search_Node* n = new Search_Node( NULL , a, head, problem().task().actions()[ a ]->cost() );

			
			if ( is_closed( n ) ) {
				delete n;
				continue;
			}
			
			if( previously_hashed(n) ) {
				delete n;
			}
			else{
				if( prune( n ) ){
					n->h1n() = 2;
					#ifdef DEBUG
					if ( verbose() ) {
						std::cout << std::endl;
						std::cout << "PRUNED State: ";
						if( n->has_state() )
							std::cout << n->state();
						std::cout << " " << n->parent()->state() << " " << n->gn() << " ";
						if( n->has_state() )
							n->state()->print( std::cout );
						std::cout << problem().task().actions()[ n->action() ]->signature() << std::endl;
					}
					#endif
				}
				else
					n->h1n() = 1;
				
				#ifdef DEBUG
				if ( verbose() ) {
					std::cout << std::endl;
					std::cout << "State: ";
					if( n->has_state() )
						std::cout << n->state();
					std::cout << " " << n->parent()->state() << " " << n->gn() << " ";
					if( n->has_state() )
						n->state()->print( std::cout );
					std::cout << problem().task().actions()[ n->action() ]->signature() << std::endl;
				}
				#endif			

				open_node(n);				
				if( is_goal( n ) )
					return n;
			}

		} 



		return NULL;
	}

	//Maybe change to check only in expansion, so it becomes like delayed eval
	virtual bool    is_goal( Search_Node* n  ){ 
		if( n->has_state() ){
			m_h->eval( *(n->state()), n->h2n() );
			return n->h2n() < m_init_h; 
		}
		else{			
			n->parent()->state()->progress_lazy_state(  problem().task().actions()[ n->action() ] );	
			m_h->eval( *(n->state()), n->h2n() );
			const bool is_goal = n->h2n() < m_init_h;
			n->parent()->state()->regress_lazy_state( problem().task().actions()[ n->action() ] );
			return is_goal;
		}
			
	}

	void exclude_actions( Bit_Set& excluded ){
		std::vector< const Action*>::const_iterator it_a =  problem().task().actions().begin();
		unsigned asize = problem().num_actions();
		unsigned fsize = m_goals_achieved.size();
		const bool has_ceff = problem().task().has_conditional_effects();

		for ( unsigned i = 0; i < asize ; i++, it_a++ ) {
						
			/**
			 * If actions edel or adds fluent that has to persist, exclude action.
			 */
			unsigned p = 0;
			for(; p < fsize; p++){
				unsigned fl = m_goals_achieved.at(p);
				
				if(has_ceff){
					if( (*it_a)->consumes( fl ) ){
						excluded.set( i ); 
						break;
					}
				}
				else if( (*it_a)->edeletes( fl ) ){ 
					excluded.set( i ); 
					break;
				}
								
			}
			if( p == fsize )
				excluded.unset( i ); 
			
		}

		
	}
		
	// virtual bool  is_goal( Search_Node* n ){

	// 	const bool has_state = n->has_state();
	// 	static Fluent_Vec added_fluents;
	// 	static Fluent_Vec deleted_fluents;

	// 	State* s = has_state ? n->state() : n->parent()->state();

	// 	if( ! has_state ){
	// 		added_fluents.clear();
	// 		deleted_fluents.clear();
	// 		n->parent()->state()->progress_lazy_state(  problem().task().actions()[ n->action() ], &added_fluents, &deleted_fluents );	
	// 	}


	// 	for(Fluent_Vec::iterator it =  m_goals_achieved.begin(); it != m_goals_achieved.end(); it++){
	// 		if(  ! s->entails( *it ) ){
	// 			if( ! has_state )
	// 				n->parent()->state()->regress_lazy_state( problem().task().actions()[ n->action() ], &added_fluents, &deleted_fluents );

	// 			return false;
	// 		}
					
	// 	}
				
	// 	bool new_goal_achieved = false; 
	// 	Fluent_Vec unachieved;
	// 	for(Fluent_Vec::iterator it = m_goal_candidates.begin(); it != m_goal_candidates.end(); it++){
	// 		if(  s->entails( *it ) )
	// 		{
	// 			m_goals_achieved.push_back( *it );		


	// 			if(!m_consistency_test){
	// 				new_goal_achieved = true;
	// 				return true;
	// 			}

	// 			static Bit_Set excluded( problem().num_actions() );
	// 			exclude_actions( excluded );
					
	// 			if(m_reachability->is_reachable( s->fluent_vec() , problem().task().goal() , excluded  ) ){
	// 				new_goal_achieved = true;
	// 				return true;
	// 			}		
	// 			else{	
	// 				unachieved.push_back( *it );
	// 				m_goals_achieved.pop_back();
	// 			}
					
	// 		}
	// 		else
	// 			unachieved.push_back( *it );
	// 	}

	// 	if( ! has_state )
	// 		n->parent()->state()->regress_lazy_state( problem().task().actions()[ n->action() ], &added_fluents, &deleted_fluents );

	// 	if ( new_goal_achieved ){
	// 		m_goal_candidates = unachieved;				

	// 		if( ! has_state )
	// 			n->set_state( n->parent()->state()->progress_through( *(problem().task().actions()[ n->action() ]) ));

			
	// 		return true;
	// 	}
	// 	else
	// 		return false;	

	// }


	
protected:
	const Search_Model&			m_problem;
	Closed_List_Type			m_closed, m_open_hash;
        Closed_List_Type*                       m_global_closed;
	unsigned				m_exp_count;
	unsigned				m_gen_count;
	unsigned				m_cl_count;
	unsigned                                m_max_depth;
	Search_Node*				m_root;
	std::vector<Action_Idx> 		m_app_set;
	unsigned                                m_max_expanded;

	
	Open_List_Type				m_open;
	Open_List_Type				m_open2;
	bool                                    open_one;
	aptk::agnostic::Reachability_Test*      m_reachability;
	Fluent_Vec                              m_goals_achieved;
	Fluent_Vec                              m_goal_candidates;
	bool                                    m_consistency_test;
		
	Abstract_Novelty*      			m_novelty;
	unsigned				m_pruned_B_count;
	float					m_B;
	bool					m_verbose;
	Heuristic*                              m_h;
	unsigned                                m_init_h;

	bool                                    m_ignore_novelty;
};

}

}

}

#endif // iw.hxx
