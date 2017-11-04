#include <iostream>
using namespace std;

int main()
{
	int n,c,area=0,bed_area=0,bal_area=0;
	scanf("%d%d",&n,&c);
	while(n--){
		int x;
		char s[16];
		scanf("%d%s",&x,s);
		area+=x;
		if(strcmp(s,"bedroom")==0)
			bed_area+=x;
		else if(strcmp(s,"balcony")==0)
			bal_area+=x;
	}
	printf("%d\n%d\n%.6lf\n",area,bed_area,(area-bal_area*0.5)*c);
	
}