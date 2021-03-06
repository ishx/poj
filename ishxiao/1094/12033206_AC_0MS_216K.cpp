//1094

#include<iostream>
using namespace std;

int n,m;  //n结点下限，m关系对
char top_out[26];  //排序输出列表
int po=0;  //输出列表的指针

typedef class degree
{
public:
	int in;      //入度
	char to[26];   //记录指向的所有顶点，以便删除出度的操作
	int pt;    //数组to的指针
};

int top_sort(degree alph[],bool mark[],int num)
{
	/*假设图G的当前子图为F*/

	memset(top_out,'\0',sizeof(top_out));
	po=0;
	
	int del_n=0;
	int zero=0;  //记录图F中入度为0的结点个数
	for(int i='A';i<'A'+n;i++)
		if(mark[i] && !alph[i].in)
			zero++;

	bool flag=false;
	while(zero>0)
	{
		if(zero>1)  //图F的无前驱结点的个数不唯一，排序无法确定
			flag=true;  //考虑到"矛盾"的优先性，避免在多个0入度结点情况下，最后一步输入刚好出现环（此时为矛盾）
		                //所以这里先不返回值，而是先标记，执行拓扑，根据情况决定返回值

		for(int k='A';k<='A'+n;k++)   //寻找图F的唯一的前驱结点
			if(mark[k] && !alph[k].in)
			{
				mark[k]=false;       //删除图F的唯一无前驱结点k
				del_n++;            //记录删除的结点数
				top_out[po++]=k;    //k记录到排序输出列表
				for(int i=0;i<alph[k].pt;i++)   //删除结点k的所有出度边
					alph[ alph[k].to[i] ].in--;
				break;
			}

		zero=0;
		for(int j='A';j<='A'+n;j++)
			if(mark[j] && !alph[j].in)
				zero++;
	}

    if(flag && del_n==num)
		return 3;
	if(del_n<num)   //说明图F存在有向环,矛盾，与0入度结点的多少无关。因为矛盾优先
		return 2;
	if(!flag && del_n==num && del_n<n)  //图F能排序，但不能确定图G是否能排序，还需继续输入观察
		return 3;
	if(!flag && del_n==n)    //图G能排序
		return 1;
}

int main(void)
{
	int num;      //标记前n个字母出现个数,用于最终检查是否前n个字母均已被读入
	     //*_t[]是用于备份的额外数组
	bool mark['Z'+1],mark_t['Z'+1];  //标记当前图G所使用的字母（结点）
	degree alph['Z'+1],alph_t['Z'+1];   

	while(true)
	{
		/*Input*/

		cin>>n>>m;

		if(!n||!m)
			break;
		
		/*Initial*/

		memset(mark,false,sizeof(mark));
		memset(mark_t,false,sizeof(mark_t));
		num=0;

		for(int k='A';k<'A'+n;k++)
		{
			alph[k].in=alph_t[k].in=0;
			alph[k].pt=alph_t[k].pt=0;
			memset(alph[k].to,'\0',sizeof(alph[k].to));
			memset(alph_t[k].to,'\0',sizeof(alph_t[k].to));
		}
		
		/*Structure Maps*/

		char x,symbol,y;  //临时变量
		bool flag=false;
		bool sign=false;
		int value;   //记录拓扑返回的值
		int step;   //记录当前情况发生的步骤
		for(int pair=1;pair<=m;pair++)
		{
			cin>>x>>symbol>>y;

			if(x>='A'+n || y>='A'+n)  //当输入的结点不在前n个字母范围内时
				sign=true;       //不再进行拓扑,单纯检查后续输入是否把前n个字母都输入了
				                 //为了区分非前n个字母的字母的输入时间，是在确认了排序或矛盾之前还是之后
			                     //在确认 排序或矛盾之前:flag=false,sign=true
			                     //在确认 排序或矛盾之后:flag=true,sign=true

			if(!mark[x] && x<'A'+n)
				num++;
			if(!mark[y] && y<'A'+n)
				num++;

			if(!flag && !sign)
			{
				value=0;

			    mark[x]=mark[y]=true;        //顶点标记
			    mark_t[x]=mark_t[y]=true;

			    alph[y].in++;                //入度标记
			    alph_t[y].in++;

			    alph[x].to[ alph[x].pt++ ]=y;        //指向标记 & 指针移动
			    alph_t[x].to[ alph_t[x].pt++ ]=y;

			/*Top-Sort & Sign*/
				
				value=top_sort(alph_t,mark_t,num);  //每次输入后图都被更新，要重新拓扑
			    if(value==1)       //排序确认
				{
			     	step=pair;    //记录确认排序的位置
			    	flag=true;    //不再对后续输入处理
				}
		    	else if(value==2)  //矛盾
				{
			    	step=pair;    //记录矛盾发生的位置
			    	flag=true;    //不再对后续输入处理
				}
		    	else if(value==3 && pair<m)  //排序（暂时）无法确认，需继续处理后续输入 
			    	for(int k='A';k<'A'+n;k++)        //数据还原
					{
				    	mark_t[k]=mark[k];
				    	alph_t[k].in=alph[k].in;
					}

				if(pair==m && value==0)
					value=3;
			}

			if(sign && !flag && num==n)  //在确认 排序或矛盾之前,当存在有非前n个字母的结点时的"矛盾"
			{
				step=pair;
				value=2;
			}
			else if(sign && !flag && pair==m && num<n) //在确认 排序或矛盾之前,当存在有非前n个字母的结点时的"无法确认排序"
				value=3;
		}

		if(value==1)
		{
			cout<<"Sorted sequence determined after "<<step<<" relations: ";
			for(int i=0;i<po;i++)
				cout<<top_out[i];
			cout<<'.'<<endl;
		}
		else if(value==2)
			cout<<"Inconsistency found after "<<step<<" relations."<<endl;
		else if(value==3)
			cout<<"Sorted sequence cannot be determined."<<endl;
	}
	return 0;
}
