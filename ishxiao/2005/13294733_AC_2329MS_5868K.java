import java.util.*;
public class Main
{
 
 public static void main(String[] args){
   Scanner sc = new Scanner(System.in);
   int tot[]=new int[12],t[]=new int[4];
   char ts[]=new char[5];
    int sum,s1,s2,win,tem;
    while (sc.hasNext()) {
       int n=sc.nextInt();
       if(n==0) break;
        for (int i=2;i< 10;i++) tot[i]=4*n;
        tot[10]=16*n;tot[11]=4*n;
        sum=52*n-3;win=0;
        for (int i=1;i<=3;i++) {
            ts=sc.next().toCharArray();
            if (ts[0]=='T'||ts[0]=='J'||ts[0]=='Q'||ts[0]=='K') t[i]=10;
            else if (ts[0]=='A') t[i]=11;
            else t[i]=ts[0]-48;
            tot[t[i]]--;
        }
        s1=t[1];s2=t[2]+t[3];
        if (s2>21) s2-=10;
        for (int i=2;i<=11;i++) {
            tem=s1+i;if (tem>21) tem-=10;
            if (tem< s2) win+=tot[i];
        }
        System.out.printf("%.3f%%\n\n",100.0*win/sum);
    }
  }
}
