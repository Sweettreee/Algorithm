#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"
using namespace std;

int n;
int ans;
vector<int> v;
vector<int> lis;
vector<int> Index; // Index[i] = j; -> i -> LIS의 위치, i -> 큰 수열의 원소 위치, 즉 LIS i번째 들어가는 전체 수열 i번째 원소.

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i=0; i<n; i++){
        int tmp; cin >> tmp;
        v.push_back(tmp);
    }
    Index.push_back(0);
    lis.push_back(v[0]);
    for(int i=1; i<n; i++){
        if(lis.back()<v[i]) {
            lis.push_back(v[i]);
            Index.push_back(i);
        }
        else{
            int idx = lower_bound(lis.begin(),lis.end(),v[i]) - lis.begin();
            Index[idx] = i;
            lis[idx] = v[i];
        }
    }
    ans = lis.size();
    cout << ans << endl;
    
    for(int i=0; i<ans; i++)
        cout << v[Index[i]] << " ";

    return 0;
}