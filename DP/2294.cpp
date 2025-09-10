#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int n,k;
int coin[101];
int dp[10001]={0,};

int sol()
{
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int p = q.front();
        q.pop();
        for(int i=0; i<n; i++){
            int cur = p + coin[i];
            if(cur>k) continue;
            if(!dp[cur]) q.push(cur);
            if(dp[cur]) dp[cur] = min(dp[cur],dp[p]+1);
            else dp[cur] = dp[p] + 1;
        }
    }
    if(dp[k]) return dp[k];
    else return -1;
}

int main(void)
{
    cin >> n >> k;
    for(int i=0; i<n; i++){
        cin >> coin[i];
    }

    cout << sol() << "\n";

    return 0;
}