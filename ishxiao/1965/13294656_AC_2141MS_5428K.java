import java.math.BigDecimal;
import java.util.Scanner;
public class Main {
 public static void main(String[] args) {		
 Scanner scan=new Scanner(System.in);
  BigDecimal k;
  BigDecimal root=new BigDecimal("1");		
  BigDecimal aux=new BigDecimal("0.0000000001");
  BigDecimal tr=new BigDecimal("3");
   String a;
   int ind=0,sum;
   while(scan.hasNext()){
    k=scan.nextBigDecimal();
    root=k.divide(new BigDecimal("2"));
    while(k.subtract(root.pow(3)).abs().compareTo(aux)>0)
     root=root.subtract(root.pow(3).subtract(k).divide(root.pow(2).multiply(tr),120,BigDecimal.ROUND_DOWN));
	a=root.toPlainString();
	ind=a.indexOf('.');
	a=a.substring(0,ind+11);
	sum=0;
	for(int j=0;j< a.length();j++) if(j!=ind)sum+=a.charAt(j)-48;
	System.out.println(sum%10+" "+a);
     }
  }
}
