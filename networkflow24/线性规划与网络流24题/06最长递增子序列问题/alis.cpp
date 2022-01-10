/* 
 * Problem: 线性规划与网络流24题 #6 最长递增子序列问题
 * Author: Guo Jiabao
 * Time: 2009.7.3 13:52
 * State: Solved
 * Memo: 网络最大流 动态规划
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=501*2,MAXM=MAXN*MAXN*2,INF=~0U>>1;
struct edge
{
	edge *next,*op;
	int t,c;
}*V[MAXN],*P[MAXN],ES[MAXM],*Stae[MAXN],*x1,*xn;
int N,S,T,EC,Ans,Maxflow;
int A[MAXN],F[MAXN],Lv[MAXN],Stap[MAXN];
inline void addedge(int a,int b,int c)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c;
	if (a==1 && b==N+1) x1 = V[a];
	if (a==N && b==N+N) xn = V[a];
	ES[++EC].next = V[b]; V[b]=ES+EC; V[b]->t=a; V[b]->c=0;
	V[a]->op = V[b]; V[b]->op = V[a];
}
void init()
{
	freopen("alis.in","r",stdin);
	freopen("alis.out","w",stdout);
	scanf("%d",&N);
	S=0; T=N+N+1;
	for (int i=1;i<=N;i++)
		scanf("%d",&A[i]);
}
void dynamic()
{
	for (int i=N;i>=1;i--)
	{
		F[i] = 1;
		for (int j=i+1;j<=N;j++)
			if (A[j] > A[i] && F[j]+1 > F[i])
				F[i] = F[j]+1;
		if (F[i] > Ans)
			Ans = F[i];
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
void makegraph()
{
	int c,d;
	for (int i=1;i<=N;i++)
	{
		addedge(i,i+N,1);
		c=d=1;
		if (i==1) c=INF;
		if (i==N) d=INF;
		if (F[i]==Ans)
			addedge(S,i,c);
		if (F[i]==1)
			addedge(i+N,T,d);
		for (int j=i+1;j<=N;j++)
			if (F[i] == F[j]+1 /*&& A[i] < A[j]*/)
				addedge(i+N,j,1);
	}
}
void solve()
{
	dynamic();
	printf("%d\n",Ans);
	makegraph();
	Dinic();
	printf("%d\n",Maxflow);
	x1->c = xn->c = INF;
	Dinic();
	printf("%d\n",Maxflow);
}
int main()
{
	init();
	solve();
	return 0;
}
