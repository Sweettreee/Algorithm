#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define INF 1e9

struct Edge{
    int from,to,weight;
};

int N,M,W;

void BellmanFod(vector<Edge> v) {
    vector<int> dist(N+1,INF);
 
    dist[1] = 0; // init starting point

    for(int i=1; i<N; i++){
        for(int j=0; j<v.size(); j++){
            int from = v[j].from;
            int to = v[j].to;
            int w = v[j].weight;

            if(dist[to] > dist[from] + w){
                dist[to] = dist[from] + w;
            }
        }
    }

    for (int i = 0; i < v.size(); i++)
	{
		int from = v[i].from;
		int to = v[i].to;
		int weight = v[i].weight;

		// 현재까지의 가중치 + 다음으로 가기 위한 가중치가 다음 위치의 저장된 가중치보다 작다면 음의 사이클이 존재
		if (dist[from] + weight < dist[to])
		{
			cout << "YES" << "\n";
			return;
		}
	}
    cout << "NO" << "\n";
}

int main(void)
{
    cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);
    int tc;
    cin >> tc;

    for(int j=0; j<tc; j++){

        vector<Edge> v;

        cin >> N >> M >> W;

        int s,e,t;
        for(int i=0; i<M; i++){
            cin >> s >> e >> t;
            v.push_back({s,e,t});
            v.push_back({e,s,t});
        }
        for(int i=0; i<W; i++){
            cin >> s >> e >> t;
            v.push_back({s,e,-t});
        }
        BellmanFod(v);
        v.clear();
    }

    return 0;
}