/*
This is a common problem in Computer Science. Given a maze in the form of binary 
rectangular matrix, find the shortest path’s length from a given source to a given 
destination. A path consists of cells with 1, and at any given moment, we can only 
move one cell in one of the four directions. The valid moves are:
Go Top:   (x, y) ——> (x – 1, y)
Go Left:  (x, y) ——> (x, y – 1)
Go Down:  (x, y) ——> (x + 1, y)
Go Right: (x, y) ——> (x, y + 1)
*/

#include <iostream>
#include <queue> 	// for breadth first traversal
#include "Graph.hpp"

using namespace std;

int shortestPath(Graph<string>&, Vertex<string>*, Vertex<string>*);

int main() {
   
   Graph<string> g;
   
   // 4.It may be helpful to modify the Vertex class to have a property to store the 
   // distance from the source. (In Vertex.hpp)
   // 5.It may be helpful to modify the Vertex class to have an x and y property to store its coordinates in the matrix.
   // 6.Also, be sure to stay in bounds. You will need to check to see if you are on a matrix edge.

    return 0;
}

int shortestPath(Graph<string>& g, Vertex<string>* source, Vertex<string>* destination) {
   // 1.Create an empty queue and enqueue the source vertex having a distance 0 from 
   // the source (itself) and mark it as visited.
   int distance = 0;
   bool* visited = new bool[ g.size()+1 ]();
	queue<Vertex<string>*> q;
	visited[ source->getId() ] = true;
	
   // 2.Continue until the queue is exhausted.
	while ( !q.empty() ) {
      // a. Dequeue the front vertex.
      distance++; // increment distance
		Vertex<string>* vert = q.front();
		q.pop();
		// b. If the vertex is the destination node, then return its distance.
      if (vert == destination) {
         delete[] visited;
         return distance;
      }
      
      // c. Otherwise, for each of four adjacent cells, enqueue each vertex with +1 
      // distance and mark them as visited.
		for (int v : vert->getConnections()) {
			if ( !visited[v] ) {
				Vertex<string>* _v = g.getVertex(v);
				q.push( _v );
				visited[ v ] = true;
			}
		}
	}

   // 3.If the destination has not been reached after visiting all vertices, return false.
   return -1;


	delete[] visited;
}