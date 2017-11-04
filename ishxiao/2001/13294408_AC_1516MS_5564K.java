import java.util.*;

public class Main {
 static int MAX = 1010;
 static TrieNode root = new TrieNode();
 static char[][] result = new char[MAX][22];
 static char[][] s = new char[MAX][22];

 public static void main(String[] args) {
  Scanner cin = new Scanner(System.in);
  TrieNode my = new TrieNode();
  int n=0;
  char[] ss = new char[21];
  while(cin.hasNext()) {
    ss = cin.nextLine().toCharArray();
    s[n++] = ss;
    insert(ss);
  }

  int i;
  for(i=0;i< n;i++) {
   check(i);
   System.out.println(new String(s[i])+" "+ new String(result[i]).trim());
  }
 }

private static void insert(char[] str) {
 TrieNode p = root;
 int i,len = str.length;
 for(i=0;i< len;i++){
   if(p.num[str[i]-'a'] == null) {
   p.num[str[i]-'a'] = new TrieNode();
   p = p.num[str[i]-'a'];
  }else{
   p = p.num[str[i]-'a'];
  }
  p.value++;
 }
}

private static void check(int ind) {
 TrieNode p = root;
 int i;
 for(i=0;i< s[ind].length;i++) {
  if(p.value == 0) {
   return;
  }
  p = p.num[s[ind][i]-'a'];
  result[ind][i] = s[ind][i];
 }
}

}
class TrieNode {
 int value;
 TrieNode[] num = new TrieNode[26];
 public TrieNode() {
  value=-1;
  int i;
  for(i=0;i< 26;i++)
    num[i] = null;
  }
} 
