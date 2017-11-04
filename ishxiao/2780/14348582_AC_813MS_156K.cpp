//poj 2780
//sep9
#include <iostream>
#include <algorithm> 
#include <cmath>
using namespace std;
const int maxN=1024;
const int maxM=500024;
struct POINT
{
	int x,y;
}p[maxN];
struct LINE
{
	int x,y;	
}l[maxM];

int cmp(LINE a,LINE b)
{
	 return a.x*b.y-a.y*b.x>=0;		
}

int main()
{
	int n;
	while(scanf("%d",&n)==1){
		int num_line,ans=-1;
		for(int i=0;i<n;++i)
			scanf("%d%d",&p[i].x,&p[i].y);		
		for(int i=0;i<n;++i){
			num_line=0;
			for(int j=i+1;j<n;++j){
				int dx=p[i].x-p[j].x,dy=p[i].y-p[j].y;
				if(dy<0) dy=-dy,dx=-dx; 
				else if(dy==0&&dx<0)
					dx=-dx;
				l[num_line].x=dx,l[num_line].y=dy;
				++num_line;
			}
			sort(l,l+num_line,cmp);
			int cnt=0;
			for(int k=0;k<num_line;++k)
				if(k==0||l[k-1].x*l[k].y==l[k-1].y*l[k].x)
					++cnt;
				else{
					ans=max(ans,cnt);
					cnt=1;
				}
			ans=max(ans,cnt);		
		}
		printf("%d\n",ans+1);
	}
	return 0;	
} 