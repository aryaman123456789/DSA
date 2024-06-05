#include "List.h"
void rotate (List L, int n);
int countEven(List L);
List mergeSortedLists(List A, List B);
void splitList(List source, List* front, List* back);

void rotate (List L, int n) {
    if (n == 0 || n == length(L)) {
        return;
    }
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            moveBack(L);
            prepend(L, get(L));
            delete(L);
        }
    }
    if (n < 0) {
        for (int i = 0; i > -n; i--) {
            moveFront(L);
            append(L, get(L));
            delete(L);
        }
    }
}

int countEven(List L) {
    int count = 0;
    moveFront(L);
    for (int i = 0; i < length(L); i++) {
        if (get(L) % 2 == 0) {
            count++;
        }
        moveNext(L);
    }
    return count;
}

List mergeSortedLists(List A, List B) {
    List sort = newList();
    moveFront(A);
    moveFront(B);
    while (index(A) >= 0 || index(B) >= 0) {
        if (index(A) >= 0 && ((index(B) < 0) || get(A) <= get(B))) {
            append(sort, get(A));
            moveNext(A);
        }
        else if (index(B) >= 0 && ((index(A) < 0) || get(B) < get(A))) {
            append(sort, get(B));
            moveNext(B);
        }
    }
    freeList(&sort);
    return sort;
}

void splitList(List source, List* front, List* back) {
    if (length(source) == 0) {
        return;
    } else if (length(source) == 1) {
        append(*front, get(source));
    } else {
        int left = (length(source)) / 2;
        int right = length(source) - left;
        moveFront(source);
        while (index(source) < left) {
            append(*front, get(source));
            moveNext(source);
        }
        while (index(source) >= 0) {
            append(*back, get(source));
            moveNext(source);
        }
    }
}