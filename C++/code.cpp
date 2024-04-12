#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> Edge;

void find_start_vert(vector<vector<int>>& tempGraph, int& start) {
    for (int i = 0; i < tempGraph.size(); i++) {
        int deg = 0;
        for (int j = 0; j < tempGraph[i].size(); j++) {
            deg += tempGraph[i][j];
        }
        if (deg % 2 != 0) {
            start = i;
            return;
        }
    }
    start = 0;
}

bool is_bridge(int u, int v, vector<vector<int>>& tempGraph) {
    int deg = 0;
    for (int i = 0; i < tempGraph[v].size(); i++) {
        deg += tempGraph[v][i];
    }
    if (deg > 1) {
        return false;
    }
    return true;
}

int edge_count(vector<vector<int>>& tempGraph) {
    int count = 0;
    for (int i = 0; i < tempGraph.size(); i++) {
        for (int j = 0; j < tempGraph[i].size(); j++) {
            count += tempGraph[i][j];
        }
    }
    return count / 2;
}

void fleury_algorithm(int start, vector<vector<int>>& tempGraph, vector<Edge>& path, bool& circuit_found) {
    int edge = edge_count(tempGraph);
    for (int v = 0; v < tempGraph.size(); v++) {
        if (tempGraph[start][v]) {
            if (edge <= 1 || !is_bridge(start, v, tempGraph)) {
                path.push_back({start, v});
                tempGraph[start][v] = tempGraph[v][start] = 0;
                edge--;
                fleury_algorithm(v, tempGraph, path, circuit_found);
            }
        }
    }
    if (edge == 0 && !circuit_found) {
        circuit_found = true;
    }
}

void process_graphs(string filename) {
    ifstream infile(filename);
    vector<vector<int>> graph;
    vector<vector<int>> tempGraph;
    vector<Edge> path;
    bool circuit_found = false;

    string line;
    while (getline(infile, line)) {
        if (!line.empty()) {
            vector<int> row;
            string num;
            for (char c : line) {
                if (c != ' ') {
                    num += c;
                } else {
                    row.push_back(stoi(num));
                    num.clear();
                }
            }
            row.push_back(stoi(num));
            graph.push_back(row);
        } else {
            tempGraph.clear();
            for (vector<int> row : graph) {
                tempGraph.push_back(row);
            }
            path.clear();
            circuit_found = false;

            int start_node;
            find_start_vert(tempGraph, start_node);
            fleury_algorithm(start_node, tempGraph, path, circuit_found);

            if (circuit_found) {
                cout << "Euler Path or Circuit: ";
                for (Edge edge : path) {
                    cout << edge.first << "--" << edge.second << " ";
                }
                cout << endl;
            } else {
                cout << "No Euler circuit or path" << endl;
            }

            graph.clear();  // Reset the graph for the next input
        }
    }

    // Process the last graph if it exists
    if (!graph.empty()) {
        tempGraph.clear();
        for (vector<int> row : graph) {
            tempGraph.push_back(row);
        }
        path.clear();
        circuit_found = false;

        int start_node;
        find_start_vert(tempGraph, start_node);
        fleury_algorithm(start_node, tempGraph, path, circuit_found);

        if (circuit_found) {
            cout << "Euler Path or Circuit: ";
            for (Edge edge : path) {
                cout << edge.first << "--" << edge.second << " ";
            }
            cout << endl;
        } else {
            cout << "No Euler circuit or path" << endl;
        }
    }
}

int main() {
    process_graphs("graph.txt");
    return 0;
}