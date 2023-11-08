import java.io.*;

public class Baekjoon_1946 {

    public static void main(String[] args) throws Exception {
        // 입출력 stream 설정
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        // 테스트 케이스 수 입력
        int test_case;
        test_case = Integer.parseInt(br.readLine());

        // 각 테스트 케이스에 대해
        for (int tc = 0; tc < test_case; tc++) {
            // 지원자 수
            int candidate_cnt = Integer.parseInt(br.readLine());

            // 지원자의 서류 순위를 인덱스로, 면접 순위를 값으로 가지는 배열
            int[] candidates = new int[candidate_cnt];

            // 지원자의 서류 순위와 면접 순위를 입력받아 배열에 저장
            for (int i = 0; i < candidate_cnt; i++) {
                String[] input = br.readLine().split(" ");
                int docu_rank = Integer.parseInt(input[0]) - 1;
                candidates[docu_rank] = Integer.parseInt(input[1]) - 1;
            }
            
            // 서류 1위 지원자는 반드시 합격하므로, 면접 순위 최소값을 1위 지원자의 면접 순위로 초기화
            int top_rank = candidates[0];
            int cnt = 1;

            // 서류 순위(앞서 정의된 배열의 인덱스)를 2위부터 순회하면서 면접 순위의 최소값(최고순위)를 tracking
            // tracking 하던 면접 순위 최소값보다 낮은 순위의 지원자가 나타나면 최고순위를 갱신하고 카운트
            for (int i = 1; i < candidate_cnt; i++) {
                if (candidates[i] < top_rank) {
                    cnt++;
                    top_rank = candidates[i];
                }
            }

            // 각 테스트 케이스에 대한 결과 출력
            bw.write(String.valueOf(cnt) + '\n');
        }
        // 입출력 stream close
        bw.flush();
        bw.close();
        br.close();
    }
}
