import java.io.BufferedInputStream;   
import java.util.Scanner;   
public class Main {   
  
    public static void main(String[] args) {   
        final int MAXSIZE = 10000;   
        int[] edge1 = new int[MAXSIZE];   
        int[] edge2 = new int[MAXSIZE];   
        Scanner scan = new Scanner(new BufferedInputStream(System.in));   
        String r1 = "is a tree.";   
        String r2 = "is not a tree.";   
        int caseI = 1;   
        int root = 0;
        while (scan.hasNext()) {   
            int a = scan.nextInt();   
            int b = scan.nextInt();   
            if (a == -1 && b == -1) {   
                break;   
            }   
            int j = 0;   
            for (j = 0;; j++) {   
                if (a == 0 && b == 0) {   
                    break;   
                }   
                edge1[j] = a;   
                edge2[j] = b;   
                a = scan.nextInt();   
                b = scan.nextInt();   
            }   
            if (j == 0) {   
                System.out.println("Case " + caseI + " " + r1);   
                caseI++;   
            } else {   
                String result = "";   
                boolean resultFlag = true;   
                DisjointSet dj = new DisjointSet(MAXSIZE);   
                for (int jj = 0; jj < j; jj++) {   
                    if (dj.parent[edge1[jj]] == 0) {   
                        dj.init(edge1[jj]);   
                    }   
                    if (dj.parent[edge2[jj]] == 0) {   
                        dj.init(edge2[jj]);   
                    }   
                    root = edge1[jj];   
                    int ra = dj.find(edge1[jj]);   
                    int rb = dj.find(edge2[jj]);   
                    if (ra == rb) {   
                        resultFlag = false;   
                        break; 
                    } else {   
                        dj.union(ra, rb);   
                    }   
                }   
                result = "Case " + caseI + " ";   
                if (resultFlag) {   
                    int k;   
                    for (k = 0; k < MAXSIZE; k++) {   
                        if (dj.parent[k] != 0) {   
                            if (dj.find(k) != dj.find(root)) {   
                                result += r2;   
                                break;   
                            }   
                        }   
                    }   
                    if (k == MAXSIZE) {   
                        result += r1;   
                    }   
                } else {   
                    result += r2;   
                }   
                System.out.println(result);   
                caseI++;   
            }   
  
        }   
    }   
}   
  
class DisjointSet {   
  
    protected int n;   
    protected int[] parent;   
    protected int[] rank;   
  
    public DisjointSet(int n) {   
        this.n = n;   
        init();   
    }   
  
    private void init() {   
        this.parent = new int[this.n + 1];   
        this.rank = new int[this.n + 1];   
    }   
  
    protected void init(int i) {   
        parent[i] = i;   
        rank[i] = 1;   
    }   
  
    protected int find(int x) { 
        if (parent[x] != x) {   
            parent[x] = find(parent[x]);   
        }   
        return parent[x];   
    }   
  
    protected void union(int ra, int rb) {   
        if (rank[ra] > rank[rb]) {   
            parent[rb] = ra;   
        } else if (rank[ra] < rank[rb]) {   
            parent[ra] = rb;   
        } else {   
            rank[rb]++;   
            parent[ra] = rb;   
        }   
    }   
}  
