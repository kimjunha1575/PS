#include <iostream>
using namespace std;

#define MAX_STUDENT_NUM 100010
#define MAX_QUERY_NUM   500000

// https://www.acmicpc.net/problem/17616

// 특정 학생보다 앞 순위의 학생들의 번호와
// 특정 학생보다 뒷 순위의 학생들의 번호를 저장할 구조체
struct Rating {
    vector<int> upper;
    vector<int> lower;
};

// 학생들의 순위 정보를 저장할 구조체 배열
Rating board[MAX_STUDENT_NUM];
bool visited[MAX_STUDENT_NUM];

// (now)번 학생보다 높은 등수의 학생들의 수를 반환
int DFS_upper(int now) {
    int res = 1;

    for (int i = 0; i < board[now].upper.size(); i++) {
        int next = board[now].upper[i];
        if (visited[next]) continue;
        visited[next] = true;
        res += DFS_upper(next);
    }
    return res;
}

// (now)번 학생보다 낮은 등수의 학생들의 수를 반환
int DFS_lower(int now) {
    int res = 1;

    for (int i = 0; i < board[now].lower.size(); i++) {
        int next = board[now].lower[i];
        if (visited[next]) continue;
        visited[next] = true;
        res += DFS_lower(next);
    }
    return res;
}

int main(void) {
    // input
    int cntStudent, cntQuery, target;
    cin >> cntStudent >> cntQuery >> target;
    for (int i = 0; i < cntQuery; i++) {
        int a, b;
        cin >> a >> b;
        board[a].lower.push_back(b);
        board[b].upper.push_back(a);
    }

    // (target)번 학생보다 높은 등수의 학생 수를 저장
    int up = DFS_upper(target) - 1;
    // visited 초기화
    for (int i = 1; i <= cntStudent; i++) visited[i] = false;
    // (target)번 학생보다 낮은 등수의 학생 수를 저장
    int down = DFS_lower(target) - 1;

    // 조건에 맞춰 출력
    cout << 1 + up << " " << cntStudent - down;
}