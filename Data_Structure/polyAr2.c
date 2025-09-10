#include <stdio.h>
#define MAX_TERMS 100
#define COMPARE(x, y) ((x < y) ? -1 : ((x == y) ? 0 : 1)) 

typedef struct {
    float coef;
    int expon;
}polynomial;

polynomial terms[MAX_TERMS];

polynomial d[MAX_TERMS];
int avail = 0;

void attach(float cof, int expon)
{
    d[avail].coef = cof;
    d[avail].expon = expon;
    avail++;
}

void padd(int starta, int finisha, int startb, int finishb)
{
    float coefficient;
    int startd = avail;
    while(starta <= finisha && startb <+ finishb){
        switch (COMPARE(terms[starta].expon,terms[startb].expon))
        {
            case -1: 
                attach(terms[startb].coef,terms[startb].expon);
                startb++;
                break;
            case 0:
                coefficient = terms[starta].coef + terms[startb].coef;
                starta++;
                startb++;
                break;
            case 1:
                attach(terms[starta].coef,terms[starta].expon);
                starta++;
                break;
        }
    }
    if(starta<finisha){
        for(;starta<=finisha; starta++){
            attach(terms[starta].coef,terms[starta].expon);
        }
    }
    else{
        for(;startb<=finishb; startb++){
            attach(terms[startb].coef,terms[startb].expon);
        }
    }
}

int main(void)
{
    int sizeA,sizeB;
    
    scanf("%d %d", &sizeA, &sizeB);
    for(int i=0; i<sizeA; i++){
        scanf("%f %d", &terms[i].coef, &terms[i].expon);
    }
    for(int i=sizeA; i<sizeA+sizeB; i++){
        scanf("%f %d", &terms[i].coef, &terms[i].expon);
    }

    int startA = 0;
    int startB = sizeA;

    padd(startA,sizeA-1,startB,sizeA+sizeB-1);

    for(int i=0; i<avail; i++){
        printf("%f %d\n", d[i].coef, d[i].expon);
    }

    return 0;
}