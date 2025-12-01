#include <iostream>
#include <climits>
#include <vector>

using namespace std;

// function prototypes
int minDist(int[], bool[]);
void Dijkstra(int[6][6], int);
vector<int> path(int, int[], int);

int main(){
	// adjacency matrix
	int graph[6][6]={// {A, B, C, D, E, F}
						{0, 1, 2, 0, 0, 0}, // A
						{1, 0, 0, 5, 1, 0}, // B
						{2, 0, 0, 2, 3, 0}, // C
						{0, 5, 2, 0, 2, 2}, // D
						{0, 1, 3, 2, 0, 1}, // E
						{0, 0, 0, 2, 1, 0}  // F
					};
	int SOURCE = 0;
	Dijkstra(graph, SOURCE);
	return 0;
}
/*
	Dijkstra's Algorithm to find the shortest path from source vertex to all other vertices
	Parameters:
		graph[6][6] : adjacency matrix representing the graph
		src			: source vertex index

	Discription:
		Initializes distance, seen, and parent arrays.
		Iteratively selects the unseen vertex with the smallest distance,
		updates distances to its neighbors, and records the path.
		Prints the shortest path and cost from source to each vertex.

	Efficiency:
		Time Complexity: O(V^2) where V is the number of vertices (6 in this case)
		Space Complexity: O(V) for distance, seen, and parent arrays

	Implementation:
		Uses an adjacency matrix to represent the graph.
		Employs a simple linear search to find the minimum distance vertex.
		Updates the distances and paths in place.
		Records the final paths for each vertex.
*/
void Dijkstra(int graph[6][6], int src){
	// arrays for algorithm
	int		distance[6];					// array to store minimum cost for each V
	bool	seen[6];						// array to mark visited and unvisited for each V
	int		parent[6];						// array to store the path
	
	for(int k = 0; k<6; k++){				// algorithm setup
		distance[k] = INT_MAX;				// set to large value, real distance guaranteed to be smaller
		seen[k]		= false;				// mark all as not seen
		parent[k]	= -1;					// set parents to -1 (no parent)
	}
	
	distance[ src ] = 0;					// Source vertex cost is 0
	
	for(int i = 0; i < 6; i++){				// iterate through vertices O(V^2)
		int m = minDist(distance,seen); 	// find the unknown vertex with the smallest distance
		seen[m] = true;						// mark it as seen
		for(int j = 0; j < 6; j++) 			// iterate through current vertex's neighbors
			// unseen, connected and smaller cost?
			if(!seen[j] && graph[m][j] && distance[m] + graph[m][j] < distance[j]){
				distance[j]	= distance[m] + graph[m][j];	// update neighbors
				parent[j]	= m;							// record parent
			}
	}

	cout << "\nPaths from Vertex: " << (char)(src + 65) << endl << endl;
	cout << "Vertex\tCost\tPath" << endl;// print results
	cout << "====================" << endl;
	for(int k = 0; k < 6; k++){
		if(k != src){
			cout << (char)(65 + k) << "\t" << distance[k] << "\t";
			// get path to current vertex
			vector<int> jumps = path(k, parent, sizeof(parent) / sizeof(parent[0])); 
			for(int i = jumps.size() - 2; i > 0; --i)
				cout << (char)(jumps[i] + 65) << "->";
			cout << (char)(65 + k) <<endl;
		}
	}
}

// iterate through distance array, finding the least cost, unseen vertex
int minDist(int distance[], bool Tset[]){ 		// O(N) -> scans entire array.
	int minimum = INT_MAX, ind = 0;				// set initial minimum distance to large value
	for(int k = 0; k < 6; k++)					// iterate through distance array
		if(!Tset[k] && distance[k] <= minimum){ // vertex not seen and has smaller cost
			minimum = distance[k];				// update the distance
			ind		= k;						// store index of smallest
		}
	return ind;
}

// reconstruct path from source to vertex using parent array
vector<int> path(int vertex, int parents[], int size){
	vector<int> jumps;							// vector to store path
	jumps.push_back(vertex);					// add source vector to back of vector
	while(vertex != -1){						// loop until there is no parent
		vertex = parents[ vertex ];				// get the parent vertex
		jumps.push_back(vertex);				// add it to vector
	}
	return jumps;								// return vector
}