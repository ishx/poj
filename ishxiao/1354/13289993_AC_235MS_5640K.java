import java.io.BufferedInputStream;   
import java.math.BigDecimal;   
import java.util.Scanner;   
public class Main {   
  
    public static void main(String[] args) {   
        Scanner scan = new Scanner(new BufferedInputStream(System.in));   
        while (scan.hasNext()) {   
            int n = scan.nextInt();   
            if (n == -1) {   
                break;   
            }   
            BigDecimal nn = new BigDecimal(n);   
            BigDecimal sum = BigDecimal.ONE;   
            for (BigDecimal i = BigDecimal.ONE; i.compareTo(nn) == -1; i = i.add(BigDecimal.ONE)) {   
                sum = sum.multiply(i);   
            }   
            System.out.println("N=" + n + ":");   
            System.out.println(sum.multiply(new BigDecimal(2)));   
        }   
    }   
}  
