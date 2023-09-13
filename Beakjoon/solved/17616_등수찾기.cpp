#include <iostream>
using namespace std;

#define MAX_STUDENT_NUM 100010
#define MAX_QUERY_NUM   500000

// N명의 학생(1번 ~ N번)
// 두 명의 학생이 찾아가면 누가 더 높은 등수인지 알려준다
// 동점인 경우는 없다
// 둘 씩 짝을 지어 본부에 총 M번의 질문
// 등수를 알고싶은 학생 X
// 학생 X의 등수 범위를 계산해 출력한다

// input
// N M X (학생 수, 질문 수, 학생 X의 번호)
// A B (M번 주어진다) (A의 등수가 B보다 높다)

// output
// 가장 높은 등수 U, 가장 낮은 등수 V를 출력( ex. 2 5 )
// U V

// X의 위로 몇 명, 아래로 몇 명이 있는가
struct Rating {
    vector<int> upper;
    vector<int> lower;
};

Rating board[MAX_STUDENT_NUM];
bool visited[MAX_STUDENT_NUM];

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

    // solve
    // upper
    int up = DFS_upper(target) - 1;
    for (int i = 1; i <= cntStudent; i++) visited[i] = false;
    // lower
    int down = DFS_lower(target) - 1;

    cout << 1 + up << " " << cntStudent - down;
}