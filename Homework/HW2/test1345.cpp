#include<bits/stdc++.h>
using namespace std;

#define MAXN 805
#define MAXM 200005
#define LL long long

int n,m,nn,k;
struct bian
{
	int x,y,l;
}b[MAXM];
int c[MAXM],a[MAXN];
long long dis[MAXN][MAXN];
long long d[MAXN*MAXN];

inline int read()
{
    register int x = 0 , ch = getchar();
    while( !isdigit( ch ) ) ch = getchar();
    while( isdigit( ch ) ) x = x * 10 + ch - '0' , ch = getchar();
    return x;
}

bool cmp(bian a,bian b) {
	return a.l < b.l;
}
void rd()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1; i <= m; i ++) {
		b[i].x = read();
		b[i].y = read();
		b[i].l = read();
	}
	sort(b+1,b+m+1,cmp);
}

signed main()
{
	rd();
	memset(dis,0x3f,sizeof(dis));
	for(int i = 1; i <= k; i ++) {
		c[b[i].x] = 1;
		c[b[i].y] = 1;
	}
	for(int i = 1; i <= n; i ++) 
		a[i] = a[i-1] + c[i];
	nn = a[n];
	for(int i = 1; i <= k; i ++) {
		dis[ a[b[i].x] ][ a[b[i].y] ] = b[i].l;
		dis[ a[b[i].y] ][ a[b[i].x] ] = b[i].l;
		
	}
	n = nn;
	for(int k = 1; k <= n; k ++)
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
			if(dis[i][j] > dis[i][k] + dis[k][j])
				dis[i][j] = dis[i][k] + dis[k][j];
	int cnt = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j < i; j ++)
		{
			cnt ++;
			d[cnt] = dis[i][j];
		}
	sort(d+1,d+cnt+1);
	cout<<d[k];
	return 0;
}
