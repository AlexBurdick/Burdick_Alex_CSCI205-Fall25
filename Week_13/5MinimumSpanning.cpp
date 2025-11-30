/*
Often it would be nice to have an algorithm that, for any connected vertices and 
edges, would remove any extra edges. The result would be a graph with the minimum 
number of edges necessary to connect the vertices. For example, Figure a) shows five 
vertices with an excessive number of edges, while Figure b) shows the same vertices 
with the minimum number of edges necessary to connect them. This constitutes a 
minimum spanning tree (MST). Sketch the MST from the following graph using Prim’s 
algorithm and determine the “cost”.
Implement Prim’s algorithm using the Graph.h and Vertex.h classes and demonstrate 
that your solution is correct.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include "Graph.hpp"

using namespace std;

int mst(Graph<string>&, Vertex<string>*);

int main() {
    // Tests written by DeepSeek (11/30/2025)
    cout << "Prim's Alrgorithm - Minimum Spanning Tree\n";
    
    // Test Case 1: (5 vertices)
    cout << "\n5-Vertices Graph -\n";
    Graph<string> g1;
    for (int i = 1; i <= 5; i++)  g1.addVertex(i, "payload");
    g1.addEdge(1, 2, 2);  // A-B
    g1.addEdge(1, 3, 3);  // A-C
    g1.addEdge(1, 4, 1);  // A-D
    g1.addEdge(2, 3, 4);  // B-C
    g1.addEdge(2, 4, 3);  // B-D
    g1.addEdge(2, 5, 2);  // B-E
    g1.addEdge(3, 4, 5);  // C-D
    g1.addEdge(3, 5, 1);  // C-E
    g1.addEdge(4, 5, 4);  // D-E
    cout << "Original Graph has " << g1.size() << " vertices\n";
    int mstCost1 = mst(g1, g1.getVertex(1));
    cout << "Total cost of MST: " << mstCost1 << endl;
    
    // Test Case 2: Larger graph for more comprehensive testing
    cout << "\n6-Vertices Graph -\n";
    Graph<string> g2;
    for (int i = 1; i <= 6; i++)  g2.addVertex(i, "payload");
    g2.addEdge(1, 2, 4);
    g2.addEdge(1, 3, 2);
    g2.addEdge(2, 3, 1);
    g2.addEdge(2, 4, 5);
    g2.addEdge(3, 4, 8);
    g2.addEdge(3, 5, 10);
    g2.addEdge(4, 5, 2);
    g2.addEdge(4, 6, 6);
    g2.addEdge(5, 6, 3);
    cout << "Original Graph has " << g2.size() << " vertices\n";
    int mstCost2 = mst(g2, g2.getVertex(1));
    cout << "\nTotal cost of MST: " << mstCost2 << endl;
    
    // Test Case 3: Simple 3-vertex graph
    cout << "\n3-Vertices Graph -\n";
    Graph<string> g3;
    for (int i = 1; i <= 3; i++)  g3.addVertex(i, "payload");
    g3.addEdge(1, 2, 5);
    g3.addEdge(1, 3, 3);
    g3.addEdge(2, 3, 2);
    cout << "Original Graph has " << g3.size() << " vertices\n";
    int mstCost3 = mst(g3, g3.getVertex(1));
    cout << "\nTotal cost of MST: " << mstCost3 << endl;
    
    // Manual verification for the 5-vertex example
    cout << "\n=== VERIFICATION FOR 5-VERTEX GRAPH ===" << endl;
    cout << "Graph edges and weights:" << endl;
    cout << "1-2:2, 1-3:3, 1-4:1, 2-3:4, 2-4:3, 2-5:2, 3-4:5, 3-5:1, 4-5:4" << endl;
    cout << "Expected MST edges: 1-4(1), 4-2(3), 2-5(2), 5-3(1)" << endl;
    cout << "Expected total cost: 1 + 3 + 2 + 1 = 7" << endl;
    cout << "Actual total cost: " << mstCost1 << (mstCost1 == 7 ? "CORRECT!" : "INCORRECT!") << endl;
    
    return 0;
}

// Function to print the MST edges (from DeepSeek 11/30/2025)
void printMST(Graph<string>& g, const vector<int>& parent) {
    cout << "\nMinimum Spanning Tree Edges:" << endl;
    cout << "============================" << endl;
    for (size_t i = 1; i < parent.size(); i++) {
        if (parent[i] != -1) {
            Vertex<string>* v = g.getVertex(parent[i]);
            if (v != nullptr) {
                int weight = v->getWeight(i);
                cout << parent[i] << " - " << i << " (weight: " << weight << ")" << endl;
            }
        }
    }
}

// Function to find Minimum Spanning Tree using Prim's algorithm (from DeepSeek 11/30/2025)
int mst(Graph<string>& g, Vertex<string>* start) {
    
    int totalCost = 0;
    vector<bool> inMST(g.size() + 1, false); // keep track of what's been added
    vector<int> key(g.size() + 1, INT_MAX);  // Minimum weight edge to connect to MST
    vector<int> parent(g.size() + 1);        // To store the MST structure
    
    // Priority Queue template parameters (from DeepSeek, 11/30/2025):
    //             ElementType     ContainerType           ComparisonFunction
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // stores pairs of (weight, vertexId)
    
    // Start with the first vertex
    key[start->getId()] = 0;
    pq.push({0, start->getId()});
    
    while (!pq.empty()) {
        int currentId = pq.top().second;
        int currentKey = pq.top().first;
        pq.pop();
        
        // If vertex is already in MST, skip it
        if (inMST[currentId]) continue;
        
        // Add vertex to MST
        inMST[currentId] = true;
        totalCost += currentKey;
        
        Vertex<string>* currentVertex = g.getVertex(currentId);
        if (currentVertex == nullptr) continue;
        
        // Update keys for all adjacent vertices
        for (int neighborId : currentVertex->getConnections()) {
            Vertex<string>* neighbor = g.getVertex(neighborId);
            if (neighbor == nullptr) continue;
            
            int weight = currentVertex->getWeight(neighborId);
            
            // If neighbor not in MST and weight is smaller than current key
            if (!inMST[neighborId] && weight < key[neighborId]) {
                key[neighborId] = weight;
                parent[neighborId] = currentId;
                pq.push({weight, neighborId});
            }
        }
    }
    
    printMST(g, parent);
    return totalCost;
}