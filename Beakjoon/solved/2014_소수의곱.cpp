#include <iostream>
#include <vector>
using namespace std;

int K, N;
int prime_numbers[100];
int pointers[100];
int ans[100001];
vector<int> targets;

void input() {
    cin >> K >> N;
    for (int i = 0; i < K; i++) {
        cin >> prime_numbers[i];
    }
    ans[0] = 1;
}

int main(void) {
    input();
    int cnt = 1;
    while (cnt <= N) {
        targets.clear();
        long long min = 214847364700;
        for (int i = 0; i < K; i++) {
            long long tmp = prime_numbers[i] * ans[pointers[i]];
            if (tmp < min) {
                targets.clear();
                min = tmp;
                targets.push_back(i);
            }
            else if (tmp == min) {
                targets.push_back(i);
            }
        }
        ans[cnt] = min;
        // printf("ans[%d]: %d\n", cnt, min);
        if (cnt == N) {
            cout << min;
            return 0;
        }
        cnt++;
        for (int i = 0; i < targets.size(); i++) {
            pointers[targets[i]]++;
        }
    }
}