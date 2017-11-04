#include <iostream>
using namespace std;
const int MaxNum = 100;
int a[MaxNum];     //递归中的当前扫描路径
int b[MaxNum];     //记录当前找到的最短路径
void PrintPath(int n) {
for (int i = 0; i <= n; i++)
cout << b[i] << " ";
cout << endl;
}
int shortest_len = MaxNum;
void FindShortestChian(int n, int i) {
for (int j = i - 1; j >= 0; j--) {
int sum = a[i - 1] + a[j];
if (sum == n) {
a[i] = n;
for (int k = 0; k <= i; k++ )
b[k] = a[k];
shortest_len = i;
return;
} else if (sum < n && i + 1 < shortest_len) {
a[i] = sum;
FindShortestChian(n, i+1);
}
}
}
int main(int argc, char *argv[])
{
int n;
a[0] = 1;
a[1] = 2;
b[0] = 1;
b[1] = 2;
while (1) {
cin >> n;
if (n == 0)
break;
else if (n == 1 || n == 2)
PrintPath(n - 1);
else {
shortest_len = MaxNum;
FindShortestChian(n, 2);
PrintPath(shortest_len);
}
}
return 0;
}