import java.math.*;
import java.util.*;

public class Main
{
    public static BigInteger calc(BigInteger a,BigInteger b,BigInteger c)
    {
        BigInteger now = c;
        BigInteger last = b;
        BigInteger llast = a;
        BigInteger answer;
        for(int i=0;i<97;i++) {
            answer = now.add(last);
            answer = answer.add(llast);
            llast = last;
            last = now;
            now = answer;
        }
        return now;
    }

    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        while(in.hasNext()) {
            int a0 = in.nextInt();
            BigInteger A0 = BigInteger.valueOf(a0);
            int a1 = in.nextInt();
            BigInteger A1 = BigInteger.valueOf(a1);
            int a2 = in.nextInt();
            BigInteger A2 = BigInteger.valueOf(a2);
            System.out.println(calc(A0,A1,A2));
        }
    }
}


