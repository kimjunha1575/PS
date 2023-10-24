#include <iostream>
using namespace std;

// https://www.acmicpc.net/problem/1654

// 가지고 있는 랜선의 개수
int K;
// 만들어야 하는 랜선의 개수
int N;
// 가지고 있는 랜선의 길이를 저장할 배열
int len[10000];

void input() {
    cin >> K >> N;
    for (int i = 0; i < K; i++)
        cin >> len[i];
}

// 길이 n의 랜선을 N개 이상 만들 수 있는지 검사
bool Possible(int n) {
    int cnt = 0;
    for (int i = 0; i < K; i++) {
        cnt += len[i] / n;
        // N개 이상 만들어지면 즉시 true를 반환
        if (cnt >= N) return true;
    }
    return false;
}

// 이진탐색
// mid 값을 계산하는 과정에서 overflow가 일어날 수 있으므로 long long으로 선언해야한다
long long binary_search() {
    // 이진 탐색의 최소값과 최대값
    long long left = 1;
    long long right = 0x7fffffff;

    while (left <= right) {
        long long mid = (left + right) / 2;
        if (Possible(mid))
            left = mid + 1;
        else
            right = mid - 1;
    }

    if (right > 0)
        return right;
    else
        return left;
}

int main(void) {
    input();
    cout << binary_search();
}