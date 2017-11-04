import java.io.BufferedInputStream;   
import java.util.Arrays;   
import java.util.Scanner;   
 
public class Main {   
  
    static int x[];   
    static int y[];   
  
    public static void main(String[] args) {   
        Scanner scan = new Scanner(new BufferedInputStream(System.in));   
        if (scan.hasNext()) {   
            int n = scan.nextInt();   
            x = new int[n];   
            y = new int[n];   
            for (int i = 0; i < n; i++) {   
                x[i] = scan.nextInt();   
                y[i] = scan.nextInt();   
            }   
            Arrays.sort(x);   
            Arrays.sort(y);   
            for (int i = 0; i < n; i++) {   
                x[i] -= i;   
            }   
            Arrays.sort(x);   
            int midX = x[(n + 1) / 2 - 1];   
            int midY = y[(n + 1) / 2 - 1];   
            int num = 0;   
            for (int i = 0; i < n; i++) {   
                num += Math.abs(x[i] - midX) + Math.abs(y[i] - midY);   
            }   
            System.out.println(num);   
  
        }   
    }   
}