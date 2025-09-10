#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
vector<int> v;
vector<int> lis;
int ans;
int result;

void input()
{
    cin >> N;
    for(int i=0; i<N; i++){
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
}

void solution()
{
    lis.push_back(v[0]);
    for(int i=1; i<N; i++){
        if(v[i]>lis.back()){
            lis.push_back(v[i]);
        }
        else{
            int idx = lower_bound(lis.begin(),lis.end(),v[i]) - lis.begin();
            lis[idx] = v[i];
        }
    }
}

void output()
{
    result = v.size() - lis.size();
    cout << result << "\n";
}

void solve()
{
    input();
    solution();
    output();
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    solve();

    return 0;
}