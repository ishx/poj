/***************************************************************************** 
 * Author : Xiao 
 * Last modified : 2014-08-09 21:05 
 * Filename : POJ1065 Wooden Sticks.cpp 
 * Description : 这条题我用的是贪心算法。首先先对长度len排序，则问题就转化为求 
                weight的没有交点的上升子序列的个数。对于任何一个上升子序列，必 
                然有头元素和尾元素，我们这里就找尾元素。我们用num数组来标记是否 
                尾元素，是的话是0，不是的话是1。对于第i个元素，往前找到一个既是 
                某上升序列的尾元素，同时比第i个元素小的元素里面的最大值，设其下 
                标为index，则我们可以把num[index]设为1表示其不是尾元素了。最后 
                统计还有多少个尾元素就可以知道有多少个上升子序列了。总的时间复杂 
                度为O(N^2)。 
 * *****************************************************************************/  
// ZOJ1025 POJ1065 HDU1051 Wooden Sticks.cpp : Defines the entry point for the console application.  

  
#include <stdio.h>  
#include <string.h>  
#include <string>  
#include <memory.h>  
#include <algorithm>  
  
using namespace std;  
  
struct node  
{  
    int len,weight;  
}sticks[5010];  
  
int num[5010];  
  
bool cmp(const node &lhs,const node &rhs)  
{  
    if(lhs.len !=rhs.len)  
        return lhs.len<rhs.len;  
    else  
        return lhs.weight<rhs.weight;  
}  
  
int main(void)  
{  
    int ncases,n;  
  
    scanf("%d",&ncases);  
    while(ncases--)  
    {  
        memset(num,0,sizeof(num));  
        scanf("%d",&n);  
        int sum=n;  
  
        for(int i=0;i<n;++i)  
            scanf("%d %d",&sticks[i].len,&sticks[i].weight);  
  
        sort(sticks,sticks+n,cmp);  
  
        for(int i=1;i<n;++i)  
        {  
            int minlen=-1;  
            int index=-1;  
            for(int j=i-1;j>=0;--j)  
            {  
                if(sticks[i].weight>=sticks[j].weight && !num[j] && minlen<sticks[j].weight)  
                {  
                    index=j;  
                    minlen=sticks[j].weight;  
                }  
            }  
            if(minlen>-1)  
            {  
                num[index]=1;  
                --sum;  
            }  
        }  
        printf("%d\n",sum);  
    }  
    return 0;  
}
