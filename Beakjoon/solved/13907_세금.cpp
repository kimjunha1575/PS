#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// https://www.acmicpc.net/problem/13907

// 문제 요약
// 통행료의 합이 가장 적은 경로로 이동
// 도로마다 통행료가 존재
// 세금이 A만큼 오르면 모든 도로의 통행료가 각각 A씩 오른다
// 도시의 수(cntCity) 2 ~ 1000
// 도로의 수(cntRoad) 1 ~ 30000
// 세금 인상 회수(cntIncr) 0 ~ 30000

// 문제해결 전략
// 세금 인상 회수만큼 dijkstra?
// 최악의 경우 1천개의 노드에 대해 3만번의 dijkstra를 행한다
// 시간초과 날 듯

// 세금이 인상됨에 따라 최적 경로 자체가 바뀔 수 있음.
// start 에서 dest 까지의 모든 경로의 통행료와 통과한 도로 개수를 미리 저장해두고
// 통행료 인상에 따라 각 경로의 통행료만 다시 계산할 수 있도록 하면
// 통행료 인상마다 새롭게 경로를 찾지 않아도 된다.

// 통행료가 최소인 경로를 찾는 것이고, 도착할 수 없는 경우는 주어지지 않기 때문에
// 같은 도로를 두 번 이상 지나가는 경우는 고려하지 않아도 된다.

// 그럼 경로 정보를 어떻게 저장?
// 정확히 어느어느 도로를 지나갔는지는 몰라도 됨
// 서로다른 모든 경로의 현재 통행료, 각 경로마다 지나간 도로의 개수.
// 위 두 정보만 저장해둘 수 있다면, 통행료 인상 후 최적경로를 찾는 건 쉽다(sort 등)

// 통행료, 지나온 도로 개수 를 pair<int, int>로 저장하는 벡터를 초기화하고
// dfs로 도착점에 도착할 때 마다 저장해주면 될 듯.

// pair<int, int> 보다 구조체로 저장하는 게 좋아보임
// 정렬할 때 총 통행료 기준으로 정렬해야하는데 그 때 그게 더 편할거같음

// 위 전략대로 구현한 결과 시간초과!
// 아예 다르게 접근해야 할 듯 함

// "모든 경로"를 찾을 필요가 없다
// dest로 n개의 노드를 거쳐 도착한 경로 중 최소값만 저장하면 된다.
// 같은 개수의 도로를 거쳐 도착한 경로들은 세금인상이 같은 값만큼 올라가기 때문에!!
// 먼저 작성했던 코드는 같은 개수의 도로를 거치는 서로다른 경로들도 모두 저장했음.

struct Path {
    int total_tax;
    int cnt;
};

struct Edge {
    int to;
    int cost;

    bool operator<(Edge e) const {
        return cost > e.cost;
    }
};

vector<Path> paths;
// dest에 도착하는 동안 거쳐갈 수 있는 도로의 최대값은 (도시 개수 - 1)임.
// 기본적으로 통행료의 최솟값을 찾기 때문에, 갔던 도시를 다시 방문하는 경우는 고려 안하기 때문
// 그렇기 때문에 지나간 도로 또한 도시의 개수보다 크거나 같을 수 없다!
int dist[1001][1000];
vector<Edge> map[1001];
int visited[1001];
int increases[30000];
int cntCity, cntRoad, cntIncr;
int start, dest;

// 불필요한 경로까지 모두 vector에 저장하는 함수임!
void dfs(int now, int acc_cost, int cnt) {
    if (now == dest) {
        paths.push_back({acc_cost, cnt});
        return;
    }

    for (int i = 0; i < map[now].size(); i++) {
        int next = map[now][i].to;
        if (visited[next]) continue;
        int cost = map[now][i].cost;

        visited[next] = 1;
        dfs(next, acc_cost + cost, cnt + 1);
        visited[next] = 0;
    }
}

// 필요한 경로만 찾는 함수!
void dijkstra() {
    for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 1000; j++) {
            dist[i][j] = 0x7FFFFFFF;
        }
    }
    priority_queue<pair<Edge, int>> pq;
    pq.push({{start, 0}, 0});
    dist[start][0] = 0;

    while (not pq.empty()) {
        int now = pq.top().first.to;
        int cost = pq.top().first.cost;
        int cnt = pq.top().second;
        pq.pop();

        if (dist[now][cnt] < cost) continue;
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

int calcMin(int n) {
    int res = 0x7FFFFFFF;
    for (int i = 0; i < paths.size(); i++) {
        paths[i].total_tax += paths[i].cnt * increases[n];
        if (paths[i].total_tax < res) res = paths[i].total_tax;
    }
    return res;
}

int Cal(int n) {
    int res = 0x7FFFFFFF;
    for (int i = 1; i < cntCity; i++) {
        if (dist[dest][i] == 0x7FFFFFFF) continue;
        dist[dest][i] += increases[n] * i;
        // increases[i] 가 나머지 부분은 0으로 초기화되어 있기 때문에
        // 오버플로우 걱정 ㄴㄴ
        if (dist[dest][i] < res) res = dist[dest][i];
    }
    return res;
}

void printDist(int row, int col) {
    for (int j = 1; j <= col; j++) {
        printf("%d ", dist[dest][j]);
    }
    printf("\n");
}

int main(void) {
    input();
    // visited[start] = 1;
    // dfs(start, 0, 0);
    dijkstra();
    // printDist(3, 3);
    for (int i = 0; i <= cntIncr; i++) {
        printf("%d\n", Cal(i));
    }
    return 0;
}