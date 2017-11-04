#include <iostream>
using namespace std;
int n, t, m;
void SolveGreedy() 
{
      int l = m % n;
      int k = m / n;
      int time_now;   //当前船只来到原岸的时间
      int time_return = 0; //前一组运送渡船的返回时间
      int trans_times = k;
      if (l) {
           trans_times += 1;
            for (int i = 0; i < l; i++)
            cin >> time_now;
            time_return = time_now + 2 * t;
       }
      for (int i = 0; i < k; i++) {
           for (int j = 0; j < n; j++)
                  cin >> time_now;
            if (time_now <= time_return)
                  time_return = time_return + 2 * t;
            else
                  time_return = time_now + 2 * t;
       }
      //输出结果
      cout << time_return - t <<" " << trans_times << endl;
}
int main(int argc, char *argv[])
{
      int testNum;
      cin >> testNum;
      while (testNum--) {
           cin >> n >> t >> m;
            SolveGreedy();
      }
     return 0;
}
