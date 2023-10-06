#include <cstdio>
using namespace std;

// https://www.acmicpc.net/problem/2606

// dfs

// 그래프 저장
int map[101][101];
int visited[101];
// 컴퓨터 개수
int N;
// 연결된 컴퓨터 쌍의 수(edge)
int M;
// 정답
int ans = 0;

void input() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        map[a][b] = 1;
        map[b][a] = 1;
    }
}

// 순회하면서 노드를 만날 때 마다 ans에 1 추가
void dfs(int now) {
    for (int i = 1; i <= N; i++) {
        if (i == now) continue;
        if (visited[i]) continue;
        if (map[now][i] == 0) continue;
        visited[i] = 1;
        ans++;
        dfs(i);
    }
}

int main(void) {
    input();
    visited[1] = 1;
    dfs(1);
    printf("%d\n", ans);
}