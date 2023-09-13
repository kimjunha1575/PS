#include <iostream>
#include <queue>
using namespace std;

struct History {
    int value;
    char command;
};

History visited2[10000];

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

void BFS2(int ori, int target) {
    for (int i = 0; i < 10000; i++)
        visited2[i] = {-1, 0};
    queue<int> que;
    que.push(ori);
    visited2[ori] = {ori, 0};

    while (not que.empty()) {
        int now = que.front();
        que.pop();

        if (now == target) {
            return;
        }

        // DSLR
        int tmp = D(now);
        if (visited2[tmp].value == -1) {
            visited2[tmp] = {now, 'D'};
            que.push(tmp);
        }

        tmp = S(now);
        if (visited2[tmp].value == -1) {
            visited2[tmp] = {now, 'S'};
            que.push(tmp);
        }

        tmp = L(now);
        if (visited2[tmp].value == -1) {
            visited2[tmp] = {now, 'L'};
            que.push(tmp);
        }

        tmp = R(now);
        if (visited2[tmp].value == -1) {
            visited2[tmp] = {now, 'R'};
            que.push(tmp);
        }
    }
}

int main(void) {
    int T;
    cin >> T;
    for (int test = 1; test <= T; test++) {
        int ori, target;
        cin >> ori >> target;
        BFS2(ori, target);
        string ans = "";
        while (target != ori) {
            string tmp = "0";
            tmp[0] = visited2[target].command;
            ans += tmp;
            target = visited2[target].value;
        }
        for (int i = 0; i < ans.length(); i++) {
            cout << ans[ans.length() - 1 - i];
        }
        cout << "\n";
    }
}