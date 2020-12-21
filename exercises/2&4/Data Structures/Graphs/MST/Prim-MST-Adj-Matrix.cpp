// A C++ program for Prim's Minimum 
// Spanning Tree (MST) algorithm. The program is 
// for adjacency matrix representation of the graph 

// Source: https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/

#include <iostream> 

// Number of vertices in the graph 
#define V 9 

// A utility function to find the vertex with 
// minimum key value, from the set of vertices 
// not yet included in MST 
int minKey( int key[], bool mstSet[] )
{
	// Initialize min value 
	int min = INT_MAX, min_index = -1;

	for ( int v = 0; v < V; v++ )
	{
		if ( mstSet[ v ] == false && key[ v ] < min )
		{
			min = key[ v ];
			min_index = v;
		}
	}

	return min_index;
}

// A utility function to print the 
// constructed MST stored in parent[] 
void printMST( int parent[], int graph[ V ][ V ] )
{
	std::cout << "Edge \tWeight\n";
	for ( int i = 1; i < V; i++ )
		std::cout << parent[ i ] << " - " << i << " \t" << graph[ i ][ parent[ i ] ] << " \n";
}

// Function to construct and print MST for 
// a graph represented using adjacency 
// matrix representation
// Time complexity O(|V|^2)
void primMST( int graph[ V ][ V ] )
{
	// Array to store constructed MST 
	int parent[ V ] = { -1, };

	// Key values used to pick minimum weight edge in cut 
	int key[ V ] = { INT_MAX, };

	// To represent set of vertices included in MST 
	bool mstSet[ V ] = { false, };

	// Always include first 1st vertex in MST. 
	// Make key 0 so that this vertex is picked as first vertex. 
	key[ 0 ] = 0;
	parent[ 0 ] = -1; // First node is always root of MST 

	// The MST will have V vertices 
	for ( int count = 0; count < V - 1; count++ )
	{
		// Pick the minimum key vertex from the 
		// set of vertices not yet included in MST 
		int u = minKey( key, mstSet );

		// Add the picked vertex to the MST Set 
		mstSet[ u ] = true;

		// Update key value and parent index of 
		// the adjacent vertices of the picked vertex. 
		// Consider only those vertices which are not 
		// yet included in MST 
		for ( int v = 0; v < V; v++ )

			// graph[u][v] is non zero only for adjacent vertices of m 
			// mstSet[v] is false for vertices not yet included in MST 
			// Update the key only if graph[u][v] is smaller than key[v] 
			if ( graph[ u ][ v ] && mstSet[ v ] == false && graph[ u ][ v ] < key[ v ] )
			{
				parent[ v ] = u;
				key[ v ] = graph[ u ][ v ];
			}
	}

	// print the constructed MST 
	printMST( parent, graph );
}
/*
int main() 
{ 
	int graph[V][V] = { { 0, 4 , 0, 0 , 0 , 0 , 0, 8 , 0 }, 
						{ 4, 0 , 8, 0 , 0 , 0 , 0, 11, 0 }, 
						{ 0, 8 , 0, 7 , 0 , 4 , 0, 0 , 2 }, 
						{ 0, 0 , 7, 0 , 9 , 14, 0, 0 , 0 }, 
						{ 0, 0 , 0, 9 , 0 , 10, 0, 0 , 0 }, 
						{ 0, 0 , 4, 14, 10, 0 , 2, 0 , 0 }, 
						{ 0, 0 , 0, 0 , 0 , 2 , 0, 1 , 6 }, 
						{ 8, 11, 0, 0 , 0 , 0 , 1, 0 , 7 },
						{ 0, 0 , 2, 0 , 0 , 0 , 6, 7 , 0 } }; 

				// TODO: направи го със списък на съседи		
	// Print the solution 
	primMST(graph); 

	return 0; 
}
*/