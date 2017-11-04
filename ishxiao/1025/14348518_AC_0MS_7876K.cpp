//poj1025
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;
//每个人的状态：
#define STS_ENTER_BUILDING 1		//进入大楼
#define STS_LEAVE_BUILDING 2		//离开大楼
#define STS_IN_ROOM 3				//在房间里
#define STS_WAIT_ROOM 4				//在房间外等候
#define STS_WAIT_ELEVATOR 5			//等电梯
//每个房间的状态：
#define ROOM_BUSY 1					//房间里有人
#define ROOM_FREE 2					//房间里没人
class agent{
public:
	int sts; 									//当前状态
	int ctime; 			   						//当前时间
	int cfloor; 								//当前所在楼层 			
	int sen;									//优先级		
	int croom; 									//当前所在房间号
	int nroom; 									//下一个房间号
	int drooms[400]; 							//要去的房间
	int nrooms;									//要去的房间数目
	int stytime[400]; 							//每个房间要待的时间								
	string tracestr; 							//访问轨迹
	void initagent();							//初始化
	int arrange();								//行程安排函数1
	int arrange(int reqroom);					//行程安排函数2
	int arrange(int cuttime, int reqroom);		//行程安排函数3
	int waitele();								//等待电梯
	int transfer(int nInd);						//从一个房间到另一个房间
	int stayroom(int reqroom, int entertime);	//在房间里待着
	agent();									//构造函数
};
class room{
public:
	room();										//构造函数
	int req[30]; 								//要访问此房间的人
	int finished[30]; 							//完成访问此房间的人
	int ctime; 									//当前时间
	int sts; 									//当前状态
	int ftime; 									//下一次到达空闲的时间
};
class elevator{
public:
	elevator();									//构造函数			
	int btime[90000]; 							//不能进入的时间								 			
};
agent ag[30];
room ros[2000];
elevator ele[20];
int main(void)
{
	char ch, ctime[10];
	int nr, nt, nch, i, j = 0;
	cin >> ch;
	while (ch != '.')
	{
		nch = (int)ch - 64;
		ag[nch].sen = nch;
		cin >> ctime;
		ag[nch].ctime = ((int)ctime[0] - 48) * 36000 + ((int)ctime[1] - 48) * 3600 + ((int)ctime[3] - 48) * 600 +
			((int)ctime[4] - 48) * 60 + ((int)ctime[6] - 48) * 10 + ((int)ctime[7] - 48);
		cin >> nr;
		j = 0;
		while (nr != 0)
		{
			cin >> nt;
			ag[nch].drooms[j++] = nr;
			ag[nch].stytime[nr] = nt;
			ros[nr].req[nch] = 1;
			cin >> nr;
		}
		ag[nch].nrooms = j;
		ag[nch].initagent();
		cin >> ch;
	}
	for (i = 1; i <= 26; i++)
	{
		if (ag[i].sen != 0 && ag[i].sts != STS_LEAVE_BUILDING)
		{
			ag[i].arrange();
		}
	}
	for (i = 1; i <= 26; i++)
	{
		if (ag[i].sts != -1)
		{
			cout << char(i + 64) << endl << ag[i].tracestr << endl;
		}
	}
	return 0;
}
int agent::arrange()
{
	int i;
	if (sts == STS_WAIT_ELEVATOR) waitele();
	for (i = nroom; i<nrooms; i++)
	{
		arrange(drooms[i]);
		transfer(i);
	}
	return 0;
}
int agent::transfer(int nInd)
{
	int nt, nf;
	char str[100];
	if (nInd == nrooms - 1)
	{
		if (cfloor > 1)
		{
			nt = ctime + 10;
			sprintf(str, "%02d:%02d:%02d %02d:%02d:%02d Transfer from room %04d to elevator\n",
				ctime / 3600, (ctime / 60) % 60, ctime % 60, nt / 3600, (nt / 60) % 60, nt % 60, drooms[nroom]);
			tracestr += str;
			ctime = nt;
			nt = (5 - ctime % 5) % 5 + ctime;
			while (ele[cfloor].btime[nt] != 0) nt += 5;
			if (nt != ctime)
			{
				sprintf(str, "%02d:%02d:%02d %02d:%02d:%02d Waiting in elevator queue\n",
					ctime / 3600, (ctime / 60) % 60, ctime % 60, nt / 3600, (nt / 60) % 60, nt % 60);
				tracestr += str;
				ctime = nt;
			}
			ele[cfloor].btime[nt] = 1;
			nf = (cfloor - 1) * 30 + ctime;
			sprintf(str, "%02d:%02d:%02d %02d:%02d:%02d Stay in elevator\n", ctime / 3600, (ctime / 60) % 60, ctime % 60,
				nf / 3600, (nf / 60) % 60, nf % 60);
			tracestr += str;
			ctime = nf;
		}
		nt = ctime + 30;
		sprintf(str, "%02d:%02d:%02d %02d:%02d:%02d Exit\n", ctime / 3600, (ctime / 60) % 60, ctime % 60,
			nt / 3600, (nt / 60) % 60, nt % 60);
		tracestr += str;
		sts = STS_LEAVE_BUILDING;
		ctime = nt;
		return 0;
	}
	nroom = nInd + 1;
	if (drooms[nroom] / 100 > drooms[nInd] / 100) waitele();
	else
	{
		nt = ctime + 10;
		sprintf(str, "%02d:%02d:%02d %02d:%02d:%02d Transfer from room %04d to room %04d\n",
			ctime / 3600, (ctime / 60) % 60, ctime % 60, nt / 3600, (nt / 60) % 60, nt % 60, drooms[nInd], drooms[nroom]);
		tracestr += str;
		ctime = nt;
	}
	return 0;
}
int agent::waitele()
{
	int nt, nf;
	char str[100];
	if (nroom != 0)
	{
		nt = ctime + 10;
		sprintf(str, "%02d:%02d:%02d %02d:%02d:%02d Transfer from room %04d to elevator\n",
			ctime / 3600, (ctime / 60) % 60, ctime % 60, nt / 3600, (nt / 60) % 60, nt % 60, drooms[nroom - 1]);
		tracestr += str;
		ctime = nt;
	}
	nt = (5 - ctime % 5) % 5 + ctime;
	while (ele[cfloor].btime[nt] != 0) nt += 5;
	if (nt != ctime)
	{
		sprintf(str, "%02d:%02d:%02d %02d:%02d:%02d Waiting in elevator queue\n",
			ctime / 3600, (ctime / 60) % 60, ctime % 60, nt / 3600, (nt / 60) % 60, nt % 60);
		tracestr += str;
		ctime = nt;
	}
	ele[cfloor].btime[nt] = 1;
	nf = (drooms[nroom] / 100 - cfloor) * 30 + ctime;
	sprintf(str, "%02d:%02d:%02d %02d:%02d:%02d Stay in elevator\n", ctime / 3600, (ctime / 60) % 60, ctime % 60,
		nf / 3600, (nf / 60) % 60, nf % 60);
	tracestr += str;
	ctime = nf + 10;
	sprintf(str, "%02d:%02d:%02d %02d:%02d:%02d Transfer from elevator to room %04d\n",
		nf / 3600, (nf / 60) % 60, nf % 60, ctime / 3600, (ctime / 60) % 60, ctime % 60, drooms[nroom]);
	tracestr += str;
	cfloor = drooms[nroom] / 100;
	sts = STS_WAIT_ROOM;
	return 0;
}
int agent::arrange(int reqroom)
{
	int i, qlist[30], nq = 0, pro[30], flg = 0, tmp1, tmp2, j = 0, k, minp, mini, tmp;
	memset(qlist, 0, sizeof(qlist));
	memset(pro, 0, sizeof(pro));
	if (ros[reqroom].ftime >= ctime)
	{
		stayroom(reqroom, ros[reqroom].ftime);
		return 0;
	}
	for (i = sen + 1; i <= 26; i++)
	{
		if (ros[reqroom].req[i] != 0 && ros[reqroom].finished[i] == 0 && ag[i].ctime<ctime)
		{
			tmp = ag[i].arrange(ctime, reqroom);
			if (tmp != 0)
			{
				qlist[j] = tmp;
				pro[j] = i;
				j++;
			}
		}
	}
	while (flg == 0)
	{
		flg = 1;
		for (i = 0; i<j - 1; i++)
		{
			if (qlist[i]>qlist[i + 1] || (qlist[i] == qlist[i + 1] && pro[i]>pro[i + 1]))
			{
				flg = 0;
				tmp1 = qlist[i];
				qlist[i] = qlist[i + 1];
				qlist[i + 1] = tmp1;
				tmp2 = pro[i];
				pro[i] = pro[i + 1];
				pro[i + 1] = tmp2;
			}
		}
	}
	if (qlist[0] >= ctime || j == 0)
	{
		stayroom(reqroom, ctime);
		return 0;
	}
	i = 0;
	nq = i;
	while (ctime>ros[reqroom].ftime)
	{
		while (ros[reqroom].finished[pro[nq]] != 0 && nq<j) nq++;
		if (nq == j) break;
		if (qlist[nq] > ros[reqroom].ftime)
		{
			ag[pro[nq]].stayroom(reqroom, qlist[nq]);
			ag[pro[nq]].transfer(ag[pro[nq]].nroom);
			nq++;
			continue;
		}
		i = nq;
		while (qlist[i] <= ros[reqroom].ftime) i++;
		minp = pro[nq];
		mini = nq;
		for (k = nq; k<i; k++)
		{
			if (pro[k]<minp && ros[reqroom].finished[pro[k]] == 0) { minp = pro[k]; mini = k; }
		}
		ag[minp].stayroom(reqroom, ros[reqroom].ftime);
		ag[minp].transfer(ag[minp].nroom);

	}
	if (ctime <= ros[reqroom].ftime)
	{
		stayroom(reqroom, ros[reqroom].ftime);
	}
	else
	{
		stayroom(reqroom, ctime);
	}
	return 0;
}
int agent::arrange(int cuttime, int reqroom)
{

	int i;
	if (nroom == 0 && drooms[0] / 100>1 && sts == STS_WAIT_ELEVATOR)
	{
		waitele();
	}
	for (i = nroom; drooms[i]<reqroom && ctime<cuttime; i++)
	{
		arrange(drooms[i]);
		transfer(i);
	}
	if (ctime >= cuttime) return 0;
	else return ctime;
}
int agent::stayroom(int reqroom, int entertime)
{
	int nt;
	char str[100];
	nt = entertime + stytime[reqroom];
	if (entertime > ctime)
	{
		sprintf(str, "%02d:%02d:%02d %02d:%02d:%02d Waiting in front of room %04d\n",
			ctime / 3600, (ctime / 60) % 60, ctime % 60, entertime / 3600, (entertime / 60) % 60, entertime % 60, reqroom);
		tracestr += str;
		ctime = entertime;
	}
	sprintf(str, "%02d:%02d:%02d %02d:%02d:%02d Stay in room %04d\n", ctime / 3600, (ctime / 60) % 60, ctime % 60,
		nt / 3600, (nt / 60) % 60, nt % 60, reqroom);
	tracestr += str;
	ctime = nt;
	ros[reqroom].finished[sen] = 1;
	ros[reqroom].ftime = ctime;
	return 0;
}
agent::agent()
{
	sts = -1;
	ctime = 0;
	cfloor = 1;
	sen = 0;
	croom = 0;
	nroom = 0;
	nrooms = 0;
	memset(drooms, 0, sizeof(drooms));
	memset(stytime, 0, sizeof(stytime));
	tracestr = "";
}
void agent::initagent()
{
	char str[100];
	cfloor = 1;
	if (drooms[0] <= 0)
	{
		sts = STS_LEAVE_BUILDING;
		return;
	}
	nroom = 0;
	sprintf(str, "%02d:%02d:%02d", ctime / 3600, (ctime / 60) % 60, ctime % 60);
	tracestr += str;
	ctime += 30;
	sprintf(str, " %02d:%02d:%02d Entry\n", ctime / 3600, (ctime / 60) % 60, ctime % 60);
	tracestr += str;
	if (drooms[0] / 100 > 1) sts = STS_WAIT_ELEVATOR;
	else sts = STS_WAIT_ROOM;
}
room::room()
{
	memset(req, 0, sizeof(req));
	memset(finished, 0, sizeof(finished));
	ctime = 0;
	sts = ROOM_FREE;
	ftime = 0;
}
elevator::elevator()
{
	memset(btime, 0, sizeof(btime));
}