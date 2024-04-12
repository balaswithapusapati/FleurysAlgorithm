def find_start_vert(tempGraph):
    for i in range(len(tempGraph)):
        deg = sum(tempGraph[i])
        if deg % 2 != 0:
            return i
    return 0

def is_bridge(u, v, tempGraph):
    deg = sum(tempGraph[v])
    if deg > 1:
        return False
    return True

def edge_count(tempGraph):
    count = sum(sum(row) for row in tempGraph) // 2
    return count

def fleury_algorithm(start, tempGraph, path, circuit_found):
    edge = edge_count(tempGraph)
    for v in range(len(tempGraph)):
        if tempGraph[start][v]:
            if edge <= 1 or not is_bridge(start, v, tempGraph):
                path.append((start, v))
                tempGraph[start][v] = tempGraph[v][start] = 0
                edge -= 1
                fleury_algorithm(v, tempGraph, path, circuit_found)
    if edge == 0 and not circuit_found[0]:
        circuit_found[0] = True

def process_graphs(filename):
    with open(filename, "r") as infile:
        graph = []
        for line in infile:
            if line.strip():
                row = list(map(int, line.strip().split()))
                graph.append(row)
            else:
                tempGraph = [row[:] for row in graph]
                path = []
                circuit_found = [False]

                start_node = find_start_vert(tempGraph)
                fleury_algorithm(start_node, tempGraph, path, circuit_found)

                if circuit_found[0]:
                    print("Euler Path or Circuit:", end=" ")
                    for edge in path:
                        print(f"{edge[0]}--{edge[1]}", end=" ")
                    print()
                else:
                    print("No Euler circuit or path")

                graph = []  # Reset the graph for the next input

        # Process the last graph if it exists
        if graph:
            tempGraph = [row[:] for row in graph]
            path = []
            circuit_found = [False]

            start_node = find_start_vert(tempGraph)
            fleury_algorithm(start_node, tempGraph, path, circuit_found)

            if circuit_found[0]:
                print("Euler Path or Circuit:", end=" ")
                for edge in path:
                    print(f"{edge[0]}--{edge[1]}", end=" ")
                print()
            else:
                print("No Euler circuit or path")

if __name__ == "__main__":
    process_graphs("graph.txt")
