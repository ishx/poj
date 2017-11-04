//3270
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

const int N = 100010;

int a[N], b[N], p[N];
bool vis[N];
int sum;
int m, n;

int solve() {
    int res = 0;
    int i, j, x, pos, ti;
    CL(vis, 0);
    for(j = 1; j <= n; ++j) {
        i = p[j];
        if(!vis[a[i]]) {
            x = 1;
            pos = a[i]; vis[a[i]] = true;
            ti = Min(a[i], i);
            while(pos != i) {
                x++; vis[a[pos]] = true;
                pos = a[pos];
                ti = Min(ti, pos);
            }
            res += Min((x-2)*ti, (x + 1)*m + ti);
        }
    }
    return res;
}

int main() {
    //freopen("data.in", "r", stdin);

    scanf("%d", &n);
    m = ~0u>>2; sum = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &b[i]);
        m = Min(m, b[i]);
        p[i] = b[i];
        sum += b[i];
    }
    sort(p + 1, p + n + 1);
    for(int i = 1; i <= n; ++i) {
        a[p[i]] = b[i];
    }
    int res = solve();
    printf("%d\n", sum + res);
    return 0;
}