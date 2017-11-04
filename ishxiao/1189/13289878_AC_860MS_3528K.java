import java.util.*;
public class Main {
static long gcd(long a,long b)//计算a,b的最大公约数
{
        if(b==0)
           return a;
        else
           return gcd(b,a%b);
}

public static void main(String[] args){
  Scanner sc = new Scanner(System.in);
    
    int m,n;
    long d,tmp;
        n=sc.nextInt();
        m=sc.nextInt();
       char ss[][]=new char[n][];
       long dp[][]=new long[n+1][];

        for(int i=0;i< n;i++){
           ss[i]=new char[i+1];
          for(int j=0;j< i+1;j++)  
           ss[i][j]=sc.next().charAt(0);
         
       }
        for(int i=0;i<=n;i++)
         dp[i]=new long[i+1];

        dp[0][0]=1l<< n;
        for(int i=1;i<=n;i++){
         for(int j=0;j< i;j++)
         {
            if(ss[i-1][j]=='*')
            {
                tmp=dp[i-1][j]>>1;
                dp[i][j]+=tmp;
                dp[i][j+1]+=tmp;
            }
            else                                                                        
                dp[i+1][j+1]+=dp[i-1][j];
         }
     
        }
        
         d=gcd(dp[n][m],dp[0][0]);
         System.out.printf("%d/%d\n",dp[n][m]/d,dp[0][0]/d);

            
   }
}