#include<bits/stdc++.h>
using namespace std;
int v1[100005],v2[100005],v3[200005], l1 = 1, l2 = 1, l3 = 1;
int main(){
	int n, m;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&v1[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&v2[i]);
		
	while(l1<=n && l2<=m)
		if(v1[l1] <= v2[l2])
			v3[l3++] = v1[l1++];
		else
			v3[l3++] = v2[l2++];
	while(l1<=n)
		v3[l3++] = v1[l1++];
	while(l2<=m)
		v3[l3++] = v2[l2++];
	for(int i=1;i<l3;i++)
		printf("%d ",v3[i]);
	return 0;
}

