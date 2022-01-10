#include<bits/stdc++.h>
using namespace std;
// 输出n个正整数，第i个表示以 ai结尾的最长下降子序列长度
int a[100005], b[100005], cnt = 0;
int main(){
	// 4
	// 1 3 4 2
	// 1 3 4 2
	// 4 2
	// int n, l, r, mid;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(cnt == 0){
			b[1] = a[i];
			printf("1 ");
			cnt++;
			continue;
		}
		if(b[cnt]>a[i]){
			b[++cnt] = a[i];
			printf("%d ",cnt);
			continue;
		}
		// Return the value that is the first item smaller than a[i];
		int pos = upper_bound(b+1,b+cnt+1,a[i],greater<int>())-b;
		// if(b[pos-1] == a[i]) pos--;
		if(b[pos]<a[i]) b[pos] = a[i];
		printf("%d ",pos);
	}
	return 0;
}
