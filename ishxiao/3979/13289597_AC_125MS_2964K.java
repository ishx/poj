import java.util.*;

public class Main {

    static Scanner in = new Scanner(System.in);

    public static void main(String[] args) {
        String str;
        int n1, n2, n3, d1, d2, d3, op, x, y, z;
        boolean neg = false;
        while (in.hasNext()) {
            neg = false;
            str = in.next();
            op = 1;
            n1 = str.charAt(0) - '0';
            d1 = str.charAt(2) - '0';
            if (str.charAt(3) == '-') {
                op = -1;
            }
            n2 = str.charAt(4) - '0';
            d2 = str.charAt(6) - '0';
            n3 = n1 * d2 + op * n2 * d1;
            d3 = d1 * d2;
            if (n3 == 0) {
                System.out.println("0");
                continue;
            }
            if (n3 < 0) {
                neg = true;
            }
            n3 = Math.abs(n3);
            d3 = Math.abs(d3);
            x = n3 > d3 ? n3 : d3;
            y = n3 < d3 ? n3 : d3;
            while (y > 0) {
                z = x % y;
                x = y;
                y = z;
            }
            n3 /= x;
            d3 /= x;

            if (neg) {
                System.out.print("-");
            }
            if (d3 == 1) {
                System.out.println(n3);
            } else {
                System.out.println(n3 + "/" + d3);
            }
        }
    }
}