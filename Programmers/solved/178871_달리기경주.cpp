#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/178871

/*
풀이전략
선수가 최대 50000명, 추월이 일어나는 회수가 최대 1000000번이므로,
추월이 일어날 때 마다 해당 선수가 몇 위인지 찾아서 순위를 갱신하는 방식으로는
시간내로 문제를 해결할 수 없다.
이름을 불린 선수의 순위, 그리고 해당 선수의 바로 앞 순위의 선수를
O(1)로 찾을 수 있는 unordered_map을 이용하여 찾는다.
*/

vector<string> solution(vector<string> players, vector<string> callings) {
    // 선수 이름을 key, 순위를 value로 가지는 unordered_map(hashmap) 초기화
    unordered_map<string, int> get_rank;
    // map에 순위정보 저장
    for (int i = 0; i < players.size(); i++) {
        get_rank.insert({players[i], i});
    }
    // 해설진이 선수를 부를 때 마다 순위정보 갱신
    for (int i = 0; i < callings.size(); i++) {
        string callee = callings[i];
        int rank = get_rank[callee];

        get_rank[callee]--;
        get_rank[players[rank-1]]++;
        
        swap(players[rank], players[rank-1]);
    }
    // 갱신된 players 배열 반환
    return players;
}