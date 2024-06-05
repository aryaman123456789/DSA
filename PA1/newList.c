Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   assert(N != NULL);
   N->data = data;
   N->next = NULL;
   return(N);
}

void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}

void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

int length(List L) {
    if(L==NULL){
        fprintf(stderr, "L is NULL");
    exit(EXIT_FAILURE);
    }
    return L->length;
}

int index(List L) {
    return L->index;
}

int front(List L) {
    if (length(L) == 0) {
        fprintf(stderr, "front() called on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

int back(List L) {
    if (length(L) == 0) {
        fprintf(stderr, "back() called on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

int get(List L) {
    if (length(L) == 0) {
        fprintf(stderr, "get() called on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "get() called with undefined index\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

bool equals(List A, List B) {
    bool eq = false;
    Node N = NULL;
    Node M = NULL;

    eq = (length(A) == length(B));
    N = A->front;
    M = B->front;
    while (eq && N != NULL) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

void clear(List L) {
    if (L == NULL) {
        printf("calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node curr = L->front;
    while (curr != NULL) {
        Node temp = curr->next;
        freeNode(&curr);
        curr = temp;
    }
    L->front = NULL;
    L->back = NULL;
    L->length = 0;
    L->index = -1;
}

void set(List L, int x) {
    if (L == NULL) {
        printf("calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        printf("calling set() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        printf("calling set() with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

void moveFront(List L) {
    if (L == NULL) {
        printf("calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L) {
    if (L == NULL) {
        printf("calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

void movePrev(List L) {
    if (L == NULL) {
        printf("calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        if (L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        } else {
            L->cursor = L->cursor->prev;
            L->index--;
        }
    }
}

void moveNext(List L) {
    if (L == NULL) {
        printf("calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        if (L->cursor == L->back) {
            L->cursor = NULL;
            L->index = -1;
        } else {
            L->cursor = L->cursor->next;
            L->index++;
        }
    }
}

void prepend(List L, int x) {
    Node N = newNode(x);
    if (L->length == 0) {
        L->front = N;
        L->back = N;
        L->cursor = N;
        L->index = 0;
    } else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
        L->index++;
    }
    L->length++;
}

void append(List L, int x) {
    Node N = newNode(x);
    if (L->length == 0) {
        L->front = L->back = N;
    } else {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length++;
}

void insertBefore(List L, int x) {
  if (L == NULL) {
    fprintf(stderr, "calling insertBefore() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) <= 0 || index(L) < 0) {
    fprintf(stderr, "calling insertBefore() on empty or NULL cursor\n");
    exit(EXIT_FAILURE);
  }
  Node N = newNode(x);
  if (index(L) == 0) {
    L->front->prev = N;
    N->next = L->front;
    L->front = N;
  } else {
    N->prev = L->cursor->prev;
    L->cursor->prev->next = N;
    N->next = L->cursor;
    L->cursor->prev = N;
  }
  L->index++;
  L->length++;
}
  
void insertAfter(List L, int x) {
    if (L->cursor == NULL) {
        fprintf(stderr, "insertAfter() called on undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->cursor == L->back) {
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    } else {
        N->next = L->cursor->next;
        L->cursor->next->prev = N;
        N->prev = L->cursor;
        L->cursor->next = N;
    }
    L->length++;
}

void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
        Node n = L->front;
        if (L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        }
        if (L->length > 1) {
            L->front = L->front->next;
            L->front->prev = NULL;
            if(L->index!=-1){
                L->index--;
            }
            
        } else {
            L->front = L->back = NULL;
            if(L->index!=-1){
                L->index--;
            }
        }
        L->length--;
        freeNode(&n);
    }
}

void deleteBack(List L) {
  if (L == NULL) {
    printf("calling deleteBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) <= 0) {
    printf("calling deleteBack() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  Node temp = L->back;
  if (L->cursor == L->back) {
    L->cursor = NULL;
    L->index = -1;
  }
  if (length(L) == 1) {
    L->front = NULL;
    L->back = NULL;
    L->length = 0;
    freeNode(&temp);
  } else {
    L->back = temp->prev;
    L->back->next = NULL;
    L->length--;
    freeNode(&temp);
  }
}

void delete(List L) {
   if (L == NULL) {
      fprintf(stderr, "calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) == 0 || index(L) < 0) {
      fprintf(stderr, "calling delete() on empty List or undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   Node temp = L->cursor;
   if (temp == L->front) {
      L->front = temp->next;
      if (L->front != NULL) {
         L->front->prev = NULL;
      }
   } else if (temp == L->back) {
      L->back = temp->prev;
      if (L->back != NULL) {
         L->back->next = NULL;
      }
   } else {
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
   }
   L->cursor = NULL;
   L->index = -1;
   L->length--;
   freeNode(&temp);
}

void printList(FILE* out, List L) {
   if (L == NULL) {
      fprintf(stderr, "calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   for (Node N = L->front; N != NULL; N = N->next) {
      fprintf(out, "%d ", N->data);
   }
}

List copyList(List L) {
   if (L == NULL) {
      fprintf(stderr, "calling copyList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   List newL = newList();
   for (Node N = L->front; N != NULL; N = N->next) {
      append(newL, N->data);
   }
   return newL;
}