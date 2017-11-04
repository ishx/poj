#include <stdio.h>
#include <string.h>

int main()
{
    char m[100],d[100];
    int t,n,a,b,c,aa,bb,cc;
    scanf("%d", &t);
    while(t-- && scanf("%d", &n))
    {
        aa = 100000;
        cc = bb = 1;
        while(n-- && scanf("%s %d %d", m, &a, &b))
        {
            if(b < 200) continue;
            c = b/200 < 5 ? b/200 : 5;
            if(aa*c > a*cc)
            {
                aa = a;
                bb = b;
                cc = c;
                strcpy(d, m);
            }
            else if(aa*c == a*c && b > bb)
            {
                bb = b;
                strcpy(d, m);
            }
        }
        puts(d);
    }
    return 0;
}