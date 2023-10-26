import java.util.Comparator;
import java.util.Arrays;

// https://school.programmers.co.kr/learn/courses/30/lessons/181188

// 풀이 전략

// 미사일의 우측 끝단의 위치를 기준으로 오름차순 정렬한 뒤,
// 좌에서 우 방향으로 미사일을 검색하면서 미사일이 겹치는지 확인하면서
// 필요한 요격 미사일의 개수를 증가시킨다.

// 가장 좌측 미사일과 그 바로 오른쪽 미사일을 각각
// '기준 미사일'(left)과 '비교 미사일'(right)로 초기화.

// 1.   기준 미사일의 e값보다 비교 미사일의 s값이 작다면 (미사일이 겹친다면)
//      비교 미사일을 그 다음 미사일로 변경하고 다시 비교.

// 2.   미사일이 겹치지 않는다면
//      필요한 미사일의 개수를 1 증가시키고
//      겹치지 않게 된 미사일부터 새롭게 시작.

// 위 과정을 가장 우측 미사일까지 반복한 뒤, 필요한 미사일의 개수를 반환한다.

class Programmers_181188 {
    public int solution(int[][] targets) {
        int ans = 1;
        // 미사일이 1개라면 바로 1을 리턴
        if (targets.length == 1) {
            return ans;
        }

        // 미사일이 2개 이상이라면 끝나는 시간을 기준으로 정렬
        Arrays.sort(targets, new Comparator<int[]>() {
            @Override
            public int compare(int[] o1, int[] o2) {
                return o1[1] - o2[1];
            }
        });

        // 기준이 되는 미사일 (기준 미사일)
        int left = 0;
        // 비교할 미사일 (비교 미사일)
        int right = 1;

        // 모든 미사일에 대해 작업 수행
        while (right <= targets.length - 1) {
            // 기준 미사일의 e값보다 비교 미사일의 s값이 작다면 (미사일이 겹친다면)
            if (targets[right][0] < targets[left][1]) {
                // 비교 미사일을 그 다음 미사일로 변경
                right++;
                continue;
            }
            // 미사일이 겹치지 않는다면
            else {
                // 기준 미사일을 비교 미사일로 변경하고
                left = right;
                // 비교 미사일을 그 다음 미사일로 변경
                right++;
                // 필요한 요격 미사일 1개 증가
                ans++;
                continue;
            }
        }
        // 계산된 요격 미사일 개수 반환
        return ans;
    }
}