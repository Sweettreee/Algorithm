#include <iostream>
#include <vector>
using namespace std;

int N,Q;
vector<long long> arr;
long long segTree[400001];

long long init(int node, int st, int end)
{
    if(st==end) return segTree[node] = arr[st];
    int mid = (st+end)/2;

    return segTree[node] = init(node*2,st,mid) + init(node*2+1,mid+1,end);
}

void update(int n, int st, int end, int t, long long diff)
{
    if(t<st || t>end) return;

    segTree[n] += diff;

    if(st==end) return;
    int mid = (st+end)/2;
    update(n*2,st,mid,t,diff);
    update(n*2+1,mid+1,end,t,diff);
}

long long sum(int l,int r, int node, int st, int end)
{
    if(r<st || end<l) return 0;
    
    if(l<=st && end<=r) return segTree[node];

    int m = (st+end)/2;
    return sum(l,r,node*2,st,m) + sum(l,r,node*2+1,m+1,end);
}

int main(void)
{
    ios::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    cin >> N >> Q;
    for(int i=0; i<N; i++){
        long long num;
        cin >> num;
        arr.push_back(num);
    }
    init(1,0,N-1);
    for(int i=0; i<Q; i++){
        int x,y;
        long long a,b;
        cin >> x >> y >> a >> b;
        if(x<=y){
            cout << sum(x-1,y-1,1,0,N-1) << "\n";
        }
        else{
            cout << sum(y-1,x-1,1,0,N-1) << "\n";
        }
        update(1,0,N-1,a-1,b-arr[a-1]);
        arr[a-1] = b;
    }

    return 0;
}