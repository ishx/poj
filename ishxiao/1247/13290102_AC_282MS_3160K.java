import java.util.Scanner;
public class Main
{
 public static void main(String[] args)
 {
  Scanner in=new Scanner(System.in);
  while(true)
  {
   int a=in.nextInt();
    if(a==0)break;
    int[] arr=new int[a];
    int t=0;
    for(int i=0;i< a;i++)
    {
	arr[i]=in.nextInt();
	t+=arr[i];
     }
    if(t%2==1)System.out.println("No equal partitioning.");	
    else
    {
	t=t/2;
	for(int i=0;i< a;i++)
	{
	  t-=arr[i];
	  if(t==0){
	   System.out.println("Sam stops at position "+(i+1)+" and Ella stops at position "+(i+2)+".");
		break;
	   }
	  else if(t< 0)
	  {
	   System.out.println("No equal partitioning.");
		break;
	   }
	}
     }
    }
  }
}