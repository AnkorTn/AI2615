#include<bits/stdc++.h>
using namespace std;
struct fkt{
	int s;
	int t;
	int p;
	inline bool operator <(const fkt &x)const{
		if(t == x.t)
			return s<x.s;
        return t<x.t;
    }
}fct[1000005];
int main(){
	int n,m,x;
	scanf("%d%d%d",&n,&m,&x);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&fct[i].s,&fct[i].t,&fct[i].p);
	sort(fct+1,fct+m+1);
	int current_time = 0, ans = 0;
	for(int i=1;i<=m;i++)
		if(current_time < fct[i].s){
			current_time = fct[i].t;
			ans+=fct[i].p;
		}
	printf("%d\n",ans);
	return 0;
}

