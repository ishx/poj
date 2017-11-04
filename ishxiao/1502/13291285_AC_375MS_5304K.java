import java.util.*;
public class Main {
 public static void main(String[] args) {
   Scanner cin = new Scanner(System.in);
   int n = cin.nextInt();
   int a[][] = new int[n][n];
   for (int i = 0; i < n; i++) {
    a[i][i] = 0;
    for (int j = 0; j < i; j++) {
	if (cin.hasNextInt()) {
	  a[i][j] = cin.nextInt();
	} else {
	   a[i][j] = Integer.MAX_VALUE / 200;
	   cin.next();
	}
	a[j][i] = a[i][j];
     }
   }
		
  for (int k = 0; k < n; k++) {
   for (int i = 0; i < n; i++) {
    for (int j =0; j < n; j++) {
     a[i][j] = a[i][j] < (a[i][k] + a[k][j]) ? a[i][j] : (a[i][k] + a[k][j]);
    }
   }
  }
		
  int max = a[0][1];
  for (int i = 2; i < n; i++) { 
    if (max < a[0][i]) max = a[0][i]; 
   }
  System.out.println(max);
 }
}
