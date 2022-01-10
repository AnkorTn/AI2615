#include<bits/stdc++.h>
using namespace std;
struct fkt{
	int w;
	int v;
	long long c;
	inline bool operator <(const fkt &x)const{
		if(w == x.w)
			return v>x.v;
        return w<x.w;
    }
}fct[1000];
long long f[10005];
// 这个程序仅能完成无限道具的情况
// 一件道具则贪心 
int main(){
	int n,w;
	scanf("%d%d",&n,&w);
	for(int i=1;i<=n;i++){
		scanf("%d%d%lld",&fct[i].w,&fct[i].v,&fct[i].c);
		fct[i].c = min(fct[i].c, (long long)w/fct[i].w);
	}
	sort(fct+1,fct+n+1);
	for(int i=1;i<=n;i++){
//		for(int j=1;j<=w;j++){
		for(int j=w;j>=1;j--){
			long long tmpw = fct[i].w, tmpv = fct[i].v, tmp;
			if(tmpw>j)
				continue;
			f[j] = max(f[j],f[j-tmpw] + tmpv);
			for(int k=1;k<fct[i].c;k++){
				tmpw += fct[i].w;
				if(tmpw>j)
					break;
				tmpv += fct[i].v;
				tmp = f[i-tmpw]+tmpv;
				f[j] = max(f[j],tmp);
			}
		}
	}
	printf("%lld\n",f[w]);
	return 0;
}

