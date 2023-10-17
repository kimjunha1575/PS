#include <iostream>
#include <queue>
using namespace std;

// https://www.acmicpc.net/problem/16953

int solve(int start, int target) {
    // bfs 초기값 설정
    queue<pair<int, int>> que;
    que.push({start, 1});

    while (not que.empty()) {
        int now = que.front().first;
        int cnt = que.front().second;
        que.pop();

        // 현재 값이 target보다 크면 반복 종료
        if (now > target) {
            continue;
        }
        // 현재 값이 target값과 같으면 반환
        if (now == target) {
            return cnt;
        }

        // 2배한 값, 오른쪽에 1을 덧붙인 값을 push
        int next;
        if (next < (0x7FFFFFFF / 2)) {
            next = now * 2;
            que.push({next, cnt + 1});
        }

        if (now < (0x7FFFFFFF / 10)) {
            next = now * 10 + 1;
            que.push({next, cnt + 1});
        }
    }
    return -1;
}

int main(void) {
    // 시작값 a, 목표값 b
    int a, b;
    cin >> a >> b;
    // bfs
    cout << solve(a, b);
}
