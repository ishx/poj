//poj 2556
//sep9
#include<iostream>
using namespace std;
char s[256];

int main()
{
	while(scanf("%s",&s)==1){
		int px=300,py=420;
		int x=310,y=420;
		puts("300 420 moveto\n310 420 lineto");
		for(int i=0;s[i]!='\0';++i){
			int dx=x-px,ddx;
			int dy=y-py,ddy;
			px=x;
			py=y;
			if(s[i]=='V'){
				ddx=-dy;
				ddy=dx;	
			}else if(s[i]=='A'){
				ddx=dy;
				ddy=-dx;
			}
			x=x+ddx;
			y=y+ddy;
			printf("%d %d lineto\n",x,y);	
		}
		puts("stroke\nshowpage");
	}
	return 0;	
} 