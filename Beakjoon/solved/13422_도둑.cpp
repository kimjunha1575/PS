#include <iostream>
using namespace std;

#define MAX_HOUSE_NUM 100000
#define MAX_ALERT_LIMIT 1000000000

// N개의 집이 원형으로 이웃한 마을
// 각자 자신의 집에 돈을 보관
// 각 집의 숫자는 돈의 금액을 나타낸다
// 도둑은 M개의 연속된 집에서, 각각의 집에 보관중인 모든 돈을 훔친다
// 도둑이 K원 이상의 돈을 훔치면 도둑은 바로 붙잡힌다

// input
// 테스트 케이스의 수 T
// 각 테스트케이스 마다
// 집의 개수 N
// 도둑이 돈을 훔칠 집의 개수 M
// 방범장치가 작동하는 최소 돈의 양 K
// 각 집에서 보관중인 돈의 양이 순서대로 주어진다

// output
// 도둑이 붙잡히지 않고 돈을 훔칠 수 있는 방법의 수를 출력한다

int N, M, K;
int total;
int map[2*MAX_HOUSE_NUM + 1];


void input() {
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        cin >> map[i];
        map[N+i] = map[i];
        total += map[i];
    }
}

// N개의 집에 대해 한 방향으로 M개의 집을 털 수 있나 검사?
// 시간초과 예상됨

// 투포인터 이용해서 가야할듯. 배열 크기 두배로 하거나 나머지 연산자 이용해서.
// 슬라이딩 윈도우?
// 가지수를 찾는 문제라서 이분탐색은 적용하기 힘들어보임

// sliding window면 O(N)으로 처리 가능할 듯 함
// 배열 크기는 널널하니까 두배 해서 잡으면 될 듯

int solve() {
    int res = 0;
    // sliding window의 초기값 구성
    int left = 0;
    int right = M-1;
    int cur = 0;
    for (int i = left; i <= right; i++) cur += map[i];

    // 탐색 시작
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
        total = 0;
        input();
        if (N == M and total < K) {
            cout << 1 << "\n";
            continue;
        }
        int ans = solve();
        cout << ans << "\n";
    }
}
