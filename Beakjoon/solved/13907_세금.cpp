#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// https://www.acmicpc.net/problem/13907

// dijkstra로 해결하나, dist를 2차원으로 만들어서,
// dist[node_num][cnt_edge]: (node_num)번 노드까지 (cnt_edge)개의 도로를 거쳐 도착하는 최소통행비
// 형식으로 저장한다.
// 이렇게 저장하면 탐색을 여러 번 하지 않아도, 세금 인상 후 경로의 통행비를 바로 계산할 수 있다.

// 도로 정보를 저장할 구조체
// dijkstra를 이용할 것이므로 less operator 구현
struct Edge
{
    int to;
    int cost;

    bool operator<(Edge e) const {
        return cost > e.cost;
    }
};

// dist[node_num][cnt_edge]: (node_num)번 노드까지 (cnt_edge)개의 도로를 거쳐 도착하는 최소통행비
int dist[1001][1000];
// 도로 정보 저장할 vector
vector<Edge> map[1001];
int visited[1001];
// 세금 인상 정보
int increases[30000];
// 도시 개수, 도로 정보, 세금인상 회수
int cntCity, cntRoad, cntIncr;
// 출발지, 도착지
int start, dest;

// dijkstra
void dijkstra() {
    // dist 초기화
    for (int i = 0; i < 1001; i++)
        for (int j = 0; j < 1000; j++)
            dist[i][j] = 0x7FFFFFFF;

    // 출발지 추가
    priority_queue<pair<Edge, int>> pq;
    pq.push({{start, 0}, 0});
    dist[start][0] = 0;

    while (not pq.empty()) {
        int now = pq.top().first.to;
        int cost = pq.top().first.cost;
        int cnt = pq.top().second;
        pq.pop();

        if (dist[now][cnt] < cost) continue;
        // 최소경로를 찾아야 하므로, 지나온 도시 개수가 총 도시 개수보다 많은 경우 무시한다
        if (cnt >= cntCity) continue;
        cnt++;
        for (auto edge : map[now]) {
            int next = edge.to;
            int ncost = edge.cost;

            if (dist[next][cnt] > cost + ncost) {
                dist[next][cnt] = cost + ncost;
                pq.push({{next, cost + ncost}, cnt});
            }
        }
    }
}

void input() {
    scanf("%d %d %d", &cntCity, &cntRoad, &cntIncr);
    scanf("%d %d", &start, &dest);
    for (int i = 0; i < cntRoad; i++) {
        int from, to, cost;
        scanf("%d%d%d", &from, &to, &cost);
        map[from].push_back({to, cost});
        map[to].push_back({from, cost});
    }
    increases[0] = 0;
    for (int i = 1; i <= cntIncr; i++) {
        scanf("%d", &increases[i]);
    }
}

// n번 째 세금 인상에 대해, 최소 비용을 계산해서 반환한다
int Cal(int n) {
    // 최솟값 추적을 위해 초기화
    int res = 0x7FFFFFFF;
    // 출발지에서 도착지까지 i개의 도로를 거쳐온 모든 경로에 대해
    for (int i = 1; i < cntCity; i++) {
        // 비용이 초기값 그대로인 경우 무시(이동 가능한 경로가 없어서 갱신되지 않은 경우)
        if (dist[dest][i] == 0x7FFFFFFF) continue;
        // 이동가능한 경로가 있는 경우, n회 째의 세금인상 적용
        // main 함수에서 첫 번째 세금인상부터 마지막 세금인상까지 순차적으로 호출하므로
        // n 번째의 세금인상만 적용해주면 누적되어 적용된다.
        dist[dest][i] += increases[n] * i;
        // 최소비용 추적
        if (dist[dest][i] < res) res = dist[dest][i];
    }
    return res;
}

int main(void) {
    // input 받고
    input();
    // 경로 저장
    dijkstra();
    // 각 세금 인상마다
    for (int i = 0; i <= cntIncr; i++) {
        // 최소비용을 계산해서 출력
        printf("%d\n", Cal(i));
    }
    return 0;
}
