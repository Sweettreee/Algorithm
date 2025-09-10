#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
vector<int> v;
vector<int> lis;

int main(void)
{
    cin >> N;
    for(int i=0; i<N; i++){
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
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
    int result = v.size() - lis.size();
    cout << result << "\n";

    return 0;
}