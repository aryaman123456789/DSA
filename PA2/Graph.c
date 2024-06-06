// Aryaman Gautam, pa2, 1969309
#include "Graph.h"

typedef struct GraphObj {
    List* adjList;
    int source;
    int order;
    int size;
    int* color;
    int* parent;
    int* distance;
} GraphObj;

Graph newGraph(int n) {
    Graph g = malloc(sizeof(GraphObj));
    g->order = n;
    g->adjList = malloc((n + 1) * sizeof(List));
    g->color = malloc((n + 1) * sizeof(int));
    g->parent = malloc((n + 1) * sizeof(int));
    g->distance = malloc((n + 1) * sizeof(int));
    g->size = 0;
    g->source = NIL;
    for (int i = 1; i <= n; i++) {
        g->adjList[i] = newList();
        g->color[i] = 1;
        g->parent[i] = NIL;
        g->distance[i] = INF;
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
    free(*pG);
    *pG = NULL;
}

int getOrder(Graph G) {
    return G->order;
}

int getSize(Graph G) {
    return G->size;
}

int getSource(Graph G) {
    return G->source;
}

int getParent(Graph G, int u) {
    return G->parent[u];
}

int getDist(Graph G, int u) {
    return G->distance[u];
}

void getPath(List L, Graph G, int u) {
    if (getSource(G) == NIL || u < 1 || u > G->order) {
        exit(EXIT_FAILURE);
    }
    if (u == G->source) {
        append(L, G->source);
    } else if (G->parent[u] == NIL) {
        append(L, NIL);
    } else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}

void makeNull(Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        G->adjList[i] = newList();
        G->color[i] = NIL;
        G->parent[i] = NIL;
        G->distance[i] = INF;
   }
   G->size = 0;
   G->source = NIL;
   G->order = getOrder(G);
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

void addArc(Graph G, int u, int v) {
    if (u < 1 || u > G->order || v < 1 || v > G->order) {
        exit(EXIT_FAILURE);
    }
    append(G->adjList[u], v);
    G->size++;
} 

void BFS(Graph G, int s) {
    if (s < 1 || s > G->order) {
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= G->order; i++) {
        G->color[i] = 1;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->source = s;
    G->color[s] = 2;
    G->parent[s] = NIL;
    G->distance[s] = 0;
    List Q = newList();
    append(Q, s);
    while (length(Q) > 0) {
        int u = front(Q);
        deleteFront(Q);
        List neighbors = G->adjList[u];
        for (moveFront(neighbors); index(neighbors) >= 0; moveNext(neighbors)) {
            int v = get(neighbors);
            if (G->color[v] == 1) {
                G->color[v] = 2;
                G->parent[v] = u;
                G->distance[v] = G->distance[u] + 1;
                append(Q, v);
            }
        }
        G->color[u] = 3;
    }
    freeList(&Q);
}

void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjList[i]);
        fprintf(out, "\n");
    }
}