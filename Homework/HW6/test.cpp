#include<bits/stdc++.h>
using namespace std;
int tree[100000] = {0,-10,9,20,0,0,15,7};
int ans = 0;
int root = 1;
int dfs(int rt);
int main(){
	// consider all the leaves.
	for(int i=1;i<=7;i++)
		ans = max(ans,tree[i]);
	dfs(1);
	printf("%d\n",ans);
	return 0;
}

int dfs(int rt){
	// leaves just return it and it's enough.
	if(rt == 4 || rt == 5 || rt == 6 || rt == 7)
		return tree[rt];
	int left = dfs(rt*2);
	int right = dfs(rt*2+1);
	ans = max(ans, max(tree[rt]+left,max(tree[rt]+right,tree[rt]+left+right)));
	return max(0,max(tree[rt]+left,tree[rt]+right));
}
