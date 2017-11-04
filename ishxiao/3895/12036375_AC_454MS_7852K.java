//3895
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.List;
public class Main {
	private int n;//顶点个数
        private boolean[] used;//节点状态,值为false的是未访问的   
	private List< ArrayList< Integer>> G;//邻接表
	private int maxlen=0;
        private int[] num;
  

        public Main(int n,List< ArrayList< Integer>> G){
             this.n=n;
             this.G=G;
             used=new boolean[n+1];  
             num=new int[n+1];
          
            // Arrays.fill(visited,false);   

        }


private void dfs(int v, int t)  {  
   
    num[v] = t;  
    used[v] = true;  
    int x = G.get(v).size();  
    for(int i = 0; i < x; i++){  
        if(!used[G.get(v).get(i)]){  
            dfs(G.get(v).get(i), t + 1);  
        }  
        else  
        {  
            if(maxlen < num[v] - num[G.get(v).get(i)] + 1)  
            maxlen = num[v] - num[G.get(v).get(i)] + 1;  
        }  
    }  
  }  
   public void go(){
      for(int i = 1; i <= n; i++){  
            if(!used[i])  
            dfs(i, 1);  
        }  
        if(maxlen > 2) System.out.printf("%d\n", maxlen);  
        else System.out.println("0");  
  }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t=sc.nextInt();
        while(t-->0){
            int n=sc.nextInt();
            int m=sc.nextInt();
             
            List< ArrayList< Integer>> G;
            G = new ArrayList< ArrayList< Integer>>();//初始化邻接表
            for(int i = 1;i<=n+1;i++)
                  G.add(new ArrayList< Integer>());
            for(int i=0;i<m;i++){
              int u = sc.nextInt();
              int v = sc.nextInt();
              G.get(u).add(v);
              G.get(v).add(u);      
             }
              
            Main ma=new Main(n,G);
             ma.go();
          
        }
   }
}