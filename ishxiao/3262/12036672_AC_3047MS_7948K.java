//3262
/*

有N头牛，每头牛有两个参数T和D。把第i头牛送到目的地要2*Ti的时间，在这期间其他牛会吃掉2*Ti*Di的花，问如何排放牛的顺序使得被吃到的花最少.
这是POJ上一道简单的贪心， 策略很简单，就是按每分钟吃掉的花从大到小排序，大的先运走。。。
*/


import java.util.*; 

class Cow implements Comparable{ 
    private long t;
    private long d;
   
     
    public long getT(){
     return this.t;
    }

    public long getD(){
      return this.d;
    }
    public Cow(long t,long d){ 
        this.t=t;
        this.d=d; 
       
    } 
     
    public int compareTo(Object o){ 
        Cow b = (Cow)o;
         double diff=1.0 * this.d / this.t - 1.0 * b.d / b.t;
        if (diff > 0) 
                return -1; 
            else if (diff == 0) 
                return 0; 
            else 
                return 1; 
         

    } 
     public String toString(){
       return ("("+t+"  "+d+")");
     }
   } 

public class Main{
   

   public static void main(String args[]){
    long ans=0,sum=0;
    
    Scanner in=new Scanner(System.in);
    int n=in.nextInt();
    Cow cow[]=new Cow[n];
    for(int i=0;i<n;i++){
      cow[i]=new Cow(in.nextLong(),in.nextLong());
        }
    Arrays.sort(cow);
    sum = 2 * cow[ 0 ].getT();
    ans = 0;
    for(int  i = 1; i < n; i ++ )
    {
        ans = ans + sum * cow[ i ].getD();
        sum = sum + cow[ i ].getT() * 2;
    }
    System.out.println(ans);
 }
}