#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    sort(a.begin(), a.end());

    long long best = LLONG_MAX;
    long long ans1 = 0, ans2 = 0, ans3 = 0;

    for (int i = 0; i < n - 2; ++i) {
        int l = i + 1, r = n - 1;
        while (l < r) {
            long long sum = a[i] + a[l] + a[r];
            if (llabs(sum) < llabs(best)) {
                best = sum;
                ans1 = a[i]; ans2 = a[l]; ans3 = a[r];
                if (best == 0) { // 더 나아질 수 없음
                    cout << ans1 << " " << ans2 << " " << ans3 << "\n";
                    return 0;
                }
            }
            if (sum > 0) r--;
            else l++;
        }
    }

    vector<long long> out = {ans1, ans2, ans3};
    sort(out.begin(), out.end());
    cout << out[0] << " " << out[1] << " " << out[2] << "\n";
    return 0;
}
