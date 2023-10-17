#include <iostream>
using namespace std;

// https://www.acmicpc.net/problem/2977

// 부품 구조체
struct Component
{
    int demand, stock, sm, pm, sv, pv;
};

// 부품의 종류
int N;
// 효진이가 가진 돈
int M;
// 부품 정보를 저장할 배열
Component components[100];

void input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> components[i].demand;
        cin >> components[i].stock;
        cin >> components[i].sm;
        cin >> components[i].pm;
        cin >> components[i].sv;
        cin >> components[i].pv;
    }
}

// i번째 부품을 폭탄 n개치만큼 구매하는 데 필요한 최소금액을 반환
int calc(int n, int i) {
    int demand = n * components[i].demand - components[i].stock;
    if (demand <= 0) return 0;

    int sm = components[i].sm;
    int pm = components[i].pm;
    int sv = components[i].sv;
    int pv = components[i].pv;

    int mini_max = demand / sm;
    if (demand % sm) mini_max++;

    int min = 0x7FFFFFFF;
    for (int i = 0; i <= mini_max; i++) {
        int left = demand - i * sm;
        int vol = 0;
        if (left > 0) {
            vol = left / sv;
            if (left % sv) vol++;
        }
        int tmp = i * pm + vol * pv;
        if (tmp < min) min = tmp;
    }
    return min;
}

// n개의 부품을 만들 수 있는지?
bool isValid(int n) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        // i번째 부품을 폭탄 n개치만큼 만드는 데 드는 금액 누적
        cost += calc(n, i);
        // 누적 금액이 효진이가 가진 돈을 넘어가면 false 반환
        if (cost > M) return false;
    }
    // 가능하면 true 반환
    return true;
}

// 최대 몇 개의 부품을 만들 수 있는 지 이분탐색
int bs() {
    int left = 0;
    int right = 110000;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (isValid(mid))
            left = mid + 1;
        else
            right = mid - 1;
    }

    if (right < 0) return left;
    return right;
}

int main(void) {
    input();
    int ans = bs();
    cout << ans;
}
