import java.io.BufferedInputStream; 
import java.util.Scanner; 

/** 
*poj1218 
* @author NC 
*/ 
public class Main { 

    public static void main(String[] args) { 
        Scanner scan = new Scanner(new BufferedInputStream(System.in)); 
        if (scan.hasNext()) { 
            int t = scan.nextInt(); 
            for (int i = 0; i < t; i++) { 
                int n = scan.nextInt(); 
                boolean[] cells = new boolean[n + 1]; 
                for (int j = 1; j < cells.length; j++) { 
                    cells[j] = false; 
                } 
                for (int j = 2; j <= n; j++) { 
                    for (int k = j; k <= n; k = k + j) { 
                        if (cells[k]) { 
                            cells[k] = false; 
                        } else { 
                            cells[k] = true; 
                        } 
                    } 
                } 
                int count = 0; 
                for (int k = 1; k <= n; k++) { 
                    if (!cells[k]) { 
                        count++; 
                    } 
                } 
                System.out.println(count); 
            } 
        } 
    } 
} 
