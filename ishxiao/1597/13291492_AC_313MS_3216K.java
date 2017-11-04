import java.util.Scanner;
public class Main {

    public static void main(String[] args) {
        Scanner scan=new Scanner(System.in);
        int s=0,m=0,ac=0;
        boolean[] bands;
        boolean flaj;
        while(scan.hasNext()){
            s=scan.nextInt();
            m=scan.nextInt();
            bands=new boolean[m+1];
            flaj=true;
            ac=0;
            for(int i=0;i< m;i++){
                if(bands[ac]){
                    flaj=false;
                    break;
                }
                bands[ac]=true;
                ac+=s;
                ac=ac%m;
            }
            ac=10-(s+"").length();
            for(int i=0;i< ac;i++)System.out.print(" ");
            System.out.print(s);
            ac=10-(m+"").length();
            for(int i=0;i< ac;i++)System.out.print(" ");
            if (flaj) System.out.print(m+"    Good Choice\n\n");
            else System.out.print(m+"    Bad Choice\n\n");
        }
    }
}