#include<bits/stdc++.h>
using namespace std;
struct people{
	int rate;
	int pos;
}a[100005];
bool cmp(people x, people y){
	if(x.rate == y.rate)
		return x.pos<y.pos;
	return x.rate < y.rate;
}
int main(){
	int n,temp;
	bool flag0 = false, flag1 = false;
	scanf("%d",&n);
	scanf("%d",&temp);
	a[0].rate = temp == 0?-1:1;
	a[0].pos = 1;
	for(int i=1;i<n;i++){
		scanf("%d",&temp);
		if(temp == 1)flag1 = true;
		if(temp == 0)flag0 = true;
		a[i].rate = temp == 0?-1:1;
		a[i].rate += a[i-1].rate;
		a[i].pos = i+1;
	}
	
	if(!flag0 && !flag1){
		printf("0\n");
		return 0;
	}
	
	sort(a,a+n,cmp);
//	for(int i=0;i<n;i++)
//		printf("%d\t",a[i].rate);
//	printf("\n");
//	for(int i=0;i<n;i++)
//		printf("%d\t",a[i].pos);
	int l = 0; int r = 0; int ans = 0;
	while(l<n){
		if(a[l].rate == a[r].rate){
			r++;
			ans = max(ans, a[r].pos-a[l].pos);
			continue;
		}		
		l = r;
	}
	for(int i=0;i<n;i++)
		if(a[i].rate == 0)
			ans = max(ans,a[i].pos);
	printf("%d\n",ans);	
	return 0;
}

