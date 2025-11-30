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
#include <queue>
#include <vector>
#include "Graph.hpp"

using namespace std;

void bfs(Graph<string>&, Vertex<string>*);
bool hasCycleBFS(Graph<string>& g, Vertex<string>* start);

int main() {

	// Tests written by DeepSeek (11/30/2025)
    Graph<string> g;               // create graph object
    for (int i = 1; i <= 10; i++)  // create ten vertex objects
        g.addVertex(i, "payload"); // keys will be 1 - 10

    // add edges - making it an undirected graph by adding both directions
    //        F   T   W       (F)rom, (T)o, (W)eight
    g.addEdge(1,  2,  5);
    g.addEdge(2,  1,  5);  // undirected - add reverse edge
    g.addEdge(1,  5,  2);
    g.addEdge(5,  1,  2);  // undirected - add reverse edge
    g.addEdge(5,  6,  4);
    g.addEdge(6,  5,  4);  // undirected - add reverse edge
    g.addEdge(5,  8,  7);
    g.addEdge(8,  5,  7);  // undirected - add reverse edge
    g.addEdge(1,  9,  3);
    g.addEdge(9,  1,  3);  // undirected - add reverse edge
    g.addEdge(2,  3,  8);
    g.addEdge(3,  2,  8);  // undirected - add reverse edge
    g.addEdge(9,  10, 1);
    g.addEdge(10, 9,  1);  // undirected - add reverse edge
    g.addEdge(3,  4,  1);
    g.addEdge(4,  3,  1);  // undirected - add reverse edge
    g.addEdge(5,  7,  9);
    g.addEdge(7,  5,  9);  // undirected - add reverse edge
    g.addEdge(9,  11, 3);  // this call to add edge will add the new vertex with key = 11
    g.addEdge(11, 9,  3);  // undirected - add reverse edge
    g.addEdge(11, 10, 2);
    g.addEdge(10, 11, 2);  // undirected - add reverse edge

    cout << "Cycle Detection - \n";
    bool hasCycle = hasCycleBFS(g, g.getVertex(1));
    if (hasCycle) {
        cout << "The graph contains cycles!" << endl;
    } else {
        cout << "The graph is acyclic (no cycles found)." << endl;
    }

    // Graph without cycles (tree)
    cout << "\nNo cycles - \n";
    Graph<string> tree;

    // Create vertices for a tree structure
    for (int i = 1; i <= 11; i++)  tree.addVertex(i, "payload");

    tree.addEdge(1, 2, 1);
    tree.addEdge(2, 1, 1);
    tree.addEdge(1, 5, 1);
    tree.addEdge(5, 1, 1);
    tree.addEdge(1, 9, 1);
    tree.addEdge(9, 1, 1);
    tree.addEdge(2, 3, 1);
    tree.addEdge(3, 2, 1);
    tree.addEdge(3, 4, 1);
    tree.addEdge(4, 3, 1);
    tree.addEdge(5, 6, 1);
    tree.addEdge(6, 5, 1);
    tree.addEdge(5, 8, 1);
    tree.addEdge(8, 5, 1);
    tree.addEdge(6, 7, 1);
    tree.addEdge(7, 6, 1);
    tree.addEdge(9, 10, 1);
    tree.addEdge(10, 9, 1);
    tree.addEdge(10, 11, 1);
    tree.addEdge(11, 10, 1);

	cout << "Tree has " << tree.size() << " vertices" << endl;
    
    hasCycle = hasCycleBFS(tree, tree.getVertex(1));
    if (hasCycle) {
        cout << "RESULT: The tree contains cycles!" << endl;
    } else {
        cout << "RESULT: The tree is acyclic (no cycles found)." << endl;
    }

    return 0;
}

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

bool hasCycleBFS(Graph<string>& g, Vertex<string>* start) {
    if (start == nullptr) return false;
    
    vector<bool> visited(g.size() + 1, false);  // track visited vertices
    vector<int> parent(g.size() + 1, -1);       // track parent of each vertex in BFS tree
    
    queue<Vertex<string>*> q;
    q.push(start);
    visited[start->getId()] = true;
    parent[start->getId()] = -1;  // root has no parent
    
    cout << "BFS Traversal (showing potential cycles):" << endl;
    
    while (!q.empty()) {
        Vertex<string>* current = q.front();
        q.pop();
        int currentId = current->getId();
        
        cout << "Processing vertex " << currentId << " (parent: " << parent[currentId] << ")" << endl;
        
        // Check all neighbors
        for (int neighborId : current->getConnections()) {
            Vertex<string>* neighbor = g.getVertex(neighborId);
            if (neighbor == nullptr) continue;
            
            cout << "  -> Checking neighbor " << neighborId;
            
            if (!visited[neighborId]) {
                // If neighbor is not visited, mark it visited and set its parent
                visited[neighborId] = true;
                parent[neighborId] = currentId;
                q.push(neighbor);
                cout << " - not visited, adding to queue" << endl;
            } else if (parent[currentId] != neighborId) {
                // If neighbor is visited and not the parent of current, we found a cycle
                cout << " - ALREADY VISITED! CYCLE DETECTED!" << endl;
                cout << "     Cycle: " << currentId << " -> " << neighborId 
                     << " (but " << neighborId << " is not parent of " << currentId 
                     << ", parent is " << parent[currentId] << ")" << endl;
                return true;
            } else {
                // Neighbor is visited but it's the parent (this is normal in BFS tree)
                cout << " - visited but is parent (normal edge in BFS tree)" << endl;
            }
        }
    }
    
    cout << "No cycles detected in BFS traversal." << endl;
    return false;
}