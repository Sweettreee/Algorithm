#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int dist[1010];
int route[1010];

vector<int> ans;
const int inf = 987654321;//무한값
int main() {
	int n, m,a,b,c,st,ed;
	cin >> n >> m;
	for (int i = 0; i < n + 2; i++)
		dist[i] = inf;
	vector<pair<int, int>> path[1000];
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		path[a].push_back({ b,c });
	}
	
	
	cin >> st >> ed;

	priority_queue<pair<int,int>> pq;//비용, 도착지
	pq.push({ 0,st });//st >st 비용은 0
	dist[st] = 0;
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int now = pq.top().second;
		pq.pop();
		
		if (now == ed) {
			break;
		}
		

		//if (dist[now] <= cost)continue;//만약 새로 찾은 경로가 기존경로보다 값이 높다면 스킵.

		//dist[now] = cost;//최단거리 갱신.

		for (auto e : path[now]) {
			int nxt = e.first;
			int nxt_cost = e.second;
			if (dist[nxt]>dist[now]+nxt_cost) {//해당위치 위치로 최단경로 갱신 가능할 시, pq에 넣어 탐색한다. 
				dist[nxt] = dist[now] + nxt_cost;
				route[nxt] = now;//nxt로 가는 최단경로는 직전에 now를 거친다. ***
				pq.push({ -dist[nxt],nxt });

			}
		}
	}
	cout << dist[ed] << endl;
	int idx = ed;//***
	while (idx != st) {//***
		ans.push_back(idx);//***
		idx = route[idx];//***
	}
	ans.push_back(idx);//출발경로도 추가.
	cout << ans.size()<<endl;
	for (int i = ans.size()-1; i >= 0; i--) {//도착지>출발지 경로를 저장했으므로 
		cout << ans[i] << " ";         //거꾸로 출력해 출발> 도착지의 경로를 출력한다.
	}
	
	cout << endl;
}