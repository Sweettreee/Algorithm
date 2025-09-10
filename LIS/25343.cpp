#include <iostream>
#include <algorithm>
#include <vector>
#define endl "\n"
using namespace std;

int n;
int ans;
vector<int> v;
vector<int> lis;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i=0; i<n; i++){
        int tmp; cin >> tmp;
        v.push_back(tmp);
    }
    lis.push_back(v[0]);
    for(int i=1; i<n; i++){
        if(lis.back()<v[i]) lis.push_back(v[i]);
        else{
            int idx = lower_bound(lis.begin(),lis.end(),v[i]) - lis.begin();
            lis[idx] = v[i];
        }
    }
    ans = lis.size();
    cout << ans << endl;

    return 0;
}


