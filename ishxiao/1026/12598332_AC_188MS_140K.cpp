//1026
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
#include <set>

#define CL(arr, val)    memset(arr, val, sizeof(arr))
#define REP(i, n)       for((i) = 0; (i) < (n); ++(i))
#define FOR(i, l, h)    for((i) = (l); (i) <= (h); ++(i))
#define FORD(i, h, l)   for((i) = (h); (i) >= (l); --(i))
#define L(x)    (x) << 1
#define R(x)    (x) << 1 | 1
#define MID(l, r)   (l + r) >> 1
#define Min(x, y)   x < y ? x : y
#define Max(x, y)   x < y ? y : x
#define E(x)    (1 << (x))

typedef long long LL;
using namespace std;

const int N = 210;

char str[N];
char ans[N];
int a[N];
int vis[N];
int n, k;

void solve() {
    int i, tmp;
    CL(vis, 0);
    for(i = 0; i < n; ++i) {
        if(!vis[a[i]]) {
            tmp = a[i]; vis[a[i]] ++;
            while(tmp != i) {
                vis[a[i]] ++;
                tmp = a[tmp];
            }
        }
    }
    int pos;
    for(i = 0; i < n; ++i) {
        tmp = k%vis[a[i]];
        pos = a[i];
        while(tmp --)   pos = a[pos];
        ans[pos] = str[i];
    }
}

int main() {
    //freopen("data.in", "r", stdin);

    int i, l, x;
    while(scanf("%d", &n), n) {
        CL(a, 0);
        for(i = 0; i < n; ++i) {
            scanf("%d", &x);
            a[i] = x-1;
        }
        while(scanf("%d", &k), k) {
            getchar();
            gets(str);
            k--;
            l = strlen(str);
            if(l < n) {
                for(i = l; i < n; ++i)  str[i] = ' ';
            }
            solve();
            for(i = 0; i < n; ++i) {
                printf("%c", ans[i]);
            }
            putchar('\n');
        }
        putchar('\n');
    }
    return 0;
}