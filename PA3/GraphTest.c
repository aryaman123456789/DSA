#include <stdio.h>
#include "Graph.h"

int main() {
    int n = 5;
    Graph G = newGraph(n);

    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 1);

    printGraph(stdout, G);

    printf("Order: %d\n", getOrder(G));
    printf("Size: %d\n", getSize(G));

    for(int i = 1; i <= n; i++) {
        printf("Parent of %d: %d\n", i, getParent(G, i));
        printf("Discover time of %d: %d\n", i, getDiscover(G, i));
        printf("Finish time of %d: %d\n", i, getFinish(G, i));
    }

    List S = newList();
    for(int i = 1; i <= n; i++) {
        append(S, i);
    }
    DFS(G, S);

    Graph T = transpose(G);
    Graph C = copyGraph(G);

    printGraph(stdout, T);
    printGraph(stdout, C);

    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);
    freeList(&S);

    return 0;
}