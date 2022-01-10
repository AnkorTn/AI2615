/* 
 * Problem: 线性规划与网络流24题 #24 骑士共存问题
 * Author: Guo Jiabao
 * Time: 2009.6.28 11:09
 * State: Solved
 * Memo: 网络最大流 二分图最大独立集
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXL=201,MAXN=MAXL*MAXL,MAXM=MAXN*8*2,INF=~0U>>1;
const int dx[]={-2,-1,1,2,2,1,-1,-2},dy[]={1,2,2,1,-1,-2,-2,-1};
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
	int i,j,k,a,b;
	freopen("kni.in","r",stdin);
	freopen("kni.out","w",stdout);
	scanf("%d%d",&N,&M);
	S=0; T=N*N+1;
	Total = N*N-M;
	for (i=1;i<=M;i++)
	{
		scanf("%d%d",&a,&b);
		Map[a][b] = -1;
	}
	for (i=1;i<=N;i++)
		for (j=1;j<=N;j++)
			if (Map[i][j]==0)
			{
				Map[i][j] = ++C;
				if ((i+j)%2==0)
					addedge(S,C,1);
				else
					addedge(C,T,1);
			}
	for (i=1;i<=N;i++)
		for (j=1;j<=N;j++)
			if (Map[i][j]!=-1 && (i+j)%2==0)
			{
				for (k=0;k<8;k++)
				{
					int x=i+dx[k],y=j+dy[k];
					if (x>=1 && x<=N && y>=1 && y<=N && Map[x][y]!=-1)
						addedge(Map[i][j],Map[x][y],INF);
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
