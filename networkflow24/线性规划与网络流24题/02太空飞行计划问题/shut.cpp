/* 
 * Problem: 线性规划与网络流24题 #2 太空飞行计划问题
 * Author: Guo Jiabao
 * Time: 2009.6.26 18:09
 * State: Solved
 * Memo: 网络最大流 最小割
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=101,MAXM=MAXN*MAXN*2,INF=~0U>>1;
struct edge
{
	edge *next,*op;
	int t,c;
}*V[MAXN],*P[MAXN],ES[MAXM],*Stae[MAXN];
int N,M,S,T,EC,Ans,Maxflow;
int Lv[MAXN],Stap[MAXN];
inline void addedge(int a,int b,int c)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c;
	ES[++EC].next = V[b]; V[b]=ES+EC; V[b]->t=a; V[b]->c=0;
	V[a]->op = V[b]; V[b]->op = V[a];
}
void init()
{
	int i,a,c;
	freopen("shut.in","r",stdin);
	freopen("shut.out","w",stdout);
	scanf("%d%d",&M,&N);
	S=0; T=N+M+1;
	for (i=1;i<=M;i++)
	{
		scanf("%d",&c);
		addedge(S,i,c);
		Ans += c;
		for (;;)
		{
			do c=getchar(); while (c==' '); ungetc(c,stdin);
			if (c==10 || c==13) break;
			scanf("%d",&a);
			addedge(i,a+M,INF);
		}
	}
	for (i=1;i<=N;i++)
	{
		scanf("%d",&c);
		addedge(i+M,T,c);
	}
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
void print()
{
	for (int i=1;i<=M;i++)
		if (Lv[i]!=-1)
			printf("%d ",i);
	putchar('\n');
	for (int i=M+1;i<=M+N;i++)
		if (Lv[i]!=-1)
			printf("%d ",i-M);
	Ans -= Maxflow;
	printf("\n%d\n",Ans);
}
int main()
{
	init();
	Dinic();
	print();
	return 0;
}
