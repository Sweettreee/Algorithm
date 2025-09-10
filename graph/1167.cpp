#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int,int> > > tree;
vector<int> startNode;
vector<bool> isVisited;
int v;
int l_distance = -1;
int Max = 0;

void dfs(int cur, int cur_dis)
{
    isVisited[cur] = true;
    for(int i=0; i<tree[cur].size(); i++){
        int next = tree[cur][i].first;
        int nextD = tree[cur][i].second;
        Max = max(cur_dis+nextD,Max);
        if(!isVisited[cur]){
            dfs(next,cur_dis+nextD);
        }
    }
}

int main(void)
{
    // vector<pair<int,int> > v2(10);
    // tree.push_back(v2); // 전역변수론 안됌.
    int result = 0;
    cin >> v;
    tree.assign(10, vector<pair<int, int> >(10, make_pair(0, 0)));


    for(int i=0; i<v; i++){
        int a,b,d;
        cin >> a;

        startNode.push_back(a);
        while(1){
            cin >> b;
            if(b==-1) break;
            cin >> d;
            tree[a].push_back(make_pair(b,d));
            tree[b].push_back(make_pair(a,d));
        }
        // cout << "errrr";
    }
    // for(int i=0; i<v; i++){
    //     isVisited.assign(v+1,false);
    //     Max = 0;
    //     dfs(startNode[i],0);
    //     result = max(result,Max);
    // }
    // cout << result << "\n";

    return 0;
}