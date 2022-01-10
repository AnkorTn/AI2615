#include<bits/stdc++.h>
using namespace std;
long long ans=0; 
int a[100005];
map<int, int>mp;
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		ans += a[i];
	}
	for(int i=1;i<=n;i++){
		mp[a[i]] += 2;
		int u = mp.begin()->first;
		printf("%d ",a[i]-u);
		ans -= u;
		--mp[u];
		if(!mp[u])
			mp.erase(u);
	}
	printf("%lld\n",ans);
	return 0;
}
