#include<bits/stdc++.h>
using namespace std;
long long a, f[2][100005];
int main(){
	int n, mid;
	int f1=0, f2=1;
	scanf("%d",&n);
	// mid = n / 2;
	// 这个空间复杂度基本没问题了，关键在于时间复杂度如何优化
	// 目前的算法复杂度O(N^2)而题目要求的应该是O(NlogN)或者O(N)
	// 关键在于这个遍历手中持有i支股票时候的情况。
	// 我什么时候一定不用买入？什么时候一定不用卖出？
	// 下坡不卖出上坡不买入？对吗？ 
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);
		memset(f[f2],-0x3f3f3f3f,sizeof(f[f2]));
		f[f2][0] = 0;		f[f2][1] = -1 * a;
		for(int j=0;j<=i;j++)
			f[f2][j] = max(f[f2][j],f[f1][j]); 
		// 买入
		for(int j=1;j<=i;j++)
			f[f2][j] = max(f[f2][j],f[f1][j-1]-a);
		// 卖出
		for(int j=0;j<=i;j++)
			f[f2][j] = max(f[f2][j],f[f1][j+1]+a);
		f1 = 1 - f1; f2 = 1 - f2;
	}
	printf("%lld\n",max(f[0][0],f[1][0]));
	return 0;
}
