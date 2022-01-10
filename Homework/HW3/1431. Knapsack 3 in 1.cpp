#include<bits/stdc++.h>
using namespace std;
long long f[10005];
int w_[10005],v_[10005];
int main(){
	int n,w,ww,vv,cnt=0;
	long long cc;
	scanf("%d%d",&n,&w);
	for(int i=1;i<=n;i++){
		scanf("%d%d%lld",&ww,&vv,&cc);
		cc = min(cc,(long long)w/ww);
		int base = 1;
		while(base<=cc){
			w_[++cnt] = ww*base;
			v_[cnt]	  = vv*base;
			cc		 -= base;
			base	 *= 2;
		}
		if(cc>0){
			w_[++cnt] = ww*cc;
			v_[cnt]	  = vv*cc;
		}
	}
	
	for(int i=1;i<=cnt;i++)
		for(int j=w;j>=w_[i];j--)
			f[j] = max(f[j],f[j-w_[i]]+v_[i]);
	printf("%lld\n",f[w]);
	return 0;
}
