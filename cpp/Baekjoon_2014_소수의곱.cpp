#include <iostream>
#include <vector>
using namespace std;

// https://www.acmicpc.net/problem/2014

#define MAX_PRIME 100
#define MAX_COUNT 100000

int K, N;

// 주어지는 소수를 저장할 배열
// prime_numbers[i]: 주어진 i번째 소수
int prime_numbers[MAX_PRIME];

// 각 소수가 가리키는 ans 배열의 인덱스를 저장할 배열
// pointers[i]: i번째 소수가 가리키는 ans 배열의 인덱스
// pointers[i] = j라면, i번째 소수 * ans[j]가 가리키는 값이,
// i번째 소수를 인수로 가지면서 ans 배열에 추가될 수 있는 수 중 가장 작은 수임을 의미함
// i번째 소수 * ans[pointers[i]]의 값이 ans에 추가되면, pointers[i]를 1 증가시킴
int pointers[MAX_PRIME];

// 주어진 소수들을 곱해서 만들 수 있는 수들을 오름차순으로 저장한 배열
// ans[i]: 문제가 요구하는 i번째 수
int ans[MAX_PRIME + 1];

// ans 배열에 새롭게 추가될 수 중 가장 작은 수를 고르기 위한 버퍼
// ans에 추가될 수들 중에는 int범위를 넘어가는 경우가 있을 수 있기 때문에
// unsigned long long 사용함
vector<unsigned long long> targets;

// input
void input() {
    cin >> K >> N;
    for (int i = 0; i < K; i++) {
        cin >> prime_numbers[i];
    }
}

int main(void) {
    input();
    // ans[i] = 조건을 만족하는 i번째 소수 형태로 저장할 것이기 때문에
    // ans[0] = 1로 초기화
    ans[0] = 1;
    // 몇 번째 수인지 추적하기 위한 cnt 변수 초기화
    int cnt = 1;

    // N번째 수에 도달할 때 까지 반복
    while (cnt <= N) {
        // 버퍼 초기화
        targets.clear();

        // 최솟값을 추적하기 위한 변수 초기화
        unsigned long long min = 0xFFFFFFFFFFFFFFFF;

        // 주어진 모든 소수에 대해
        for (int i = 0; i < K; i++) {
            // tmp: i번째 소수 * i번째 소수가 가리키는 값
            // 현재 상황에서 i번째 소수를 인수로 가지면서 ans 배열에 추가될 수 있는 수 중 가장 작은 수
            unsigned long long tmp = prime_numbers[i] * ans[pointers[i]];

            // tmp가 min보다 작다면, targets를 초기화하고 min을 tmp로 갱신
            if (tmp < min) {
                targets.clear();
                min = tmp;
                targets.push_back(i);
            }
            // tmp가 min과 같다면, targets에 i를 추가
            else if (tmp == min) {
                targets.push_back(i);
            }
        }

        // 위에서 찾은 후보들 중 가장 작은 값을 ans 배열에 추가
        ans[cnt] = min;

        // N번째 수에 도달했다면, ans[cnt]를 출력하고 종료
        if (cnt == N) {
            cout << min;
            return 0;
        }

        // N번째 수에 도달하지 않았다면, cnt를 1 증가시키고
        // ans에 새롭게 추가된 값을 가리키는 pointers를 1 증가시킴
        cnt++;
        for (int i = 0; i < targets.size(); i++) {
            pointers[targets[i]]++;
        }
    }
}