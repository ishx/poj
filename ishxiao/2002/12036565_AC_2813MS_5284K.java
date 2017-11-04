//2002
import java.util.Scanner;
import java.util.HashSet;

public class Main{
  private int n;
  private Point p[];
  private HashSet<Point> pset=new HashSet<Point>(); 
  private int sum;
  public Main(int n,Point p[]){
     this.n=n;
     this.p=p;
     for(int i=0;i<p.length;i++)
        pset.add(p[i]);
  }

  public int getSum(){
    return sum;
  }

  public void doIt(){
   
     int bound;
     int a1, a2, b1, b2, ab1, ab2, x1, y1, x2, y2, x3, y3, x4, y4;
     for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++) {
             a1 = p[i].getX();
             a2 = p[i].getY();
             b1 = p[j].getX();
             b2 = p[j].getY();
             ab1 = a1 - b1;
             ab2 = a2 - b2;
             x1 = a1 + ab2;
             y1 = a2 - ab1;
             x2 = b1 + ab2;
             y2 = b2 - ab1;

             if (pset.contains(new Point(x1, y1)) && pset.contains(new Point(x2, y2))) sum++;
             x3 = a1 - ab2;
             y3 = a2 + ab1;
             x4 = b1 - ab2;
             y4 = b2 + ab1;

             if (pset.contains(new Point(x3, y3)) && pset.contains(new Point(x4, y4))) sum++;         
           }
      }

  }

  public static void main(String args[]){
     Scanner in=new Scanner(System.in);
     int x=0;
     int y=0;
           
      while(true){
         int  n=in.nextInt();
        if(n==0) break;
           Point p[]=new Point[n];
          for(int i=0;i<n;i++){
             x=in.nextInt();
            
             y=in.nextInt();

            p[i]=new Point(x,y);
            //System.out.println(p[i]);
             
           }
     
        Main m=new Main(n,p);
        m.doIt();
        System.out.println(m.getSum()/4);
       
     }  
  }
       
}

class Point   
{   
    private int x;    
    private int y;    
       
    public Point(int x,int y)    
    {    
        this.x = x;    
        this.y = y;    
    }    

   public void setX(int x){
       this.x=x;
   }

   public void setY(int y){
      this.y=y;
   }
   public int getX(){
      return this.x;
   }

   public int getY(){
     return this.y;
  }
   
    public boolean equals(Object o)    
    {    
        if (this == o)    
        {    
            return true;    
        }    
           
    if (o.getClass() == Point.class)    
        {    
            Point p = (Point)o;    
            return (p.x==x) && (p.y==y);    
        }    
        return false;    
    }    


    public int hashCode() {
        long bits = getX();
        bits ^= getY() * 31;
        return (((int) bits) ^ ((int) (bits >> 32)));
    }



    public String toString() 
    { 
        return "Point[" +x+"," +y+ "]"; 
    } 


}   



