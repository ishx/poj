import java.util.*;

public class Main {

    static int n;
    static LinkedList< Integer>[] matrix;
    static int[] result;
    static boolean[] state;
    static int ans;
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Scanner sc = new Scanner(System.in);
        while(sc.hasNextInt()) {
            init(sc);
            for(int i = 0; i < n; i++) {
                Arrays.fill(state, false);
                if (find(i)) {
                    ans++;
                }
            }
            System.out.println(n-ans/2);
        }
    }

    private static boolean find(int i) {
        for(int t : matrix[i]) {
            if(!state[t]) {
                state[t] = true;
                if(result[t] == -1
                        || find(result[t])) {
                    result[t] = i;
                    return true;
                }
            }
        }
        return false;
    }

    private static void init(Scanner sc) {
        ans = 0;
        n = sc.nextInt();
        matrix = (LinkedList< Integer>[])new LinkedList[n];
        for(int i = 0; i < n; i++) {
            sc.next();//id, the same as i
            String str = sc.next();
            String numStr = str.substring(1, str.length()-1);
            int num = Integer.parseInt(numStr);
            matrix[i] = new LinkedList< Integer>();
            for (int j = 0; j < num; j++) {
                int id = sc.nextInt();
                matrix[i].add(id);
            }
        }
        state = new boolean[n];
        Arrays.fill(state, false);
        result = new int[n];
        Arrays.fill(result, -1);
    }
}
