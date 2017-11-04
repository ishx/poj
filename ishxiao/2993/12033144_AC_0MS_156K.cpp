//2993

#include<iostream>
#include<string>
using namespace std;

class whit
{
public:
	int row;
	char col;
	char pie;
}ww[16];

class blac
{
public:
	int row;
	char col;
	char pie;
}bb[16];

int main(void)
{
	char white[63],black[63];
	gets(white);
	gets(black);

	int x,y,z,r;

	int count_w=0;
	int count_b=0;
	const int length_w=strlen(white);
	const int length_b=strlen(black);

	for(x=7,y=0;x<length_w;)
		if(white[x]>='B' && white[x]<='R')
		{
			ww[y].pie=white[x];
			ww[y].col=white[x+1];
			ww[y].row=white[x+2]-'0';  //字符转数字
			y++;
			x+=4;
			count_w++;
		}
		else if(white[x]>='a' && white[x]<='h')
		{
			ww[y].pie='P';
			ww[y].col=white[x];
			ww[y].row=white[x+1]-'0';
			y++;
			x+=3;
		    count_w++;
		}
		else
			break;

		for(x=7,y=0;x<length_b;)
		if(black[x]>='B' && black[x]<='R')
		{
			bb[y].pie=black[x]+32;      //大写字母转换小写字母
			bb[y].col=black[x+1];
			bb[y].row=black[x+2]-'0';
			y++;
			x+=4;
			count_b++;
		}
		else if(black[x]>='a' && black[x]<='h')
		{
			bb[y].pie='p';
			bb[y].col=black[x];
			bb[y].row=black[x+1]-'0';
			y++;
			x+=3;
		    count_b++;
		}
		else
			break;

		char chess[9]['i'];

		memset(chess,':',sizeof(chess));

		for(x=1;x<=7;x+=2)
			for(y='a';y<='g';y+=2)
				chess[x][y]='.';
		for(x=2;x<=8;x+=2)
			for(y='b';y<='h';y+=2)
				chess[x][y]='.';

		for(x=0;x<count_w;x++)
			chess[9-ww[x].row][ww[x].col]=ww[x].pie;

		for(x=0;x<count_b;x++)
			chess[9-bb[x].row][bb[x].col]=bb[x].pie;

		cout<<"+---+---+---+---+---+---+---+---+"<<endl;
		
		for(x=1,r=2;x<=7;x+=2,r+=2)
		{
			cout<<'|';
			for(y='a',z='b';y<='g';y+=2,z+=2)
				cout<<"."<<chess[x][y]<<".|:"<<chess[x][z]<<":|";
			cout<<endl;
			cout<<"+---+---+---+---+---+---+---+---+"<<endl;
			cout<<'|';
			for(y='a',z='b';y<='g';y+=2,z+=2)
				cout<<":"<<chess[r][y]<<":|."<<chess[r][z]<<".|";
			cout<<endl;
			cout<<"+---+---+---+---+---+---+---+---+"<<endl;
		}

	return 0;
}