#include <iostream>
#include <queue>
using namespace std;

// 빙산에 해당하는 각 칸의 주위에 바다(0)가 몇 칸인지 알아야 함
// 빙산이 두개로 쪼개졌는지 아직 하나의 빙산인지 구분할 수 있어야 함
// 배열의 크기는 최대 300 * 300 = 90000
// 빙산의 최대 높이는 10000
// 최악의 경우 10000 * 90000 수준의 반복회수
// 각 칸이 0과 닿고 있는 면의 개수를 알고 나면 굳이 1씩 넘어갈 필요 없음
// 가장 빨리 녹아 없어지는 칸을 찾고 > 바로 그 칸이 없어진 상황으로 넘어간다

// BFS 한번에 최소 1개의 칸이 녹아 없어지므로 최대 BFS 9만번?

#define MAX_HEIGHT 300
#define MAX_WIDTH  300

struct Ice {
    int height;
    int speed;
};

int dy[] = {0, 1, 0, -1};
int dx[] = {1, 0, -1, 0};

Ice map[MAX_HEIGHT][MAX_WIDTH];
bool visited[MAX_HEIGHT][MAX_WIDTH];
int height, width;
int ys, xs;  // BFS start point;
int cntIce;
int cntMelt = 0;

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
                cntIce++;
                ys = i;
                xs = j;
            }
        }
    }
}

void initVisited() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            visited[i][j] = false;
        }
    }
}

int calSpeed() {
    int res = 0x7FFFFFFF;
    initVisited();
    queue<pair<int, int>> que;
    que.push({ys, xs});
    visited[ys][xs] = true;

    while (not que.empty()) {
        int y = que.front().first;
        int x = que.front().second;
        que.pop();

        ys = y;
        xs = x;

        map[y][x].speed = 0;

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny < 0 || nx < 0 || ny >= height || nx >= width) continue;
            if (visited[ny][nx]) continue;
            if (map[ny][nx].height == 0) {
                map[y][x].speed++;
                continue;
            }

            visited[ny][nx] = true;
            que.push({ny, nx});
        }

        if (map[y][x].speed > 0) {
            int speed = map[y][x].speed;
            int height = map[y][x].height;
            int tmp = 0;
            while (height > 0) {
                height -= speed;
                tmp++;
            }
            // printf("(%d,%d): %d\n", y, x, speed);
            if (tmp < res) {
                res = tmp;
            }
        }
    }

    return res;
}

void melt(int n) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j].height > 0) {
                map[i][j].height -= n * map[i][j].speed;
                if (map[i][j].height <= 0) {
                    map[i][j].height = 0;
                    map[i][j].speed = 0;
                    cntMelt++;
                }
                else {
                    ys = i;
                    xs = j;
                }
            }
        }
    }
}

void prtMap() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d(%d) ", map[i][j].height, map[i][j].speed);
        }
        printf("\n");
    }
}

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

bool isSeparated() {
    initVisited();
    int validity = 1;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j].height > 0 and visited[i][j] == false) {
                if (validity) {
                    visited[i][j] = true;
                    DFS(i, j);
                    validity = 0;
                }
                else
                    return true;
            }
        }
    }
    return false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int cnt = 0;
    input();
    while (cntMelt < cntIce) {
        int n = calSpeed();
        melt(n);
        cnt += n;
        if (isSeparated()) {
            cout << cnt;
            return 0;
        }
    }
    cout << 0;
}