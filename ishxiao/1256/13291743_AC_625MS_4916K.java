 import java.io.BufferedReader;
 import java.io.IOException;
 import java.io.InputStreamReader;
 import java.util.Arrays;
 import java.util.Comparator;

 public class Main {

     class Compara implements Comparator<Character> {
         public int compare(Character o1, Character o2) {
             char a = Character.toLowerCase(o1);
             char b = Character.toLowerCase(o2);
             if (a == b) {
                 return o1 - o2;
             } else {
                 return a - b;
             }
         }
     }

     public int compareTo(char o1, char o2) {
         char a = Character.toLowerCase(o1);
         char b = Character.toLowerCase(o2);
         if (a == b) {
             return o1 - o2;
         } else {
             return a - b;
         }
     }

     public Main() throws NumberFormatException, IOException {
         BufferedReader read = new BufferedReader(new InputStreamReader(
                 System.in));
         int t = Integer.parseInt(read.readLine());
         String s;
         char[] o;
         Character[] oc;
         StringBuilder buff;
         for (int i = 0; i < t; i++) {
             s = read.readLine();
             o = s.toCharArray();
             oc = new Character[o.length];
             for (int j = 0; j < o.length; j++) {
                 oc[j] = new Character(o[j]);
             }
             Arrays.sort(oc, new Compara());
             buff = new StringBuilder();
             for (int j = 0; j < o.length; j++) {
                 buff.append(oc[j]);
             }
             System.out.println(buff);
             findAll(buff.toString().toCharArray());
         }
     }

     public void findAll(char[] c) {
         int t;
         int t2;
         char t3;
         while (true) {
             t = -1;
             // 从右往左找第一个比它的左边大的数，设为t
             for (int i = c.length - 1; i > 0; i--) {
                 if (compareTo(c[i], c[i - 1]) > 0) {
                     t = i;
                     break;
                 }
             }
             if (t == -1) {
                 break;
             }
             // 在 t-1的右边找第一个比t-1大的数，设为t2
             for (int i = c.length - 1;; i--) {
                 if (compareTo(c[i], c[t - 1]) > 0) {
                     t2 = i;
                     break;
                 }
             }
             // t2和t-1交换
             t3 = c[t2];
             c[t2] = c[t - 1];
             c[t - 1] = t3;
             // 将t-1的右边反序
             for (int j = c.length - 1, i = t; i < j; i++, j--) {
                 t3 = c[j];
                 c[j] = c[i];
                 c[i] = t3;
             }
             System.out.println(c);
         }
     }

     public static void main(String[] args) throws NumberFormatException,
             IOException {
         new Main();
     }
}