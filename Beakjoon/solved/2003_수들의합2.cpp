#include <iostream>
using namespace std;

// https://www.acmicpc.net/problem/2003

// 수열의 길이
int len;
// 수들의 합이 될 숫자
int target;
// 수열
int arr[10000];

void input() {
    cin >> len >> target;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
}

int main(void) {
    input();

    // sliding window 초기값 설정
    int left = 0, right = 0;
    int cur = arr[0];
    int ans = 0;

    // right가 len 보다 작다면 반복.
    // right가 len보다 크거나 같다면
    // right가 배열의 마지막 원소를 가리키고 있는 상황에서
    // 수들의 합이 target보다 작다는 뜻이므로 종료
    while (right < len) {
        // 합이 target보다 작으면 right를 오른쪽으로 이동
        if (cur < target) {
            right++;
            cur += arr[right];
            continue;
        }
        // 합이 target보다 크다면 left를 오른쪽으로 이동
        else if (cur > target) {
            cur -= arr[left];
            left++;
            continue;
        }
        // 합이 target과 같다면 경우의 수를 추가하고
        // left, right를 모두 한 칸씩 이동
        else {
            ans++;
            right++;
            cur += arr[right];
            cur -= arr[left];
            left++;
        }
    }
    // 정답 출력
    cout << ans;
}