#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <iostream>

/// vertices are characters
typedef char vertex;
/// weights are numbers
typedef int weight;
/// each edge is a tuple s_vertex : e_vertex : weight
using edge = std::tuple<vertex, vertex, weight>; 
/// for each vertex we will have a list of it's edges to children
using children_list = std::multiset<edge>;
/// the graph is represented as a lists of adjacent for each vertex
using graph = std::unordered_map<vertex, children_list>;

using graphMatrix = std::unordered_map<vertex, std::unordered_map<vertex, weight>>;

/**
* @brief Creates a graph with some edges.
* @retval the created graph
*/
graph init_graph()
{
	edge a2b( 'a', 'b', 9 ),
		a2c( 'a', 'c', 3 ),
		a2c_( 'a', 'c', 3 ),
		a2d( 'a', 'd', 5 ),
		b2e( 'b', 'e', 1 ),
		c2b( 'c', 'b', 2 ),
		c2d( 'c', 'd', 1 ),
		d2e( 'd', 'e', 7 ),
		e2a( 'e', 'a', 1 ),
		e2c( 'e', 'c', 6 );

	graph g;
	g[ 'a' ] = { a2b, a2c, a2c_, a2d };
	g[ 'b' ] = { b2e };
	g[ 'c' ] = { c2b, c2d };
	g[ 'd' ] = { d2e };
	g[ 'e' ] = { e2a, e2c };
	return g;
}

/**
* @brief simply output a graphs contain
* @param[in] G: graph to be outputted
*/
void print_graph( const graph& G )
{

	for ( const std::pair<vertex, children_list>& v_child : G )
	{
		std::cout << "from " << v_child.first  << " to : { ";
		for ( const edge& e : v_child.second )
		{
			std::cout << "( " << std::get<1>( e ) << ", " <<  std::get<2>( e )  << " )" ;
		}
		std::cout << "}" << std::endl;
	}

	std::cout << std::endl << std::endl;
}

int main()
{
	graph G = init_graph();
	std::cout << "\nthe given graph contains:"<< std::endl;
	print_graph( G );


	graphMatrix g;
	g[ 'a' ][ 'b' ] = 4;

	return 0;
}