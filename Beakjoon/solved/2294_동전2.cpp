#include <iostream>
using namespace std;

// https://www.acmicpc.net/problem/2294

// 동전의 가지수
int cntCoin;
// 만들어야 할 가치
int target;
// 동전의 종류
int coins[101];
// dp[n]: n원을 최소 몇 개의 동전으로 만들 수 있는지
int dp[10001];

void input() {
    cin >> cntCoin >> target;
    for (int i = 1; i <= cntCoin; i++) {
        cin >> coins[i];
    }
}

void solve(int cnt, int worth) {
    // dp배열에 개수 저장
    dp[worth] = cnt;
    // 모든 종류의 동전에 대해
    for (int i = 1; i <= cntCoin; i++) {
        // 현재 가치에서 해당 종류의 동전의 가치를 더하고
        int next = worth + coins[i];
        // 더한 값이 target 값보다 작거나 같고,
        // 이전에 만들어진 적이 없거나 이전보다 적은 종류의 동전으로 만들어졌다면
        // 재귀호출하여 배열에 저장한다.
        if (next <= target && (dp[next] == 0 || (dp[next] && dp[next] > cnt + 1))) solve(cnt + 1, next);

        // 조건에 맞지 않는 경우 재귀호출 하지 않음
    }
}

int main(void) {
    input();
    // 0개의 동전으로 만든 0원으로 재귀시작
    solve(0, 0);
    int ans = dp[target];
    // 주어진 값을 주어진 동전의 조합으로 만들 수 있는 경우, 저장된 최소종류 출력
    if (ans) printf("%d", ans);
    // 만들 수 없는 경우, -1 출력
    else
        printf("-1");
}
