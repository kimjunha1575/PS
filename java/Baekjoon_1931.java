import java.util.Arrays;
import java.util.Scanner;
public class Baekjoon_1931 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // 전체 회의 수
        int N = sc.nextInt();

        // 회의 정보를 저장할 배열
        int[][] meetings = new int[N][2];

        // 회의 정보 저장
        for (int i = 0; i < N; i++) {
            meetings[i][0] = sc.nextInt();
            meetings[i][1] = sc.nextInt();
        }

        // 회의가 끝나는 시간에 대해 오름차순으로 정렬
        Arrays.sort(meetings, (a, b) -> {
            if (a[1] == b[1]) return a[0] - b[0];
            else return a[1] - b[1];
        });

        // 가장 먼저 끝나는 회의는 반드시 포함되므로 해당 회의로 초기화
        int cnt = 1;
        int time = meetings[0][1];
        int meeting = 1;

        // 이후 회의에 대해 순회하면서
        // 현재 진행중인 회의가 끝난 뒤 시작할 수 있는 회의 중, 가장 먼저 끝나는 회의를 시작한다.
        while (meeting < N) {
            if (meetings[meeting][0] >= time) {
                cnt++;
                time = meetings[meeting][1];
            }
            meeting++;
        }
        
        // 진행된 회의 개수 출력
        System.out.println(cnt);
        sc.close();
    }
}
