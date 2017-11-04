import java.io.BufferedInputStream;   
import java.util.LinkedList;   
import java.util.Scanner;   
  
/**  
 *  
 *poj1978  
 *简单模拟  
 * @author Xiao  
 */  
public class Main {   
  
    public static void main(String[] args) {   
        Scanner scan = new Scanner(new BufferedInputStream(System.in)); 

  
        while (scan.hasNext()) {   
            int m = scan.nextInt();   
            int n = scan.nextInt();   
            if (m == 0 && n == 0) {   
                break;   
            }   
            LinkedList<Integer> cards = new LinkedList<Integer>();   
            for (int i = 1; i <= m; i++) {   
                cards.addFirst(i);   
            }   
            for (int i = 0; i < n; i++) {   
                int p = scan.nextInt();   
                int c = scan.nextInt();   
                LinkedList<Integer> lk = new LinkedList<Integer>();   
                for (int j = 0; j < c; j++) {   
                    int a = cards.remove(p - 1);   
                    lk.addLast(a);   
                }   
                for (int j = 0; j < c; j++) {   
                    int a = lk.removeLast();   
                    cards.addFirst(a);   
                }   
            }   
            System.out.println(cards.getFirst());   
        }   
    }   
}  
