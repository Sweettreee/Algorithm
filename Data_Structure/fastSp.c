#include <stdio.h>
#define MAX_TERMS 101
#define MAX_COL 50

typedef struct {
	int row;
	int col;
	int value;
} term;

term a[MAX_TERMS];

void fast_transpose(term a[], term b[]){
    // (1) 필요한 변수 선언
    int i, j;
    int row_terms [MAX_COL], starting_pos [MAX_COL];
    int num_cols = a[0].col, num_terms = a[0].value;

    // (2) a[0]값 b[0]에 복사
    b[0].row = num_cols;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    if ( num_terms > 0 ){
        // (3) row_terms 완성
        // (3-1) col 갯수만큼 row_terms의 배열 0으로 초기화
        // (3-2) col->인덱스로 들어가짐. 인덱스에 해당하는 row_terms 값을 +1 
        for(i=0; i<num_cols; i++) row_terms[i] = 0;
        for(i=1; i<=num_terms; i++) row_terms[a[i].col]++;

        // (4) starting_pos 완성
        starting_pos[0] = 1;
        for(i=1; i<num_cols; i++){
            starting_pos[i] = starting_pos[i-1] + row_terms[i-1];
        }

        // (5) transpose과정
        for(i=1; i<=num_terms; i++){
            j = starting_pos[a[i].col]++;
            printf("(j = %2d) = (starting_pos[a[%2d].col]++) <= (starting_pos[%d]++)\n", j, i, a[i].col);
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
        printf("starting_pos : ");
        for (int i = 0; i < 6; i++){
            printf("[%d]", starting_pos[i]);
        }
        printf("\n\n");          
    }      
}

int main(void) {
    // !! a[0]에는 통계값을 집어넣어야 함.
    // a[0]에 들어가는 col과 row는 index가 아닌 갯수로 들어가야함
    term a[9] = { {6,6,8}, {0,0,15}, {0,3,22}, {0,5,-15}, {1,1,11}, {1,2,3}, {2,3,-6}, {4,0,91}, {5,2,28} };
    term b[9];
	
	//원행렬 출력
	printf("index   row   col   value\n");
    printf("--------------------------\n");
	for (int i = 0; i < 9; i++){
    	printf(" a[%d] |  %d     %d     %d\n", i, a[i].row, a[i].col, a[i].value);		
	}
    printf("\n\n");
    
	//변형 알고리즘 적용
	fast_transpose(a,b);
    
    printf("\n\n");
	printf("Transpose processing has been finished.\n");
    printf("\n\n");
    
    //전치행렬 출력
	printf("index   row   col   value\n");
    printf("--------------------------\n");
	for (int i = 0; i < 9; i++){
    	printf(" b[%d] |  %d     %d     %d\n", i, b[i].row, b[i].col, b[i].value);		
	}
    printf("\n\n");  
    
	return 0;
}