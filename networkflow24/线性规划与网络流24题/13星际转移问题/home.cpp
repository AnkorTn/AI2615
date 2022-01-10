/* 
 * Problem: 线性规划与网络流24题 #13 星际转移问题
 * Author: Guo Jiabao
 * Time: 2009.6.28 19:36
 * State: Solved
 * Memo: 分层图网络最大流 枚举答案
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=20*50,MAXM=MAXN*20,INF=~0U>>1;
struct UFS
{
	int f[MAXN];
	void init(int N)
	{
		for (int i=1;i<=N;i++)
			f[i]=i;
	}
	int getroot(int a)
	{
		int r=a,t;
		while (r!=f[r]) r=f[r];
		while (a!=r)
		{
			t=f[a];
			f[a]=r;
			a=t;
		}
		return r;
	}
	void merge(int a,int b)
	{
		f[getroot(a)]=getroot(b);
	}
	bool judge(int a,int b)
	{
		return getroot(a)==getroot(b);
	}
}U;
struct ship
{
	int c,len,p[21];
}Ship[21];
struct edge
{
	edge *next,*op;
	int t,c;
}*V[MAXN],*P[MAXN],ES[MAXM],*Stae[MAXN];
int N,M,K,S,T,EC,Ans,Maxflow;
int Lv[MAXN],Stap[MAXN];
inline void addedge(int a,int b,int c)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c;
	ES[++EC].next = V[b]; V[b]=ES+EC; V[b]->t=a; V[b]->c=0;
	V[a]->op = V[b]; V[b]->op = V[a];
}
void init()
{
	int i,j,c;
	freopen("home.in","r",stdin);
	freopen("home.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	S=0; T=MAXN-1;
	U.init(N+2);
	for (i=1;i<=M;i++)
	{
		scanf("%d%d",&Ship[i].c,&Ship[i].len);
		for (j=1;j<=Ship[i].len;j++)
		{
			scanf("%d",&c);
			if (c==0)
				c=N+2;
			if (c==-1)
				c=N+1;
			Ship[i].p[j] = c;
			if (j>1)
				U.merge(Ship[i].p[j-1],c);
		}
	}
	N+=2;
}
bool Dinic_Label()
{
	int head,tail,i,j;
	Stap[head=tail=0]=S;
	memset(Lv,-1,sizeof(Lv));
	Lv[S]=0;
	while (head<=tail)
	{
		i=Stap[head++];
		for (edge *e=V[i];e;e=e->next)
		{
			j=e->t;
			if (e->c && Lv[j]==-1)
			{
				Lv[j] = Lv[i]+1;
				if (j==T)
					return true;
				Stap[++tail] = j;
			}
		}
	}
	return false;
}
void Dinic_Augment()
{
	int i,j,delta,Stop;
	for (i=S;i<=T;i++)
		P[i] = V[i];
	Stap[Stop=1]=S;
	while (Stop)
	{
		i=Stap[Stop];
		if (i!=T)
		{
			for (;P[i];P[i]=P[i]->next)
				if (P[i]->c && Lv[i] + 1 == Lv[j=P[i]->t])
					break;
			if (P[i])
			{
				Stap[++Stop] = j;
				Stae[Stop] = P[i];
			}
			else
				Stop--,Lv[i]=-1;
		}
		else
		{
			delta = INF;
			for (i=Stop;i>=2;i--)
				if (Stae[i]->c < delta)
					delta = Stae[i]->c;
			Maxflow += delta;
			for (i=Stop;i>=2;i--)
			{
				Stae[i]->c -= delta;
				Stae[i]->op->c += delta;
				if (Stae[i]->c==0)
					Stop = i-1;
			}
		}
	}
}
void Dinic()
{
	while (Dinic_Label())
		Dinic_Augment();
}
inline int Point(int p,int d)
{
	return d * N + p;
}
void solve()
{
	int Day,i,a,b;
	addedge(S,Point(N,0),INF);
	addedge(Point(N-1,0),T,INF);
	for (Day = 1;Maxflow < K;Day++)
	{
		addedge(S,Point(N,Day),INF);
		addedge(Point(N-1,Day),T,INF);
		for (i=1;i<=N;i++)
			addedge(Point(i,Day-1),Point(i,Day),INF);
		for (i=1;i<=M;i++)
		{
			a = Ship[i].p[ (Day - 1) % Ship[i].len + 1 ];
			b = Ship[i].p[ Day % Ship[i].len + 1 ];
			addedge(Point(a,Day-1),Point(b,Day),Ship[i].c);
		}
		Dinic();
	}
	Ans = Day - 1;
}
int main()
{
	init();
	if (U.judge(N-1,N))
		solve();
	else
		Ans = 0;
	printf("%d\n",Ans);
	return 0;
}
