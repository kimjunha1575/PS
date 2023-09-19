#include <iostream>
#include <queue>
using namespace std;

// https://www.acmicpc.net/problem/2578

// 빙고판 정보를 저장하기 위한 구조체
struct Pos {
    int row;
    int col;
};
// board[n]: n이 적힌 곳의 row, col 값을 구조체로 저장한다
Pos board[26];
// 사회자가 부르는 숫자를 큐에 저장
queue<int> announce;

void input() {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            int tmp;
            cin >> tmp;
            board[tmp].row = i;
            board[tmp].col = j;
        };
    for (int i = 0; i < 25; i++) {
        int tmp;
        cin >> tmp;
        announce.push(tmp);
    }
}

int main(void) {
    input();

    // 각각의 가로줄, 세로줄, 두 대각선에 대해 불려진 숫자의 개수를 저장
    int rows[5] = {0};
    int cols[5] = {0};
    int ru = 0;
    int lu = 0;

    // 사회자가 부른 숫자의 개수
    int i = 0;
    // 현재 빙고의 개수
    int bingo = 0;

    // 모든 숫자를 부를 때 까지 반복
    while (not announce.empty()) {
        // 사회자가 숫자를 부른다
        i++;
        int n = announce.front();
        announce.pop();

        // 해당 숫자가 어디에 위치해 있는지 찾는다
        int row = board[n].row;
        int col = board[n].col;

        // 해당하는 가로줄, 세로줄, 대각선의 값에 1을 더하고,
        // 빙고가 완성되면 빙고 개수를 갱신한다
        if (row == col) {
            lu++;
            if (lu == 5) bingo++;
        }
        if (row + col == 4) {
            ru++;
            if (ru == 5) bingo++;
        }
        rows[row]++;
        if (rows[row] == 5) bingo++;
        cols[col]++;
        if (cols[col] == 5) bingo++;

        // 빙고가 3개 이상이 되면 사회자가 부른 숫자의 개수를 출력하고 종료
        if (bingo >= 3) {
            cout << i;
            return 0;
        }
    }
}