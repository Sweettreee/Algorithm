#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> lis;
vector<int> v;

void input(int N)
{
    int tmp;
    for(int i=0; i<N; i++){
        cin >> tmp;
        v.push_back(tmp);
    }
}

void solution(int N)
{
    lis.push_back(v[0]);
    for(int i=1; i<N; i++){
        if(lis.back()<v[i]){
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
    int ans = lis.size();
    cout << ans << "\n";
}

void solve(int N)
{
    input(N);
    solution(N);
    output();
}

int main(void)
{
    while(1){
        int N;
        cin >> N;
        if(cin.eof()) break;
        solve(N);
        v.clear();
        lis.clear();
    }

    return 0;
}