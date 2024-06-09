#include "Graph.h"

typedef struct GraphObj {
    List* adjList;
    int source;
    int order;
    int size;
    int* color;
    int* parent;
    int* distance;
    int* discover;
    int* finish;
} GraphObj;

Graph newGraph(int n) {
    Graph g = malloc(sizeof(GraphObj));
    g->order = n;
    g->adjList = malloc((n + 1) * sizeof(List*));
    g->color = malloc((n + 1) * sizeof(int));
    g->parent = malloc((n + 1) * sizeof(int));
    g->distance = malloc((n + 1) * sizeof(int));
    g->discover = malloc((n + 1) * sizeof(int));
    g->finish = malloc((n + 1) * sizeof(int));
    g->size = 0;
    g->source = NIL;
    for (int i = 1; i <= n; i++) {
        g->adjList[i] = newList();
        g->color[i] = 1;
        g->parent[i] = NIL;
        g->distance[i] = INF;
        g->discover[i] = UNDEF;
        g->finish[i] = UNDEF;
    }
    return g;
}
void freeGraph(Graph* pG) {
    if (pG == NULL || *pG == NULL) {
        return;
    }
    for (int i = 1; i <= (*pG)->order; i++) {
        freeList(&((*pG)->adjList[i]));
    }
    free((*pG)->adjList);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->distance);
    free((*pG)->discover);
    free((*pG)->finish);
    free(*pG);
    *pG = NULL;
}

int getOrder(Graph G) {
    return G->order;
}

int getSize(Graph G) {
    return G->size;
}

int getParent(Graph G, int u) {
    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    return G->discover[u];
}

int getFinish(Graph G, int u) {
    return G->finish[u];
}

void addArc(Graph G, int u, int v) {
    List L = G->adjList[u];
    moveFront(L);
    while (index(L) > -1 && v > get(L)) {
        moveNext(L);
    }
    if (index(L) == -1) {
        append(L, v);
        G->size++;
    } else if (get(L) != v) {
        insertBefore(L, v);
        G->size++;
    }
}

void addEdge(Graph G, int u, int v) {
    if (u < 1 || u > G->order || v < 1 || v > G->order) {
        exit(EXIT_FAILURE);
    }
    List adjU = G->adjList[u];
    moveFront(adjU);
    while (index(adjU) != -1 && get(adjU) < v) {
        moveNext(adjU);
    }
    if (index(adjU) == -1) {
        append(adjU, v);
    } else {
        insertBefore(adjU, v);
    }
    List adjV = G->adjList[v];
    moveFront(adjV);
    while (index(adjV) != -1 && get(adjV) < u) {
        moveNext(adjV);
    }
    if (index(adjV) == -1) {
        append(adjV, u);
    } else {
        insertBefore(adjV, u);
    }
    G->size++;
}

void Visit(Graph G, int u, int *time, List S);

void DFS(Graph G, List S) {
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = 1;
        G->parent[i] = NIL;
    }
    int time = 0;
    List x = copyList(S);
    clear(S);
    moveFront(x);
    while (index(x) >= 0) {
        int u = get(x);
        if (G->color[u] == 1) {
            Visit(G, u, &time, S);
        }
        moveNext(x);
    }
    freeList(&x);
}

void Visit(Graph G, int u, int *time, List S) {
    G->color[u] = 2;
    G->discover[u] = (++(*time));
    List adjList = G->adjList[u];
    moveFront(adjList);
    while (index(adjList) >= 0) {
        int v = get(adjList);
        if (G->color[v] == 1) {
            G->parent[v] = u;
            Visit(G, v, time, S);
        }
        moveNext(adjList);
    }
    G->color[u] = 3;
    G->finish[u] = (++(*time));
    prepend(S, u);
}

Graph transpose(Graph G) {
    Graph transpose = newGraph(getOrder(G));
    for (int u = 1; u <= getOrder(G); u++) {
        List L = G->adjList[u];
        moveFront(L);
        while (index(L) >= 0) {
            int v = get(L);
            addArc(transpose, v, u);
            moveNext(L);
        }
    }
    return transpose;
} 

Graph copyGraph(Graph G) {
    Graph copy = newGraph(getOrder(G));
    for (int u = 1; u <= getOrder(G); u++) {
        List L = G->adjList[u];
        moveFront(L);
        while (index(L) >= 0) {
            int v = get(L);
            addArc(copy, u, v);
            moveNext(L);
        }
    }
    return copy;
} 

void printGraph(FILE* out , Graph G) {
    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjList[i]);
        fprintf(out, "\n");
    }
}