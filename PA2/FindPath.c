#include "Graph.h"

int main(int argc, char* argv[]) {
    FILE* infile = fopen(argv[1], "r");
    FILE* outfile = fopen(argv[2], "w");
    if (infile == NULL || outfile == NULL) {
        exit(EXIT_FAILURE);
    }
    int nVertices, vertexU, vertexV;
    fscanf(infile, "%d", &nVertices);
    Graph G = newGraph(nVertices);

    while (fscanf(infile, "%d %d", &vertexU, &vertexV) == 2) {
        if (vertexU == 0 && vertexV == 0) {
            break;
        }
        addEdge(G, vertexU, vertexV);
    }
    printGraph(outfile, G);
    while (fscanf(infile, "%d %d", &vertexU, &vertexV) == 2) {
        if (vertexU == 0 && vertexV == 0) {
            break;
        }
        BFS(G, vertexU);
        if (getDist(G, vertexV) == INF) {
            fprintf(outfile, "The distance from %d to %d is infinity\n", vertexU, vertexV);
            fprintf(outfile, "No %d-%d path exists", vertexU, vertexV);
        } else {
            fprintf(outfile, "\nThe distance from %d to %d is %d\n", vertexU, vertexV, getDist(G, vertexV));
            fprintf(outfile, "A shortest %d-%d path is: ", vertexU, vertexV);
            List L = newList();
            getPath(L, G, vertexV);
            printList(outfile, L);
            freeList(&L);
        }
        fprintf(outfile, "\n");
    }

    freeGraph(&G);
    fclose(infile);
    fclose(outfile);
    return 0;
}