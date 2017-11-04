//1503

#include<iostream>
#include<cstring>
using namespace std;

const int large=1000;
char sum_temp[large];
char digit_temp[large];

int plus(int j,int carry_bit)
{
	int count;
	count=(sum_temp[j]-'0')+(digit_temp[j]-'0')+carry_bit;
	sum_temp[j]=count%10+'0';
	if(count<10)
		return 0;
	else
		return 1;
}

int main(void)
{
	int length,i,j,k;
	int max=0,carry_bit=0;
	char digit[large],sum[large];

	memset(sum_temp,'0',sizeof(sum_temp));

	for(i=-1;strcmp(digit,"0");)
	{
		i++;
		gets(digit);
		length=strlen(digit)-1;

		memset(digit_temp,'0',sizeof(digit_temp));

		for(k=0,j=length;j>=0;--j,++k)
			digit_temp[k]=digit[j];        //倒置
		if(max<length)
			max=length;
		for(carry_bit=0,j=0;j<=max;j++)     //每两个长数相加一次进位必须初始化进位值
			carry_bit=plus(j,carry_bit);
	    if(carry_bit==1)         //最高位进位检查
		    sum_temp[++max]='1';
	    for(i=max,j=0;i>=0;--i,++j)
		{
		    if(i==max&&sum_temp[i]=='0')   //检查并消去高位0
			{
		    	--max;
		    	continue;
			}
		    sum[j]=sum_temp[i];         //倒置
		}
		sum[j]='\0';           //末尾添加结束符
	}
	cout<<sum<<endl;
	return 0;
}