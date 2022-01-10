/* 
 * Problem: 线性规划与网络流24题 #20 深海机器人问题
 * Author: Guo Jiabao
 * Time: 2009.6.30 10:40
 * State: Solved
 * Memo: 最大费用最大流
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=20*20,MAXM=MAXN*6*2,INF=~0U>>1;
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
int N,M,S,T,EC,Ans,Costflow;
int dist[MAXN],ft[MAXN];
inline void addedge(int a,int b,int c,int v)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c; V[a]->v=v;
	ES[++EC].next = V[b]; V[b]=ES+EC; V[b]->t=a; V[b]->c=0; V[b]->v=-v;
	V[a]->op = V[b]; V[b]->op = V[a];
}
inline int Point(int x,int y)
{
	return x * (M + 1) + y + 1;
}
void init()
{
	int i,j,Ca,Cb,a,b,c;
	freopen("robo.in","r",stdin);
	freopen("robo.out","w",stdout);
	scanf("%d%d%d%d",&Ca,&Cb,&N,&M);
	S=0; T=(N+1)*(M+1)+1;
	for (i=1;i<=N+1;i++)
	{
		for (j=1;j<=M;j++)
		{
			scanf("%d",&c);
			a=Point(i-1,j-1),b=Point(i-1,j);
			addedge(a,b,1,c);
			addedge(a,b,INF,0);
		}
	}
	for (i=1;i<=M+1;i++)
	{
		for (j=1;j<=N;j++)
		{
			scanf("%d",&c);
			a=Point(j-1,i-1),b=Point(j,i-1);
			addedge(a,b,1,c);
			addedge(a,b,INF,0);
		}
	}
	for (i=1;i<=Ca;i++)
	{
		scanf("%d%d%d",&c,&a,&b);
		addedge(S,Point(a,b),c,0);
	}
	for (i=1;i<=Cb;i++)
	{
		scanf("%d%d%d",&c,&a,&b);
		addedge(Point(a,b),T,c,0);
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
int main()
{
	init();
	SPFAFlow();
	printf("%d\n",Costflow);
	return 0;
}
