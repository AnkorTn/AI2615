/* 
 * Problem: 线性规划与网络流24题 #15 汽车加油行驶问题
 * Author: Guo Jiabao
 * Time: 2009.6.29 15:16
 * State: Solved
 * Memo: 分层图最短路径 SPFA
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXL=101,MAXK=11,MAXN=MAXL*MAXL*MAXK,MAXM=MAXN*5,INF=~0U>>1;
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
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
	edge *next;
	int t,c;
}*V[MAXN],ES[MAXM];
int N,K,A,B,C,EC,Ans,Maxflow,Total;
int dist[MAXN];
bool oil[MAXL][MAXL],vis[MAXN];
inline void addedge(int a,int b,int c)
{
	ES[++EC].next = V[a]; V[a]=ES+EC; V[a]->t=b; V[a]->c=c;
}
inline int Point(int x,int y,int d)
{
	return d * N * N + (x - 1) * N + y;
}
void init()
{
	int i,j,k,l,c,x,y;
	freopen("trav.in","r",stdin);
	freopen("trav.out","w",stdout);
	scanf("%d%d%d%d%d",&N,&K,&A,&B,&C);
	for (i=1;i<=N;i++)
		for (j=1;j<=N;j++)
		{
			scanf("%d",&c);
			oil[i][j] = c;
		}
	for (i=1;i<=N;i++)
	{
		for (j=1;j<=N;j++)
		{
			for (l=0;l<=K;l++)
			{
				c = oil[i][j] ? A : A+C;
				if (l<K)
					addedge(Point(i,j,l),Point(i,j,K),c);
				if ((!oil[i][j] && l>0) || l==K)
				{
					for (k=0;k<4;k++)
					{
						x = i + dx[k];
						y = j + dy[k];
						c= k<2 ? 0 : B;
						if (x>=1 && x<=N && y>=1 && y<=N)
							addedge(Point(i,j,l),Point(x,y,l-1),c);
					}
				}
			}
		}
	}
}
void SPFA(int S)
{
	int i,j;
	Q.init();
	for (i=1;i<=Total;i++)
		dist[i]=INF;
	dist[S]=0;
	Q.ins(S);
	while (Q.size)
	{
		i=Q.pop();
		for (edge *e=V[i];e;e=e->next)
		{
			j=e->t;
			if (dist[i] + e->c < dist[j])
			{
				dist[j] = dist[i] + e->c;
				if (!Q.inq[j])
					Q.ins(j);
			}
		}
	}
}
void solve()
{
	int i,a;
	Total = Point(N,N,K);
	SPFA(Point(1,1,K));
	Ans = INF;
	for (i=0;i<=K;i++)
		if ((a=dist[Point(N,N,i)]) < Ans)
			Ans = a;
}
int main()
{
	init();
	solve();
	printf("%d\n",Ans);
	return 0;
}
