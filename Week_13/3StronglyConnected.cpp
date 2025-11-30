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

bool isStronglyConnected(Graph<string>&);

int main() {
	// Tests written by DeepSeek (11/30/2025)
    // Test Case 1: Strongly Connected Graph
    Graph<string> g1;
    for (int i = 1; i <= 4; i++)  g1.addVertex(i, "payload");
    
    // Create a strongly connected graph
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    g1.addEdge(4, 1);
    
    cout << "Testing Graph 1 (Strongly Connected) -\n";
    bool result1 = isStronglyConnected(g1);
    cout << "Graph 1 is strongly connected: " << (result1 ? "Yes" : "No") << endl << endl;
    
    // Test Case 2: Not Strongly Connected Graph
    Graph<string> g2;
    for (int i = 1; i <= 4; i++)  g2.addVertex(i, "payload");
    
    // Create a graph that is not strongly connected (missing edge from 4 back to 1)
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.addEdge(3, 4);
    
    
    cout << "Testing Graph 2 (Not Strongly Connected) -\n";
    bool result2 = isStronglyConnected(g2);
    cout << "Graph 2 is strongly connected: " << (result2 ? "Yes" : "No") << endl << endl;
    
    // Test Case 3: Single Node
    Graph<string> g3;
    g3.addVertex(1, "single");
    
    cout << "Testing Graph 3 (Single Vertex) -\n";
    bool result3 = isStronglyConnected(g3);
    cout << "Graph 3 is strongly connected: " << (result3 ? "Yes" : "No") << endl;
    
    return 0;
}

// Function to perform DFS and check if all vertices are visited
bool dfs(Graph<string>& g, Vertex<string>* r) {
    char* c = new char[ g.size()+1 ]();				// array to store "visited" status. +1 for 1-based indexing
	stack< Vertex<string>* > s;						// stack of Vertex pointers to store edges
    s.push(r);										// push starting vertex
	int visitedCount = 0; // keep track of number of visited vertices, must be the same as the total 
						  // number of vertices in the graph for it to be strongly connected
    
    while( s.size() > 0 ) {							// as long as the stack is not empty
        Vertex< string >* vert = s.top();			// get current Vertex
		int key = vert->getId();					// get the key of the current vertex
        s.pop();									// pop current Vertex from Stack
    	if( c[ key ] != 'v' ){						// has this vertex been visited?
            c[ key ]  = 'v';						// It has not. Mark it as visited
            visitedCount++; // keep track of nodes visited in this dfs
            vector<int> edges = g.getVertices();	// edges connected to i
			for (int key : vert->getConnections())	// loop through edges stemming from current vertex
				s.push( g.getVertex( key ) );		// push each vertext on to stack
        }
    }
    
    // Check if we visited all vertices
    return visitedCount == g.size();
}

// Run a dfs for each node, if they all return true then the graph is strongly connected
bool isStronglyConnected(Graph<string>& g) {
    vector<int> vertices = g.getVertices();
    
    // Perform DFS from every vertex
    for (int key : vertices) {
        Vertex<string>* vert = g.getVertex(key);
        if (vert == nullptr) continue;
        
        vector<bool> visited(g.size() + 1, false);
        if ( !dfs(g, vert) )  return false; // if dfs from any vertex doesn't visit all
    }									    // other vertices, graph is not strongly connected
    
    return true;
}