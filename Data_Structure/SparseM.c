#include <stdio.h>

typedef struct {
    int row;
    int col;
    int value;
}term;

void smTranspose(term a[], term b[])
{
    int i,j,currentb;
    b[0].col = a[0].row; // 전치니깐 행과 열이 바뀌므로 행의 개수가 열의 개수가 됌
    b[0].row = b[0].col;
    b[0].value = a[0].value;

    if(a[0].value>0){ // if not 0
        currentb = 1;
        for(int i=0; i<a[0].col; i++){ // 열별로 전치 반복 수행
            for(int j=0; j<=a[0].value; j++) // 0이 아닌 항만 수행
                b[currentb].row = a[j].col;
                b[currentb].col = a[j].row;
                b[currentb].value = a[j].value;
                currentb++;
        }
    } 


}

int main(void)
{
    int i, j;
    term A[11] = { {8,7,10}, {0,2,2}, {0,6,12}, {1,4,7}, {2,0,23}, {3,3,31}, {4,1,14}, {4,5,25}, {5,6,6}, {6,0,52}, {7,4,11} };
    term B[11];

    smTranspose(A, B); // 행렬의 전치

    printf("행의 수: %d, 열의 수: %d, 0이 아닌 항의 수: %d\n", A[0].row, A[0].col, A[0].value);

    for (i = 1; i < 11; i++)
        printf("행: %d, 열: %d, 값: %d\n", A[i].row, A[i].col, A[i].value);
    printf("\n\n");

    smTranspose(A, B);

    printf("Transpose processing has been finished.\n");
    printf("\n\n");

    printf("행의 수: %d, 열의 수: %d, 0이 아닌 항의 수: %d\n", B[0].row, B[0].col, B[0].value);

    for (i = 1; i < 11; i++)
        printf("행: %d, 열: %d, 값: %d\n", B[i].row, B[i].col, B[i].value);
    printf("\n\n");

    return 0;
}