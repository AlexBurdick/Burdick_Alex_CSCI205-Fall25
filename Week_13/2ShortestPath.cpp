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
#include <vector>
#include <string>
#include <queue>
#include <utility>
#include "Graph.hpp"
#include "Vertex.hpp"

using namespace std;


// Function to convert 2D coordinates to a unique vertex key
int coordToKey(int row, int col, int cols) {
    return row * cols + col;
}

// Function to get row and col from vertex key
void keyToCoord(int key, int cols, int& row, int& col) {
    row = key / cols;
    col = key % cols;
}

int shortestPath(Graph<pair<int, int>>&, Vertex<pair<int, int>>*, Vertex<pair<int, int>>*);

int main() {
    // Creation of maze graph from DeepSeek (11/30/2025)
    // Define the maze
    vector<vector<int>> maze = {
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {0, 0, 1, 0, 0, 1, 1, 0, 0, 1}
    };
    
    int rows = maze.size();
    int cols = maze[0].size();
    
    // Create graph with pair<int, int> payload (coordinates)
    Graph<pair<int, int>> mazeGraph;
    
    // Add vertices for all path cells (where maze value is 1)
    // Use sequential integer indices starting from 0
    int vertexIndex = 0;
    vector<pair<int, int>> coordinateMap; // Map from index to coordinates
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 1) {
                pair<int, int> coordinates = make_pair(i, j);
                mazeGraph.addVertex(vertexIndex, coordinates);
                coordinateMap.push_back(coordinates); // Store mapping
                vertexIndex++;
            }
        }
    }
    
    // Add edges between adjacent path cells
    // We need to find the vertex indices for adjacent cells
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 1) {
                // Find the vertex index for current cell
                int currentIndex = -1;
                for (int idx = 0; idx < coordinateMap.size(); idx++) {
                    if (coordinateMap[idx].first == i && coordinateMap[idx].second == j) {
                        currentIndex = idx;
                        break;
                    }
                }
                if (currentIndex == -1) continue;
                
                // Check and add right neighbor
                if (j + 1 < cols && maze[i][j + 1] == 1) {
                    int rightIndex = -1;
                    for (int idx = 0; idx < coordinateMap.size(); idx++) {
                        if (coordinateMap[idx].first == i && coordinateMap[idx].second == j + 1) {
                            rightIndex = idx;
                            break;
                        }
                    }
                    if (rightIndex != -1) {
                        mazeGraph.addEdge(currentIndex, rightIndex, 1);
                    }
                }
                
                // Check and add down neighbor
                if (i + 1 < rows && maze[i + 1][j] == 1) {
                    int downIndex = -1;
                    for (int idx = 0; idx < coordinateMap.size(); idx++) {
                        if (coordinateMap[idx].first == i + 1 && coordinateMap[idx].second == j) {
                            downIndex = idx;
                            break;
                        }
                    }
                    if (downIndex != -1) {
                        mazeGraph.addEdge(currentIndex, downIndex, 1);
                    }
                }
                
                // Check and add left neighbor
                if (j - 1 >= 0 && maze[i][j - 1] == 1) {
                    int leftIndex = -1;
                    for (int idx = 0; idx < coordinateMap.size(); idx++) {
                        if (coordinateMap[idx].first == i && coordinateMap[idx].second == j - 1) {
                            leftIndex = idx;
                            break;
                        }
                    }
                    if (leftIndex != -1) {
                        mazeGraph.addEdge(currentIndex, leftIndex, 1);
                    }
                }
                
                // Check and add up neighbor
                if (i - 1 >= 0 && maze[i - 1][j] == 1) {
                    int upIndex = -1;
                    for (int idx = 0; idx < coordinateMap.size(); idx++) {
                        if (coordinateMap[idx].first == i - 1 && coordinateMap[idx].second == j) {
                            upIndex = idx;
                            break;
                        }
                    }
                    if (upIndex != -1) {
                        mazeGraph.addEdge(currentIndex, upIndex, 1);
                    }
                }
            }
        }
    }
    
    // Print graph information
    cout << "Maze Graph created with " << mazeGraph.size() << " vertices." << endl;
    
    // Helper function to find vertex index from coordinates
    auto findVertexIndex = [&](int row, int col) -> int {
        for (int i = 0; i < coordinateMap.size(); i++) {
            if (coordinateMap[i].first == row && coordinateMap[i].second == col) {
                return i;
            }
        }
        return -1;
    };
    
    // Test shortest path between two points
    int startRow = 0, startCol = 0;  // Top-left
    int endRow = 9, endCol = 9;      // Bottom-right
    
    int startIndex = findVertexIndex(startRow, startCol);
    int endIndex = findVertexIndex(endRow, endCol);
    
    if (startIndex != -1 && endIndex != -1) {
        Vertex<pair<int, int>>* startVertex = mazeGraph.getVertex(startIndex);
        Vertex<pair<int, int>>* endVertex = mazeGraph.getVertex(endIndex);
        
        pair<int, int> startCoords = startVertex->getPayload();
        pair<int, int> endCoords = endVertex->getPayload();
        
        cout << "Finding path from (" << startCoords.first << "," << startCoords.second 
            << ") to (" << endCoords.first << "," << endCoords.second << ")" << endl;
        
        int pathLength = shortestPath(mazeGraph, startVertex, endVertex);
        if (pathLength != -1) {
            cout << "Shortest path length: " << pathLength << endl;
        } else {
            cout << "No path exists between the given coordinates" << endl;
        }
    } else {
        if (startIndex == -1) 
            cout << "Start vertex at (" << startRow << "," << startCol << ") not found!" << endl;
        if (endIndex == -1) 
            cout << "End vertex at (" << endRow << "," << endCol << ") not found!" << endl;
    }
    
    return 0;
}

int shortestPath(Graph<pair<int, int>>& g,
                 Vertex<pair<int, int>>* source,
                 Vertex<pair<int, int>>* destination) {
    
    // Data validation (equals check)
    if (source->getId() == destination->getId()) return 0;

    bool* seen = new bool[ g.size() + 1 ]();                // boolean array to track visited nodes.
    queue<Vertex<pair<int, int>>*> q;                       // queue of Vertex pointers
    q.push(source);                                         // enqueue the starting node
    seen[ source->getId() ] = true;                         // mark the starting node as being "seen"
    
    while (!q.empty()) {                                    // as long as the queue is not empty
        Vertex<pair<int, int>>* current = q.front();        // dequeue the front vertex
        q.pop();                                            // remove it from the queue
        
        if (current->getId() == destination->getId()) {     // if we found the destination
            int result = current->getDistance();            // get the distance
            delete[] seen;                                  // memory cleanup
            return result;                                  // return its distance
        }
        
        for (int neighborId : current->getConnections()) {  // get all of the edges from the current vertex
            if ( !seen[neighborId] ) {                      // if the current key has not been "seen"
                Vertex<pair<int, int>>* neighbor = g.getVertex(neighborId); // get the vertex
                if ( neighbor != nullptr ) {                // if the neighbor exists       
                    neighbor->setDistance(current->getDistance() + 1); // set distance for neighbor (current distance + 1)
                    q.push( neighbor );                     // enqueue the vertex
                    seen[ neighborId ] = true;              // mark it as seen
                }
            }
        }
    }
       
    delete[] seen;
    return -1; // destination not reachable
}