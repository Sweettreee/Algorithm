#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (((x) > (y)) ? 1 : ((x) == (y)) ? 0 : -1)

typedef struct polyNode *polyPointer;
typedef struct polyNode {
    int coef;
    int expon;
    polyPointer link;
}polyNode;

void makePolyNode(int cof, int exp, polyPointer *ptr)
{
    polyPointer tmp = (polyPointer)malloc(sizeof(polyNode));
    (*ptr)->coef = cof;
    (*ptr)->expon = exp;

    (*ptr)->link = tmp;
    tmp->link = NULL;
    *ptr = tmp;
}

void attach(float coefficient, int exponent, polyPointer *ptr)
{
    polyPointer temp;
    temp = (polyPointer)malloc(sizeof(polyNode));

    temp -> coef = coefficient;
    temp -> expon = exponent;
    (*ptr) -> link = temp;
    *ptr = temp;
}

polyPointer padd(polyPointer a, polyPointer b)
{
    int sum = 0;
    polyPointer rear,c;
    rear = (polyPointer)malloc(sizeof(polyNode));
    c = (polyPointer)malloc(sizeof(polyNode));
    c = rear;

    while(a->link!=NULL && b->link!=NULL){
        switch (COMPARE(a->expon,b->expon))
        {
            case -1:
                attach(b->coef,b->expon,&rear);
                b = b->link;
                break;
            case 0:
                sum = a->coef + b->coef;
                attach(sum,b->expon,&rear);
                a = a->link;
                b = b->link;
                break;
            case 1:
                attach(a->coef,a->expon,&rear);
                a = a->link;
                break;
        }
    }
    for(; a; a=a->link) attach(a->coef,a->expon,&rear);
    for(; b; b=b->link) attach(b->coef,b->expon,&rear);
    rear -> link = NULL;
    c = c->link;
    return c;
}

void print(polyPointer a)
{
    int i = 1;
    while(a->link!=NULL){
        printf("%d %d %d\n",i,a->coef,a->expon);
        a = a->link;
        i++;
    }
}

int main(void)
{
    int n,m;
    int cof,exp;
    scanf("%d %d", &n, &m);
    polyPointer tmpA,tmpB,sum;
    polyPointer a;
    a = (polyPointer)malloc(sizeof(polyNode));
    polyPointer b;
    b = (polyPointer)malloc(sizeof(polyNode));
    tmpA = a;
    tmpB = b;
    for(int i=0; i<n; i++){
        scanf("%d %d", &cof, &exp);
        makePolyNode(cof,exp,&tmpA);
    }
    for(int i=0; i<m; i++){
        scanf("%d %d", &cof, &exp);
        makePolyNode(cof,exp,&tmpB);
    }
    // print(a);
    // print(b);
    sum = padd(a,b);
    print(sum);
    free(a);
    free(b);
    return 0;
}

// 3 3
// 3 14
// 2 8
// 1 0
// 8 14
// -3 10
// 10 6
