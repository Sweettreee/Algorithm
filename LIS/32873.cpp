#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    
    // 입력 배열 A
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    
    // 스택을 담을 벡터, 각 스택의 최상위 원소를 관리
    vector<int> stacks;
    
    for (int i = 0; i < N; i++) {
        int a = A[i];
        
        // a가 들어갈 수 있는 스택을 찾음 (가장 큰 값보다 작은 값을 찾는 것)
        auto it = lower_bound(stacks.begin(), stacks.end(), a);
        
        // 찾은 자리에 a를 넣거나, 새로운 스택을 생성
        if (it == stacks.end()) {
            stacks.push_back(a);  // 새로운 스택을 생성
        } else {
            *it = a;  // 기존 스택에 a를 삽입 (내림차순으로 정렬되도록)
        }
    }
    
    // 스택의 개수를 출력
    cout << stacks.size() << endl;
    
    return 0;
}
