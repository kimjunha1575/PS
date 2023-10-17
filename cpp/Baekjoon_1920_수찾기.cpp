#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

// https://www.acmicpc.net/problem/1920

// 정수의 개수
int N;
// 찾을 수의 개수
int M;
// 수를 저장할 집합
set<int> s;

int main(void) {
    // 입력
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int tmp;
        scanf("%d", &tmp);
        s.insert(tmp);
    }
    scanf("%d", &M);

    // 입력받은 숫자에 대해 집합에 있는지 확인
    for (int i = 0; i < M; i++) {
        int tmp;
        scanf("%d", &tmp);
        // 있으면 1, 없으면 0 출력
        if (s.find(tmp) != s.end()) {
            printf("1\n");
        }
        else printf("0\n");
    }
    return 0;
}
