#include<bits/stdc++.h>
using namespace std;
int T = 610;
int a[400005];
double pi = 3.1415926535;
double cos_a[1000], sin_a[1000];
// Decline L from 
int main(){
	int n = T;
//	cout<<sin(pi)<<endl; 
//	cout<<cos(pi)<<endl;
	freopen("text.txt","w",stdout);
	for(int i=0;i<=n;i++){
		cos_a[i] = cos(pi * i / T);
		sin_a[i] = sin(pi * i / T);
	}
	printf("1220\n");
	for(int i=1;i<n;i++){
		printf("%.0f %.0f\n", 10000000 * cos_a[i], 10000000 * sin_a[i]);
		printf("%.0f %.0f\n", -10000000 * cos_a[i], -10000000 * sin_a[i]);
	}
	printf("10000000 0\n");
	printf("-10000000 0");
//	printf("0 0\n");
//	printf("10000 0");
	fclose(stdout);
	return 0;
}
