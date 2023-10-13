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

// 입력 받기
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

// bfs로 최단거리 찾기
int bfs() {
    queue<int> que;
    int visited_station[100001] = {0};
    int visited_tube[1000] = {0};
    // 출발지 설정
    que.push(1);
    visited_station[1] = 1;

    while (not que.empty()) {
        int now = que.front();
        que.pop();

        // 도착지에 도착하면 종료
        if (now == N) return visited_station[now];

        // 현재 역에서 갈 수 있는 튜브를 모두 탐색
        for (int i = 0; i < stations[now].size(); i++) {
            int available_tube = stations[now][i];
            // 이미 탐색한 튜브라면 continue
            if (visited_tube[available_tube]) continue;

            // 현재 튜브에서 갈 수 있는 역을 모두 탐색
            for (int j = 0; j < hyper_tubes[available_tube].size(); j++) {
                // 현재 역에서 갈 수 있는 역
                int next = hyper_tubes[available_tube][j];

                // 이미 방문한 역이라면 continue
                if (visited_station[next]) continue;

                // 다음 역을 큐에 넣고 방문 표시
                que.push(next);
                visited_station[next] = visited_station[now] + 1;
            }
            // 한번 탐색한 튜브는 다시 탐색하지 않도록 표시
            visited_tube[available_tube] = 1;
        }
    }
    // 도착지에 도착하지 못했다면 -1 반환
    return -1;
}

int main() {
    input();
    printf("%d\n", bfs());
    return 0;
}