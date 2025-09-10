#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> v;
vector<int> lis;

int LIS(int N)
{
    int count = 0;
    int tmp;
    for(int i=0; i<N; i++){
        cin >> tmp;
        v.push_back(tmp);
    }
    for(int i=0; i<N; i++){
        lis.push_back(v[i]);
        count += 1;
        for(int j=i+1; j<N; j++){
            if(lis.back()<v[j]){
                lis.push_back(v[j]);
            }
            else{
                int idx = lower_bound(lis.begin(),lis.end(),v[j]) - lis.begin();
                lis[idx] = v[j];
            }
            count += (lis.size());
        }
        lis.clear();
    }
    return count;
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for(int i=0; i<T; i++){
        int N;
        cin >> N;
        int ans = LIS(N);
        cout << "Case #" << i+1 << ": " << ans << "\n";
        v.clear();
    }


    return 0;
}