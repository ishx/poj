import java.util.*;
public class Main {
 
 public static void main(String[] args){

    Scanner sc = new Scanner(System.in);
    int in[]=new int[1001];   
    int out[]=new int[1001];   
    int stack[]=new int[1001];   

    int n;   
    int i,j;   
    for(i=0;i< 1001;i++)   
        in[i]=i+1;   
    while(sc.hasNext())   
    {   
         n=sc.nextInt();
         if(n==0) break;  
        while(true)   
        {   
            out[0]=sc.nextInt();
            if(out[0]==0)   
                break;   
            for(i=1;i< n;i++)   
                out[i]=sc.nextInt();   
            i=j=0;   
            int top=-1;   
            while(i< n)   
            {   
                top++;   
                stack[top]=in[i];   
                i++;   
                while(stack[top]==out[j])   
                {   
                    top--;   
                    j++;   
                    if(top==-1)break;   
                }   
            }   
            if(top==-1)   
                System.out.printf("Yes\n");   
            else  
                System.out.printf("No\n");   
        }   
        System.out.printf("\n");   
    }   
   }
} 
