//1087
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
const int inf=10000;
using namespace std;
short cap[420][420];
short flow[420][420];
int n_rec,n_item,n_adp;

int id_counter;
int id_adp_s;
map<string,int> dict;
int path_find_index[1000];
vector<int> found_path;
int v_count;

int _find_path(int from)
{
	if (path_find_index[from]!=0) return 0;
	path_find_index[from]=1;
	int i;
	for (i=1;i<=v_count;i++) 
	{
		if (cap[from][i]-flow[from][i]>0) 
		{
			if (i==2) 
			{
				found_path.push_back(2);
				found_path.push_back(from);
				return 1;
			}
			if (_find_path(i))
			{
				found_path.push_back(from);
				return 1;
			}
		}
	}
	path_find_index[from]=2;
	return 0;
}

int find_path()
{
	int i;
	for (i=0;i<=v_count;i++) path_find_index[i]=0;
	found_path.clear();
	return _find_path(1);
}

int remain(int ids,int ide)
{
	return cap[ids][ide]-flow[ids][ide];
}


int plug()
{
	id_counter=2;
	dict.clear();
	cin>>n_rec;

	//prepare the max flow algorithm
	int i;
	 int j;
	 for (i=310;i>0;i--) for (j=310;j>0;j--)
	 {
		 cap[i][j]=flow[i][j]=0;
	 }

	//read receptacles
	for (i=1;i<=n_rec;i++)
	{
		pair<string,int> temp;
		cin>>temp.first;
		map<string,int>::iterator pDict;
		if ((pDict=dict.find(temp.first))==dict.end())
		{			
			temp.second=++id_counter;
			dict.insert(temp);
		}
		else temp=*pDict;
		++cap[1][temp.second];
	}
	//read items
	cin>>n_item;
	for (i=1;i<=n_item;i++)
	{
		pair<string,int> temp;
		cin>>temp.first;
		cin>>temp.first;
		map<string,int>::iterator pDict;
		if ((pDict=dict.find(temp.first))==dict.end())
		{
			temp.second=++id_counter;
			dict.insert(temp);
		}
		else temp=*pDict;
		++cap[temp.second][2];
	}
	
	//read adps
	cin>>n_adp;
	for (i=1;i<=n_adp;i++)
	{
		int idr,idp;
		pair<string,int> temp;
		cin>>temp.first;
		map<string,int>::iterator pDict;
		if ((pDict=dict.find(temp.first))==dict.end())
		{
			temp.second=++id_counter;
			dict.insert(temp);
		}
		else temp=*pDict;
		idr=temp.second;
		cin>>temp.first;
		if ((pDict=dict.find(temp.first))==dict.end())
		{
			temp.second=++id_counter;
			dict.insert(temp);
		}
		else temp=*pDict;
		idp=temp.second;
		cap[idp][idr]=inf;
	}


	//max flow
	v_count=id_counter;
	while(find_path())
	{
		int len=found_path.end()-found_path.begin();
		int i;
		int cf=remain(found_path[len-1],found_path[len-2]);
		for(i=len-2;i>=1;i--)
		{
			int temp=remain(found_path[i],found_path[i-1]);
			if (temp<cf) cf=temp;
		}
		for(i=len-1;i>=1;i--)
		{
			int ids,ide;
			ids=found_path[i];
			ide=found_path[i-1];
			flow[ids][ide]+=cf;
			flow[ide][ids]-=cf;
		}
	}

	int result=0;
	for (i=1;i<=v_count;i++) result+=flow[1][i];
	cout<<n_item-result<<endl;	
	return 0;
}

int main()
{
	try
	{
		plug();
	}
	catch(exception e){cout<<e.what();}
}
