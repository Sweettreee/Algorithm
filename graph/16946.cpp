#include <iostream>
#include <vector>
#include <string.h>
#include <queue>
#define MAX 1001
using namespace std;

int N,M;
int map[MAX][MAX];
bool visited[MAX][MAX] = {false,};
int result[MAX][MAX] = {0,};
int dy[4]={1,-1,0,0};
int dx[4]={0,0,1,-1};
int Count;

void dfs(int x, int y)
{
    visited[y][x] = true;

    for(int i=0; i<4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(nx<1 || nx>M || ny<1 || ny>N) continue;

        if(map[ny][nx]==0 && visited[ny][nx]==false){
            Count++;
            dfs(nx,ny);
        }
    }
}

int main(void)
{
    cin >> N >> M;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            scanf("%1d", &map[i][j]);
        }
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(map[i][j]==1) {
                Count = 1;
                memset(visited,false,sizeof(visited));
                dfs(j,i);
                result[i][j] = Count;
            }
        }
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            cout << result[i][j];
        }
        cout << "\n";
    }

    return 0;
}