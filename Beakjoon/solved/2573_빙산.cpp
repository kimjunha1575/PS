#include <iostream>
#include <queue>
using namespace std;

// https://www.acmicpc.net/problem/2573

#define MAX_HEIGHT 300
#define MAX_WIDTH  300

// 얼음의 정보를 저장할 구조체
// height: 높이, speed: 녹는 속도
struct Ice
{
    int height;
    int speed;
};

int dy[] = {0, 1, 0, -1};
int dx[] = {1, 0, -1, 0};

// 얼음의 정보를 저장할 배열
Ice map[MAX_HEIGHT][MAX_WIDTH];
bool visited[MAX_HEIGHT][MAX_WIDTH];
int height, width;
// 출발지점
int ys, xs;
// 얼음의 개수
int cntIce;
// 녹은 얼음의 개수
int cntMelt = 0;

// 입력 받기
void input() {
    cntIce = 0;
    cin >> height >> width;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int height;
            cin >> height;
            map[i][j].height = height;
            map[i][j].speed = 0;
            if (height > 0) {
                // 얼음의 개수 세기
                cntIce++;
                // 출발지점 설정
                ys = i;
                xs = j;
            }
        }
    }
}

// visited 배열 초기화
void initVisited() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            visited[i][j] = false;
        }
    }
}

// 녹는 속도 계산
int calSpeed() {
    int res = 0x7FFFFFFF;
    initVisited();
    queue<pair<int, int>> que;
    // 순회 시작점 설정
    que.push({ys, xs});
    visited[ys][xs] = true;

    while (not que.empty()) {
        int y = que.front().first;
        int x = que.front().second;
        que.pop();

        ys = y;
        xs = x;

        // 방문 위치 얼음의 녹는 속도 초기화
        map[y][x].speed = 0;

        // 상하좌우 탐색
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            // 범위를 벗어나거나 이미 방문했다면 continue
            if (ny < 0 || nx < 0 || ny >= height || nx >= width) continue;
            if (visited[ny][nx]) continue;

            // 바다라면 녹는 속도 증가
            if (map[ny][nx].height == 0) {
                map[y][x].speed++;
                continue;
            }

            // 방문 표시하고 큐에 넣기
            visited[ny][nx] = true;
            que.push({ny, nx});
        }

        // 해당 위치 주변에 바다가 1칸 이상 있었다면
        if (map[y][x].speed > 0) {
            // 지도 정보 갱신
            int speed = map[y][x].speed;
            int height = map[y][x].height;
            int tmp = 0;

            // 해당 위치 얼음이 전부 녹는 데 걸리는 시간 계산
            while (height > 0) {
                height -= speed;
                tmp++;
            }
            // 가장 빨리 녹는 얼음이 녹는 데 걸리는 시간 tracking
            if (tmp < res) {
                res = tmp;
            }
        }
    }

    // 가장 빨리 녹는 얼음이 녹는 데 걸리는 시간 반환
    return res;
}

// 얼음 녹이기
void melt(int n) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // 얼음이 있다면
            if (map[i][j].height > 0) {
                // 녹이기
                map[i][j].height -= n * map[i][j].speed;
                // 높이가 0 이하가 되면 0으로 설정하고 녹은 얼음의 개수 증가
                if (map[i][j].height <= 0) {
                    map[i][j].height = 0;
                    map[i][j].speed = 0;
                    cntMelt++;
                }
                // 다 녹지 않았다면 다음 순회 시작점으로 설정
                else {
                    ys = i;
                    xs = j;
                }
            }
        }
    }
}

// DFS로 발견한 빙산에 방문 표시
void DFS(int y, int x) {
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if (ny < 0 || nx < 0 || ny >= height || nx >= width) continue;
        if (visited[ny][nx]) continue;
        if (map[ny][nx].height == 0) continue;

        visited[ny][nx] = true;
        DFS(ny, nx);
    }
}

// 빙산이 두 덩어리 이상으로 분리되었는지 확인
bool isSeparated() {
    initVisited();
    int validity = 1;
    // 모든 점에 대해
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // 빙산이 있다면
            if (map[i][j].height > 0 and visited[i][j] == false) {
                if (validity) {
                    // DFS로 발견한 빙산에 방문 표시
                    visited[i][j] = true;
                    DFS(i, j);
                    // 이미 하나의 빙산을 발견했다는 표시
                    validity = 0;
                }
                // 빙산을 하나 발견한 이후에 또 빙산을 발견한다면 두 덩어리 이상으로 분리되었다고 판단
                else
                    return true;
            }
        }
    }
    // 두 번째 빙산을 발견하지 못했다면 두 덩어리 이상으로 분리되지 않았다고 판단
    return false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int cnt = 0;
    // 입력 받고
    input();
    // 녹을 얼음이 없을 때까지 반복
    while (cntMelt < cntIce) {
        // 녹는 속도 계산
        int n = calSpeed();
        // 한 얼음이 전부 녹을 때까지 녹이기
        melt(n);
        // 해당 얼음이 녹을 때 까지 걸린 시간 누적
        cnt += n;
        // 두 덩어리 이상으로 분리되었다면 종료
        if (isSeparated()) {
            cout << cnt;
            return 0;
        }
    }
    // 모든 얼음이 녹을 때까지 두 덩어리로 분리되지 않았다면 0 출력
    cout << 0;
}