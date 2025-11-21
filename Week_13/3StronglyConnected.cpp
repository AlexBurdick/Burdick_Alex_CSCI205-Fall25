/*
Exercise: Strongly Connected Graph
Given a directed graph, check if it is strongly connected or not. A directed graph is 
considered “strongly connected” if every vertex is reachable from every other vertex.
A simple solution is to perform a depth or breadth first traversal starting from 
every vertex in the graph. If each DFS/BFS call visits every other vertex in the 
graph, then the graph is strongly connected. Use a vector to track the “visited” 
status of the vertices. 
*/

#include <vector>