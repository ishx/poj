import java.io.*;
import java.util.Arrays;
import java.util.Comparator;
public class Main
{
 static my[] s=new my[10001];
 public static void main(String[] args) throws IOException
 {
  InputStreamReader is=new InputStreamReader(System.in);
  BufferedReader in=new BufferedReader(is);
  int l=0,max=-1,rr=-1;
  while(in.ready())
  {
	String t=in.readLine();
	s[l++]=new my(t);
  }
  Comparator< my> cp=new Comparator< my>()
  {
	public int compare(my o1, my o2) {
		return o1.l-o2.l;
	}
   };
   Arrays.sort(s,0,l,cp);
   for(int i=0;i< l;i++)
   {
	for(int j=0;j< i;j++)
	{
	 if(s[j].l==s[i].l) break;
	 if(s[j].l!=s[i].l-1) continue;
		int cnt=0,k=0;
		while(k< s[j].l&&cnt< 2)
		{
	          if(s[j].c[k]!=s[i].c[k+cnt]) cnt++;
		  else k++;
		}
		if(cnt< 2)
		{
		  if(s[i].n< s[j].n+1){
			s[i].n=s[j].n+1;
			s[i].r=j;
		  }		
		}	
	}
    }
	
   for(int i=0;i< l;i++)
   {
	if(s[i].n>max)
	{
		max=s[i].n;
		rr=i;
	}
   }
   p(rr);
 }

  static void p(int a)
  {
    if(s[a].r!=-1)
	p(s[a].r);
    System.out.println(s[a].s);
  }
}
class my
{
	String s;
	int n=0;
	int l;
	int r=-1;
	char[] c;
	public my(String t)
	{
		s=t;
		l=s.length();
		c=new char[l];
		for(int i=0;i< l;i++)
			c[i]=s.charAt(i);
		Arrays.sort(c);
	}
}