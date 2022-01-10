#include<bits/stdc++.h>
using namespace std;
struct fkt{
	int s;
	int t;
	long long p;
	inline bool operator <(const fkt &x)const{
		if(t == x.t)
			return s<x.s;
        return t<x.t;
    }
}fct[1000005];
vector<fkt>q[400];
long long f[400][400];
int main(){
	int n,m;
	long long x;
	scanf("%d%d%lld",&n,&m,&x);
	for(int i=1;i<=m;i++){
		scanf("%d%d%lld",&fct[i].s,&fct[i].t,&fct[i].p);
		q[fct[i].t].push_back(fct[i]);
	}
	sort(fct+1,fct+m+1);
	// Dp: O(NM)
	// Initialize 出去全部都是工作
	// f[i][0] 出去工作了i天的最大收益 
	memset(f,-0x3f3f3f3f,sizeof(f));
	f[0][0] = 0;
	for(int j=1;j<=n;j++)
		f[j][0] = 0;
	for(int j=1;j<=n;j++)
		for(int i=1;i<=m;i++)
			if(fct[i].t<=j)
				f[j][0] = max(f[fct[i].s - 1][0] + fct[i].p, f[j][0]);
	// Work()
	// f[i][j]: 出去了i天玩了j天 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			// 啥也不干
			f[i][j] = max(f[i-1][j],f[i][j]);
			
			// 玩一天
			if(f[i-1][j-1]-x>=0)
				f[i][j] = max(f[i-1][j-1]-x,f[i][j]);
			
			// 工作一天
			for(int k=0;k<q[i].size();k++)
				f[i][j] = max(f[q[i][k].s - 1][j] + q[i][k].p,f[i][j]);

		}
	
		
	for(int i=n;i>=0;i--)
		if(f[n][i]>=0){
			printf("%lld ",f[n][i]);
			break;
		}			
//	printf("\n%lld\n",f[n]);	
	return 0;
}
