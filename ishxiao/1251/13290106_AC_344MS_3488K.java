import java.util.Scanner;
public class Main {
 
  static int MAXCOST=Integer.MAX_VALUE;
 
 static int Prim(int graph[][], int n){
   /* lowcost[i]记录以i为终点的边的最小权值，当lowcost[i]=0时表示终点i加入生成树 */
   int lowcost[]=new int[n+1];
 
   /* mst[i]记录对应lowcost[i]的起点，当mst[i]=0时表示起点i加入生成树 */
   int mst[]=new int[n+1];
 
   int min, minid, sum = 0;
 
   /* 默认选择1号节点加入生成树，从2号节点开始初始化 */
    for (int i = 2; i <= n; i++){
	/* 最短距离初始化为其他节点到1号节点的距离 */
	lowcost[i] = graph[1][i];
 
	/* 标记所有节点的起点皆为默认的1号节点 */
	mst[i] = 1;
     }
 
    /* 标记1号节点加入生成树 */
    mst[1] = 0;
 
    /* n个节点至少需要n-1条边构成最小生成树 */
    for (int i = 2; i <= n; i++){
	min = MAXCOST;
	minid = 0;
 
       /* 找满足条件的最小权值边的节点minid */
       for (int j = 2; j <= n; j++){
	  /* 边权值较小且不在生成树中 */
	  if (lowcost[j] < min && lowcost[j] != 0){
	     min = lowcost[j];
	     minid = j;
	  }
       }
     
       /* 输出生成树边的信息:起点，终点，权值 */
	//System.out.printf("%c - %c : %d\n", mst[minid] + 'A' - 1, minid + 'A' - 1, min);
 
       /* 累加权值 */
       sum += min;
 
       /* 标记节点minid加入生成树 */
       lowcost[minid] = 0;
 
       /* 更新当前节点minid到其他节点的权值 */
       for (int j = 2; j <= n; j++){
         /* 发现更小的权值 */
	  if (graph[minid][j] < lowcost[j]){
	      /* 更新权值信息 */
	      lowcost[j] = graph[minid][j];
 
	      /* 更新最小权值边的起点 */
	      mst[j] = minid;
	   }
       }
     }
     /* 返回最小权值和 */
	return sum;
   }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (sc.hasNext()) {   
       int n = sc.nextInt();   
       if (n == 0) {   
          break;   
        }   
       int graph[][]=new int[n+1][n+1];

      /* 初始化图，所有节点间距离为无穷大 */
       for (int i = 1; i <= n; i++){
	  for (int j = 1; j <= n; j++){
		graph[i][j] = MAXCOST;
	   }
       }
               
        for (int i = 1; i <=n-1; i++) {   
          char  chx = sc.next().charAt(0);
          int x = chx - 'A' + 1;
          int m = sc.nextInt();   
          int j = 0;   
          while (j < m) {   
              char chy= sc.next().charAt(0);  
              int y = chy - 'A' + 1;
              int cost = sc.nextInt();   
              graph[x][y] = cost;
	       graph[y][x] = cost;
              j++;   
          }   
        }   

        System.out.println(Prim(graph, n));
      }
   }
}
