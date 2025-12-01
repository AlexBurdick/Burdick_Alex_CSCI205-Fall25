#include <iostream>
#include <climits>
#include <vector>
#include "Graph.hpp"
#include "Vertex.hpp"

using namespace std;

// function prototypes
void buildGraph(Graph<string>&);						// Builds a graph. Change this function for other graphs
void Djikstra(Graph<string>&, Vertex<string>*);			// runs Djikstras: O(V+E)
void percUp(vector<Vertex<string>*> &, Vertex<string>*);// PQ enqueue: O(logN) 
Vertex<string>* removeMin(vector<Vertex<string>*> &);	// dequeues minimum cost and re-heapifies: O(logN) 
void printResults(Graph<string> &, Vertex<string>*);	// Prints all paths and weights from src

// DJIKSTRAS ALGORITHM USING AN ADJACENCY LIST GRAPH
int main(){
	Graph<string> graph;								// graph object
	buildGraph(graph);									// fill it with some vertices.

	int SOURCE_ID = 1;									// Where should we begin? Change this for other paths
	Vertex<string>* src = graph.getVertex(SOURCE_ID);	// get the SOURCE ID vertex

	Djikstra(graph, src);								// do Dijsktras algo from source
	printResults(graph, src);							// print the results

	return 0;
}

/*
	Modified Breadth First Search using a "cost based" Priority Queue w/ Min Heap
	
	Parameters:
		g	: Graph<string> adjacency list graph
		src	: pointer to source Vertex<string>

	Dscription:
		Initializes all vertex distances to INT_MAX.
		Uses a min-heap based priority queue to always extend the least-cost path.
		Updates distances and parent pointers as shorter paths are found.
	Efficiency:
		Time Complexity: O((V + E) log V) where V is number of vertices and E is number of edges
			Each Vertex is processed once: O(V)
			PQ Dequeue and Enqueue operations: O(log V)
			This step yields: O(V log V)

			When examining each vertex's neighbors (edges): O(E)
			PQ Enqueue operations for neighbors: O(E log V)
			Total: O(V log V + E log V) = 	O((V + E) log V)

		Space Complexity: O(V) for the priority queue and vertex data
	
	Implementation:
		Employs an adjacency list representation of the graph.
		Uses a min-heap priority queue to efficiently retrieve the next vertex with the smallest distance.
		Updates vertex distances and parent pointers to reconstruct paths later.
*/
void Djikstra(Graph<string>& g, Vertex<string>* src){
	// ALGORITHM SETUP (min heap based PQ, set distances to max int, queue the source vertex)
	vector<Vertex<string>*> minHeap;			// the PQ min heap: maintain O(LogN) enqueue

	for(int k = 1; k <= g.size(); k++)			// prepare each Vertex<string> O(V)
		g.getVertex(k)->distance = INT_MAX;		// set distance to large value, real distance guaranteed to be smaller
												// if initial distance is unchanged, the vertex could not be reached
												// don't print those

	src->distance = 0;							// set src cost to 0
	minHeap.push_back(src);						// add source to the PQ. First vertex, no need to percUp

	// BEGIN DJIKSTRA
	while(!minHeap.empty()){										// iterate through the PQ in O(V+E) time
		Vertex<string>* current = removeMin( minHeap );				// dequeue vertex
		vector<int> 	nbrs	= current->getConnections();		// grab current V's neighbors from the adjacency list

		for(int n = 0; n < nbrs.size(); ++n){						// iterate through neighbors: O(E)
			Vertex<string>* neighbor = g.getVertex( nbrs[n] );		// grab a neighbor
			int weight = current->getWeight( neighbor->getId() ); 	// get edge weight from current to neighbor

			// Logic is variation on "visited"
			// If the distance to the current V + the neighbors weight is smaller than neighbor's distance
			// If the neighbor is unvisited, it will be equal to INT_MAX
			// If it has been visited, is the path being examined lower cost than previous path?
			if((current->distance + weight) < neighbor->distance ){ // is new path to current less than neighbor's distance?
				neighbor->distance = current->distance + weight;	// update neighbors distance
				neighbor->parent   = current->getId();				// record the parent (how we got here)
				percUp(minHeap, neighbor);							// enqueue current Vertex<string> and perc up
			}
		}
	}
}

// modified minHeap enqueue
// this function includes logic to not add duplicate vertices to the PQ
// if the vertex is already in the PQ, it will not be added again
// and the vertex's distance will be updated if the new distance is smaller
// O(LogN) enqueue
void percUp(vector<Vertex<string>*> &minHeap, Vertex<string>* src){		// O(LogN) enqueue

	// check if src Vertex is already in the PQ
	// If it exists we need not add it again
	// but it's distance may have changed so we need to re-heapify
	bool exists = false;								// assume the vertex is not in the PQ
	for(int i = 0; i < minHeap.size(); ++i){			// iterate through PQ
		if(minHeap[i]->getId() == src->getId()){		// does the vertex exist?
			exists = true;								// yes, it exists
			break;										// stop looking
		}
	}
	if (!exists) minHeap.push_back( src );				// insert src at end of PQ only if it does not exist

	// re-heapify
	int self	= minHeap.size() - 1;					// get index of src
	int parent	= self >> 1;							// get parent index (bit shift divide by 2)
	
	// perculate src vertex up the min heap
	while(self > 0 && src->distance <= minHeap[ parent ]->distance){
		swap(minHeap[ self ], minHeap[ parent ]);		// vector's swap method
		self	= parent;								// update self to point to parent's position
		parent	>>= 1;									// get new parent (bit shift divide by 2)
	}
}

Vertex<string>* removeMin(vector<Vertex<string>*> &minHeap){
	Vertex<string>* min = minHeap[0];					// get the front of the PQ
	minHeap.erase( minHeap.begin() );					// remove it

	if( minHeap.size() > 0){							// don't perc up if the PQ is now empty 
		Vertex<string>* current = minHeap[0];			// get the new front
		minHeap.erase( minHeap.begin() );				// remove it from the front
		percUp(minHeap, current);						// re-heapify
	}

	return min;
}

void printResults(Graph<string>& g, Vertex<string>* src){
	int total_cost = 0;
	cout << endl;
	for(int v = 1; v <= g.size(); ++v){								// print the resulting path and weights O(V)
		Vertex<string>* vert = g.getVertex(v);						// iterate through graph
		total_cost += vert->distance;								// accumulate total path cost
		bool blank = 1;												// to remove blank lines for unreachable vertices in the tree
		// don't print the source or any unvisited vertices
		if(vert->distance != INT_MAX && src->getId() != vert->getId()){
			cout 	<< "Least cost path from: " << src << " to " << vert << "\t"
					<< "has a weight of " << vert->distance << "\t"
					<< "PATH: " << src->getId() << " ";				// start path with the source vertex
			blank = 0;												// no unreached vertices
		}
		// Prepare the individual paths
		vector<int> path;											// want to print the paths from source
		while(vert->parent != src->parent && vert->parent != -1){	// have we made it to the source? Or there is no parent?
			path.push_back( vert->getId() );						// load them into a vector in reverse order
			vert = g.getVertex( vert->parent );						// go to the parent
		}
		// print the path for from source to current vertex
		while(!path.empty()){										// print vector in reverse order
			cout << g.getVertex( path.back() )->getId() << " ";
			path.pop_back();
		}
		if(!blank) cout << endl;
	}
	cout << "\nTree has a total cost of: " << total_cost << endl;
}

void buildGraph(Graph<string>& g){
	for (int i = 1; i <= 10; i++) 	// create ten vertex objects
		g.addVertex(i, "placeholder");		// keys will be 1 - 10

	// add edges
	//        F   T   W		(F)rom, (T)o, (W)eight . . . not (F)or (T)he (W)in
	g.addEdge(1,  2,  5);
	g.addEdge(1,  5,  12);
	g.addEdge(6,  5,  4);
	g.addEdge(5,  8,  7);
	g.addEdge(1,  9,  3);
	g.addEdge(2,  3,  8);
	g.addEdge(9,  10, 1);
	g.addEdge(3,  4,  1);
	g.addEdge(5,  7,  9);
	g.addEdge(9,  11, 3);	// add new vertex
	g.addEdge(11, 10, 2);
	g.addEdge(2,  5,  1);
	g.addEdge(9,  5,  4);
	g.addEdge(4,  6,  2);
	g.addEdge(10, 7,  5);
	g.addEdge(8,  4,  3);
	g.addEdge(5,  12, 2);	// add new vertex
}
