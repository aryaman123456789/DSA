// Aryaman Gautam, CSE102, Programming Project
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 500

typedef struct Edge {
    int src, dest;
    double weight;
    int label;
} Edge;

typedef struct Graph {
    int numVertices, numEdges;
    Edge edges[MAX_EDGES];
} Graph;

void readGraph(Graph* g, char* filename);
int compareEdges(const void* a, const void* b);
int findParent(int* parent, int vertex);
void unionSets(int* parent, int x, int y);
void kruskalMST(Graph* g, Edge* mst);
void writeMST(Edge* mst, int numMSTEdges, char* filename);

void readGraph(Graph* g, char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", &g->numVertices, &g->numEdges);
    for (int edgeIndex = 0; edgeIndex < g->numEdges; edgeIndex++) {
        int sourceVertex, destinationVertex;
        double edgeWeight;
        fscanf(file, "%d %d %lf", &sourceVertex, &destinationVertex, &edgeWeight);
        g->edges[edgeIndex].src = sourceVertex - 1;
        g->edges[edgeIndex].dest = destinationVertex - 1;
        g->edges[edgeIndex].weight = edgeWeight;
        g->edges[edgeIndex].label = edgeIndex + 1;
    }

    fclose(file);
}

int compareEdges(const void* a, const void* b) {
    Edge* EdgeA = (Edge*)a;
    Edge* EdgeB = (Edge*)b;
    if (EdgeA->weight > EdgeB->weight) {
        return 1;
    } else if (EdgeA->weight < EdgeB->weight) {
        return -1;
    } else {
        return 0;
    }
}

void kruskalMST(Graph* g, Edge* mst) {
    int numMSTEdges = 0;
    int parent[MAX_VERTICES];

    for (int i = 0; i < g->numVertices; i++)
        parent[i] = i;

    qsort(g->edges, g->numEdges, sizeof(Edge), compareEdges);

    for (int i = 0; i < g->numEdges && numMSTEdges < g->numVertices - 1; i++) {
        int srcParent = findParent(parent, g->edges[i].src);
        int destParent = findParent(parent, g->edges[i].dest);

        if (srcParent != destParent) {
            mst[numMSTEdges++] = g->edges[i];
            unionSets(parent, srcParent, destParent);
        }
    }
}

int findParent(int* parent, int vertex) {
    if (parent[vertex] == vertex)
        return vertex;
    return parent[vertex] = findParent(parent, parent[vertex]);
}

void unionSets(int* parent, int x, int y) {
    int xParent = findParent(parent, x);
    int yParent = findParent(parent, y);
    parent[xParent] = yParent;
}

void writeMST(Edge* mst, int numMSTEdges, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numMSTEdges; i++) {
        fprintf(file, "%4d: (%d, %d) %0.1f\n", mst[i].label, mst[i].src + 1, mst[i].dest + 1, mst[i].weight);
    }

    double totalWeight = 0;
    for (int i = 0; i < numMSTEdges; i++) {
        totalWeight += mst[i].weight;
    }
    fprintf(file, "Total Weight = %.2f\n", totalWeight);

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    Graph g;
    readGraph(&g, argv[1]);

    Edge mst[MAX_VERTICES - 1];
    kruskalMST(&g, mst);

    writeMST(mst, g.numVertices - 1, argv[2]);

    return 0;
}

