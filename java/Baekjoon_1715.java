import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.PriorityQueue;

// https://www.acmicpc.net/problem/1715

// 현재 있는 카드묶음들 중 가장 작은 두 묶음을 합쳐나갈 때 최소
// 우선순위 큐 이용
// 가장 작은 두 묶음을 큐에서 뽑아 둘을 합한 뒤
// 다시 큐에 넣는 방식으로 해결

public class Baekjoon_1715 {

    // 카드 묶음의 수
	static int N;

    // 카드 묶음의 개수들을 저장할 우선순위 큐
	static PriorityQueue<Integer> deck_sizes;

	public static void main(String[] args) throws IOException {
        // 초기화, 입력 받기
		init();

        // 계산된 값 출력
		System.out.println(solution());
	}

    // 최소값을 구하는 메소드
	public static int solution() {
		int ans = 0;

        // 카드 묶음이 1개가 될 때 까지 합친다
		while (deck_sizes.size() > 1) {
            // 가장 작은 두 뭉치를 합친 뒤
			int tmp = deck_sizes.poll() + deck_sizes.poll();
            
            // 비교 회수를 더하고
			ans += tmp;
            
            // 합친 카드뭉치를 다시 큐에 넣는다
			deck_sizes.add(tmp);
		}

        // 계산된 값 반환
		return ans;
	}

    // 초기화, 입력 받기
	public static void init() throws IOException {
		deck_sizes = new PriorityQueue<>();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		for (int i = 0; i < N; i++) {
			int deck = Integer.parseInt(br.readLine());
			deck_sizes.add(deck);
		}
		br.close();
	}
}
