#include <iostream>


#include <algorithm>
using namespace std;
int test_num;
int sl[20];
bool choosen[20];
int stick_num;
bool find_square;
int sum;
int len;
struct cmper{
	inline bool operator ()(const int &a, const int &b)const{
	return a > b;
}
};
//确保了最大的要小于＝ len,也正确 但递归调用较多，考虑用下面的循环减少递归
//void find_group(int set_num, int depth) {
//    if (depth == stick_num) 
//        return;
//    if (set_num == 0) {
//        find_square = true;
//        throw true;
//    }
//
//    if (choosen[depth] == true)
//        find_group(set_num, depth + 1);
//    else {
//            if (depth && !sl[depth - 1] && sl[depth] == sl[depth -1]) {
//                find_group(set_num, depth + 1);
//                return;
//            }
//            int sum_now = sl[depth] + sum;
//            if (sum_now < len) {
//                choosen[depth] = true;                                     
//                sum = sum_now;
//                find_group(set_num, depth + 1);
//                sum = sum_now - sl[depth];                              
//                choosen[depth] = false;
//                if (sum != 0)                          //剪枝，最大的只能被选中，不需要考虑不被选中的情况，剪枝50%
//                    find_group(set_num, depth + 1);
//            } 
//            else if (sum_now == len) {                
//                choosen[depth] = true;
//                sum = 0;
//                find_group(set_num - 1, 0);  
//                choosen[depth] = false;       
//
//            }   
//            else {
//                find_group(set_num, depth + 1);    //sum_now > len 只能不选当前的
//            }
// 
//    }
//}
bool find_group(int set_num, int depth , int sum = 0) {
	if (set_num == 1)             //选好3组了，返回成功
		return true;
	
	for (int i = depth; i < stick_num; i++) {
		if (choosen[i] == true)           //前面的选好的组已经用到该元素，略过继续查找。
			continue;
		if (i && !sl[i - 1] && sl[i] == sl[i -1])  //剪枝,作用不大
            		continue;
		int sum_now = sl[i] + sum;
		if (sum_now < len) {
			choosen[i] = true;         //选中当前元素，继续后续查找当前组组元素
			if (find_group(set_num, i + 1, sum_now))
				return true;
			choosen[i] = false;  //不选中当期元素的情形(注意向上返回时都已置回false),继续后续查找当前组元素
		}
		else if (sum_now == len) {
			choosen[i] = true;
			if (find_group(set_num - 1, 0, 0))  //找到1组，查找后续分组，成功的话返回true
				return true;
			choosen[i] = false;
		}
		if (sum_now == len || sum == 0)  //剪枝，首元素要被选中，当包含首元素的组查找其它分组失败即为失败5.2
			break;         //当选中当前元素，能构成一个组的时候，如果查找后续分组失败即为失败5.3
	}
	return false;  //当前选择的情形，已经扫描到末尾仍为成功失向上层返回标识为失败
}
bool group_stick() {
	find_square = false;
	for (int i = 0; i < 20; i++)
		choosen[i] = false;
	//try{
	return   find_group(4, 0);
	//} catch(bool nothing){ }
	//return find_square;
}
int main(int argc, char *argv[])
{
	cin >> test_num;
	int sum;
	for (int i = 0; i < test_num; i++) {
		cin >> stick_num;
		sum = 0;
		for (int j = 0; j < stick_num; j++) {
			cin >> sl[j];
			sum += sl[j];
			//choosen[i] = false;
		}
		if ((sum % 4) != 0)
			cout << "no" << endl;
		else {
			sort(sl, sl + stick_num, cmper());
			len = sum / 4;
			if (sl[0] > len)
				cout << "no" << endl;
			else {
				if (group_stick())
					cout << "yes" << endl;
				else
					cout << "no" << endl;
			}
 		}
	}
return 0;
}