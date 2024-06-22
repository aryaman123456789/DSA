#include <stdio.h>
#include <stdlib.h>

// create node structure that represents the node (data and pointer to next node)
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// allocate memory for a new node and initialize its data and next pointer
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// go through the linked list and print each node's value
void printList(Node* node) {
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("null\n");
}

// main to create 4 nodes, link them together, print them, and free the memory
int main() {
    Node* node1 = createNode(3);
    Node* node2 = createNode(5);
    Node* node3 = createNode(13);
    Node* node4 = createNode(2);
    
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    printList(node1);

    free(node1);
    free(node2);
    free(node3);
    free(node4);
    return 0;
}