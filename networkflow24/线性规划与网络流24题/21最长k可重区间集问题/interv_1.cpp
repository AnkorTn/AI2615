/* 
 * Problem: 线性规划与网络流24题 #21 最长k可重区间集问题
 * Author: Guo Jiabao
 * Time: 2009.6.30 12:32
 * State: Solved
 * Memo: 最大费用最大流
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=501*2,MAXM=(MAXN*MAXN/4+MAXN*3)*2,INF=~0U>>1;
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
struct interval
{
	int a,b;
}I[MAXN];
struct edge
{
	edge *next,*op;
	int t,c,v;
}*V[MAXN],ES[MAXM],*fe[MAXN],*P[MAXN];
int N,K,S,SS,T,EC,Ans,Costflow;
int dist[MAXN],ft[MAXN];
inline void addedge(int a,int b,int c,int v)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c; V[a]->v=v;
	ES[++EC].next = V[b]; V[b]=ES+EC; V[b]->t=a; V[b]->c=0; V[b]->v=-v;
	V[a]->op = V[b]; V[b]->op = V[a];
	//printf("(%d,%d) c=%d v=%d\n",a,b,c,v);
}
inline int cmp(const void *a,const void *b)
{
	return ((interval *)a)->a - ((interval *)b)->a;
}
void init()
{
	int i,j;
	freopen("interv.in","r",stdin);
	freopen("interv.out","w",stdout);
	scanf("%d%d",&N,&K);
	S=0; T=N+N+2; SS=T-1;
	addedge(S,SS,K,0);
	for (i=1;i<=N;i++)
	{
		scanf("%d%d",&I[i].a,&I[i].b);
		addedge(SS,i,1,0);
		addedge(i+N,T,1,0);
	}
	qsort(I+1,N,sizeof(I[0]),cmp);
	for (i=1;i<=N;i++)
	{
		addedge(i,i+N,1,I[i].b-I[i].a);
		P[i] = ES+EC-1;
		for (j=i+1;j<=N;j++)
			if (I[j].a>=I[i].b)
				addedge(i+N,j,1,0);
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
	/*for (int i=1;i<=N;i++)
		if (P[i]->c==0)
			printf("%d %d\n",I[i].a,I[i].b);*/
	return 0;
}
