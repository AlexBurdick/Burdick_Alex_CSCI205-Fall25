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