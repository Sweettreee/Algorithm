#include <stdio.h>

typedef struct listNode *listPointer;
typedef struct listNode {
    int data;
    listPointer link;
}listNode;

void insert(listPointer *first, listPointer x, int input)
{   
    listPointer temp = (listPointer)malloc(sizeof(listNode));

    temp->data = input;

    if(first) // if node exist
    {
        temp->link = x->link;
        x->link = temp;
    }
    else{
        temp->link = NULL;
        *first = temp;
    }
}

void delete(listPointer *first, listPointer trail, listPointer x)
{ // trail은 삭제하려고 하는 노드의 선행 노드
    if(trail){ // if trail is not first node
        trail -> link = x->link;
    }else{
        *first = (*first)->link;
    }
    free(x);
}

int main(void)
{
    listPointer head;
    head = NULL;



    return 0; 
}