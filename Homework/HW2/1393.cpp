#include<bits/stdc++.h>
using namespace std;
int n,m,temp;
int a[100005],b[100005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n/2;i++){
		temp = a[i];
		a[i] = a[n-i+1];
		a[n-i+1] = temp;
	}
	for(int i=1;i<=m;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=m/2;i++){
		temp = b[i];
		b[i] = b[m-i+1];
		b[m-i+1] = temp;
	}
	
	for(int i=1;i<=n;i++){
		a[i] += b[i];
		if(a[i]>=10){
			a[i]-=10;
			a[i+1]++;
		}
	}
	if(a[n+1] == 1) n++;
	for(int i=1;i<=n/2;i++){
		temp = a[i];
		a[i] = a[n-i+1];
		a[n-i+1] = temp;
	}
	for(int i=1;i<=n;i++)
		printf("%d ",a[i]);
	
	return 0;
}

