/*
This is a common problem in Computer Science. Given a maze in the form of binary 
rectangular matrix, find the shortest path’s length from a given source to a given 
destination. A path consists of cells with 1, and at any given moment, we can only 
move one cell in one of the four directions. The valid moves are:
Go Top: (x, y) ——> (x – 1, y)
Go Left:  (x, y) ——> (x, y – 1)
Go Down:  (x, y) ——> (x + 1, y)
Go Right:  (x, y) ——> (x, y + 1)
*/

#include <iostream>
#include <queue> 	// for breadth first traversal
#include "Graph.hpp"

using namespace std;

void bfs(Graph<string>&, Vertex<string>*);

int main() {
    /*
    1.Create an empty queue and enqueue the source vertex having a distance 0 from the 
      source (itself) and mark it as visited.
    2.Continue until the queue is exhausted. 
        a. Dequeue the front vertex.
        b. If the vertex is the destination node, then return its distance.
        c. Otherwise, for each of four adjacent cells, enqueue each vertex with +1 
           distance and mark them as visited.
    3.If the destination has not been reached after visiting all vertices, return false.
    4.It may be helpful to modify the Vertex class to have a property to store the 
      distance from the source.
    5.It may be helpful to modify the Vertex class to have an x and y property to store 
      its coordinates in the matrix.
    6.Also, be sure to stay in bounds. You will need to check to see if you are on a 
      matrix edge.
    */

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