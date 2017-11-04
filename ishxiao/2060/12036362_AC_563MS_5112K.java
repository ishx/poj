//2060
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main{
	static int n = 0;
	static final int MAX = 505;
	static Booked[] booked = new Booked[MAX];
	static boolean[][] graph = new boolean[MAX][MAX];
	static boolean[] visit = new boolean[MAX];
	static int[] link = new int[MAX];
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int Case = Integer.parseInt(br.readLine());
		while (Case-- != 0) {
			n = Integer.parseInt(br.readLine());
			for (int i = 1; i <= n; i++) {
				String[] ss = br.readLine().split(" ");
				int time = Integer.parseInt(ss[0].substring(0, 2)) * 60 + Integer.parseInt(ss[0].substring(3));
				booked[i] = new Booked(time, Integer.parseInt(ss[1]), Integer.parseInt(ss[2]), Integer.parseInt(ss[3]), Integer.parseInt(ss[4]));
			}
			init();
			System.out.println(n - hungray());
		}
	}
	static void init() {
		for (int i = 0; i < MAX; i++)
			Arrays.fill(graph[i], false);
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (booked[i].reachable(booked[j]))
					graph[i][j] = true;
			}
		}
	}
	static boolean find(int x) {
		for (int i = x + 1; i <= n; i++) {
			if (graph[x][i] && !visit[i]) {
				visit[i] = true;
				if (link[i] == -1 || find(link[i])) {
					link[i] = x;
					return true;
				}
			}
		}
		return false;
	}
	static int hungray() {
		int ans = 0;
		Arrays.fill(link, -1);
		for (int i = 1; i <= n; i++) {
			Arrays.fill(visit, false);
			if (find(i))
				ans++;
		}
		return ans;
	}
}
class Booked {
	int time, a, b, c, d;
	public Booked(int time, int a, int b, int c, int d) {
		this.time = time;
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
	}
	boolean reachable(Booked bo) {
		return this.time + Math.abs(this.a - this.c) + Math.abs(this.b - this.d) + Math.abs(bo.a - this.c) + Math.abs(bo.b - this.d) < bo.time;
	}
}
