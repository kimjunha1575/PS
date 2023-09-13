#include <iostream>
#include <algorithm>
using namespace std;

// https://www.acmicpc.net/problem/17619

int N, Q;

struct Log {
    int x1, x2, num;
};

bool cmp(Log a, Log b) {
    return a.x1 < b.x1;
}

Log logs[100001];
int group[100001];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        int x1, x2, y;
        cin >> x1 >> x2 >> y;
        logs[i] = {x1, x2, i};
    }

    // sort by x1
    sort(logs, logs + N, cmp);

    // initialize variables for the first log & first group
    int group_id = 0;
    int farthest = logs[0].x2;
    group[0] = group_id;

    // group the logs
    for (int i = 1; i < N; i++) {
        // if next log is reachable from the previous log
        if (logs[i].x1 <= farthest) {
            // if next log is farther than the previous log
            // update the farthest log
            if (logs[i].x2 > farthest) farthest = logs[i].x2;
        }
        else {
            // if next log is not reachable from the previous log
            // update the group index
            group_id++;
            // update the farthest log
            farthest = logs[i].x2;
        }
        // group the log
        group[logs[i].num] = group_id;
    }

    for (int i = 0; i < Q; i++) {
        // input query
        int start, dest;
        cin >> start >> dest;
        start--;
        dest--;

        // output
        if (group[start] == group[dest])
            cout << 1 << '\n';
        else
            cout << 0 << '\n';
    }

    return 0;
}