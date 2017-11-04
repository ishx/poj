//1724
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;


class Node{
    int num;
    int dist;
    int cost;
}

class Edge{
    int t;
    int next;
    int spent;
    int len;
}

public class Main{
    Edge e[] = new Edge[10005];
    PriorityQueue<Node> q = new PriorityQueue<Node>(100,new Comparator<Node>(){
        @Override
        public int compare(Node o1, Node o2){
            if(o1.dist > o2.dist)return 1;
            if(o1.dist < o2.dist)return -1;
            return 0;
        }
    });

    int head[] = new int[105];
    int num = 1;
   
    void addEdge(int s, int t, int len, int money){
        if(e[num] == null)e[num] = new Edge();
        e[num].t = t;
        e[num].next = head[s];
        e[num].spent = money;
        e[num].len = len;
        head[s] = num++;
    }
   
    void solve() throws IOException{
        BufferedReader cin = new BufferedReader(new InputStreamReader(System.in));
        //BufferedReader cin = new BufferedReader(new FileReader(new File("in")));
        int i, k, n, r, u, tmp = -1;
        Node p, newP;
        String read;
        k = Integer.parseInt(cin.readLine());
        n = Integer.parseInt(cin.readLine());
        r = Integer.parseInt(cin.readLine());
        Arrays.fill(head, 0);
        for(i=0;i<r;i++){
            read = cin.readLine();
            int s = Integer.parseInt(read.split(" ")[0]);
            int d = Integer.parseInt(read.split(" ")[1]);
            int l = Integer.parseInt(read.split(" ")[2]);
            int t = Integer.parseInt(read.split(" ")[3]);
            addEdge(s, d, l, t);
        }
        p = new Node();
        p.num = 1;
        p.dist = p.cost = 0;
        q.offer(p);
        while(q.size()!=0){
            p = q.poll();
            if(p.num == n){
                tmp = p.dist;
                break;
            }
            for(u = head[p.num];u!=0;u = e[u].next){
                if(p.cost+e[u].spent <= k){
                    newP = new Node();
                    newP.num = e[u].t;
                    newP.dist = p.dist+e[u].len;
                    newP.cost = p.cost+e[u].spent;
                    q.offer(newP);
                }
            }
        }
        System.out.println(tmp);
    }
   
    public static void main(String[] args) throws IOException {
        Main test = new Main();
        test.solve();
    }
}