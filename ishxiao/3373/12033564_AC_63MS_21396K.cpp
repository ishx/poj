//3373

#include<iostream>
#include<string>
using namespace std;

class solve
{
	public:
		solve(char* sn,int tk)
		{
			len=strlen(sn);
			k=tk;
			n_MODk=0;

			InitialFlag(len,k);
			PlayTable_Mod();
			Calculation_n_MODk(sn);

			for(int AllowNum=1;AllowNum<=len;AllowNum++)  //枚举允许修改的数字个数
				if(DFS(len-1,AllowNum,n_MODk)) //要保证搜索区间最大
					break;
		}
		~solve()
		{
			for(int i=len-1;i>=0;i--)
				cout<<m[i];
			cout<<endl;

			delete[] flag;
		}
		void InitialFlag(int len,int k);
		void PlayTable_Mod(void);   //打表mod[][]，利用同余模公式
		void Calculation_n_MODk(char* sn);  //计算n%k
		bool DFS(int pos,int RestNum,int m_MODk);

	protected:
		int len;
		int n[101],m[101];
		int k;
		int n_MODk;  //n%k
		int mod[101][10];  //mod[i][j]=((10^i)*j)%k
		int** flag;  //flag[pos][m_MODk]=RestNum
};        /* 
		     当搜索m的位置区间为[0,pos]，且当前数字串m对k取模值为m_MODk时，
			 若剩下允许的修改数字的个数只允许修改RestNum个，
			 则无论如何修改区间[0,pos]内的数字也无法使得m_MODk==0，
			 那么对于同样的pos和m_MODk, 小于RestNum的个数则更加不可能了,这用于剪枝
          */

void solve::InitialFlag(int len,int k)
{
	flag=new int*[len+1];
	for(int i=0;i<=len;i++)
	{
		flag[i]=new int[k];
		memset(flag[i],false,sizeof(int)*k);
	}
	return;
}

void solve::PlayTable_Mod(void)
{
	for(int j=0;j<=9;j++)
		mod[0][j]=j%k;

	for(int i=1;i<len;i++)
		for(int j=0;j<=9;j++)
			mod[i][j]=(mod[i-1][j]*10)%k;
	return;
}

void solve::Calculation_n_MODk(char* sn)
{
	for(int i=0;i<len;i++)
	{
		n[i]=m[i]=sn[len-i-1]-'0';  //倒序n，并转换为数字串
		n_MODk=(n_MODk+mod[i][ n[i] ])%k;  //n%k
	}

	return;
}

bool solve::DFS(int pos,int RestNum,int m_MODk)
{
	if(m_MODk==0)
		return true;

	if(RestNum==0 || pos<0)
		return false;

	if(RestNum <= flag[pos][m_MODk])  //剪枝
		return false;

	int i,j;

	for(i=pos;i>=0;i--)  //枚举比n小的数m，且m要尽可能小，则从高位开始
		for(j=0;j<n[i];j++)
		{
			if(i==len-1 && j==0)  //m最高位不为0
				continue;

			int res=(m_MODk-(mod[i][m[i]]-mod[i][j])+k)%k;
			int tmp=m[i];
			m[i]=j;
            //i-1即缩减搜索区间
			if(DFS(i-1,RestNum-1,res))
				return true;
			
			m[i]=tmp;
		}

	for(i=0;i<=pos;i++)  //枚举比n大的数m，但m要尽可能小，则从低位开始
		for(j=n[i]+1;j<=9;j++)
		{
			if(i==len-1 && j==0)  //m最高位不为0
				continue;

			int res=(m_MODk+(mod[i][j]-mod[i][m[i]]))%k;  //同余模公式
			int tmp=m[i];
			m[i]=j;
			//i-1即缩减搜索区间
			if(DFS(i-1,RestNum-1,res))
				return true;

			m[i]=tmp;
		}

	flag[pos][m_MODk]=RestNum;  //在区间[0,pos]内只允许修改RestNum个数字无法使得m_MODk==0
	return false;
}

int main(void)
{
	char sn[101];
	int tk;

	while(cin>>sn>>tk)
		solve poj3373(sn,tk);

	return 0;
}