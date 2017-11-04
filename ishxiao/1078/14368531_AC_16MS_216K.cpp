// poj1078
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

__int64 a,b;//a是大的，b是小的
int flag[101];
int flag1;

int Dfs(int index,__int64 a,__int64 b,int x)
{
 if (index <= 0)
  return 0;
 if (a == 1)
 {
  flag1 = 1;
  if (x == 1)
   return Dfs(100,b,b,2);
  else
   return 1;
 }
 int i;
 for (i = index; i >= 1; i --)
  if (a % i == 0 && flag[i] == 0)
  {
   flag[i] = 1;
   if (Dfs(i -1,a / i,b,x))
    return 1;
   flag[i] = 0;
  }
 return 0;
}

int main(void)
{
 while (cin >> a >> b)
 {
  //交换a,b
  if (a < b)
  {
   a ^= b;
   b ^= a;
   a ^= b;
  }
  memset(flag,0,sizeof(flag));
  flag1 = 0;
  if (Dfs(100,b,a,1) || flag1 == 0)
   cout << a << endl;
  else
   cout << b << endl;
 }
 return 0;
}

