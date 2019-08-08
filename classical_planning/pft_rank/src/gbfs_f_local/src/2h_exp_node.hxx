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

#ifndef __EXP_2H_NODE__
#define __EXP_2H_NODE__

#include <aptk/search_prob.hxx>
#include <aptk/resources_control.hxx>
#include <vector>
#include <algorithm>
#include <iostream>
#include <aptk/hash_table.hxx>

namespace aptk {

namespace search {

namespace gbfs_2h_exp{

template <typename Search_Model, typename State>
class Node {
public:
	

	typedef State                            State_Type;
	typedef Node<Search_Model,State>*        Node_Ptr;
	typedef typename std::vector< Node<Search_Model,State>* >                      Node_Vec_Ptr;
	typedef typename std::vector< Node<Search_Model,State>* >::reverse_iterator    Node_Vec_Ptr_Rit;
	typedef typename std::vector< Node<Search_Model,State>* >::iterator            Node_Vec_Ptr_It;

	Node( State* s, float cost, Action_Idx action, Node<Search_Model,State>* parent ) 
		: m_state( s ), m_parent( parent ), m_action(action), m_g( 0 ), m_g_unit( 0 ), m_f(0), m_h1(0), m_h2(0), m_partition(0), m_seen(false), m_helpful(false), m_novelty(1) {
		m_g = ( parent ? parent->m_g + cost : 0.0f);
		m_g_unit = ( parent ? parent->m_g_unit + 1.0f : 0.0f);
	}
	
	virtual ~Node() {
		if ( m_state != NULL ) delete m_state;
	}

	unsigned&		h1n()				{ return m_h1; }
	unsigned		h1n() const 			{ return m_h1; }
	unsigned&		h2n()				{ return m_h2; }
	unsigned		h2n() const 			{ return m_h2; }
	unsigned&      		partition()    	  { return m_partition; }			
	unsigned       		partition() const { return m_partition; }
	unsigned&      		novelty()	{ return m_novelty; }			
	unsigned       		novelty() const	{ return m_novelty; }
	unsigned                goals_unachieved() const        { return m_goals_unachieved; }                
	unsigned&               goals_unachieved()              { return m_goals_unachieved; }                
	float&			gn()				{ return m_g; }			
	float			gn() const 			{ return m_g; }
	float&			gn_unit()			{ return m_g_unit; }			
	float			gn_unit() const 		{ return m_g_unit; }
	float&			fn()				{ return m_f; }
	float			fn() const			{ return m_f; }
	Node_Ptr		parent()   			{ return m_parent; }
	const Node_Ptr		parent() const 			{ return m_parent; }
	Action_Idx		action() const 			{ return m_action; }
	State*			state()				{ return m_state; }
        void			set_state( State* s )  		{ m_state = s; }
	bool			has_state() const		{ return m_state != NULL; }
	const State&		state() const 			{ return *m_state; }
	void			set_seen( )			{ m_seen = true; }
	bool			seen() const			{ return m_seen; }
	void			set_helpful( )			{ m_helpful = true; }
	bool                    is_helpful()                    { return m_helpful; }

    // Used in Novelty_Parition
        bool                  is_better( Node* n ) const{
	        bool ret = false;
		
		float n1 = this->h2n() + this->gn();
		float n2 = n->h2n() + n->gn();
                ret =  n1 < n2;
                if(ret) return ret;

                if(n1 == n2){
                        ret =  this->h2n() < n->h2n();
                        if(ret) return ret;

                        if(this->h2n() == n->h2n()){
                                ret =  this->gn() < n->gn();
                        }

                }

                return ret;
		
	}
  
      	
	void			print( std::ostream& os ) const {
		os << "{@ = " << this << ", s = " << m_state << ", parent = " << m_parent << ", g(n) = ";
		os << m_g << ", h1(n) = " << m_h1 << ", h2(n) = " << m_h2  << ", f(n) = " << m_f << "}";
	}

	bool   	operator==( const Node<Search_Model,State>& o ) const {
		
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

	size_t      hash() const { return m_state ? m_state->hash() : m_hash; }

	void        update_hash() {
		Hash_Key hasher;
		hasher.add( m_action );
		if ( m_parent != NULL )
			hasher.add( m_parent->state()->fluent_vec() );
		m_hash = (size_t)hasher;
	}

public:

	State*		m_state;
	Node_Ptr	m_parent;
	Action_Idx	m_action;
	float		m_g;
	float		m_g_unit;
	float		m_f;
	unsigned	m_h1;
	unsigned	m_h2;
        unsigned        m_partition;
	unsigned        m_goals_unachieved;
	bool		m_seen;
	bool		m_helpful;
	size_t		m_hash;
	unsigned        m_novelty;
	
};

}

}

}

#endif
