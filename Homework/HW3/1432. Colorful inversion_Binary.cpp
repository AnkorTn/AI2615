#include<bits/stdc++.h>
using namespace std;
// 输出n个正整数，第i个表示以 ai结尾的最长下降子序列长度
int a[100005], b[100005], cnt = 1;
int bi_search(int tmp, int l, int r);
int main(){
	// 4
	// 1 3 4 2
	// 1 3 4 2
	// 4 2
	int n, pos;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		pos = bi_search(a[i],1,cnt);
		if(b[pos] == 0)
			cnt++;
		b[pos] = a[i];
//		printf("\nb:");
//		for(int j=1;j<=pos;j++)
//			printf("%d ",b[j]);
//		printf(":d\n");
		printf("%d ",pos);
	}
	return 0;
}
int bi_search(int tmp, int l, int r){
	if(r == 0) return 1;
	int mid;
	while(l<r){
		mid = (l+r)>>1;
		if(tmp>b[mid])
			r = mid;
		else
			l = mid+1;
	}
	return l;
}
