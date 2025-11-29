/*
Exercise: Level order traversal of a binary tree
Given a binary tree, print its nodes level by level, i.e., print all nodes of level 1 first, followed by nodes of level 2 
and so on... Print nodes for any level from left to right.
Print all nodes of level 1 first, followed by level 2, until level h, where h is the tree’s height. We can print all nodes 
present in a level by modifying the preorder traversal on the tree.
*/

#include <iostream>
#include <queue> 	// for breadth first traversal
#include "Graph.hpp"

using namespace std;

void printTree(Graph<string>&, Vertex<string>*);

int main() {
	Graph<string> g;				// create graph object

	for (int i = 1; i <= 10; i++) 	// create ten vertex objects
		g.addVertex(i, "payload");	// keys will be 1 - 10

	// Add edges in a Binary Tree configuration
	//        F   T   W		(F)rom, (T)o, (W)eight
	g.addEdge(1,  2,  5);
	g.addEdge(1,  3,  2);
	g.addEdge(2,  4,  4);
	g.addEdge(2,  5,  7);
	g.addEdge(3,  6,  3);
	g.addEdge(3,  7,  8);
	g.addEdge(4,  8,  1);
	g.addEdge(4,  9,  1);
	g.addEdge(5,  10, 9);
	//g.addEdge(5,  11, 3);
	//g.addEdge(6,  12, 2);

	// print graph
	cout 	<< "\nGraph has " 
			<< g.size() << " vertices"	// print number of vertices
			<< g << endl;				// print using overloaded graph stream insertion

	cout << "Level Order Traversal" << endl;
	printTree(g, g.getVertex(1));

	return 0;
}


void printTree(Graph<string>& g, Vertex<string>* v) {
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