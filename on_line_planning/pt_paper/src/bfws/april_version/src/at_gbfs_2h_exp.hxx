/*
Lightweight Automated Planning Toolkit
Copyright (C) 2013
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

#ifndef __ANYTIME_SINGLE_QUEUE_DOUBLE_EXP_HEURISTIC_GREEDY_BEST_FIRST_SEARCH__
#define __ANYTIME_SINGLE_QUEUE_DOUBLE_EXP_HEURISTIC_GREEDY_BEST_FIRST_SEARCH__

#include <aptk/search_prob.hxx>
#include <aptk/resources_control.hxx>
#include <aptk/closed_list.hxx>
#include <landmark_graph_manager.hxx>
#include <vector>
#include <algorithm>
#include <iostream>
#include <aptk/hash_table.hxx>
#include "2h_exp_node.hxx"

namespace aptk {

namespace search {

namespace gbfs_2h_exp{



template <typename Search_Model, typename First_Heuristic, typename Second_Heuristic, typename Local_Search, typename Open_List_Type >
class AT_GBFS_2H_EXP {

public:

	typedef	        typename Search_Model::State_Type		        State;
	typedef  	typename Open_List_Type::Node_Type		        Search_Node;
	typedef 	Closed_List< Search_Node >			        Closed_List_Type;
	typedef         aptk::agnostic::Landmarks_Graph_Manager<Search_Model>   Landmarks_Graph_Manager;

	AT_GBFS_2H_EXP( 	const Search_Model& search_problem ) 
	: m_problem( search_problem ), m_exp_count(0), m_gen_count(0), m_pruned_B_count(0),
	  m_dead_end_count(0), m_open_repl_count(0),m_B( infty ), m_time_budget(infty), m_max_h2n(no_such_index), m_verbose( true ), m_ignore_novelty(false), m_stall_size( no_such_index ), m_stalled( 0 ), m_max_local_try( 0 ), m_local_try(0), m_local_search_size(0) {	
		m_first_h = new First_Heuristic( search_problem );
		m_second_h = new Second_Heuristic( search_problem );
		m_local_search = new Local_Search( search_problem );
		
		m_local_search->set_global_closed( &m_closed );
		m_local_search->set_bound(1);
		
	}

	virtual ~AT_GBFS_2H_EXP() {
		for ( typename Closed_List_Type::iterator i = m_closed.begin();
			i != m_closed.end(); i++ ) {
			delete i->second;
		}
		while	(!m_open.empty() ) 
		{	
			Search_Node* n = m_open.pop();
			delete n;
		}
		m_closed.clear();

		delete m_first_h;
		delete m_second_h;
		delete m_local_search;
	}

	void	start( float B = infty) {
		m_B = B;
		m_root = new Search_Node( m_problem.init(), 0.0f, no_op, NULL );	
		m_stalled = 0;
		m_local_try = 0;
		m_first_h->init();		
				
		eval(m_root);

		#ifdef DEBUG
		if ( m_verbose ) {
			std::cout << "Initial search node: ";
			m_root->print(std::cout);
			std::cout << std::endl;
			m_root->state()->print( std::cout );
			std::cout << std::endl;
		}
		#endif 
		m_open.insert( m_root );

		inc_gen();
	}

	void	set_arity( float v ){ m_first_h->set_arity( v ); }

	bool	find_solution( float& cost, std::vector<Action_Idx>& plan ) {
		m_t0 = time_used();
		Search_Node* end = do_search();
		if ( end == NULL ) return false;
		extract_plan( m_root, end, plan, cost );	
		
		return true;
	}

	void                    set_max_expanded( unsigned v )  { 
		m_local_search_size = v; 
		if(m_local_search) m_local_search->set_max_expanded(v); 
	}
	void                    set_stall_size( unsigned v )  { m_stall_size = v; }
	void                    set_local_tries( unsigned v )  { m_max_local_try = v; }


	float			bound() const			{ return m_B; }
	void			set_bound( float v ) 		{ m_B = v; }

	void			inc_gen()			{ m_gen_count++; }
	unsigned		generated() const		{ return m_gen_count; }
	void			inc_eval()			{ m_exp_count++; }
	unsigned		expanded() const		{ return m_exp_count; }
	void			inc_pruned_bound() 		{ m_pruned_B_count++; }
	unsigned		pruned_by_bound() const		{ return m_pruned_B_count; }
	void			inc_dead_end()			{ m_dead_end_count++; }
	unsigned		dead_ends() const		{ return m_dead_end_count; }
	void			inc_replaced_open()		{ m_open_repl_count++; }
	unsigned		open_repl() const		{ return m_open_repl_count; }

	void			set_budget( float v ) 		{ m_time_budget = v; }
	float			time_budget() const		{ return m_time_budget; }

	float			t0() const			{ return m_t0; }

	void 			close( Search_Node* n ) 	{  m_closed.put(n); }
	Closed_List_Type&	closed() 			{ return m_closed; }

	const	Search_Model&	problem() const			{ return m_problem; }

	First_Heuristic&	h1()				{ return *m_first_h; }
	Second_Heuristic&	h2()				{ return *m_second_h; }
	
	void			set_verbose( bool v ) 		{ m_verbose = v; }
    	void			set_ignore_novelty( bool v )    { m_ignore_novelty = v; }
	void			set_ignore_local_novelty( bool v )    { m_local_search->set_ignore_novelty(v); }

	
	void			eval( Search_Node* candidate ) {

		

		m_second_h->eval( *(candidate->state()), candidate->h2n() );	

		candidate->goals_unachieved() =  candidate->h2n();
		//set partition for novelty
		candidate->partition() = candidate->goals_unachieved();
		
		if ( candidate->goals_unachieved() == 0 || m_ignore_novelty ){
			
			candidate->h1n()  = 1;
		}
		else{
			candidate->goals_unachieved()--;
			candidate->partition()--;			
			m_first_h->eval( candidate, candidate->h1n() );
			//std::cout << candidate->h1n() << " / " << std::flush;
			
		}

		

		if(candidate->h2n() < m_max_h2n ){
			m_max_h2n = candidate->h2n();

			m_stalled = 0;
			m_local_try = 0;

			if ( m_verbose ) {
				//candidate->state()->print( std::cout );
				std::cout << "--[" << m_max_h2n << "/"<< expanded()<< "]--" << std::endl;
				//std::cout << "[ n:" << candidate->h1n()  <<" - hl:" << candidate->h2n() <<" - #g:" << candidate->goals_unachieved() <<" - h_a:" << candidate->h3n() <<" - gn: " << candidate->gn()  <<"]" << std::endl;
			}
		}
		else{
			m_stalled++;
		}

	}

	
	bool 		is_closed( Search_Node* n ) 	{ 
		Search_Node* n2 = this->closed().retrieve(n);

		if ( n2 != NULL ) {
			if ( n2->gn() <= n->gn() ) {
				// The node we generated is a worse path than
				// the one we already found
				return true;
			}
			// Otherwise, we put it into Open and remove
			// n2 from closed
			this->closed().erase( this->closed().retrieve_iterator( n2 ) );
		}
		return false;
	}

	Search_Node* 		get_node() {
		Search_Node *next = NULL;
		if(! m_open.empty() ) {
			next = m_open.pop();
		}
		return next;
	}

	void	 	open_node( Search_Node *n ) {
		m_open.insert(n);
		inc_gen();

		// if( generated() % 1000 == 0){
		// 	std::cout << "\nGenerated " << generated() << std::endl;
		// }
	}
	/**
	 * Succ Generator Process
	 */
	virtual void 			process(  Search_Node *head ) {

		
#ifdef DEBUG
		if ( m_verbose ) {
			std::cout << "Expanding:" << std::endl;
			head->print(std::cout);
			std::cout << std::endl;
			head->state()->print( std::cout );
			std::cout << std::endl;
		}
#endif
		//static unsigned ha=0;
		//static unsigned nonha=0;
		
		//		std::cout << "ha: "<< ha << "nonha: "<< nonha << std::endl; 

		
		std::vector< aptk::Action_Idx > app_set;
		this->problem().applicable_set_v2( *(head->state()), app_set );

			
		for (unsigned i = 0; i < app_set.size(); ++i ) {
			int a = app_set[i];

			//bool is_helpful = head->is_po(a); 

			//State *succ = is_helpful ? m_problem.next( *(head->state()), a ) : nullptr; 
			State *succ =  m_problem.next( *(head->state()), a );
			
			Search_Node* n = new Search_Node( succ, m_problem.cost( *(head->state()), a ), a, head  );			
			
			#ifdef DEBUG
			if ( m_verbose ) {
				std::cout << "Successor:" << std::endl;
				n->print(std::cout);
				std::cout << std::endl;
				if(n->has_state())
				n->state()->print( std::cout );
				std::cout << std::endl;
			}
			#endif

			eval( n );
			//pruning
			// if (n->h1n() > 1){
			//     close(n);
			//     continue;
			// }
						       
#ifdef DEBUG
			if ( m_verbose )
				std::cout << "Inserted into OPEN" << std::endl;
#endif
			open_node(n);	
				

		} 
		inc_eval();
	}

	virtual Search_Node*	 	do_search() {
		Search_Node *head = get_node();
		int counter =0;
		while(head) {
				
			if ( head->gn() >= bound() )  {
				inc_pruned_bound();
				close(head);
				head = get_node();
				continue;
			}
			if( ! head->has_state() )
			  head->set_state( m_problem.next(*(head->parent()->state()), head->action()) );

			if(m_problem.goal(*(head->state()))) {
				close(head);
				set_bound( head->gn() );	
				return head;
			}
			if ( (time_used() - m_t0 ) > m_time_budget )
				return NULL;
			// MRJ: What if we don't compute h_add and keep using the parent's h_add value for non-helpful 

			if ( is_closed( head ) ) {
				#ifdef DEBUG
				if ( m_verbose )
					std::cout << "Already in CLOSED" << std::endl;
				#endif
				delete head;
				head = get_node();
				continue;
			}
			process(head);
			
			//ADD LOCAL SEACH NODES COMPUTING H incrementally TRAVERSING TREE As DFS
			// try FIFO tie breaking for openlist for global and local
			
			if( m_stalled > m_stall_size and m_local_try < m_max_local_try ){

				m_local_search->start( head );
				Search_Node* end = m_local_search->do_search( );
				if(end){
					//eval(end);
					//open_node(end);
					std::cout << "Local Search Successful" <<std::endl;
				}
				m_local_search->dump_nodes( m_open );			       
				m_stalled = 0;
				m_local_try++;
			}
			else
				close(head);
			counter++;
			head = get_node();
		}
		return NULL;
	}


protected:

	void	extract_plan( Search_Node* s, Search_Node* t, std::vector<Action_Idx>& plan, float& cost ) {
		Search_Node *tmp = t;
		cost = 0.0f;
		while( tmp != s) {
			cost += m_problem.cost( *(tmp->state()), tmp->action() );
			plan.push_back(tmp->action());
			tmp = tmp->parent();
		}
		
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
	
protected:

	const Search_Model&			m_problem;
	First_Heuristic*			m_first_h;
	Second_Heuristic*			m_second_h;

	Open_List_Type				m_open;
	Closed_List_Type			m_closed;
	unsigned				m_exp_count;
	unsigned				m_gen_count;
	unsigned				m_pruned_B_count;
	unsigned				m_dead_end_count;
	unsigned				m_open_repl_count;
	float					m_B;
	float					m_time_budget;
	float					m_t0;
	Search_Node*				m_root;
	std::vector<Action_Idx> 		m_app_set;
	unsigned                                m_max_h2n;
	bool					m_verbose;
        bool                                    m_ignore_novelty;

	Local_Search*                           m_local_search;
	unsigned                                m_stall_size;
	unsigned                                m_stalled;
	unsigned                                m_max_local_try;
	unsigned                                m_local_try;
	unsigned                                m_local_search_size;
};

}

}

}

#endif // at_gbfs_2h_exp.hxx
