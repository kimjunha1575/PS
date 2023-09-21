#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/72412

/*
검색할 지원자의 조건이 최대 10만개 주어지므로,
10만번에 대해 조건을 모두 검색하면 시간복잡도에 의해 통과불가능.

따라서 조건에 따라 지원자들의 점수를 저장해두고
주어진 점수 이상의 지원자의 수는 이분탐색으로 계산하면
O(nlogn)의 시간복잡도로 해결할 수 있다.

조건을 나열한 문자열을 key, 조건에 맞는 지원자들의 점수를 저장한 vector를
key value pair로 가지는 unordered_map을 사용한다.

문자열 파싱은 스트링스트림 이용.
*/

// 지원자의 정보를 저장
unordered_map<string, vector<int>> db;
// db 변수에 key들을 모두 저장
set<string> keys;
// 문자열 파싱을 위한 스트링스트림
stringstream stream;
vector<int> answer;

void addParticipant(string);
int searchParticipant(string);

vector<int> solution(vector<string> info, vector<string> query) {
    // 변수 초기화
    answer.clear();
    db.clear();
    keys.clear();

    // 모든 지원자들의 정보를 db(해쉬맵 컨테이너 변수)에 저장
    for (string i : info)
        addParticipant(i);

    // 저장된 db의 모든 key에 대해 지원자들의 점수를 미리 정렬(이후 이분탐색을 위해)
    for (string key : keys)
        sort(db[key].begin(), db[key].end());

    // 모든 query에 대해 해당하는 지원자의 수를 answer 벡터에 푸쉬
    for (string q : query)
        answer.push_back(searchParticipant(q));

    // answer 벡터 반환
    return answer;
}

// query의 원소인 조건을 받아 만족되는 지원자의 수를 반환하는 함수
int searchParticipant(string str) {
    // 검색할 조건(언어, 직무, 경력, 소울푸드)
    string lang, major, career, food;
    // 원본 문자열에 포함된 "and"를 받아 처리하고, 이후 "-"를 할당하여 사용할 dummy 변수
    string dummy;
    // 검색할 지원자의 최소점수
    int score;

    // 문자열 파싱하여 key 생성
    // 검색할 조건에 해당하는 문자열들을 그대로 이어붙여서 만들었음
    // (언어, 직무, 경력, 소울푸드 순서)
    stream.str(str + "\n");
    stream >> lang >> dummy >> major >> dummy >> career >> dummy >> food >> score;
    string key = "";
    dummy = "-";
    if (lang != dummy) key += lang;
    if (major != dummy) key += major;
    if (career != dummy) key += career;
    if (food != dummy) key += food;

    // 해당하는 조건의 지원자가 한 명도 없으면, 0을 반환
    if (db.find(key) == db.end()) return 0;

    // 해당하는 조건의 지원자가 한 명 이상인 경우
    // 지원자들의 점수를 저장한 벡터를 이분탐색하여
    // 점수 조건을 만족하는 지원자가 몇 명인지 계산하여 반환
    // ** 이 때 벡터가 정렬되어 있어야 하지만, query 벡터의 모든 원소에 대해 한 번씩 정렬하면
    // 시간초과되므로, query에 대한 처리 전, 미리 정렬해두는 식으로 처리하였음
    vector<int> scores = db[key];
    int len = scores.size();

    int left = 0;
    int right = len - 1;

    // 모든 지원자가 조건에 만족하거나
    if (scores[left] >= score) return len;
    // 모든 지원자가 조건에 불만족한 경우는 따로 처리하였음
    if (scores[right] < score) return 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (scores[mid] < score)
            left = mid + 1;
        else
            right = mid - 1;
    }
    // 조건에 만족하는 지원자의 수를 반환
    return len - left;
}

// 지원자의 정보를 입력받아 데이터를 저장하는 함수
void addParticipant(string str) {
    // 지원자의 사용언어, 직무, 경력, 소울푸드
    string lang, major, career, food;
    // 지원자의 코딩테스트 점수
    int score;

    // 문자열 파싱
    stream.str(str + "\n");
    stream >> lang >> major >> career >> food >> score;

    for (int l = 0; l < 2; l++) {
        for (int m = 0; m < 2; m++) {
            for (int c = 0; c < 2; c++) {
                for (int f = 0; f < 2; f++) {
                    // 특정 조건은 고려하지 않는 경우도 있으므로,
                    // 각 4가지 조건에 대해
                    // 조건을 고려하는 경우와 고려하지 않는 경우 2가지로 나누어
                    // 총 2^4 가지의 key를 생성하여 db 변수에 저장
                    string key = "";
                    if (l) key += lang;
                    if (m) key += major;
                    if (c) key += career;
                    if (f) key += food;
                    db[key].push_back(score);
                    
                    // query에 대한 처리 전 정렬을 위해 db의 원소에 접근해야하므로
                    // key들을 미리 보관해둔다. 
                    keys.insert(key);
                }
            }
        }
    }
}
