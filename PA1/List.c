#include "List.h"

typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->prev = N->next = NULL;
    return N;
}

void freeNode(Node *pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->front = L->cursor = L->back = NULL;
    L->index = -1;
    L->length = 0;
    return L;
}

void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        while (length(*pL) != 0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

int length(List L) {
    if (L == NULL) {
        exit(EXIT_FAILURE);
    }
    return L->length;
}

int index(List L) {
    if (L == NULL) {
        exit(EXIT_FAILURE);
    }
    return L->index;
}

int front(List L) {
    if (L == NULL || L->length == 0) {
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

int back(List L) {
    if (L == NULL || L->length == 0) {
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

int get(List L) {
    if (L == NULL || L->length == 0 || L->cursor == NULL || L->index < 0) {
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

bool equals(List A, List B) {
    if (A == NULL || B == NULL) {
        exit(EXIT_FAILURE);
    }
    if (A->length != B->length) {
        return false;
    }
    Node a = A->front;
    Node b = B->front;
    while (a != NULL && b != NULL) {
        if (a->data != b->data) {
            return false;
        }
        a = a->next;
        b = b->next;
    }
    return true;
}

void clear(List L) {
    Node temp;
    while(L->front != NULL) {
        temp = L->front;
        L->front = L->front->next;
        free(temp);
    }
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}

void set(List L, int x) {
    if (L == NULL || L->length == 0 || L->index < 0) {
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

void moveFront(List L) {
    if (L == NULL) {
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L) {
    if (L == NULL) {
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

void movePrev(List L) {
    if (L == NULL) {
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->front) {
        L->cursor = NULL;
        L->index = -1;
    }
    else {
        L->cursor = L->cursor->prev;
        L->index--;
    }
}

void moveNext(List L) {
    if (L == NULL) {
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
    }
    else if (L->cursor != NULL) {
        L->cursor = L->cursor->next;
        L->index++;
    }
}

void prepend(List L, int x) {
    if (L == NULL) {
        exit(EXIT_FAILURE);
    }
    Node new = newNode(x);
    if (L->length == 0) {
        L->front = L->back = new;
        L->length++;
    }
    else {
        new->next = L->front;
        L->front->prev = new;
        L->front = new;
        if(L->cursor != NULL) {
            L->index++;
        }
        L->length++;
    }
}

void append(List L, int x) {
    if (L == NULL) {
        exit(EXIT_FAILURE);
    }
    Node new = newNode(x);
    if (L->length == 0) {
        L->front = L->back = new;
        L->length++;
    }
    else {
        new->prev = L->back;
        L->back->next = new;
        L->back = new;
        L->length++;
    }
}

void insertBefore(List L, int x) {
    if (L == NULL || L-length == 0 || L->index < 0) {
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        Node new = newNode(x);
        if (L->cursor == L->front) {
            new->next = L->front;
            L->front->prev = new;
            L->front = new;
        }
        else {
            new->prev = L->cursor->prev;
            new->next = L->cursor;
            L->cursor->prev->next = new;
            L->cursor->prev = new;
        }
        L->index++;
        L->length++;
    }
}

void insertAfter(List L, int x) {
    if (L == NULL || L->length == 0 || L->index < 0) {
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        Node new = newNode(x);
        if (L->cursor == L->back) {
            new->prev = L->back;
            L->back->next = new;
            L->back = new;
        }
        else {
            new->next = L->cursor->next;
            new->prev = L->cursor;
            L->cursor->next = new;
        }
        L->length++;
    }
}

void deleteFront(List L) {
    if (L == NULL || L->length == 0) {
        exit(EXIT_FAILURE);
    }
    if (L->length == 1) {
        freeNode(&L->front);
        L->front = L->cursor = L->back = NULL;
        L->index = -1;
        L->length = 0;
    }
    else {
        Node new = L->front;
        L->front = L->front->next;
        freeNode(&new);
        L->front->prev = NULL;
        if (L->index == 0) {
            L->cursor = NULL;
        }
        L->index--;
        L->length--;
    }
}

void deleteBack(List L) {
    if (L == NULL || L->length == 0) {
        exit(EXIT_FAILURE);
    }
    if (L->length == 1) {
        freeNode(&L->front);
        L->front = L->cursor = L->back = NULL;
        L->index = -1;
        L->length = 0;
    }
    else {
        Node new = L->back;
        if (L->cursor == new) {
            L->cursor = NULL;
            L->index = -1;
        }
        L->back = L->back->prev;
        freeNode(&new);
        L->back->next = NULL;
        L->length--;
    }    
}

void delete(List L) {
    if (L == NULL || L->length == 0 || L->index < 0) {
        exit(EXIT_FAILURE);
    }
    Node new = L->cursor;
    if (L->length == 1) {
        freeNode(&L->front);
        L->front = L->back = NULL;
    }
    else {
        if (L->front == new) {
            L->front = new->next;
        }
        if (L->back == new) {
            L->back = new->prev;
        }
        if (new->prev != NULL) {
            new->prev->next = new->next;
        }
        if (new->next != NULL) {
            new->next->prev = new->prev;
        }
        freeNode(&new);
    }
    L->cursor = NULL;
    L->length--;
    L->index = -1;
}

void printList(FILE* out, List L) {
    if (L == NULL) {
        exit(EXIT_FAILURE);
    }
    Node new = NULL;
    for (new = L->front; new != NULL; new = new->next){
        fprintf(out, "%d ", new->data);
    }
}

List copyList(List L) {
    if (L == NULL) {
        exit(EXIT_FAILURE);
    }
    Node new = NULL;
    List list = newList();
    new = L->front;
    while (new != NULL) {
        append(list, new->data);
        new = new->next;
    }
    return list;
}

List concatList(List A, List B) {
    List list = malloc(sizeof(ListObj));
    list->front = A->front;
    list->back = B->back;
    list->length = A->length + B->length;
    list->index = -1;
    list->cursor = NULL;
    A->back->next = B->front;
    B->front->prev = A->back;
    return list;
}

