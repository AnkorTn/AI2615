#include<bits/stdc++.h>
using namespace std;

struct Points{
	long long x;
	long long y;
};

Points point[1000005], temp[1000005];
long long tmp;
long long maxinf = 9223372036854775000;
bool cmp1(Points x1, Points x2){
	return x1.x < x2.x;
}
bool cmp2(Points x1, Points x2){
	return x1.y < x2.y;
}
long long dist(Points x1, Points x2){
	long long a = x1.x - x2.x;	a*=a;
	long long b = x1.y - x2.y;	b*=b;
	return a+b;
}
long long solve(int l, int r){
	if(l+1>=r)
		return maxinf;
	int m = (l+r)>>1;
	long long ans = min(solve(l,m), solve(m,r));
	int cnt = 0;
	for(int i=l;i<r;i++){
		tmp = point[i].x-point[m].x; tmp *= tmp;
		if(tmp<ans)
			temp[cnt++] = point[i];
	}
	if(cnt == 0)
		return ans;
	sort(temp, temp+cnt, cmp2);
	for(int i=0;i<cnt;i++)
		for(int j=i+1;j<cnt;j++){
			tmp = temp[i].y - temp[j].y;
			tmp *= tmp;
			if(tmp>=ans)
				break;
			ans = min(ans, dist(temp[i],temp[j]));
		}
	return ans;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%lld%lld",&point[i].x, &point[i].y);
	sort(point,point+n,cmp1);
	printf("%lld\n",solve(0,n));
	return 0;
}

