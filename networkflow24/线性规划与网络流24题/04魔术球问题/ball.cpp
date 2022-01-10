/* 
 * Problem: 线性规划与网络流24题 #4 魔术球问题
 * Author: Guo Jiabao
 * Time: 2009.6.27 12:06
 * State: Solved
 * Memo: 网络最大流 最小路径覆盖 枚举答案
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=4001,OFFSET=2000,MAXM=200000,INF=~0U>>1;
struct edge
{
	edge *next,*op;
	int t,c;
}*V[MAXN],*P[MAXN],ES[MAXM],*Stae[MAXN];
int N,M,S,T,EC,Ans,Maxflow;
int Lv[MAXN],Stap[MAXN],Match[MAXN],Path[MAXN];
bool vis[MAXN],issquare[MAXN];
inline void addedge(int a,int b,int c)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c;
	ES[++EC].next = V[b]; V[b]=ES+EC; V[b]->t=a; V[b]->c=0;
	V[a]->op = V[b]; V[b]->op = V[a];
}
void init()
{
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	scanf("%d",&N);
	S=0; T=MAXN-1;
	for (int i=1;i<=60;i++)
		issquare[i*i]=true;
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
void solve()
{
	int i,j;
	addedge(S,1,1);
	addedge(1+OFFSET,T,1);
	Dinic();
	for (i=1;i - Maxflow <= N;)
	{
		i++;
		addedge(S,i,1);
		addedge(i+OFFSET,T,1);
		for (j=1;j<i;j++)
			if (issquare[i+j])
				addedge(j,i+OFFSET,1);
		Dinic();
	}
	Ans = i-1;
	memset(V,0,sizeof(V));
	EC=Maxflow=0;
	for (i=1;i<=Ans;i++)
	{
		addedge(S,i,1);
		addedge(i+OFFSET,T,1);
		for (j=1;j<i;j++)
			if (issquare[i+j])
				addedge(j,i+OFFSET,1);
	}
	Dinic();
}
void print()
{
	int i,j,p;
	printf("%d\n",Ans);
	for (i=Ans+OFFSET;i>=1+OFFSET;i--)
	{
		for (edge *e=V[i];e;e=e->next)
		{
			if (e->c==1)
			{
				Match[e->t] = i-OFFSET;
				break;
			}
		}
	}
	for (i=1;i<=Ans;i++)
	{
		if (vis[i]) continue;
		p=0;
		for (j=i;j;j=Match[j])
		{
			Path[++p]=j;
			vis[j]=true;
		}
		for (j=1;j<p;j++)
			printf("%d ",Path[j]);
		printf("%d\n",Path[j]);
	}
}
int main()
{
	init();
	solve();
	print();
	return 0;
}
