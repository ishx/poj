// poj1040
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define maxm 23
#define maxn 8

struct Order
{
    int s, e, p;
}order[maxm];

int cap, n, m;
int ans;
int ocount;
int down[maxn];

bool operator < (const Order &a, const Order &b)
{
    if (a.s == b.s)
        return a.e < b.e;
    return a.s < b.s;
}

void input()
{
    ocount = 0;
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        order[i].s = a;
        order[i].e = b;
        order[i].p = c;
    }
}

void dfs(int i, int p, int money)
{
    if (i == m)
    {
        ans = max(ans, money);
        return;
    }
    if (i > 0)
        for (int j = order[i - 1].s + 1; j <= order[i].s; j++)
            p -= down[j];
    if (p + order[i].p <= cap)
    {
        down[order[i].e] += order[i].p;
        dfs(i + 1, p + order[i].p, money + order[i].p * (order[i].e - order[i].s));
        down[order[i].e] -= order[i].p;
    }
    dfs(i + 1, p, money);
}

int main()
{
    //freopen("t.txt", "r", stdin);
    while (scanf("%d%d%d", &cap, &n, &m), cap | n | m)
    {
        input();
        sort(order, order + m);
        ans = 0;
        dfs(0, 0, 0);
        printf("%d\n", ans);
    }
    return 0;
}