#pragma GCC optimize(3)
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
using namespace std;

const int N=1e4+10;
const int M=30;
const int INF=1e6;
const double eps=1e-6;
double A[M][M],B[M][M]; 
double s[M];
int p[M];
struct link
{
	int top=1,fi[N],to[N],la[N],ne[N],cap[N],cur[N];
	double cost[N];
	void clear()
	{
		top=1;
		memset(fi,0,sizeof fi);
		memset(to,0,sizeof to);
		memset(la,0,sizeof la);
		memset(ne,0,sizeof ne);
		memset(cap,0,sizeof cap);
		memset(cur,0,sizeof cur);
		memset(cost,0,sizeof cost);
	}
	void add(int x,int y,int z,double c)
	{
		top++,to[top]=y;cap[top]=z,cost[top]=c;
		if(fi[x]==0)fi[x]=top;else ne[la[x]]=top;
		la[x]=top;
	}
	void adde(int x,int y,int z,int c)
	{
		add(x,y,z,c);
		add(y,x,0,-c);
	}
}L;
int S,T;
double TOTcost;
int TOTflow,vis[N];
double dis[N];
int ans[N][M];
queue<int> q; 
int SPFA()
{
	for(int i=1;i<=T;i++)dis[i]=INF,vis[i]=0;
	dis[T]=0;
	while(!q.empty())q.pop();
	q.push(T);
	while(!q.empty())
	{
		int now=q.front();
		q.pop();vis[now]=0;
		for(int i=L.fi[now];i;i=L.ne[i])
		if(L.cap[i^1]>0)
		if(dis[L.to[i]]>dis[now]+L.cost[i^1])
		{
			dis[L.to[i]]=dis[now]+L.cost[i^1];
			if(!vis[L.to[i]])
				q.push(L.to[i]),vis[L.to[i]]=1;
		}
	}
	return fabs(dis[S]-INF)>eps;
}
int DFS(int now,int maxflow)
{
	vis[now]=1;
	if(now==T)return maxflow;
	int tot=0;
	for(int i=L.cur[now];i;i=L.ne[i],L.cur[now]=i)
	if(L.cap[i]>0&&fabs(dis[now]-dis[L.to[i]]-L.cost[i])<eps&&!vis[L.to[i]])
	{
		int del=DFS(L.to[i],min(maxflow,L.cap[i]));
		tot+=del;TOTcost+=del*L.cost[i];maxflow-=del;
		L.cap[i]-=del;
		L.cap[i^1]+=del;
	}
	return tot;
}
double calc(int* p)
{
	double re=0;
	for(int i=1;i<=28;i++)
	{
		for(int j=1;j<=28;j++)
			re+=s[i]*s[j]*(A[i][j]-B[p[i]][p[j]])*(A[i][j]-B[p[i]][p[j]]);
	}
	return re;
}
int main()
{
	srand(233);
	freopen("A.txt","r",stdin);
	for(int i=1;i<=28;i++)
	{
		for(int j=1;j<=28;j++)
		scanf("%lf",&A[i][j]);
	}
	for(int i=1;i<=28;i++)
	{
		scanf("%lf",&s[i]);
		s[i]=1.0;
		p[i]=i;
	}
	freopen("B.txt","r",stdin);
	for(int i=1;i<=28;i++)
	{
		for(int j=1;j<=28;j++)
		scanf("%lf",&B[i][j]);
	}
	
	int cas=0; 
	for(int rou=1;rou<=40;rou++)
	{
		random_shuffle(p+1,p+1+28);
		for(int ti=1;ti<=50;ti++)
		{
		L.clear();
		S=2*28+1,T=S+1;
		for(int i=1;i<=28;i++)
		{
			for(int j=1;j<=28;j++)
			{
				double C=0;
				for(int k=1;k<=28;k++)if(i!=k)C+=s[i]*s[k]*(A[i][k]-B[j][p[k]])*(A[i][k]-B[j][p[k]]);
				L.adde(i,j+28,1,C);
			}
			L.adde(S,i,1,0);
			L.adde(i+28,T,1,0);
		}
		TOTcost=0;
		TOTflow=0;
		while(SPFA())
		{
			for(int i=1;i<=T;i++)vis[i]=0,L.cur[i]=L.fi[i];
			TOTflow+=DFS(S,INF);
		}
		cas++;
		for(int i=1;i<=28;i++)
		{
			for(int j=L.fi[i];j;j=L.ne[j])
			if(L.cap[j]==0&&(L.to[j]>28)&&(L.to[j]<=28*2))
			{
				p[i]=L.to[j]-28;
			}
			ans[cas][i]=p[i];
		}
	}
	}
	
	double mn=1e9;
	int ans1;
	for(int i=1;i<=cas;i++)
	{
//		cout<<calc(ans[i])<<endl;
		if(calc(ans[i])<mn)
		{
			mn=calc(ans[i]);
			ans1=i;
		}
	}
	freopen("plan.txt","w",stdout);
	char out[4][7];
	for(int i=1;i<=26;i++)
	{
		out[(ans[ans1][i]-1)/7][(ans[ans1][i]-1)%7]='a'+i-1;
	}
	out[(ans[ans1][27]-1)/7][(ans[ans1][27]-1)%7]=' ';
	out[(ans[ans1][28]-1)/7][(ans[ans1][28]-1)%7]='-';
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<7;j++)putchar(out[i][j]);
		puts("");
	}
	return 0;
 } 
