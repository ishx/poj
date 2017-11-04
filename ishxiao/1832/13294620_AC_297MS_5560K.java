import java.math.*;
import java.util.*;

public class Main {
    static BigInteger[] base = new BigInteger[128];
    static void init(){
        base[0] = BigInteger.ONE;
        for (int i=1; i< 128; i++){
            base[i] = base[i-1].multiply(BigInteger.valueOf(2));
        }
    }
    public static void main(String args[]){
        init();
        Scanner cin = new Scanner(System.in);
        int m,n = cin.nextInt();
        int[] a = new int[128];
        int[] b = new int[128];
        while ((n--)!=0){
            m = cin.nextInt();
            for (int i=0; i< m; i++){
                a[i] = cin.nextInt();
                if (i!=0){
                    a[i] = a[i]^a[i-1];
                }
            }
            for (int i=0; i< m; i++){
                b[i] = cin.nextInt();
                if (i!=0){
                    b[i] = b[i]^b[i-1];
                }
            }
            BigInteger start = BigInteger.ZERO;
            BigInteger end = BigInteger.ZERO;
            for (int i=0; i< m; i++){
                if (a[m-i-1]!=0) start = start.add(base[i]);
                if (b[m-i-1]!=0) end = end.add(base[i]);
            }
            System.out.println(end.max(start).subtract(end.min(start)));
        }
    }
}
