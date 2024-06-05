#include <assert.h>
#include "List.h"

int main() {
    List myList = newList();

    append(myList, 1);
    prepend(myList, 0);

    moveFront(myList);
    moveNext(myList);

    insertBefore(myList, -1);
    insertAfter(myList, 2);

    deleteFront(myList);
    deleteBack(myList);
    delete(myList);

    List copiedList = copyList(myList);

    List newListA = newList();
    append(newListA, 3);
    List newListB = newList();
    append(newListB, 4);
    List concatenatedList = concatList(newListA, newListB);

    assert(front(myList) == 2);
    assert(back(myList) == 2);
    assert(length(myList) == 1);
    assert(index(myList) == 0);
    assert(equals(myList, copiedList));
    assert(front(concatenatedList) == 3);
    assert(back(concatenatedList) == 4);
    assert(length(concatenatedList) == 2);

    freeList(&myList);
    freeList(&copiedList);
    freeList(&concatenatedList);

    return 0;
}
