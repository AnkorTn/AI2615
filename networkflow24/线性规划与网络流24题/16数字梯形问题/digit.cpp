/* 
 * Problem: 线性规划与网络流24题 #16 digit
 * Author: Guo Jiabao
 * Time: 2009.6.29 16:38
 * State: Solved
 * Memo: 最大费用最大流
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXL=41,MAXN=1001*2,MAXM=MAXN*2*2,INF=~0U>>1;
struct Queue
{
	int Q[MAXN],head,tail,size;
	bool inq[MAXN];
	void init()
	{
		memset(inq,0,sizeof(inq));
		head = size =0; tail = -1;
	}
	void ins(int p)
	{
		size++;
		if (++tail == MAXN) tail = 0;
		Q[tail] = p;
		inq[p]=true;
	}
	int pop()
	{
		size--;
		int p=Q[head];
		if (++head == MAXN) head = 0;
		inq[p]=false;
		return p;
	}
}Q;
struct edge
{
	edge *next,*op;
	int t,c,v;
}*V[MAXN],ES[MAXM],*fe[MAXN];
int N,M,C,S,T,EC,Ans,Costflow;
int Poi[MAXL][MAXL],Value[MAXN],dist[MAXN],ft[MAXN];
inline void addedge(int a,int b,int c,int v)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c; V[a]->v=v;
	ES[++EC].next = V[b]; V[b]=ES+EC; V[b]->t=a; V[b]->c=0; V[b]->v=-v;
	V[a]->op = V[b]; V[b]->op = V[a];
}
void init()
{
	int i,j;
	freopen("digit.in","r",stdin);
	freopen("digit.out","w",stdout);
	scanf("%d%d",&M,&N);
	for (i=1;i<=N;i++)
		for (j=1;j<=M+i-1;j++)
		{
			Poi[i][j] = ++C;
			scanf("%d",&Value[C]);
		}
}
bool SPFA()
{
	int i,j;
	for (i=S;i<=T;i++)
		dist[i]=-INF;
	dist[S]=0;
	Q.ins(S);
	while (Q.size)
	{
		i=Q.pop();
		for (edge *e=V[i];e;e=e->next)
		{
			j=e->t;
			if (e->c && dist[i] + e->v > dist[j])
			{
				dist[j] = dist[i] + e->v;
				ft[j] = i;
				fe[j] = e;
				if (!Q.inq[j])
					Q.ins(j);
			}
		}
	}
	return dist[T]!=-INF;
}
void Augment()
{
	int i,delta=INF;
	for (i=T;i!=S;i=ft[i])
		if (fe[i]->c < delta)
			delta = fe[i]->c;
	for (i=T;i!=S;i=ft[i])
	{
		fe[i]->c -= delta;
		fe[i]->op->c += delta;
		Costflow += fe[i]->v * delta;
	}
}
void SPFAFlow()
{
	Q.init();
	while (SPFA())
		Augment();
}
void solve1()
{
	int i,j;
	S=0;T=C+C+1;EC=-1;
	Costflow = 0;
	memset(V,0,sizeof(V));
	for (i=1;i<=C;i++)
		addedge(i,i+C,1,Value[i]);
	for (i=1;i<=M;i++)
		addedge(S,Poi[1][i],1,0);
	for (i=1;i<=M+N-1;i++)
		addedge(Poi[N][i]+C,T,1,0);
	for (i=1;i<N;i++)
		for (j=1;j<=M+i-1;j++)
		{
			addedge(Poi[i][j]+C,Poi[i+1][j],1,0);
			addedge(Poi[i][j]+C,Poi[i+1][j+1],1,0);
		}
	SPFAFlow();
}
void solve2()
{
	int i,j;
	S=0;T=C+1;EC=-1;
	Costflow = 0;
	memset(V,0,sizeof(V));
	for (i=1;i<=M;i++)
		addedge(S,Poi[1][i],1,0);
	for (i=1;i<=M+N-1;i++)
		addedge(Poi[N][i],T,INF,Value[Poi[N][i]]);
	for (i=1;i<N;i++)
		for (j=1;j<=M+i-1;j++)
		{
			addedge(Poi[i][j],Poi[i+1][j],1,Value[Poi[i][j]]);
			addedge(Poi[i][j],Poi[i+1][j+1],1,Value[Poi[i][j]]);
		}
	SPFAFlow();
}
void solve3()
{
	int i,j;
	S=0;T=C+1;EC=-1;
	Costflow = 0;
	memset(V,0,sizeof(V));
	for (i=1;i<=M;i++)
		addedge(S,Poi[1][i],1,0);
	for (i=1;i<=M+N-1;i++)
		addedge(Poi[N][i],T,INF,Value[Poi[N][i]]);
	for (i=1;i<N;i++)
		for (j=1;j<=M+i-1;j++)
		{
			addedge(Poi[i][j],Poi[i+1][j],INF,Value[Poi[i][j]]);
			addedge(Poi[i][j],Poi[i+1][j+1],INF,Value[Poi[i][j]]);
		}
	SPFAFlow();
}
void solve()
{
	solve1();
	printf("%d\n",Costflow);
	solve2();
	printf("%d\n",Costflow);
	solve3();
	printf("%d\n",Costflow);
}
int main()
{
	init();
	solve();
	return 0;
}
