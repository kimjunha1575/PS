import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.Math;
import java.util.Arrays;
import java.util.PriorityQueue;

// https://www.acmicpc.net/problem/1504

// 시작점에서부터 v1, v2까지,
// 도착점에서부터 v1, v2까지,
// 그리고 v1, v2 사이의 거리를
// 각각 총 5번의 dijkstra로 구한 뒤
// 최소경로가 되는 조합을 찾는다

public class Baekjoon_1504 {

	// 그래프 정보를 저장할 2차배열
	private static int[][] map;

	// 정점과 간선의 수
	private static int vertices;
	private static int edges;

	// 반드시 지나야 하는 두 정점
	private static int v1, v2;

	// 정답
	private static int ans;

	public static void main(String[] args) throws IOException {
		// 초기화, 입력 받력
		init();

		// 5번의  dijkstra
		int v1_v2 = dijkstra(v1, v2);
		int st_v1 = dijkstra(1, v1);
		int st_v2 = dijkstra(1, v2);
		int en_v1 = dijkstra(vertices, v1);
		int en_v2 = dijkstra(vertices, v2);

		// 이동 가능한 경로가 없는 경우, 정답은 -1
		if ((st_v1 == -1 && st_v2 == -1) || (en_v1 == -1 && en_v2 == -1) || (v1_v2 == -1)) {
			ans = -1;
		}
		// 이동 가능한 경우, 최단경로를 선택
		else ans = Math.min(st_v1 + v1_v2 + en_v2, st_v2 + v1_v2 + en_v1);

		// 정답 출력
		System.out.println(ans);
	}

	// dijkstra (가장 일반적인 형태)
	public static int dijkstra(int st, int en) {
		// 순회 초기값 설정
		int[] dist = new int[vertices + 1];
		Arrays.fill(dist, Integer.MAX_VALUE);
		PriorityQueue<Edge> pq = new PriorityQueue<>();
		Edge init_edge = new Edge(st, st, 0);
		pq.add(init_edge);
		dist[st] = 0;

		// 순회 시작
		while (!pq.isEmpty()) {
			Edge cur = pq.poll();
			int now = cur.to;
			int d = cur.dist;

			// 도착하면 거리 반환
			if (now == en) return d;
			if (dist[en] < d) continue;

			for (int next = 1; next <= vertices; next++) {
				if (next == now || map[now][next] == -1) continue;
				int nd = d + map[now][next];
				if (dist[next] < nd) continue;

				Edge next_edge = new Edge(now, next, nd);
				dist[next] = nd;
				pq.add(next_edge);
			}
		}

		// 이동 가능한 경로가 없다면 -1 반환
		return -1;
	}

	// dijkstra를 위해 간선 정보를 저장할 클래스(구조체)
	static class Edge implements Comparable<Edge> {

		public int from;
		public int to;
		public int dist;

		public Edge(int from, int to, int dist) {
			this.from = from;
			this.to = to;
			this.dist = dist;
		}

		// 우선순위 큐에 저장하기 위해 Comparable 인터페이스 구현
		public int compareTo(Edge e) {
			return this.dist - e.dist;
		}
	}

	// 배열 초기화, 입력 받기
	public static void init() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String[] input = br.readLine().split(" ");
		vertices = Integer.parseInt(input[0]);
		edges = Integer.parseInt(input[1]);

		map = new int[vertices + 1][vertices + 1];
		for (int[] arr : map) Arrays.fill(arr, -1);

		for (int i = 0; i < edges; i++) {
			int from, to, d;
			input = br.readLine().split(" ");
			from = Integer.parseInt(input[0]);
			to = Integer.parseInt(input[1]);
			d = Integer.parseInt(input[2]);
			map[from][to] = d;
			map[to][from] = d;
		}

		input = br.readLine().split(" ");
		v1 = Integer.parseInt(input[0]);
		v2 = Integer.parseInt(input[1]);

		br.close();
	}
}
