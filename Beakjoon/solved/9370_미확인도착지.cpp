#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

#define MAX_VERTEX_NUM     2001
#define MAX_EDGE_NUM       50001
#define MAX_CANDIDATES_NUM 101
using namespace std;

struct Edge {
    int to;
    int dist;

    bool operator<(Edge e) const {
        return dist > e.dist;
    }
};

int vertices, edges, candidates;
int start_point, confirmed_A, confirmed_B;
int dist0[MAX_VERTEX_NUM];
int dist1[MAX_VERTEX_NUM];
int dist2[MAX_VERTEX_NUM];

vector<int> candidate;
vector<Edge> map[MAX_VERTEX_NUM];

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
    for (int test = 1; test <= T; test++) {
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
        dijkstra(start_point, dist0);
        dijkstra(confirmed_A, dist1);
        dijkstra(confirmed_B, dist2);
        int gap = dist1[confirmed_B];

        sort(candidate.begin(), candidate.end());
        for (int i = 0; i < candidate.size(); i++) {

            int total = dist0[candidate[i]];
            int toA = min(dist1[start_point], dist2[start_point]);
            int toB = min(dist1[candidate[i]], dist2[candidate[i]]);

            if (total == toA + gap + toB) cout << candidate[i] << " ";
        }
        cout << "\n";

        for (int i = 0; i <= vertices; i++) map[i].clear();
        candidate.clear();
    }
}