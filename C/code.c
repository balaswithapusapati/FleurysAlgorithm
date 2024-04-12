#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int u;
    int v;
} Edge;

void find_start_vert(int tempGraph[][MAX_VERTICES], int numVertices, int* start) {
    for (int i = 0; i < numVertices; i++) {
        int deg = 0;
        for (int j = 0; j < numVertices; j++) {
            deg += tempGraph[i][j];
        }
        if (deg % 2 != 0) {
            *start = i;
            return;
        }
    }
    *start = 0;
}

int is_bridge(int u, int v, int tempGraph[][MAX_VERTICES], int numVertices) {
    int deg = 0;
    for (int i = 0; i < numVertices; i++) {
        deg += tempGraph[v][i];
    }
    if (deg > 1) {
        return 0;
    }
    return 1;
}

int edge_count(int tempGraph[][MAX_VERTICES], int numVertices) {
    int count = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            count += tempGraph[i][j];
        }
    }
    return count / 2;
}

void fleury_algorithm(int start, int tempGraph[][MAX_VERTICES], int numVertices, Edge path[], int* pathIndex, int* circuitFound) {
    int edge = edge_count(tempGraph, numVertices);
    for (int v = 0; v < numVertices; v++) {
        if (tempGraph[start][v]) {
            if (edge <= 1 || !is_bridge(start, v, tempGraph, numVertices)) {
                path[*pathIndex].u = start;
                path[*pathIndex].v = v;
                (*pathIndex)++;
                tempGraph[start][v] = tempGraph[v][start] = 0;
                edge--;
                fleury_algorithm(v, tempGraph, numVertices, path, pathIndex, circuitFound);
            }
        }
    }
    if (edge == 0 && !(*circuitFound)) {
        *circuitFound = 1;
    }
}

void process_graphs(char* filename) {
    FILE* infile = fopen(filename, "r");
    if (!infile) {
        fprintf(stderr, "Error opening input file.\n");
        return;
    }

    int graph[MAX_VERTICES][MAX_VERTICES];
    int numVertices = 0;
    int lastGraph = 0;

    char line[100];
    while (fgets(line, sizeof(line), infile) != NULL) {
        if (line[0] == '\n' || feof(infile)) {
            if (lastGraph) {
                break;
            }
            int tempGraph[MAX_VERTICES][MAX_VERTICES];
            for (int i = 0; i < numVertices; i++) {
                for (int j = 0; j < numVertices; j++) {
                    tempGraph[i][j] = graph[i][j];
                }
            }

            Edge path[MAX_VERTICES];
            int pathIndex = 0;
            int circuitFound = 0;

            int startNode;
            find_start_vert(tempGraph, numVertices, &startNode);
            fleury_algorithm(startNode, tempGraph, numVertices, path, &pathIndex, &circuitFound);

            if (circuitFound) {
                printf("Euler Path or Circuit: ");
                for (int i = 0; i < pathIndex; i++) {
                    printf("%d--%d ", path[i].u, path[i].v);
                }
                printf("\n");
            } else {
                printf("No Euler circuit or path\n");
            }

            numVertices = 0;
            lastGraph = feof(infile);
        } else {
            int row[MAX_VERTICES];
            int col = 0;
            for (int i = 0; line[i] != '\0'; i++) {
                if (line[i] != ' ') {
                    row[col++] = line[i] - '0';
                }
            }
            for (int i = 0; i < col; i++) {
                graph[numVertices][i] = row[i];
            }
            numVertices++;
        }
    }
    fclose(infile);
}

int main() {
    process_graphs("graph.txt");
    return 0;
}
