#include <iostream>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long long N, K;
  if (!(cin >> N >> K)) return 0;

  auto popc = [](unsigned long long x) {
#if __cpp_lib_bitops >= 201907L
    return (int)std::popcount(x);
#else
    return __builtin_popcountll(x);
#endif
  };

  long long ans = 0;
  while (popc((unsigned long long)N) > K) { // popcount(N) > K면 반복
    unsigned long long b = (unsigned long long)N & (-(unsigned long long)N); // 최하위 1값
    N += (long long)b;   // 다음 경계로 점프
    ans += (long long)b; // 구매 누적
  }

  cout << ans << "\n";
  return 0;
}
