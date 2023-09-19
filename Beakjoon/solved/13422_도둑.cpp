#include <iostream>
using namespace std;

// https://www.acmicpc.net/problem/13422

#define MAX_HOUSE_NUM 100000
#define MAX_ALERT_LIMIT 1000000000

// 집의 개수 N
// 도둑이 돈을 훔칠 집의 개수 M
// 방범장치가 작동하는 최소 돈의 양 K
int N, M, K;
// 도둑이 현재 훔친 돈의 총량의 초기값
int total;
// 각 집의 정보를 저장할 배열(circular 형태이므로 크기값 2배로 할당)
int map[2*MAX_HOUSE_NUM + 1];


void input() {
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        cin >> map[i];
        map[N+i] = map[i];
        // input 받으면서 total 초기값 계산
        total += map[i];
    }
}

int solve() {
    int res = 0;
    // sliding window의 초기값 구성
    // 0번 집부터 M-1번 집까지 M개의 집을 터는 경우, 그 경우 훔치는 돈
    int left = 0;
    int right = M-1;
    int cur = 0;
    for (int i = left; i <= right; i++) cur += map[i];

    // 탐색 시작
    // n개의 경우에 대해 한 칸씩 이동하면서 조건에 맞는 경우 res++
    for (int i = 0; i < N; i++) {
        if (cur < K) res++;
        cur -= map[left++];
        cur += map[++right];
    }
    return res;
}

int main(void) {
    int T;
    cin >> T;
    for (int test = 1; test <= T; test++) {
        // 도둑이 훔친 돈 초기화
        total = 0;
        input();
        // 모든 집에서 돈을 훔쳐야 하고, 그것이 가능한 경우,
        // 가능한 가짓수는 모든 집에서 돈을 훔치는 단 한 가지이기 때문에 1 출력
        if (N == M and total < K) {
            cout << 1 << "\n";
            continue;
        }
        // 다른 경우 가능한 총 경우의 수를 계산 후 출력
        int ans = solve();
        cout << ans << "\n";
    }
}
