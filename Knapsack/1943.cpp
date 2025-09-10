#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

struct Coin{
    int v;
    int c;
}coin[101];

int N;
int sum = 0;
bool dp[50001];

void input()
{
    sum = 0;
    cin >> N;
    for(int i=1; i<=N; i++){
        cin >> coin[i].v >> coin[i].c;
        sum += coin[i].v * coin[i].c;
    }
}

int sol(){
    memset(dp,false,sizeof(dp));
    input();
    if(sum%2) return 0;
    dp[0] = true;
    for(int i=1; i<=N; i++){
        for(int j=sum/2; j>=0; j--){
            if(dp[j]) continue;
            int cur = 0;
            for(int k=0; k<coin[i].c; k++){
                cur += coin[i].v;
                if(j-cur>=0) dp[j] = dp[j-cur];
                if(dp[sum/2]) return 1;
            }
        }
    }
    return dp[sum/2];
}

int main(void)
{
    for(int l=0; l<3; l++){
        cout << sol() << "\n";
    }

    return 0;
}