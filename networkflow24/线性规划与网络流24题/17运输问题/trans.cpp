/* 
 * Problem: 线性规划与网络流24题 #17 运输问题
 * Author: Guo Jiabao
 * Time: 2009.6.29 17:42
 * State: Solved
 * Memo: 费用流
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=102*2,MAXM=MAXN*MAXN*2,INF=~0U>>1;
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
int Sa[MAXN],Sb[MAXN],Sc[MAXN][MAXN],dist[MAXN],ft[MAXN];
inline void addedge(int a,int b,int c,int v)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c; V[a]->v=v;
	ES[++EC].next = V[b]; V[b]=ES+EC; V[b]->t=a; V[b]->c=0; V[b]->v=-v;
	V[a]->op = V[b]; V[b]->op = V[a];
}
void init()
{
	int i,j;
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	scanf("%d%d",&M,&N);
	S=0; T=M+N+1;
	for (i=1;i<=M;i++)
		scanf("%d",&Sa[i]);
	for (i=1;i<=N;i++)
		scanf("%d",&Sb[i]);
	for (i=1;i<=M;i++)
		for (j=1;j<=N;j++)
			scanf("%d",&Sc[i][j]);
}
bool SPFA()
{
	int i,j;
	for (i=S;i<=T;i++)
		dist[i]=INF;
	dist[S]=0;
	Q.ins(S);
	while (Q.size)
	{
		i=Q.pop();
		for (edge *e=V[i];e;e=e->next)
		{
			j=e->t;
			if (e->c && dist[i] + e->v < dist[j])
			{
				dist[j] = dist[i] + e->v;
				ft[j] = i;
				fe[j] = e;
				if (!Q.inq[j])
					Q.ins(j);
			}
		}
	}
	return dist[T]!=INF;
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
void solve()
{
	int i,j;
	for (i=1;i<=M;i++)
		addedge(S,i,Sa[i],0);
	for (i=1;i<=N;i++)
		addedge(i+M,T,Sb[i],0);
	for (i=1;i<=M;i++)
		for (j=1;j<=N;j++)
			addedge(i,j+M,INF,Sc[i][j]);
	SPFAFlow();
	printf("%d\n",Costflow);
	memset(V,0,sizeof(V));
	EC=-1;Costflow=0;
	for (i=1;i<=M;i++)
		addedge(S,i,Sa[i],0);
	for (i=1;i<=N;i++)
		addedge(i+M,T,Sb[i],0);
	for (i=1;i<=M;i++)
		for (j=1;j<=N;j++)
			addedge(i,j+M,INF,-Sc[i][j]);
	SPFAFlow();
	printf("%d\n",-Costflow);
}
int main()
{
	init();
	solve();
	return 0;
}
