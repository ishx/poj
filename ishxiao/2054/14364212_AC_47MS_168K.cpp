// poj2054
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1007;

struct node
{
    int t;    //time[]
    int p;    //记录父节点
    int c;    //c[]
    double w;    //w[]
}num[N];

int n, r;

int find()    //查找最大的权值，返回其位置
{
    int pos;
    double max = 0;
    for(int i = 1; i <= n; i++)
        if(num[i].w > max && i != r)    //pos不能为根节点
        {
            max = num[i].w;
            pos = i;
        }
    return pos;
}

int main()
{
    //freopen("data.in", "r", stdin);
    int i, j, a, b, pos, ans, f;
    while(scanf("%d%d", &n, &r), n||r)
    {
        ans = 0;
        for(i = 1; i <= n; i++)
        {
            scanf("%d", &num[i].c);    
            num[i].w = num[i].c;    //初始时w[i]置为c[i];
            num[i].t = 1;        //time[i] 置为1；
            ans += num[i].c;    //初始ans = sum(c[i]);
        }
        for(i = 1; i < n; i++)
        {
            scanf("%d%d", &a, &b);
            num[b].p = a;    //记录父节点，建立树关系
        }
        i = n;
        while(i > 1)
        {
            pos = find();    //找到最大权值的位置
            num[pos].w = 0;        //找到后将之置0，否则影响下次查找。
            f = num[pos].p;        //f为父节点
            ans += num[pos].c * num[f].t;    //将找到的c[pos]*time[f]加入ans
            for(j = 1; j <= n; j++)
                if(num[j].p == pos)
                    num[j].p = f;    //如果有节点与pos相连，让它指向pos的父节点
            num[f].c += num[pos].c;        //C_i = c[该节点] + c[父节点]
            num[f].t += num[pos].t;        //T_i = time[该节点]+time[父节点]
            num[f].w = (double)num[f].c/num[f].t;    //合并后的f节点的权值
            i--;
        }
        printf("%d\n", ans);
    }
    return 0;
}