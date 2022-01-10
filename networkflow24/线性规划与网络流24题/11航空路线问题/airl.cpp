/* 
 * Problem: 线性规划与网络流24题 #11 航空路线问题
 * Author: Guo Jiabao
 * Time: 2009.6.28 16:54
 * State: Solved
 * Memo: 最大费用最大流
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=1001,MAXM=MAXN*4*2,INF=~0U>>1;
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
char City[MAXN][16];
int N,M,S,T,EC,Ans,Costflow;
int dist[MAXN],ft[MAXN];
inline void addedge(int a,int b,int c,int v)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c; V[a]->v=v;
	ES[++EC].next = V[b]; V[b]=ES+EC; V[b]->t=a; V[b]->c=0; V[b]->v=-v;
	V[a]->op = V[b]; V[b]->op = V[a];
}
int getcity(char *s)
{
	for (int i=1;i<=N;i++)
		if (strcmp(s,City[i])==0)
			return i;
	return -1;
}
void init()
{
	int i,a,b;
	char name[16];
	freopen("airl.in","r",stdin);
	freopen("airl.out","w",stdout);
	scanf("%d%d",&N,&M);
	for (i=1;i<=N;i++)
	{
		scanf("%s",City[i]);
		if (i==1 || i==N)
			addedge(i,i+N,2,-1);
		else
			addedge(i,i+N,1,-1);
	}
	for (i=1;i<=M;i++)
	{
		scanf("%s",name);a=getcity(name);
		scanf("%s",name);b=getcity(name);
		if (a<b)
			addedge(a+N,b,1,0);
		else
			addedge(b+N,a,1,0);
	}
	S=1; T=N+N;
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

int main()
{
	init();
	SPFAFlow();
	Costflow =-Costflow;
	Costflow -= 2;
	if (ES[1].c!=0)
		Costflow = 1;
	printf("%d\n",Costflow);
	return 0;
}
