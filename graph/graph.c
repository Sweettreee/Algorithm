#include <stdio.h>
#include <stdlib.h>

typedef struct edge{
    int from;
    int to;
    float cost1;
    float cost2;
}edge;

int FindSmallNode(float *distance, int *visited, int n)
{
    int minV = 1e9;
    int minIdx = -1;
    for(int i=1; i<=n; i++){
        if(visited[i]==1){
            continue;
        }
        if(distance[i]<minV){
            minV = distance[i];
            minIdx = i;
        }
    }
    return minIdx;
}

void Dijkstra(edge **map, float *distance, int *visited, int start, float alpa, float beta, int n,int *path)
{
    for(int i=1; i<=n; i++){
        distance[i] = map[start][i].cost1*alpa + map[start][i].cost2*beta; // 초기 가중치 계산
        path[i] = start; // 경로 저장
    }

    distance[start] = 0; // 시작 노드 0
    visited[start] = 1; // 방문 처리
    path[start] = -1;

    for(int i=0; i<n-1; i++){
        int newNode = FindSmallNode(distance,visited,n); // 인접 노드 중 가중치가 가장 작은 간선 찾기
        visited[newNode] = 1;

        for(int j=0; j<=n; j++){ // 찾은 newNode의 인접 노드 탐색
            // 노드의 진출 간선들의 가중치 계산
            int curEdgeCost = map[newNode][j].cost1*alpa + map[newNode][j].cost2*beta;
            // 방문했다면 continue
            if(visited[j]==1)
                continue;
            // dp를 활용해 distance 최소값을 update
            if(distance[j]>distance[newNode]+curEdgeCost){
                distance[j] = distance[newNode] + curEdgeCost;
                path[j] = newNode;
            }
        }
    }
}

int main(void)
{
    float cost1,cost2; // first cost, second cost
    int from,to; // 출발 지점, 도착 지점
    int n,s,e; // 정점 개수, 출발 노드, 목표 노드

    float *distance; // 거리에 대한 배열
    int *visited; // 방문 처리
    int *path; // 경로 저장하는 배열 
    edge **map = (edge**)malloc(sizeof(edge*)*(n+1)); // 그래프를 구현하기 위한 인접행렬

    // input.txt 열기
    FILE *fp = fopen("input.txt","r"); 
    fscanf(fp, "%d, %d, %d\n", &n,&s,&e);
    if(fp == NULL){
        return 0;
    }

    FILE *fpwrite = fopen("output.txt","w");
    if(fpwrite == NULL){
        return 0;
    }

    // 각 배열을 동적 할당
    path = (int*)malloc(sizeof(int)*(n+1));
    distance = (float*)malloc(sizeof(float)*(n+1));
    visited = (int*)malloc(sizeof(int)*(n+1));

    // 그래프를 이차원 배열로 동적 할당
    for(int i=0; i<=n; i++){
        map[i] = (edge*)malloc(sizeof(edge)*(n+1));
    }

    for(int i=1; i<=n; i++) // 최소거리를 구하기 위해 1e9로 초기화
        for(int j=1; j<=n; j++){
            map[i][j].cost2 = 1e9;
    }

    // input.txt 내용 읽어오기
    while(fscanf(fp,"(%d,%d,%f,%f)\n", &from, &to, &cost1, &cost2)==4){
        map[from][to].cost1 = cost1;
        map[from][to].cost2 = cost2;
    }

    for(int i=0; i<=10; i++){ // 10개의 모든 가중치를 계산하기 위한 반복문
        // 가중치 계산
        float alpa = i*(0.1);
        float beta = 1 - (i*(0.1));

        for(int i=0; i<=n; i++){
            distance[i] = 1e9;
            visited[i] = 0;
        }

        // 최단 거리 구하기
        Dijkstra(map,distance,visited,s,alpa,beta,n,path);

        // output.txt에 내용 저장하기
        fprintf(fpwrite,"(%f, %f, %f)\n", alpa, beta, distance[e]);

        // 경로를 구하기 위한 배열
        int *stack = (int*)malloc(sizeof(int));
        int top = -1;

        int cur = e;
        while(cur!=-1){
            stack[++top] = cur;
            cur = path[cur];
        }

        fprintf(fpwrite,"Path: ");
        for(int i=top; i>0; i--){
            fprintf(fpwrite,"%d-", stack[i]);
        }
        fprintf(fpwrite,"%d\n",stack[0]);
    }
    
    return 0;
}
// 컴파일러 환경
// Apple clang version 17.0.0 (clang-1700.0.13.3)
// Target: arm64-apple-darwin24.4.0
// Thread model: posix
// InstalledDir: /Library/Developer/CommandLineTools/usr/bin