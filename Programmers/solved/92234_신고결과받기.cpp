#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/92334

/*
한 유저가 다른 유저를 한 번만 신고할 수 있고 중복되는 신고는 무시되므로,
각 유저에 대해
1. 본인을 신고한 유저의 집합(set): reported
2. 본인이 신고한 유저의 집합(set): reports
두 가지를 저장하기 위한 unordered_map
정답을 반환하기 위한 정수형 벡터
report 정보를 파싱하기 위한 sstream
을 초기화하고

report 정보에 따라 unordered_map에 정보 저장
전부 저장 후 모든 유저에 대해
문제가 요구한 대로 해당 유저가 신고한 유저의 누적 신고건수가 k 이상일 경우,
해당 유저가 받을 신고처리결과 메일의 수를 늘려주고,
최종적으로 반환할 벡터에 push 해준다.
*/

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    // 각 유저 별로 해당 유저를 신고한 유저들을 저장할 해쉬맵
    map<string, set<string>> reported;
    // 각 유저 별로 해당 유저가 신고한 유저들을 저장할 해쉬맵
    map<string, set<string>> reports;
    // 문자열 파싱을 위한 스트링스트림
    stringstream stream;
    // 반환을 위한 정답 벡터
    vector<int> answer;

    for (string report_log : report) {
        stream.str(report_log + "\n");
        string from, to;
        stream >> from >> to;
        // report 정보를 파싱해서 유저별로 신고한, 신고당한 유저의 정보를 저장한다.
        reports[from].insert(to);
        reported[to].insert(from);
    }

    for (string user : id_list) {
        int tmp = 0;
        for (string reported_user : reports[user]) {
            // 유저에 대해 해당 유저가 신고한 유저의 누적 신고건수가 k 이상이면 메일 수를 늘린다.
            if (reported[reported_user].size() >= k) tmp++;
        }
        // 메일 수를 push 하고 다음 유저로 넘어간다.
        answer.push_back(tmp);
    }
    // 정답 벡터를 반환
    return answer;
}