//1021

#include<stdio.h>
#include<memory.h>

class Cluster
{
public:
	Cluster(int width, int height):width(width),height(height)
	{
		grid = new bool[width*height];
		memset(grid,0,width*height*sizeof(bool));
	}
	~Cluster(){delete[]grid;}
	bool operator == (Cluster & obj);
	bool *grid;
	int width;
	int height;
private:
	void HMirror()
	{
		bool temp;
		for(int i=0;i<height;i++)
			for(int j=0;j<width/2;j++)
				temp=grid[i*width+j],grid[i*width+j]=grid[i*width+width-j-1],grid[i*width+width-j-1]=temp;
	}
	void VMirror()
	{
		bool temp;
		for(int j=0;j<width;j++)
			for(int i=0;i<height/2;i++)
				temp=grid[i*width+j],grid[i*width+j]=grid[(height-1-i)*width+j],grid[(height-1-i)*width+j]=temp;
	}
	void Transpose()
	{
		int temp;
		bool *buf = new bool[width*height];
		memcpy(buf,grid,width*height*sizeof(bool));
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
				grid[j*height+i]=buf[i*width+j];
		delete[]buf;
		temp=width;
		width=height;
		height=temp;
	}
};

bool Cluster::operator ==(Cluster & obj)
{
	if(!(height==obj.height && width==obj.width || height==obj.width && width==obj.height))
		return false;
	for(int k=0;k<2;k++)
	{
		if(height!=width && height==obj.width && width==obj.height)
			Transpose();
		if(0==memcmp(grid,obj.grid,height*width*sizeof(bool)))
			return true;
		HMirror();
		if(0==memcmp(grid,obj.grid,height*width*sizeof(bool)))
			return true;
		VMirror();
		if(0==memcmp(grid,obj.grid,height*width*sizeof(bool)))
			return true;
		HMirror();
		if(0==memcmp(grid,obj.grid,height*width*sizeof(bool)))
			return true;
		if(height!=width)break;
		Transpose();
	}
	return false;
}

int top,bottom,left,right,W,H;

void bfs(unsigned char G[][100], int i, int j)
{
	G[i][j]=2;
	if(j>0&&G[i][j-1]==1)
		bfs(G,i,j-1),left=j-1<left?j-1:left;
	if(j<W-1&&G[i][j+1]==1)
		bfs(G,i,j+1),right=j+1>right?j+1:right;
	if(i>0&&G[i-1][j]==1)
		bfs(G,i-1,j),top=i-1<top?i-1:top;
	if(i<H-1&&G[i+1][j]==1)
		bfs(G,i+1,j),bottom=i+1>bottom?i+1:bottom;
}

int main()
{
	int t,n,i,j,k,x,y,nc[2];
	unsigned char G[100][100];
	Cluster *clusters[2][5000];
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&W,&H,&n);
		for(k=0;k<2;k++)
		{
			for(i=0;i<H;i++)
				for(j=0;j<W;j++)
					G[i][j]=0;
			for(j=0;j<n;j++)
				scanf("%d%d",&x,&y),G[y][x]=1;
			nc[k]=0;
			for(i=0;i<H;i++)
				for(j=0;j<W;j++)
					if(G[i][j]!=1)
						continue;
					else
					{
						left=right=j;
						top=bottom=i;
						bfs(G,i,j);
						clusters[k][nc[k]] = new Cluster(right-left+1,bottom-top+1);
						for(int ii=top;ii<=bottom;ii++)
							for(int jj=left;jj<=right;jj++)
								if(G[ii][jj]==2)
									clusters[k][nc[k]]->grid[(ii-top)*(right-left+1)+jj-left]=true,G[ii][jj]=3;
						nc[k]++;
					}
		}
		for(i=0;i<nc[0];i++)
		{
			for(j=0;j<nc[1];j++)
			{
				if(clusters[1][j]==NULL)continue;
				if(*clusters[0][i]==*clusters[1][j])
				{
					delete clusters[1][j];
					clusters[1][j]=NULL;
					break;
				}
			}
			if(j==nc[1])break;
		}
		if(i==nc[0])printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
