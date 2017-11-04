import java.util.*;

public class Main{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		int n;
		n = in.nextInt();
		Interval intervals[] = new Interval[n];
		for(int i = 0; i < n; i++){
			int x = in.nextInt();
			int y = in.nextInt();
			intervals[i] = new Interval(x, y);
		}
		Arrays.sort(intervals);
		//System.out.println(Arrays.toString(intervals));
		int st = intervals[0].s;
		int ed = intervals[0].e;
		for(int i = 0; i < n; i++){
			if(st >= intervals[i].s && st <= intervals[i].e){
				st = intervals[i].s;
			}
			if(ed >= intervals[i].s && ed <= intervals[i].e){
				ed = intervals[i].e;
			}
			else if(ed < intervals[i].s){
				System.out.println(st + " " + ed);
				st = intervals[i].s;
				ed = intervals[i].e;
			}
		}
		System.out.println(st + " " + ed);
	}
}

class Interval implements Comparable<Interval>{
	int s;
	int e;
	public Interval(int s, int e){
		this.s = s;
		this.e = e;
	}
	public int compareTo(Interval rhs){
		if(s == rhs.s){
			return e - rhs.e;
		}
		else{
			return s - rhs.s;
		}
	}
	public String toString(){
		return s + " " + e;
	}
}