#include<bits/stdc++.h>
using namespace std;
int n,a,b;
int lef[1000005],rig[1000005];
int depth[1000005];
int ans = 1;
void dfs(int num);
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&lef[i],&rig[i]);
	depth[1] = 1;
	dfs(1);
	printf("%d\n",ans);
	return 0;
}

void dfs(int num){
	if(lef[num] == 0 && rig[num] == 0)
		return;
	if(lef[num] != 0){
		depth[lef[num]] = depth[num] + 1;
		ans = max(ans,depth[lef[num]]);
		dfs(lef[num]);
	}
	if(rig[num] != 0){
		depth[rig[num]] = depth[num] + 1;
		ans = max(ans,depth[rig[num]]);
		dfs(rig[num]);
	}
}
