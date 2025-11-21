/*
Exercise: Strongly Connected Graph
Given a directed graph, check if it is strongly connected or not. A directed graph is 
considered “strongly connected” if every vertex is reachable from every other vertex.
A simple solution is to perform a depth or breadth first traversal starting from 
every vertex in the graph. If each DFS/BFS call visits every other vertex in the 
graph, then the graph is strongly connected. Use a vector to track the “visited” 
status of the vertices. 
*/

#include <iostream>
#include <vector>
#include <stack>	// for depth first traversal
#include "Graph.hpp"

using namespace std;

void dfs(Graph<string>&, Vertex<string>*);

int main() {
	Graph<string> g;				// create graph object

	for (int i = 1; i <= 10; i++) 	// create ten vertex objects
		g.addVertex(i, "payload");	// keys will be 1 - 10

	// add edges
	//        F   T   W		(F)rom, (T)o, (W)eight . . . not (F)or (T)he (W)in
	g.addEdge(1,  2,  5);
	g.addEdge(1,  5,  2);
	g.addEdge(5,  6,  4);
	g.addEdge(5,  8,  7);
	g.addEdge(1,  9,  3);
	g.addEdge(2,  3,  8);
	g.addEdge(9,  10, 1);
	g.addEdge(3,  4,  1);
	g.addEdge(5,  7,  9);
	g.addEdge(9,  11, 3);	// this call to add edge will add the new vertex with key = 11
	g.addEdge(11, 10, 2);

	// print graph
	cout 	<< "\nGraph has " 
			<< g.size() << " vertices"	// print number of vertices
			<< g << endl;				// print using overloaded graph stream insertion

	cout << "\nDepth First Traversal" << endl;
	dfs(g, g.getVertex(1));

	return 0;
}

/*
Depth-First Search (DFS) is an algorithm used for traversing or searching tree or graph data structures.
Unlike Breadth-First Search (BFS), DFS explores as far as possible along each branch before backtracking.
It starts at the root node (or an arbitrary node in the case of a graph) and explores as deeply 
as possible along each branch before backtracking.

Start at the Source Node:
=========================
   - Begin with the source node (or starting node). If you're working with a graph, the source node is
   - typically the node from which you want to start the traversal.

Explore as Far as Possible:
===========================
   - Move to an adjacent unvisited node and repeat the process. If there are multiple adjacent nodes,
   - choose one and proceed. This creates a recursive call or a stack-based approach to remember the path.

Backtrack When Necessary:
=========================
   - If there are no more unvisited nodes from the current position, backtrack to the previous node 
   - and continue exploring other unvisited branches.

Repeat Until All Nodes Are Visited:
===================================
   - Continue this process until stack is empty meaning all nodes are visited.

DFS can be implemented using recursion or an explicit stack data structure. In the recursive approach,
the function calls act as the stack, and in the stack-based approach, an actual stack is used to keep track of nodes to be visited.

Applications of DFS include topological sorting, finding connected components in a graph,
solving puzzles (like mazes or Sudoku), and pathfinding algorithms. 

The time complexity of DFS is generally O(V + E), where V is the number of vertices and E is the number of edges in the graph.
*/
void dfs(Graph<string>& g, Vertex<string>* r) {		// iterative depth first search using explicit stack
	char* c = new char[ g.size()+1 ]();				// array to store "visited" status. +1 for 1-based indexing
	stack< Vertex<string>* > s;						// stack of Vertex pointers to store edges
	s.push(r);										// push starting vertex

	while( s.size() > 0 ) {							// as long as the stack is not empty
		Vertex< string >* vert = s.top();			// get current Vertex
		int key = vert->getId();					// get the key of the current vertex
		cout << key << endl;						// print so we can see
		s.pop();									// pop current Vertex from Stack
		if( c[ key ] != 'v' ){						// has this vertex been visited?
			c[ key ]  = 'v';						// It has not. Mark it as visited
			vector<int> edges = g.getVertices();	// edges connected to i
			for (int key : vert->getConnections())	// loop through edges stemming from current vertex
				s.push( g.getVertex( key ) );		// push each vertext on to stack
		}
	}
	delete[] c;										// free up dynamic memory
}