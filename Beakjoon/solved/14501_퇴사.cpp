#include <iostream>
using namespace std;
// https://www.acmicpc.net/problem/14501

// 상담 정보를 저장할 구조체
struct Consult {
    int days;
    int rewards;
};

// 남은 상담 날짜 (<= 15)
int N;
// 배정된 상담들을 저장할 배열 (consults[i]: i일 째에 배정된 상담의 정보)
Consult consults[16];
// 각 날짜부터 얻을 수 있는 최대수익을 저장할 배열
// dp[0][n]: n일 차의 상담을 하지 않고 n일차부터 얻을 수 있는 최대수익
// dp[1][n]: n일 차의 상담을 하고 n일차부터 얻을 수 있는 최대수익
int dp[2][16];

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int days, rewards;
        cin >> days >> rewards;
        consults[i].days = days;
        consults[i].rewards = rewards;
    }
}

// 1. 해당 날짜에 배정된 상담을 하는 경우
// 해당 날짜의 배정된 상담의 수익 + 상담이 끝난 후 얻을 수 있는 최대수익
// 2. 해당 날짜에 배정된 상담을 하지 않는 경우
// 다음 날부터 상담을 했을 때 얻을 수 있는 최대 수익
// 1, 2 중 더 큰 값이 (now)일차에 얻을 수 있는 최대수익이다.
void solve(int now) {
    // 1일차까지 계산을 마치면 재귀 종료
    if (now < 1) {
        return;
    }

    // 현재 날짜에 배정된 상담의 정보
    int days = consults[now].days;
    int rewards = consults[now].rewards;

    // 현재 날짜에 배정된 상담을 하지 않을 경우 현재 날짜부터 얻을 수 있는 최대수익
    dp[0][now] = max(dp[0][now + 1], dp[1][now + 1]);

    // 현재 날짜에 배정된 상담을 할 경우 현재 날짜부터 얻을 수 있는 최대수익
    // 배정된 상담이 퇴사 당일에 끝나는 경우
    if (now - 1 + days == N) dp[1][now] = rewards;
    // 배정된 상담이 퇴사 전까지 끝나지 않는 경우
    else if (now - 1 + days > N)
        dp[1][now] = 0;
    // 배정된 상담이 퇴사 전에 끝나서, 이후 다른 상담을 할 수 있는 경우
    else
        dp[1][now] = rewards + max(dp[0][now + days], dp[1][now + days]);

    // 1일 전에 대해 계속해서 계산
    solve(now - 1);
}

int main(void) {
    input();
    solve(N);
    // 1일차의 상담을 하는 경우와 하지 않는 경우 중 더 큰 수익을 출력
    cout << max(dp[0][1], dp[1][1]);
}
