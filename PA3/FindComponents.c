#include "Graph.h" 
#include "List.h"  =

int main(int argc, char *argv[]) {
    // Check if the correct number of command line arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the input and output files
    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = fopen(argv[2], "w");
    // Check if the files were opened successfully
    if (infile == NULL || outfile == NULL) {
        fprintf(stderr, "Error: Unable to open files %s and/or %s\n", argv[1], argv[2]);
        exit(EXIT_FAILURE);
    }

    // Read the order (number of vertices) from the input file
    int order;
    if (fscanf(infile, "%d", &order) != 1) {
        fprintf(stderr, "Error: Invalid input format for the number of vertices\n");
        exit(EXIT_FAILURE);
    }

    // Create a new graph with the given order
    Graph G = newGraph(order);

    // Read pairs of vertices from the input file and add arcs to the graph
    int u, v;
    while (fscanf(infile, "%d %d", &u, &v) == 2 && u != 0 && v != 0) {
        if (u < 1 || u > order || v < 1 || v > order) {
            fprintf(stderr, "Error: Invalid vertex number (%d, %d)\n", u, v);
            exit(EXIT_FAILURE);
        }
        addArc(G, u, v);
    }

    // Print the adjacency list representation of the graph to the output file
    fprintf(outfile, "Adjacency list representation of G:\n");
    printGraph(outfile, G);
    fprintf(outfile, "\n");

    // Create a new list and append all vertices to it
    List S = newList();
    for (int i = 1; i <= order; i++) {
        append(S, i);
    }
    // Perform depth-first search on the graph and the transpose of the graph
    DFS(G, S);
    Graph T = transpose(G);
    DFS(T, S);

    // Find the strongly connected components of the graph
    int SCC = 0;
    List stack = newList();
    List *components = calloc(order, sizeof(List));
    if (components == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // For each vertex in the list, if it has no parent in the transpose graph,
    // start a new strongly connected component
    moveFront(S);
    while (index(S) >= 0) {
        int u = get(S);
        if (getParent(T, u) == NIL) {
            List component = newList();
            components[SCC] = component;
            SCC++;
        }
        append(components[SCC - 1], u);
        moveNext(S);
    }

    // Print the strongly connected components to the output file
    fprintf(outfile, "G contains %d strongly connected components:\n", SCC);
    for (int i = SCC - 1; i >= 0; i--) {
        fprintf(outfile, "Component %d: ", SCC - i);
        printList(outfile, components[i]);
        fprintf(outfile, "\n");
    }
    // Free all allocated memory
    freeList(&S);
    freeList(&stack);
    for (int i = 0; i < SCC; i++) {
        freeList(&components[i]);
    }
    free(components);
    freeGraph(&G);
    freeGraph(&T);
    // Close the input and output files
    fclose(infile);
    fclose(outfile);

    return 0;
}
