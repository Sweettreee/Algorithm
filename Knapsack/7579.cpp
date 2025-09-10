#include <iostream>
#include <algorithm>
#define MAX 100

struct{
    int m;
    int c;
}A[101];
int dp[101][10001];
int N,M;

using namespace std;

int main(void)
{
    int sumC = 0;
    cin >> N >> M;
    for(int i=1; i<=N; i++){
        cin >> A[i].m;
    }
    for(int i=1; i<=N; i++){
        cin >> A[i].c;
        sumC += A[i].c;
    }

    for(int i=1; i<=N; i++){
        for(int j=0; j<=sumC; j++){
            if(A[i].c<=j){
                dp[i][j] = max(dp[i-1][j],A[i].m + dp[i-1][j-A[i].c]);
            }
            else
                dp[i][j] = dp[i-1][j];
        }
    }

    for(int i=0; i<=sumC; i++){
        if(dp[N][i] >= M){
            cout << i << "\n";
            break;
        }
    }

    return 0;
}