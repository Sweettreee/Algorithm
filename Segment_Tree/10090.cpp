#include <iostream>
#include <algorithm>
#define NUMBER 1000001
typedef long long ll;

using namespace std;

ll arr[NUMBER];
ll tree[4*NUMBER];
ll res=0;

void update(int node, int st, int end, int t)
{
    if(t<st || t>end) return;

    if(st==end){
        if(t==st){
            tree[node] += 1;
        }
        return;
    }
    int mid = (st+end)/2;
    update(node*2,st,mid,t);
    update(node*2+1,mid+1,end,t);
    tree[node] = tree[node*2] + tree[node*2+1];
}

ll query(int node, int st, int end, int l, int r)
{
    if(l>end || st>r) return 0;

    if(l<=st && end<=r){
        return tree[node];
    }
    
    int mid = (st+end)/2;
    return query(node*2,st,mid,l,r) + query(node*2+1,mid+1,end,l,r);
}

int main(void)
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int  n;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }
    
    for(int i=0; i<n; i++){
        res += query(1,0,n-1,arr[i],n-1);
        update(1,0,n-1,arr[i]-1);
    }

    cout << res << "\n";

    return 0;
}