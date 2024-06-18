#include "List.h"

int main() {
    List list = newList();

    append(list, 1);
    append(list, 2);
    append(list, 3);

    printf("Starting List:\n");
    printList(stdout, list);
    printf("\n");

    printf("List Length: %d\n", length(list));
    printf("List Index: %d\n", index(list));
    printf("Front Element: %d\n", *(int*)front(list));
    printf("Back Element: %d\n", *(int*)back(list));

    moveFront(list);
    printf("Moving to the front:\n");
    printList(stdout, list);
    printf("\n");

    insertBefore(list, 0);
    insertAfter(list, 10);
    printf("Inserting following elements:\n");
    printList(stdout, list);
    printf("\n");

    moveBack(list);
    printf("Moving to the back:\n");
    printList(stdout, list);
    printf("\n");

    deleteFront(list);
    deleteBack(list);
    printf("Deleting front and back:\n");
    printList(stdout, list);
    printf("\n");

    List copy = copyList(list);
    printf("List Copy:\n");
    printList(stdout, copy);
    printf("\n");

    List concatenatedList = concatList(list, copy);
    printf("Concatenated List:\n");
    printList(stdout, concatenatedList);
    printf("\n");

    freeList(&list);
    freeList(&copy);
    freeList(&concatenatedList);

    return 0;
}