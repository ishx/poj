import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {

 public static void main(String[] args) throws Exception{
	BufferedReader in = new BufferedReader(new InputStreamReader (System.in));
	int total = Integer.parseInt(in.readLine());
	String string = in.readLine();
		System.out.println(total-LCS(string,new StringBuffer(string).reverse().toString()));
}

//返回两个string的lcs的长度
public static int LCS(String str1,String str2){
	short length1 = (short)str1.length();
	short length2 = (short)str2.length();
	short[][]result = new short [length1+1][length2+1];
	for(int i=0;i< length1;i++){
		result[i][0] = 0;
	}
	for(int i=0;i< length2;i++){
		result[0][i] = 0;
	}
	for(int i=1;i<=length1;i++){
      for(int j=1;j<=length2;j++){
		if(str1.charAt(i-1)==str2.charAt(j-1))
		 result[i][j] = (short)(result[i-1][j-1]+1);
		else
         result[i][j] = result[i-1][j]>result[i][j-1]?result[i-1][j]:result[i][j-1];
		}
	}
	return result[length1][length2];
 }
	

}
