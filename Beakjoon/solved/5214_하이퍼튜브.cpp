#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// https://www.acmicpc.net/problem/5214

int N, K, M;
// n번 튜브가 연결하는 역의 목록
vector<int> hyper_tubes[1000];
// n번 역에서 탈 수 있는 튜브의 목록
vector<int> stations[100001];

void input() {
    scanf("%d %d %d", &N, &K, &M);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            int tmp;
            scanf("%d", &tmp);
            hyper_tubes[i].push_back(tmp);
            stations[tmp].push_back(i);
        }
    }
}

int bfs() {
    queue<int> que;
    int visited_station[100001] = {0};
    int visited_tube[1000] = {0};
    que.push(1);
    visited_station[1] = 1;

    while (not que.empty()) {
        int now = que.front();
        que.pop();
        if (now == N) return visited_station[now];
        for (int i = 0; i < stations[now].size(); i++) {
            int available_tube = stations[now][i];
            if (visited_tube[available_tube]) continue;
            for (int j = 0; j < hyper_tubes[available_tube].size(); j++) {
                int next = hyper_tubes[available_tube][j];
                if (visited_station[next]) continue;
                que.push(next);
                visited_station[next] = visited_station[now] + 1;
            }
            visited_tube[available_tube] = 1;
        }
    }
    return -1;
}

int main() {
    input();
    printf("%d\n", bfs());
    return 0;
}