/* 
 * Problem: 线性规划与网络流24题 #9 方格取数问题
 * Author: Guo Jiabao
 * Time: 2009.6.27 19:06
 * State: Solved
 * Memo: 网络最大流 二分图点权最大独立集
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXL=50,MAXN=50*50,MAXM=MAXN*8,INF=~0U>>1;
const int dx[]={0,0,-1,1},dy[]={-1,1,0,0};
struct edge
{
	edge *next,*op;
	int t,c;
}*V[MAXN],*P[MAXN],ES[MAXM],*Stae[MAXN];
int N,M,S,T,C,EC,Ans,Maxflow,Total;
int Lv[MAXN],Stap[MAXN],Map[MAXL][MAXL];
inline void addedge(int a,int b,int c)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c;
	ES[++EC].next = V[b]; V[b]=ES+EC; V[b]->t=a; V[b]->c=0;
	V[a]->op = V[b]; V[b]->op = V[a];
}
void init()
{
	int i,j,k,c;
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	scanf("%d%d",&M,&N);
	S=0; T=N*M+1;
	for (i=1;i<=M;i++)
	{
		for (j=1;j<=N;j++)
		{
			scanf("%d",&c);
			Total += c;
			Map[i][j] = ++C;
			if ((i+j)%2==0)
				addedge(S,C,c);
			else
				addedge(C,T,c);
		}
	}
	for (i=1;i<=M;i++)
	{
		for (j=1;j<=N;j++)
		{
			if ((i+j)%2==0)
			{
				for (k=0;k<4;k++)
				{
					int x=i+dx[k],y=j+dy[k];
					if (x>=1 && x<=M && y>=1 && y<=N)
						addedge(Map[i][j],Map[x][y],INF);
				}
			}
		}
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
int main()
{
	init();
	Dinic();
	Ans = Total - Maxflow;
	printf("%d\n",Ans);
	return 0;
}
