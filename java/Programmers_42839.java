import java.lang.Math;
import java.util.Arrays;
import java.util.HashSet;

// https://school.programmers.co.kr/learn/courses/30/lessons/42839

public class Programmers_42839 {

	static boolean[] visited;
	static int[] nums;
	static HashSet<Integer> primes;

	public int solution(String numbers) {
		nums = new int[numbers.length()];
		visited = new boolean[numbers.length()];
		primes = new HashSet<>();
		Arrays.fill(visited, false);
		for (int i = 0; i < numbers.length(); i++) {
			nums[i] = Integer.parseInt(String.valueOf(numbers.charAt(i)));
		}
		for (int i = 1; i <= numbers.length(); i++) {
			permutation(i, 0, 0);
		}
		return primes.size();
	}

	// 숫자 카드로 만들 수 있는 모든 숫자에 대해 소수판별 후 소수이면 primes에 추가
	// primes가 HashSet이므로, 중복된 숫자는 포함되지 않는다.
	public static void permutation(int depth, int cur, int cur_length) {
		if (cur_length == depth) {
			if (isPrime(cur)) {
				primes.add(cur);
			}
		} else {
			for (int i = 0; i < nums.length; i++) {
				if (visited[i] == false) {
					visited[i] = true;
					cur_length++;
					int next = cur * 10 + nums[i];
					permutation(depth, next, cur_length);
					visited[i] = false;
					cur_length--;
				}
			}
		}
	}

	// 소수 판별
	public static boolean isPrime(int n) {
		if (n <= 1) return false;
		if (n == 2) return true;
		for (int i = 2; i <= Math.sqrt(n); i++) {
			if (n % i == 0) return false;
		}
		return true;
	}
}
