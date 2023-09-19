#include <iostream>
#include <algorithm>
using namespace std;

// https://www.acmicpc.net/problem/17619

// 통나무의 수, 이동이 가능한 통나무인지 확인할 질문의 수
int N, Q;

// 주어지는 통나무의 정보를 저장할 구조체
struct Log {
    int x1, x2, num;
};

// 통나무 구조체의 정렬을 위한 비교함수
bool cmp(Log a, Log b) {
    return a.x1 < b.x1;
}

// 통나무 정보를 저장할 배열
Log logs[100001];

// 통나무가 속한 그룹의 번호를 저장할 배열
// group[i]: i번 통나무가 속한 그룹의 group id
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

    // 통나무의 시작점에 대해 오름차순으로 정렬
    sort(logs, logs + N, cmp);

    // initialize variables for the first log & first grou렬
    // 그룹화를 위한 초기값 설정
    int group_id = 0;
    // 현재 그룹의 통나무의 끝 지점 좌표 중 최대값
    int farthest = logs[0].x2;
    group[0] = group_id;

    // 그룹화 시작
    for (int i = 1; i < N; i++) {
        // 모든 통나무에 대해 (초기값으로 설정한 0 번째 통나무 제외)
        if (logs[i].x1 <= farthest) {
            // 다음 통나무의 시작점이 이전 통나무의 끝점보다 앞에 있거나 같다면
            // 최대값을 갱신
            if (logs[i].x2 > farthest) farthest = logs[i].x2;
        }
        else {
            // 현재 통나무에서 다음 통나무로 갈 수 없다면
            // 그룹 아이디와 최대값을 갱신(그룹이 바뀌므로 최대값도 갱신해야 함)
            group_id++;
            farthest = logs[i].x2;
        }
        // 그룹 저장
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