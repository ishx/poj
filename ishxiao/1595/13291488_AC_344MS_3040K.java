import java.util.Scanner;
public class Main
{
  public static void main(String[] args)
  {
   int[] arr=new int[]{
	1,2,3,5,7,11,13,17,19,23,29,31,37,41,
	43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,
	109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,
	193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,
	277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,
	373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,
	461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,
	569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,
	653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,
	757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,
	859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,
	971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,
	1063,1069,1087,1091,1093,1097
    };
	Scanner in=new Scanner(System.in);
	while(in.hasNext())
	{
	 int a=in.nextInt();
	 int b=in.nextInt();
	 System.out.print(a+" "+b+":");
	 int max=184;
	 int min=0;
	 int mid=92;
	 while(min< max)
	  {
		mid=(max+min)/2;
		if(arr[mid]==a){
			min=mid+1;
			break;
		}
		if(arr[mid]>a)max=mid;
		else if(arr[mid]< a) min=mid+1;
	   }
	  if(min%2==1){
		mid=min/2-b+1;
		max=min/2+b-1;
		if(mid< 0) mid=0;
		if(max>min)max=min-1;
	   }
	   else{
		mid=min/2-b;
		max=min/2+b-1;
		if(mid< 0) mid=0;
		if(max>min) max=min-1;
	  }
	  for(int i=mid;i<=max;i++)
		System.out.print(" "+arr[i]);
	  System.out.println();
	  System.out.println();
	}
  }
}