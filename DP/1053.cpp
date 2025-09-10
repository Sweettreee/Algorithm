#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAX 55
#define INF 987654321

int dp[MAX][MAX];
string s;

int solve(int l, int r, string a) {
	if (dp[l][r] != -1) return dp[l][r]; // 이미 확인했으면 continue
	if (l >= r) return 0; // 다 확인했으면 continue
	// int &ret = dp[l][r]; // dp의 주소를 넣어 dp의 값을 바꿈.
	dp[l][r] = min({ solve(l + 1, r, a) + 1, solve(l, r - 1, a) + 1, solve(l + 1, r - 1, a) + (a[l] != a[r]) });
	
	return dp[l][r];
}

int main() {
	cin >> s;
	memset(dp, -1, sizeof(dp));
	int ans = solve(0, s.size() - 1, s);
	for (int i = 0; i < s.size(); i++) {
		for (int j = i+1; j < s.size(); j++) {
			memset(dp, -1, sizeof(dp));
			string tmp = s;
			swap(tmp[i], tmp[j]);
			ans = min(ans, solve(0, s.size() - 1, tmp) + 1);
		}
	}
	cout << ans;
}