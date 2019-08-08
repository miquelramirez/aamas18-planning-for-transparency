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

#ifndef __NEW_NODE_COMPARARER__
#define __NEW_NODE_COMPARARER__

namespace aptk
{

namespace search {

template <typename Node>
class Node_Comparer_3H_FN
{             
public:
	bool operator()( Node* a, Node* b ) const {
		if ( dless( b->h1n(), a->h1n() ) ) return true;

		if( dequal( b->h1n(), a->h1n() ) ){
			// if ( dless( b->h2n(), a->h2n() ) ) return true;
			// if( dequal( b->h2n(), a->h2n() ) ){
			// 	if ( dless( b->h3n(), a->h3n() ) )  return true;
			// }
			if ( dless( b->fn(), a->fn() ) ) return true;
			if( dequal( b->fn(), a->fn() ) ){
				if ( dless( b->gn(), a->gn() ) )  return true;
			}
		}
		return false;

		
	}
};

template <typename Node>
class Node_Comparer_2H
{             
public:
	bool operator()( Node* a, Node* b ) const {
		if ( dless( b->h1n(), a->h1n() ) ) return true;

		if( dequal( b->h1n(), a->h1n() ) ){
			if ( dless( b->h2n(), a->h2n() ) ) return true;
			if ( dequal( b->h2n(), a->h2n() ) ) {
				if (dless(b->gn(),a->gn())) return true;
			}
		}
		//if ( dless( b->gn(), a->gn() ) )  return true;
		return false;

		
	}
};   

template <typename Node>
class Node_Comparer_2H_ehc
{             
public:
	bool operator()( Node* a, Node* b ) const {
		if ( dless( b->h2n(), a->h2n() ) ) return true;

		if( dequal( b->h2n(), a->h2n() ) ){
			if ( dless( b->h1n(), a->h1n() ) ) return true;
			if ( dequal( b->h1n(), a->h1n() ) ) {
				if (dless(b->gn(),a->gn())) return true;
			}
		}
		//if ( dless( b->gn(), a->gn() ) )  return true;
		return false;

		
	}
};   

template <typename Node>
class Node_Comparer_Second
{             
public:
	bool operator()( Node* a, Node* b ) const {
		if ( dless( b->h2novel(), a->h2novel() ) ) return true;

		if( dequal( b->h2novel(), a->h2novel() ) ){
			if ( dless( b->h2n(), a->h2n() ) ) return true;
			if ( dequal( b->h2n(), a->h2n() ) ) {
				if (dless(b->gn(),a->gn())) return true;
			}
		}
		//if ( dless( b->gn(), a->gn() ) )  return true;
		return false;

		
	}
};   

template <typename Node>
class Node_Comparer_Third
{             
public:
	bool operator()( Node* a, Node* b ) const {
		if ( dless( b->h3novel(), a->h3novel() ) ) return true;

		if( dequal( b->h3novel(), a->h3novel() ) ){
			if ( dless( b->h3n(), a->h3n() ) ) return true;
			if ( dequal( b->h3n(), a->h3n() ) ) {
				if (dless(b->gn(),a->gn())) return true;
			}
		}
		//if ( dless( b->gn(), a->gn() ) )  return true;
		return false;

		
	}
};   

// template <typename Node>
// class Node_Comparer_2H
// {             
// public:
// 	bool operator()( Node* a, Node* b ) const {
// 		if ( dless( b->h2n(), a->h2n() ) ) return true;

// 		if( dequal( b->h2n(), a->h2n() ) ){
// 			if ( dless( b->h1n(), a->h1n() ) ) return true;
// 			if ( dequal( b->h1n(), a->h1n() ) ) {
// 				if (dless(b->gn(),a->gn())) return true;
// 			}
// 		}
// 		//if ( dless( b->gn(), a->gn() ) )  return true;
// 		return false;

		
// 	}
// };   

}

}

#endif // 
