import java.io.*;
import java.util.*;
import java.math.*;

public class Main{
	public static void main(String args[])
		throws Exception{
		Scanner cin=new Scanner(System.in);
		BigDecimal a;
		int b;
		StringBuffer cout;
		while(cin.hasNext()){
		a = cin.nextBigDecimal();
		b=cin.nextInt();
		cout = new StringBuffer(a.pow(b).toPlainString());
		if('0' == cout.charAt(0)){
			cout.deleteCharAt(0);//Leading zeros should be suppressed 
		}
		while('0' == cout.charAt(cout.length()-1))
		{
			cout.deleteCharAt(cout.length()-1);//Insignificant trailing zeros must not be printed
		}
		if('.' == cout.charAt(cout.length()-1)){
			cout.deleteCharAt(cout.length()-1);//Don't print the decimal point if the result is an integer
		}
		System.out.println(cout);
		}
	}
}