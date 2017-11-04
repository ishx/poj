//3130
import java.util.Scanner;  
  
public class Main {  
  
    static double x[], y[];  
    static double tx[], ty[];  
    static double txp[], typ[];  
    static int num;  
    static int tnum;  
    static double a, b, c;  
  
    public static void main(String[] args) {  
  
        Scanner scan = new Scanner(System.in);  
  
        while (true) {  
  
            int n = scan.nextInt();  
            if (n == 0)  
                break;  
            num = n;  
  
            x = new double[100];  
            y = new double[100];  
            tx = new double[100];  
            ty = new double[100];  
            txp = new double[100];  
            typ = new double[100];  
  
            for (int i = 0; i < n; i++) {  
                x[i] = scan.nextDouble();  
                y[i] = scan.nextDouble();  
                tx[i + 1] = x[i];  
                ty[i + 1] = y[i];  
            }  
  
            x[n] = x[0];  
            y[n] = y[0];  
            tx[0] = tx[n];  
            ty[0] = ty[n];  
            tx[n + 1] = tx[1];  
            ty[n + 1] = ty[1];  
  
            for (int i = 0; i < n; i++) {  
                a = y[i + 1] - y[i];      // 求直线  aX+bY+c=0  的参数a,b,c   
                b = x[i] - x[i + 1];  
                c = x[i + 1] * y[i] - x[i] * y[i + 1];  
                solve();  
            }  
  
            if (num == 0)  
                System.out.println("0");  
            else  
                System.out.println("1");  
  
        }  
  
    }  
  
    public static void solve() {  
  
        tnum = 0;  
  
        for (int i = 1; i <= num; i++) {  
  
            if (sig(a * tx[i] + b * ty[i] + c) <= 0) {  // 在一侧   
                txp[tnum] = tx[i];  
                typ[tnum++] = ty[i];  
            } else {                                    // 在另一侧   
                if (sig(a * tx[i - 1] + b * ty[i - 1] + c) < 0)  //小于0才会有交点   
                    insert(tx[i - 1], ty[i - 1], tx[i], ty[i]);  
                if (sig(a * tx[i + 1] + b * ty[i + 1] + c )< 0)  
                    insert(tx[i + 1], ty[i + 1], tx[i], ty[i]);  
            }  
        }  
  
        num = tnum;                       //更新  num,tx,ty   
  
        for (int j = 1; j <= num; j++) {  
            tx[j] = txp[j - 1];  
            ty[j] = typ[j - 1];  
        }  
        tx[0] = tx[num];  
        ty[0] = ty[num];  
        tx[num + 1] = tx[1];  
        ty[num + 1] = ty[1];  
  
    }  
  
    private static int sig(double d) {  
        if(d<1e-10)  
            return -1;  
        else if(d>1e-10)  
            return 1;  
        return 0;  
    }  
  
    public static void insert(double x1, double y1, double x2, double y2) {  //求两直线交点  其中一条直线  已经表示成ax+by+c=0,  另一直线 是两个点   
  
        double xx = Math.abs(a * x1 + b * y1 + c);  
        double yy = Math.abs(a * x2 + b * y2 + c);  
        txp[tnum] = (x1 * yy + x2 * xx) / (xx + yy);  
        typ[tnum++] = (y1 * yy + y2 * xx) / (xx + yy);  
  
    }  
  
}  
