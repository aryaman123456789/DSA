#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct ListObj* List;
typedef struct NodeObj* Node;

List newList(void);         
void freeList(List* pL); 
Node newNode(void* data); 
void freeNode(Node* pN);   

int length(List L);            
int index(List L);       
void* front(List L);         
void* back(List L);            
void* get(List L);               

void clear(List L);               
void set(List L, void* x);            
void moveFront(List L);            
void moveBack(List L);              
void movePrev(List L);                                              
void moveNext(List L);                                               
void prepend(List L, void* x);                                         
void append(List L, void* x);                                    
void insertBefore(List L, void* x);   
void insertAfter(List L, void* x);  
void deleteFront(List L);      
void deleteBack(List L);         
void delete(List L); 
void printList(FILE* out, List L);
List copyList(List L);