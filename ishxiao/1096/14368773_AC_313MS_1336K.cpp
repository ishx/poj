// poj1096
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
int n, m, k, l;
bool tab[70][70][70], visit[70][70][70];
int face_num;
class W3{
public:
	int x, y, z;
	W3& set(int xx, int yy, int zz){
		x = xx; y = yy; z = zz;
		return *this;
	}
};
void bfs(){
	face_num = 0;
	queue<W3> Q;
	W3 temp;
	Q.push(temp.set(0, 0, 0));
	while (!Q.empty()){
		W3 Top = Q.front(); Q.pop();
		if (visit[Top.x][Top.y][Top.z])continue;
		visit[Top.x][Top.y][Top.z] = 1;
		if (Top.x - 1 >= 0){
			if (tab[Top.x - 1][Top.y][Top.z] == 0){
				if (!visit[Top.x - 1][Top.y][Top.z])Q.push(temp.set(Top.x - 1, Top.y, Top.z));
			}
			else face_num++;
		}//左走一格
		if (Top.x <= n){
			if (tab[Top.x + 1][Top.y][Top.z] == 0){
				if (!visit[Top.x + 1][Top.y][Top.z])Q.push(temp.set(Top.x + 1, Top.y, Top.z));
			}
			else face_num++;
		}//右走一格
		if (Top.y - 1 >= 0){
			if (tab[Top.x][Top.y - 1][Top.z] == 0){
				if (!visit[Top.x][Top.y - 1][Top.z])Q.push(temp.set(Top.x, Top.y - 1, Top.z));
			}
			else face_num++;
		}//后走一格
		if (Top.y <= m){
			if (tab[Top.x][Top.y + 1][Top.z] == 0){
				if (!visit[Top.x][Top.y + 1][Top.z])Q.push(temp.set(Top.x, Top.y + 1, Top.z));
			}
			else face_num++;
		}//前走一格
		if (Top.z - 1 >= 0){
			if (tab[Top.x][Top.y][Top.z - 1] == 0){
				if (!visit[Top.x][Top.y][Top.z - 1])Q.push(temp.set(Top.x, Top.y, Top.z - 1));
			}
			else face_num++;
		}//下走一格
		if (Top.z <= k){
			if (tab[Top.x][Top.y][Top.z + 1] == 0){
				if (!visit[Top.x][Top.y][Top.z + 1])Q.push(temp.set(Top.x, Top.y, Top.z + 1));
			}
			else face_num++;
		}//上走一格
	}
}
int main(){
	while (cin >> n >> m >> k >> l){
		if (!n && !m && !k && !l)break;
		memset(tab, 0, sizeof(tab));
		memset(visit, 0, sizeof(visit));
		int temp1;
		for (int i = 0; i < l; i++){
			cin >> temp1;
			tab[temp1 % (m*n) % n + 1][temp1 % (m*n) / n + 1][temp1 / (n*m) + 1] = 1;
		}//输入数据并转换为tab[][][]的3维矩阵(这里从1,1,1开始,最外层相当于无人方块)
		bfs();
		cout << "The number of faces needing shielding is " << face_num << ".\n";
	}return 0;
}