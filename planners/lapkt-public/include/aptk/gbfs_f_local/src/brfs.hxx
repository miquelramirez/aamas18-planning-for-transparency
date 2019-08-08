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

#ifndef __BREADTH_FIRST_SEARCH__
#define __BREADTH_FIRST_SEARCH__

#include <aptk/search_prob.hxx>
#include <aptk/resources_control.hxx>
#include <aptk/closed_list.hxx>
#include <aptk/hash_table.hxx>
#include "2h_exp_node.hxx"

#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>

namespace aptk {

namespace search {

namespace brfs {


template <typename Search_Model>
class BRFS {

public:

	typedef		typename Search_Model::State_Type		              State;
        typedef  	aptk::search::gbfs_2h_exp::Node< Search_Model, State >        Search_Node;
	typedef 	Closed_List< Search_Node >      		              Closed_List_Type;

	BRFS( 	const Search_Model& search_problem ) 
		: m_problem( search_problem ), m_global_closed(NULL),  m_exp_count(0), m_gen_count(0), m_cl_count(0), m_max_depth(0), m_verbose(true), m_max_expanded( no_such_index ) {		
	}

	virtual ~BRFS() {
		for ( typename Closed_List_Type::iterator i = m_closed.begin();
			i != m_closed.end(); i++ ) {
			delete i->second;
		}
		
		while	(!m_open.empty() ) 
		{	
			Search_Node* n = m_open.front();
			m_open.pop();
			delete n;
		}
		
		m_closed.clear();
		m_open_hash.clear();
	}


	void	set_verbose( bool v ) { m_verbose = v; }
	bool	verbose() const { return m_verbose; }

	void reset() {
		for ( typename Closed_List_Type::iterator i = m_closed.begin();
		      i != m_closed.end(); i++ ) {
			delete i->second;
		}
				

		while	(!m_open.empty() ) 
		{	
			Search_Node* n = m_open.front();
			m_open.pop();
			delete n;
		}
		
		m_closed.clear();
		m_open_hash.clear();
		m_max_depth=0;
	}
	
	virtual bool    is_goal( Search_Node* n  ){ 
		if( n->has_state() )
			return m_problem.goal( *(n->state()) ); 
		else{			
			n->parent()->state()->progress_lazy_state(  m_problem.task().actions()[ n->action() ] );	
			const bool is_goal = m_problem.goal( *( n->state() ) ); 
			n->parent()->state()->regress_lazy_state( m_problem.task().actions()[ n->action() ] );
			return is_goal;
		}
			
	}

	void	start( State *s = NULL ) {
	
		reset();
		
		if(!s)
			m_root = new Search_Node( m_problem.init(), 0.0f, no_op, NULL );	
		else
			m_root = new Search_Node( s, 0.0f, no_op, NULL );
#ifdef DEBUG
		std::cout << "Initial search node: ";
		m_root->print(std::cout);
		std::cout << std::endl;
#endif 
		m_open.push( m_root );
		m_open_hash.put( m_root );
		inc_gen();
	}

	virtual bool	find_solution( float& cost, std::vector<Action_Idx>& plan ) {
		Search_Node* end = do_search();
		if ( end == NULL ) return false;
		extract_plan( m_root, end, plan, cost );	
		
		return true;
	}

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
	
	bool          search_exhausted(){ return m_open.empty(); }

	Search_Node* 		get_node() {
		Search_Node *next = NULL;
		if(! m_open.empty() ) {
			next = m_open.front();
			m_open.pop();
			m_open_hash.erase( m_open_hash.retrieve_iterator( next) );
		}
		return next;
	}

	void	 	open_node( Search_Node *n ) {		
		m_open.push(n);
		m_open_hash.put(n);
		inc_gen();
		if(n->gn() + 1 > m_max_depth){
			//if( m_max_depth == 0 ) std::cout << std::endl;  
			m_max_depth = n->gn() + 1 ;
			if ( verbose() ) 
				std::cout << "[" << m_max_depth  <<"]" << std::flush;			
		}

	}

	virtual Search_Node*   process(  Search_Node *head ) {
		typedef typename Search_Model::Action_Iterator Iterator;
		Iterator it( this->problem() );
		
		int a = it.start( *(head->state()) );
		while ( a != no_op ) {	
			State *succ =  m_problem.next( *(head->state()), a ) ;			
			Search_Node* n = new Search_Node( succ, 1.0f, a, head );
			
			if ( is_closed( n ) ) {
				delete n;
				a = it.next();
				inc_closed();
				continue;
			}
			if( previously_hashed(n) ) {
				inc_closed();
				delete n;
			}
			else{
				open_node(n);			       
				if( is_goal( n ) )
					return n;
				
			}
			a = it.next();		
		} 

		
		return NULL;
	}
	
	
	virtual Search_Node*	 	do_search() {
		Search_Node *head = get_node();
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

	virtual bool 			previously_hashed( Search_Node *n ) {
		Search_Node *previous_copy = m_open_hash.retrieve(n);

		if( previous_copy != NULL ) 
			return true;
		
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


protected:

	void	extract_path( Search_Node* s, Search_Node* t, std::vector<Search_Node*>& plan ) {
		Search_Node* tmp = t;
		while( tmp != s) {
			plan.push_back(tmp);
			tmp = tmp->parent();
		}
		
		std::reverse(plan.begin(), plan.end());				
	}
	
protected:

	const Search_Model&			m_problem;
	std::queue<Search_Node*>		m_open;
        Closed_List_Type			m_closed, m_open_hash;
        Closed_List_Type*                       m_global_closed;
	unsigned				m_exp_count;
	unsigned				m_gen_count;
	unsigned				m_cl_count;
	unsigned                                m_max_depth;
	Search_Node*				m_root;
	std::vector<Action_Idx> 		m_app_set;
	bool					m_verbose;
	unsigned                                m_max_expanded;
};

}

}

}

#endif // brfs.hxx
