// https://www.acmicpc.net/problem/21758

// 입출력 양이 많으므로 Scanner 보다는 BufferedReader 사용.
// Scanner 사용시 실행시간 940ms
// BufferedReader 사용시 실행시간 328ms으로 측정됨.
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Baekjoon_21758 {

	static int N;
	static int[] arr, acc;
	static int ans;
	static int min;

	public static void main(String[] args) throws IOException {
        // N값 받은 후 사용할 클래스, 변수 초기화
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());
		arr = new int[N];
		acc = new int[N];
		int sum = 0;
		int ans = 0;

        // 배열 정보 저장
        String[] input = (br.readLine()).split(" ");
		for (int i = 0; i < N; i++) {
			arr[i] = Integer.parseInt(input[i]);
			sum += arr[i];
			acc[i] = sum;
		}

        // 3 경우에 대해 계산하면서 최대값 tracking
        // 벌의 출발 위치가 두 군데 모두 벌통의 왼쪽에 있는 경우
		int tmp;
		tmp = left();
		if (tmp > ans) {
			ans = tmp;
		}

        // 벌의 출발 위치가 두 군데 모두 벌통의 오른쪽에 있는 경우
		tmp = right();
		if (tmp > ans) {
			ans = tmp;
		}

        // 벌의 출발 위치가 벌통을 사이에 두고 양쪽에 있는 경우
		for (int i = 1; i < N - 1; i++) {
			tmp = both(i);
			if (tmp > ans) {
				ans = tmp;
			}
		}

        // 스트림 닫아주고
        br.close();
        // 정답 출력
		System.out.println(ans);
	}

    // 벌이 모두 벌통의 왼쪽에서 출발하는 경우
    // 한 마리의 벌은 무조건 가장 왼쪽에, 벌통은 가장 오른쪽에 있어야 한다.(그래야 최대값 가능)
	public static int left() {
		int ret = acc[N - 1] - arr[0];
		int max = 0;
		for (int i = N - 2; i > 0; i--) {
			int tmp = ret - arr[i] + (acc[N - 1] - acc[i]);
			if (tmp > max) {
				max = tmp;
			}
		}
		return max;
	}

    // 벌이 모두 벌통의 오른쪽에서 출발하는 경우
    // 한 마리의 벌은 가장 오른쪽에, 벌통은 가장 왼쪽에 있어야 한다.
	public static int right() {
		int ret = acc[N - 2];
		int max = 0;
		for (int i = 1; i < N - 1; i++) {
			int tmp = ret - arr[i] + (acc[i-1]);
			if (tmp > max) {
				max = tmp;
			}
		}
		return max;
	}

    // 벌이 벌통을 사이에 두고 양쪽에서 출발하는 경우
    // 벌의 출발위치는 벌통위치와 무관하게 항상 양 끝이어야 최대값을 가질 수 있다.
    // 벌통의 위치만 옮겨가면서 계산
	public static int both(int hive) {
		return (acc[hive] - arr[0]) + (acc[N-2] - acc[hive-1]);
	}
}
