//3892
/*题目说 q <= p and |q - kp| <= 10^5这个条件很重要，说明了p,q的距离很近在10^5之内

其实就是等价于k*p-q<=10^5 ---> k*p*q-q*q<=10^5*q，然后又有n=q*p ---->n*k=q*p*k

所以就是q^2>=n*k-10^5*q,所以就可以确定q和p是在sqrt(n*k)附近，于是向sqrt(n*k)两边暴力枚举...
*/
import java.io.*;
import java.util.*;
import java.math.*;
public class Main
{
 public static BigInteger sqrt(BigInteger a)
 {
  BigInteger l=BigInteger.ONE,r=a,mid;
  while(r.subtract(l).compareTo(BigInteger.ONE)>0)
  {
   mid = (l.add(r)).divide(BigInteger.valueOf(2));
   if((mid.multiply(mid)).compareTo(a)>0)
    r=mid;
   else if((mid.multiply(mid)).compareTo(a)==0)
    return mid;
   else
    l=mid;
  }
  return l;
 }
 public static void main(String[] args)
 {
  Scanner cin = new Scanner ( System.in );
  BigInteger n,p,k=BigInteger.ONE;
  while(cin.hasNext())
  {
   n = cin.nextBigInteger();
   p = cin.nextBigInteger();
   k = sqrt(n.multiply(p));
   //   System.out.println(k);
   BigInteger a,b;
   a=b=k;
   while(true)
   {
    if(n.mod(a).equals(BigInteger.ZERO) && !a.equals(n)&& !a.equals(BigInteger.ONE))
    {
     b = n.divide(a);
     break;
    }
    if(n.mod(b).equals(BigInteger.ZERO) && !b.equals(n)&& !b.equals(BigInteger.ONE))
    {
     a = n.divide(b);
     break;
    }
    a=a.subtract(BigInteger.ONE);
    b=b.add(BigInteger.ONE);
   }
   if(a.compareTo(b)>0)
   {
    k=a;
    a=b;
    b=k;
   }
   System.out.println(a+" * "+b);
  }

 }
}

