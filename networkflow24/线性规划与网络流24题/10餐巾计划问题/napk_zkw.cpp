/* 
 * Problem: 线性规划与网络流24题 #10 餐巾计划问题
 * Author: Guo Jiabao
 * Time: 2009.6.28 14:48
 * State: Solved
 * Memo: 最小费用最大流 zkw费用流
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=1001*2,MAXM=MAXN*6*2,INF=~0U>>1;
struct edge
{
	edge *next,*op;
	int t,c,v;
}*V[MAXN],ES[MAXM],*P[MAXN];
int N,S,T,EC,Ans,Costflow;
int dist[MAXN];
bool vis[MAXN];
inline void addedge(int a,int b,int c,int v)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c; V[a]->v=v;
	ES[++EC].next = V[b]; V[b]=ES+EC; V[b]->t=a; V[b]->c=0; V[b]->v=-v;
	V[a]->op = V[b]; V[b]->op = V[a];
}
void init()
{
	int i,c,newn,sd,sc,fd,fc;
	freopen("napk.in","r",stdin);
	freopen("napk.out","w",stdout);
	scanf("%d%d%d%d%d%d",&N,&newn,&sd,&sc,&fd,&fc);
	S=0; T=N+N+1;
	for (i=1;i<=N;i++)
	{
		scanf("%d",&c);
		addedge(S,i,c,0);
		addedge(i+N,T,c,0);
		addedge(S,i+N,INF,newn);
		if (i<N)
			addedge(i,i+1,INF,0);
		if (i+sd<=N)
			addedge(i,i+N+sd,INF,sc);
		if (i+fd<=N)
			addedge(i,i+N+fd,INF,fc);
	}
}
int Augment(int i,int flow)
{
	if (i==T)
	{
		Costflow += flow * dist[S];
		return flow;
	}
	vis[i]=true;
	for (edge *e=P[i];e;e=e->next)
	{
		int j=e->t;
		if (e->c && !vis[j] && dist[i] == dist[j] + e->v)
		{
			int delta = Augment(j,flow < e->c ? flow : e->c);
			if (delta)
			{
				e->c -= delta;
				e->op->c += delta;
				P[i] = e;
				return delta;
			}
		}
	}
	P[i] = 0;
	return 0;
}
bool ModifyDist()
{
	int delta=INF,i,j;
	for (i=S;i<=T;i++)
	{
		if (vis[i])
		{
			for (edge *e=V[i];e;e=e->next)
			{
				j=e->t;
				if (e->c && !vis[j] && dist[j] + e->v - dist[i] < delta)
					delta = dist[j] + e->v - dist[i];
			}
		}
	}
	if (delta == INF) return false;
	for (i=S;i<=T;i++)
	{
		if (vis[i])
		{
			dist[i] += delta;
			vis[i]=false;
		}
		P[i] = V[i];
	}
	return true;
}
void zkwFlow()
{
	memcpy(P,V,sizeof(V));
	do{
		while (Augment(S,INF));
	}while(ModifyDist());
}
int main()
{
	init();
	zkwFlow();
	printf("%d\n",Costflow);
	return 0;
}
