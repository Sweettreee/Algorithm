#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX(x,y) (x>y ? x : y) // x와 y중의 최댓값 
#define COMPARE(x,y) (x>y ? 1 : (x==y ? 0 : -1)) // x>y 이면 1, x==y이면 0, x<y 이면 -1

typedef struct { // 
    int coef; // 계수
    int degree; // 지수
}polyno;

typedef struct {
    int *coef;
    int degree;
}polynomial;

typedef struct polyNode *polyPointer;
typedef struct polyNode {
    int coef;
    int expon;
    polyPointer link;
}polyNode;

void merge(polyno list[], int left, int mid, int right, int size, polyno *tmp)
{
    int i,j,k,l;
    i = left;
    j = mid+1; 
    k = left;

    while(i<=mid && j<=right){
        if(list[i].degree>list[j].degree){ // list[i].degree 가 더 크다면 그 값부터 앞쪽에 넣기 (degree기준으로 내림차순)
            tmp[k].degree = list[i].degree; 
            tmp[k++].coef = list[i++].coef;
        }
        else{
            tmp[k].degree = list[j].degree;
            tmp[k++].coef = list[j++].coef;
        }
    }

    if(i>mid){ // mid를 넘어선 값이 남아있다면
        for(l=j; l<=right; l++){
            tmp[k].degree = list[l].degree;
            tmp[k++].coef = list[l].coef;
        }
    }
    else{ // mid를 넘지 않은 값들이 남아있다면
        for(l=i; l<=mid; l++){
            tmp[k].degree = list[l].degree;
            tmp[k++].coef = list[l].coef;
        }
    }

    for(l=left; l<=right; l++){ // 전체 복사
        list[l].degree = tmp[l].degree;
        list[l].coef = tmp[l].coef;
    }
}

void mergeSort(polyno list[], int left, int right, int size, polyno* tmp)
{
    int mid = (left+right)/2;
    if(left<right){
        mergeSort(list,left,mid,size,tmp);
        mergeSort(list,mid+1,right,size,tmp);
        merge(list,left,mid,right,size,tmp);
    }
}

polynomial* ADD_1(polynomial *a, polynomial *b)
{
    int i=0,j=0,l=0; // a, b, d 
    int sizeA = a->degree; // (sizeA+1)은 지수가 0인 항을 포함한 전체 항의 갯수
    int sizeB = b->degree; // (sizeB+1)은 지수가 0인 항을 포함한 전체 항의 갯수
    int size = MAX(sizeA,sizeB); // 합을 더해 새롭게 만들어지는 d의 항의 갯수(계수가 0인 것들도 포함)
    polynomial *d = (polynomial*)calloc(1,sizeof(polynomial)); // a와b를 더한 값을 저장할 새로운 배열
    d->coef = (int*)calloc(size+1,sizeof(int)); // 계수를 저장할 배열 생성

    d->degree = size; // 최고차

    while(i<=sizeA || j<=sizeB){
        switch COMPARE((sizeA-i),(sizeB-j)) // sizeA-i, sizeB-j는 최고차항부터 그 아래로 내려가면서 살피는 것
        {   // i=0 -> sizeA-0 = 최고차항의 인덱스
            case 1: //a>b
                d->coef[l++] = a->coef[i]; // a의 항 추가
                i++;
                break;
            case 0: // a==b
                d->coef[l++] = a->coef[i] + b->coef[j]; // a와 b항의 계수 합인 항 추가
                i++; j++;
                break;
            case -1: // a<b
                d->coef[l++] = b->coef[j]; // b항 추가
                j++;
                break;
        }
    }

    // 남은 항들은 전부 추가하기
    if(i>sizeA){ 
        for(;j<=sizeB; j++){
            d->coef[size-(sizeB-j)] += b->coef[j];
        }
    }
    else{
        for(;i<=sizeA; i++){
            d->coef[size-(sizeA-i)] += a->coef[i];
        }
    }
    
    return d;
}

polyno* ADD_2(int startA, int finishA, int startB, int finishB, polyno* d, int size)
{
    polyno* tmp = (polyno*)calloc(size,sizeof(polyno));
    int startd = 0; // d항의 시작점

    while(startA<=finishA && startB<=finishB){ 
        switch COMPARE(d[startA].degree,d[startB].degree)
        { // a와 b를 비교해 지수가 더 높은 것들을 더하기
            case 1: // a>b
                tmp[startd].coef = d[startA].coef;
                tmp[startd++].degree = d[startA++].degree;
                break;
            case 0: // a==b
                tmp[startd].coef = d[startA].coef + d[startB++].coef;
                tmp[startd++].degree = d[startA++].degree;
                break;
            case -1:
                tmp[startd].coef = d[startB].coef;
                tmp[startd++].degree = d[startB++].degree;
        }
    }
    // 남은 항들 더하기
    for(; startA<=finishA; startA++){
        tmp[startd].coef = d[startA].coef;
        tmp[startd++].degree = d[startA].degree;
    }
    for(; startB<=finishB; startB++){
        tmp[startd].coef = d[startB].coef;
        tmp[startd++].degree = d[startB].degree;
    }

    return tmp;
}

// 새 노드 만들기
void makePolyNode(int cof, int exp, polyPointer *ptr)
{
    polyPointer tmp = (polyPointer)malloc(sizeof(polyNode));
    
    tmp->coef = cof;
    tmp->expon = exp;
    tmp->link = NULL;

    (*ptr)->link = tmp;
    *ptr = tmp;
}

// 노드 이어붙이기
void attach(float coefficient, int exponent, polyPointer *ptr)
{
    polyPointer temp = (polyPointer)malloc(sizeof(polyNode));

    temp -> coef = coefficient;
    temp -> expon = exponent;

    (*ptr) -> link = temp;
    temp->link = NULL;
    *ptr = temp;
}

//연결리스트로 항 더하기
polyPointer ADD_3(polyPointer a, polyPointer b)
{
    int sum = 0;
    polyPointer rear,c;
    rear = (polyPointer)malloc(sizeof(polyNode)); // a와b를 더한 새로운 다항식의 시작점.
    c = (polyPointer)malloc(sizeof(polyNode));
    c = rear;

    while(a->link!=NULL && b->link!=NULL){
        switch (COMPARE(a->expon,b->expon))
        {
            case -1:
                attach(b->coef,b->expon,&rear); // push_back()
                b = b->link;
                break;
            case 0:
                sum = a->coef + b->coef;
                attach(sum,b->expon,&rear); // push_back()
                a = a->link;
                b = b->link;
                break;
            case 1:
                attach(a->coef,a->expon,&rear); // push_back()
                a = a->link;
                break;
        }
    }
    // 남은 항들 더하기
    for(; a; a=a->link) attach(a->coef,a->expon,&rear);
    for(; b; b=b->link) attach(b->coef,b->expon,&rear);
    rear -> link = NULL;
    c = c->link;
    return c;
}


int main(void)
{
    clock_t startClock, finishClock; // 시간측정
    double duration1,duration2,duration3;

    FILE *file = fopen("input.txt","r");
    FILE *fp = freopen("output.txt","w",stdout);

    int n,m; // m : 다항식A의 항 갯수, n : 다항식B의 항 갯수
    polyno *polA; // 다항식 A
    polyno *polB; // 다항식 B
    int a,b; // txt파일 입력 받는 변수

    if(file==NULL){
        perror("failed\n");
    }

    fscanf(file,"%d\t%d", &a,&b); // 파일의 내용 불러오기
    m = a;
    n = b;

    polA = (polyno*)malloc(m*sizeof(polyno));
    polB = (polyno*)malloc(n*sizeof(polyno));

    for(int i=0; i<m; i++){
        fscanf(file,"%d\t%d", &a,&b); // a: 계수, b: 지수

        polA[i].coef = a; // 계수 입력받기
        polA[i].degree = b; // 최고차항 구하기
    }
    for(int i=0; i<n; i++){
        fscanf(file,"%d\t%d", &a,&b); // a: 계수, b: 지수

        polB[i].coef = a;
        polB[i].degree = b;
    }
    // 지수를 기준으로 내림차순(병합정렬 활용)
    polyno* tmpA = (polyno*)calloc(m,sizeof(polyno)); // 머지소트를 위한 포인터 배열
    mergeSort(polA,0,m-1,m,tmpA);
    free(tmpA);
    polyno* tmpB = (polyno*)calloc(n,sizeof(polyno));
    mergeSort(polB,0,n-1,n,tmpB);

    free(tmpB);

    // get input from input.txt

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

    // way 1

    startClock = clock();

    polynomial polA1; // 다항식 a
    polynomial polB1; // 다항식 b
    polynomial* polyD1; // a와b를 더해 만든 다항식 d

    // 최고차항 받기
    polA1.degree = polA[0].degree;
    polB1.degree = polB[0].degree;
    // 계수들을 넣을 배열 생성
    polA1.coef = (int*)calloc(polA1.degree+1,sizeof(int));
    polB1.coef = (int*)calloc(polB1.degree+1,sizeof(int));
    // 배열에 계수들을 넣기
    for(int i=0; i<m; i++){
        polA1.coef[polA1.degree - polA[i].degree] = polA[i].coef;
    }

    for(int i=0; i<n; i++){
        polB1.coef[polB1.degree - polB[i].degree] = polB[i].coef;
    }
    // 덧셈
    polyD1 = ADD_1(&polA1,&polB1);

    int size1 = MAX(polA1.degree,polB1.degree);

    //print polyA
    
    for(int i=0; i<m-1; i++){
        printf("%dx^%d + ", polA[i].coef, polA[i].degree);
    }
    printf("%dx^%d\n", polA[m-1].coef,polA[m-1].degree);
    

    // print polB

    for(int i=0; i<polB1.degree; i++){
        if(polB1.coef[i]!=0){
            printf("%dx^%d + ", polB1.coef[i], polB1.degree-i);
        }
    }
    if(polB1.coef[polB1.degree]!=0){
        printf("%dx^%d\n", polB1.coef[polB1.degree], 0);
    }

    //출력
    for(int i=0; i<size1; i++){
        printf("%dx^%d + ", polyD1->coef[i],size1-i);
    }
    printf("%dx^%d\n", polyD1->coef[size1],0);

    finishClock = clock();

    free(polA1.coef);
    free(polB1.coef);

    duration1 = (double)(finishClock-startClock) / CLOCKS_PER_SEC;

    // ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // // way2

    startClock = clock();

    int l=0;
    polyno* polTemp; // 다항식 a와 b의 정보를 담아둘 배열
    polyno* pol2D; // a와b의 합을 구한 다항식 d를 담아놓을 포인터 배열
    int startA,startB,finishA,finishB;
    // 다항식 a의 시작점, 다항식 b의 시작점, 다항식 a의 끝점, 다항식 b의 끝점

    polTemp = (polyno*)calloc(m+n,sizeof(polyno));

    // 다항식 a와 b를 담아놓을 배열 polB
    startA = 0;
    for(int i=0; i<m; i++){
        polTemp[l].coef = polA[i].coef;
        polTemp[l++].degree = polA[i].degree;
    }
    finishA = l-1;
    startB = l;
    for(int i=0; i<n; i++){
        polTemp[l].coef = polB[i].coef;
        polTemp[l++].degree = polB[i].degree;
    }
    finishB = l-1;
    
    // 덧셈
    pol2D = ADD_2(startA,finishA,startB,finishB,polTemp,MAX(m,n));

    int size2 = MAX(polA->degree,polB->degree);

    //print polyA

    for(int i=0; i<m-1; i++){
        printf("%dx^%d + ", polTemp[i].coef, polTemp[i].degree);
    }
    printf("%dx^%d\n", polTemp[m-1].coef, polTemp[m-1].degree);

    // print polB

    for(int i=m; i<m+n-1; i++){
        printf("%dx^%d + ", polTemp[i].coef, polTemp[i].degree);
    }
    printf("%dx^%d\n", polTemp[m+n-1].coef, polTemp[m+n-1].degree);
    
    // print
    for(int i=0; i<size2; i++){
        printf("%dx^%d + ", pol2D[i].coef, pol2D[i].degree);
    }

    printf("%dx^%d\n", pol2D[size2].coef, pol2D[size2].degree);

    finishClock = clock();

    free(polTemp);
    free(pol2D);

    duration2 = (double)(finishClock-startClock) / CLOCKS_PER_SEC;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // way3

    startClock = clock();

    polyPointer headA; // 헤드 노드
    polyPointer headB;
    polyPointer tempA; // 헤드 노드의 주소를 담아놓을 포인터 변수
    polyPointer tempB;
    polyPointer polD3;

    headA = (polyPointer)malloc(sizeof(polyNode));
    headB = (polyPointer)malloc(sizeof(polyNode));

    tempA = headA;
    tempB = headB;

    // 노드 생성 및 삽입
    for(int i=0; i<m; i++){
        makePolyNode(polA[i].coef,polA[i].degree,&tempA);
    }
    headA = headA->link; // 아무 값도 입력되지 않은 헤드 노드에서 넘어가기
    for(int i=0; i<n; i++){
        makePolyNode(polB[i].coef,polB[i].degree,&tempB);
    }
    headB = headB->link;

    // 덧셈
    polD3 = ADD_3(headA,headB);

    //print polyA

    while(headA!=NULL){
        if(headA->link!=NULL)
            printf("%dx^%d + ", headA->coef,headA->expon);
        else{
            printf("%dx^%d\n", headA->coef,headA->expon);
        }
        headA = headA->link;
    }

    // print polB

    while(headB!=NULL){
        if(headB->link!=NULL)
            printf("%dx^%d + ", headB->coef,headB->expon);
        else{
            printf("%dx^%d\n", headB->coef,headB->expon);
        }
        headB = headB->link;
    }

    //출력
    while(polD3!=NULL){
        if(polD3->link!=NULL)
            printf("%dx^%d + ", polD3->coef,polD3->expon);
        else{
            printf("%dx^%d\n", polD3->coef,polD3->expon);
        }
        polD3 = polD3->link;
    }

    free(headA);
    free(headB);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    finishClock = clock();

    free(polA);
    free(polB);

    duration3 = (double)(finishClock-startClock) / CLOCKS_PER_SEC;
    printf("%f  %f  %f\n", duration1, duration2, duration3);

    fclose(fp);

    return 0;
}

// Apple clang version 17.0.0 (clang-1700.0.13.3)
// Target: arm64-apple-darwin24.4.0
// Thread model: posix

// poly.exe는 gcc를 통해 만든 실행파일로 실행하려면 ./poly.exe를 통해 실행할 수 있습니다.