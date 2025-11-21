/*
Exercise: Cycle Detection: Given a connected, un-directed graph, determine if there 
are any cycles.
When performing a breadth first search from any vertex v in an un-directed graph, you 
may encounter a cross-edge that points to a previously discovered vertex that is 
neither an ancestor nor a descendant of the current vertex. Each “cross edge” defines 
a cycle in an un-directed graph. If the cross edge is x —> y, then since y is already 
discovered, we have a path from v to y (or from y to v since the graph is 
un-directed), where v is the starting vertex of BFS. So, we can say that we have a 
path v ~~ x ~ y ~~ v that forms a cycle. (Here, ~~ represents one more edge in the 
path, and ~ represents a direct edge).
*/

#include <iostream>
#include <queue> 	// for breadth first traversal
#include "Graph.hpp"

using namespace std;

void bfs(Graph<string>&, Vertex<string>*);

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

	cout << "Breadth First Traversal" << endl;
	bfs(g, g.getVertex(1));

	return 0;
}

/*
Breadth-First Search (BFS) is an algorithm used for traversing or searching tree or graph data structures.
It starts at the tree root (or some arbitrary node of a graph) and explores the neighbor nodes at the current
depth prior to moving on to nodes at the next depth level. BFS is often used to find the shortest path
from the source node to all other nodes in an unweighted graph.

Start at the Source Node:
=========================
   - Begin with the source node (or starting node) and enqueue it. If you're working with a graph,
   - the source node is typically the node from which you want to start the traversal.

Visit Neighbors at the Current Depth:
=====================================
   - Dequeue a node from the front of the queue (starting with the source node).
   - Visit all the neighbors (adjacent nodes) of the dequeued node that haven't been visited yet.
   - Enqueue each of these neighbors.

Move to the Next Depth Level:
=============================
   - After visiting all neighbors at the current depth, move to the next depth level by
   - repeating step 2 with the nodes that are now at the front of the queue.

Repeat Until All Nodes Are Visited:
===================================
   - Continue this process until the queue is empty, meaning that all nodes have been visited.

BFS is typically implemented using a queue data structure to keep track of the nodes to be visited.
The queue follows the First-In-First-Out (FIFO) principle, ensuring that nodes are processed in the order they are discovered.

Applications of BFS include finding the shortest path in an unweighted graph, analyzing network connectivity,
and solving puzzles with multiple states. 

The time complexity of BFS is generally O(V + E), where V is the number of vertices and E is the number of edges in the graph.
*/
void bfs(Graph<string>& g, Vertex<string>* v) {
	bool* seen = new bool[ g.size()+1 ]();			// boolean array to track visited nodes. +1 for 1-based indexing
	queue<Vertex<string>*> q;						// queue of Vertex pointers
	q.push(v);										// enqueue the starting node
	seen[ v->getId() ] = true;						// mark the starting node as being "seen"
	
	while ( !q.empty() ) {							// as long as the queue is not empty
		Vertex<string>* vert = q.front();			// dequeue the front vertex
		q.pop();									// remove it from the queue
		cout 	<< "Vertex " << vert->getId();		// print the vertex
		for (int v : vert->getConnections()){		// get all of the edges from the current vertex
			cout << "-->" 							// illustrate connection
				 << g.getVertex( v )->getId();		// print the key of the connected vertex
			if ( !seen[v] ) {						// if the current key has not been "seen"
				Vertex<string>* _v = g.getVertex(v);// get the vertex
				q.push( _v );						// enqueue the vertext
				seen[ v ] = true;					// mark it as seen
			}
		}
		cout << endl;								// just for nice printing
	}
	delete[] seen;									// free up dynamic memory
}