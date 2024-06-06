// Aryaman Gautam, pa2, 1969309
#include <assert.h>
#include "Graph.h"

void printTestResult(int success) {
    if (success) {
        printf("Test: pass\n");
    } else {
        printf("Test: fail\n");
    }
}

int main(int argc, char* argv[]) {
    Graph G = NULL;
    List L = newList();
    G = newGraph(5);
    assert(getOrder(G) == 5);
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 1);
    assert(getSize(G) == 5 && getDist(G, 4) == -1 && getParent(G, 4) == NIL);
    BFS(G, 2);
    assert(getSource(G) == 2);
    getPath(L, G, 3);
    assert(front(L) == 2 && back(L) == 3 && length(L) == 2);
    assert(getDist(G, 3) == 1);
    freeGraph(&G);
    freeList(&L);
    printTestResult(1);
    return 0;
}
