#include <iostream>
#include <vector>
using namespace std;

unsigned long long findIndex(unsigned long long b)
{
    unsigned long long count = -1;
    while(b>0){
        count++;
        b/=2;
    }

    return count;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k;
    cin >> n >> k;
    vector<int> v(n,0);
    vector<int> sq[31];
    vector<int> bitIndex(n,0);

   for(int i=0; i<n; i++){
        cin >> v[i];
        int curVal = v[i];
        while(__builtin_popcountll(v[i])>1){
            unsigned long long b = (unsigned long long)v[i] & (-(unsigned long long)v[i]); // 최하위 1값
            v[i] += (long long)b;
            sq[findIndex(b)].push_back(curVal);
        }
    }

    return 0;
}