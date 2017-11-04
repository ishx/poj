// poj1044
#include <iostream>

using namespace std;

int n;
int y[20];
int a[20];
int t[20];

int main (void) {
    int case_id = 0;
    while (true) {
        cin >> n;
        if (n == 0) break;
        for (int i = 0; i < n; ++i) {
            cin >> y[i] >> a[i] >> t[i];
            t[i] -= a[i];    //计算出周期即可，b[i]以后不会再用到
        }
        int k = 0;
        //依次检验每个k是否可行
        while ((a[0] = y[0] + k * t[0]) < 10000) {
            bool flag = true;
            for (int i = 1; i < n; ++i) {
                int p = a[0] - y[i];
                if (p < 0 || p % t[i] != 0) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "Case #" << ++case_id <<":" << endl; 
                cout << "The actual year is " << a[0] << "." << endl << endl; 
                break;
            }     
            ++k;
        }
        if (a[0] >= 10000) {
            cout << "Case #" << ++case_id <<":" << endl; 
            cout << "Unknown bugs detected." << endl << endl; 
        }
    }
    system("pause");
    return 0;
}