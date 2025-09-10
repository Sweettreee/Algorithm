#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> v;
vector<int> lis_front; // the heavier
vector<int> lis_Back; // the lighter

void solution(int tmp, int p)
{
    int idx;
    if(tmp>lis_front.back()){
        lis_front.push_back(tmp);
    }
    else if(p<=tmp && tmp<=lis_front.back()){
        idx = lower_bound(lis_front.begin(),lis_front.end(),tmp) - lis_front.begin(); // lower_bound 는 iterator를 반환
        lis_front[idx] = tmp;
    }
    else if(abs(lis_Back.back())<=tmp && tmp<p){
        idx = lower_bound(lis_Back.begin(),lis_Back.end(),-1*tmp) - lis_Back.begin();
        lis_Back[idx] = -1*tmp;
    }
    else if(tmp<abs(lis_Back.back())){
        lis_Back.push_back(-1*tmp);
    }
}

int main(void)
{
    int N,ans,Max=0;
    cin >> N;
    if(N==0){
        cout << 0 << "\n";
        return 0;
    }
    for(int i=0; i<N; i++){
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
    for(int l=0; l<N; l++){
        lis_front.clear();
        lis_Back.clear();
        for(int i=l; i<N; i++){
            if(i==l){
                lis_front.push_back(v[i]);
                lis_Back.push_back(-1*v[i]);
                continue;
            }
            solution(v[i], v[l]);
        }
        
        ans = lis_front.size() + lis_Back.size() - 1;
        Max = max(ans,Max);
    }

    cout << Max << "\n";

    return 0;
}