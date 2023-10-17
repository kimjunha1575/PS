#include <iostream>
#include <queue>
using namespace std;

// target에 도착했을 때 이전까지의 경로를 저장하기 위한 구조체
struct History {
    // 이전 값
    int value;
    // 이전에 수행한 연산(DSLR)
    char command;
};
// 방문여부, 이전 값, 이전 연산을 저장하는 visited배열
// visited[n]: n이 계산된 단계의 연산, 숫자
History visited[10000];

// DSLR 연산에 해당하는 함수들
int D(int n) {
    return (2 * n) % 10000;
}
int S(int n) {
    if (n == 0) return 9999;
    return n - 1;
}
int L(int n) {
    return (n % 1000) * 10 + n / 1000;
}
int R(int n) {
    return (n / 10) + (n % 10) * 1000;
}

void BFS(int ori, int target) {
    // 초기화
    for (int i = 0; i < 10000; i++)
        visited[i] = {-1, 0};
    queue<int> que;
    // 출발점 설정
    que.push(ori);
    visited[ori] = {ori, 0};

    while (not que.empty()) {
        int now = que.front();
        que.pop();

        // target에 도착하면 반복 종료
        if (now == target) {
            return;
        }

        // DSLR에 대한 각각의 연산
        int tmp = D(now);
        if (visited[tmp].value == -1) {
            visited[tmp] = {now, 'D'};
            que.push(tmp);
        }
        tmp = S(now);
        if (visited[tmp].value == -1) {
            visited[tmp] = {now, 'S'};
            que.push(tmp);
        }
        tmp = L(now);
        if (visited[tmp].value == -1) {
            visited[tmp] = {now, 'L'};
            que.push(tmp);
        }
        tmp = R(now);
        if (visited[tmp].value == -1) {
            visited[tmp] = {now, 'R'};
            que.push(tmp);
        }
    }
}

int main(void) {
    int T;
    cin >> T;
    for (int test = 1; test <= T; test++) {
        // input
        int ori, target;
        cin >> ori >> target;
        // BFS
        BFS(ori, target);
        string ans = "";
        // visited[target]부터 시작해서 출발점까지 순회하면서 연산 경로를 추적
        while (target != ori) {
            string tmp = "0";
            tmp[0] = visited[target].command;
            ans += tmp;
            target = visited[target].value;
        }
        // 추적한 경로를 반대로 출력(target > ori 순서로 순회하므로)
        for (int i = 0; i < ans.length(); i++) {
            cout << ans[ans.length() - 1 - i];
        }
        cout << "\n";
    }
}