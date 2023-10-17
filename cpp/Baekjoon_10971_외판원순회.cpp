#include <iostream>
using namespace std;

// https://www.acmicpc.net/problem/10971

// 모든 vertex를 순회한 후, 출발지로 돌아오는 경로 중
// 비용이 최소인 경로를 찾아야 한다.

// 전략
// 1. 출발지와 연결된 vertex들에 대해 1번씩의 다익스트라(순회 후 돌아올 수 있어야 하므로)
// 2. 출발지까지 돌아오는 DFS (완전탐색) (~ 브루트 포스)

// 출발지가 조건으로 주어지는 경우, 1번이 훨씬 빠르겠으나,
// 출발지의 조건이 주이지지 않고, 맵 크기도 작으므로
// 평범한 완전탐색으로 작성.

// 도시의 수
int N;
// 인접행렬을 저장할 2차배열
int map[10][10];
// visited
int visited[10] = {0};

// input
void input() {
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];
}
// initialize visited array
void initVisited() {
    for (int i = 0; i < N; i++)
        visited[i] = 0;
}

// st를 출발지로 하는 경로 중 최소비용을 구하는 dfs
// now: 현재 노드
// st: 출발지
// cnt: 현재 노드까지 순회한 노드의 수
// acc_cost: 현재 노드까지 비용의 누적 합
// ans: 정답 (출발지에서 최소비용 갱신이 가능할 경우 포인터를 통해 갱신해준다)
void dfs(int now, int st, int cnt, int acc_cost, int *ans) {
    // 순회 후 출발지에 도착하면
    if (now == st && cnt == N + 1) {
        // 최소비용 갱신이 가능할 경우, 갱신해준다
        if (acc_cost < *ans) *ans = acc_cost;
        // 재귀 종료
        return;
    }
    // 연결된 모든 노드 중,
    for (int i = 0; i < N; i++) {
        // 연결되지 않았거나,
        if (map[now][i] == 0) continue;
        // 이미 들렀던 곳이거나,
        if (visited[i]) continue;
        // 출발지인데 다른 모든 노드를 순회하지 않은 경우, 무시한다
        if (i == st && cnt < N) continue;
        // 재귀호출
        visited[i] = 1;
        dfs(i, st, cnt + 1, acc_cost + map[now][i], ans);
        // 모든 경로를 계산해야 하므로 다시 0으로 처리해준다
        visited[i] = 0;
    }
}

int main(void) {
    // 입력 받고
    input();
    // 정답 초기값 int 최대값으로 할당
    int ans = 0x7FFFFFFF;
    // 모든 노드에 대해
    for (int i = 0; i < N; i++) {
        // visited 초기화
        initVisited();
        // 재귀 시작
        // 출발지로 다시 돌아와야 하므로 출발지에서 visited 저장하지 않음
        dfs(i, i, 1, 0, &ans);
    }
    cout << ans;
}
