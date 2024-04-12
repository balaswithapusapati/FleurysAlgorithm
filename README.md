# Fleury's Algorithm

Fleury's Algorithm is a method for finding Eulerian circuits or paths in a graph. It guarantees that each edge is traversed exactly once for an Eulerian circuit, or all edges except two for an Eulerian path.

## Algorithm

1. *Choose a Starting Vertex:*
   - If the graph has vertices with odd degrees, start from one of those vertices.
   - If all vertices have even degrees, start from a vertex with the minimum degree.

2. *While there are unvisited edges:*
   - If the current vertex has only one edge, select it.
   - If the current vertex has more than one edge, select an edge that, when removed, does not disconnect the graph. If no such edge exists, select any other edge.

3. *Repeat Step 2 until all edges are visited.*

## Complexity

- *Time Complexity:*
   - Best Case: O(E) if the graph has an Eulerian circuit or path and the algorithm selects the correct edge at each step.
   - Worst Case: O(E^2) if the algorithm has to backtrack frequently and try different edges, where E is the number of edges.
- *Space Complexity:* O(V + E), where V is the number of vertices and E is the number of edges.

## Applications

- *Graph Theory:* Fleury's Algorithm is fundamental in graph theory for finding Eulerian circuits or paths.
- *Network Analysis:* It is used in network analysis for optimizing routes and paths.
- *Puzzle Solving:* It can be applied to solve puzzles like the Seven Bridges of Königsberg problem.
