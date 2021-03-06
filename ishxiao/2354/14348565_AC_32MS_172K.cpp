#include <map>
#include <set>
#include <queue>
#include <stack>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <string>
#include <algorithm>
#define MID(x,y) ( ( x + y ) >> 1 )
#define L(x) ( x << 1 )
#define R(x) ( x << 1 | 1 )
#define BUG puts("here!!!")
#define STOP system("pause")

using namespace std;

const double r = 6875.0/2;
const double pi = acos(-1.0);
double angle_3d(double lng1, double lat1, double lng2, double lat2)
{           //经度，纬度，经度，纬度 
    return acos(cos(lat1)*cos(lat2)*cos(lng1 - lng2) + sin(lat1)*sin(lat2));
}

int main()
{
	char s[50];
	
	double x1,x2,x3;
	
	double lng1, lat1, lng2, lat2;
	
	while( ~scanf("%s", s) )
	{
		if( s[0] == '=' ) break;
		for(int i=0; i<8; i++) scanf("%s",s);
		
		scanf("%lf^%lf'%lf\" %s",&x1, &x2, &x3, s);
		lat1 = x1 + x2/60 + x3/3600;
		if( s[0] == 'S' ) lat1 *= -1;
		
		scanf("%s",s);
		
		scanf("%lf^%lf'%lf\" %s",&x1, &x2, &x3, s);
		lng1 = x1 + x2/60 + x3/3600;
		if( s[0] == 'W' ) lng1 *= -1;
		
		for(int i=0; i<5; i++) scanf("%s",s);		// iceberg
	
		scanf("%lf^%lf'%lf\" %s",&x1, &x2, &x3, s);
		lat2 = x1 + x2/60 + x3/3600;
		if( s[0] == 'S' ) lat2 *= -1;
		
		scanf("%s",s);
		
		scanf("%lf^%lf'%lf\" %s",&x1, &x2, &x3, s);
		lng2 = x1 + x2/60 + x3/3600;
		if( s[0] == 'W' ) lng2 *= -1;
		
		double ang = angle_3d(lng1*pi/180, lat1*pi/180, lng2*pi/180, lat2*pi/180);
		double dis = ang * r;
		
		printf("The distance to the iceberg: %.2lf miles.\n", dis);
		
		if( floor(dis+0.005) < 100  )
			printf("DANGER!\n");
	}

return 0;
}
