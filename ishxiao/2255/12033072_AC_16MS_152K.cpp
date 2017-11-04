#include<iostream>
#include<cstring>
using namespace std;

char post[26];
int point=0;

void right_to_left(char preo[],char inor[])
{
	post[point++]=preo[0];       //根

	const int length=strlen(inor);
	if(length==1)
		return;
	int j=0;
	for(;j<length;j++)
		if(inor[j]==preo[0])
			break;
	const int flag=j;
	int i=++j;
	char preo_temp[26],inor_temp[26];
	bool tag=false;

	for(j=0;i<length;++i,++j)          //提取右子树中序
	{
		inor_temp[j]=inor[i];
		tag=true;
	}

	if(tag)
	{
		inor_temp[j]='\0';
	    for(i=0,j=length-j;j<length;++i,++j)       //提取右子树前序
	        preo_temp[i]=preo[j];
	    preo_temp[i]='\0';

        right_to_left(preo_temp,inor_temp);
	}
		                                            //↑↑↑↑↑
	                                                //处理右子树
//===============================================================
	                                                //处理左子树
	                                                //↓↓↓↓↓
	tag=false;
	for(i=0;i<flag;i++)          //提取左子树中序
	{
		inor_temp[i]=inor[i];
	    tag=true;
	}

	if(tag)
	{
		inor_temp[i]='\0';
		for(i=0,j=1;i<flag;++i,++j)      //提取左子树前序
	    	preo_temp[i]=preo[j];
    	preo_temp[i]='\0';
		
		right_to_left(preo_temp,inor_temp);
	}
	return;
}

int main(void)
{
	char preo[26],inor[26];
	
	while(cin>>preo>>inor)
	{
		right_to_left(preo,inor);

    	for(--point;point>=0;point--)
    		cout<<post[point];
	    cout<<endl;

		point=0;
	}
	return 0;
}