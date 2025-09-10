#include <stdio.h>
#define MAX 50

typedef struct {
    int row;
    int col;
}element;

int map[MAX][MAX] = {0,};
int visited[MAX][MAX] = {0,};

int dy[4]={1,-1,0,0};
int dx[4]={0,0,1,-1};

void path(void)
{
    element stack[MAX*2+1];
    int top = -1;

    while(top>=0){
        int curX = stack[top].col;
        int curY = stack[top].row;

        top++; // pop();

        for(int i=0; i<4; i++){
            int netX = curX + dx[i];
            int nextY = curY + dy[i];

            if(netX <0 || netX>MAX || nextY<0 || nextY>MAX) continue;

            if(map[nextY][netX]==0 && visited[nextY][netX]==0){
                stack[++top].row = nextY;
                stack[top].col = netX;
            }
        }
    }
}


int main(void)
{
    path();
    
    return 0;
}