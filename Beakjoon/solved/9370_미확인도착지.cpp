#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

#define MAX_VERTEX_NUM     2001
#define MAX_EDGE_NUM       50001
#define MAX_CANDIDATES_NUM 101
using namespace std;

// https://www.acmicpc.net/problem/9370

// 예술가 한 쌍이 교차로 a, b를 지나간 것이 확인되었을 때,
// 1. 원래의 출발지를 기준으로, 
// 2. a 교차로를 기준으로,
// 3. b 교차로를 기준으로
// 총 3번의 dijkstra로 각 교차로에서의 최단거리들을 계산한다.
// 출발지부터 도착지까지의 최단경로에 교차로 a, b 사이를 잇는 도로가 포함되는 경우, '가능한 도착지' 로 간주한다.

// 교차로 정보를 저장할 구조체
struct Edge {
    int to;
    int dist;

    bool operator<(Edge e) const {
        return dist > e.dist;
    }
};

// 교차로 개수, 도로 개수, 목적지 후보의 개수
int vertices, edges, candidates;
// 출발지, 예술가 듀오가 지나간 것이 확인된 두 교차로
int start_point, confirmed_A, confirmed_B;
// 세 곳에서부터의 최단경로 정보를 저장할 배열 3개
int dist0[MAX_VERTEX_NUM];
int dist1[MAX_VERTEX_NUM];
int dist2[MAX_VERTEX_NUM];

// 도착지 후보를 저장할 벡터
vector<int> candidate;
// 그래프 정보를 저장할 벡터
vector<Edge> map[MAX_VERTEX_NUM];

// dijkstra
// 결과를 저장할 배열을 인자로 받아, 해당 배열에 결과를 저장하도록 작성함.
void dijkstra(int start, int result[MAX_VERTEX_NUM]) {
    for (int i = 1; i <= vertices; i++) {
        result[i] = 0x7FFFFFFF;
    }
    priority_queue<Edge> pq;
    pq.push({start, 0});
    result[start] = 0;

    while (not pq.empty()) {
        Edge now = pq.top();
        pq.pop();

        if (now.dist > result[now.to]) continue;

        for (int i = 0; i < map[now.to].size(); i++) {
            Edge next = map[now.to][i];
            int d = result[now.to] + next.dist;
            if (result[next.to] <= d) continue;

            result[next.to] = d;
            pq.push({next.to, d});
        }
    }
}

int main(void) {
    int T;
    cin >> T;
    // 모든 테스트 케이스에 대해
    for (int test = 1; test <= T; test++) {
        // 입력 받고
        cin >> vertices >> edges >> candidates;
        cin >> start_point >> confirmed_A >> confirmed_B;
        for (int i = 0; i < edges; i++) {
            int from, to, d;
            cin >> from >> to >> d;
            map[from].push_back({to, d});
            map[to].push_back({from, d});
        }
        for (int i = 0; i < candidates; i++) {
            int tmp;
            cin >> tmp;
            candidate.push_back(tmp);
        }

        // 세 곳으로부터의 dijkstra
        dijkstra(start_point, dist0);
        dijkstra(confirmed_A, dist1);
        dijkstra(confirmed_B, dist2);
        // a, b 사이의 거리
        int gap = dist1[confirmed_B];

        // 도착지 후보들을 오름차순으로 정렬(문제 요구조건)
        sort(candidate.begin(), candidate.end());

        // 모든 도착지 후보에 대해
        for (int i = 0; i < candidate.size(); i++) {
            // 출발지부터 도착지 후보 까지의 최단경로
            int total = dist0[candidate[i]];
            // a, b 교차로 중 출발지와 더 가까운 곳에서부터 출발지까지의 최단경로
            int toA = min(dist1[start_point], dist2[start_point]);
            // a, b 교차로 중 도착지와 더 가까운 곳에서부터 출발지까지의 최단경로
            int toB = min(dist1[candidate[i]], dist2[candidate[i]]);
            // 최단경로에 a, b 사이를 잇는 경로가 포함될 경우, '가능한 도착지 후보'로 간주하고, 출력한다.
            if (total == toA + gap + toB) cout << candidate[i] << " ";
        }
        cout << "\n";
        
        // 다음 테스트 케이스를 위해 이번 테스트 케이스에서 사용한 부분 초기화
        for (int i = 0; i <= vertices; i++) map[i].clear();
        candidate.clear();
    }
}
