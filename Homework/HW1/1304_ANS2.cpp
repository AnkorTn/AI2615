#include<bits/stdc++.h>
using namespace std;
//491:16		499:5		610:4		500:14		800:15		400:14
int T = 479;
int a[400005];
const long double pi = acosl(-1);
double cos_a[1000], sin_a[1000];
// Decline L from 
int main(){
	int n = T;
	int cnt = 0;
//	cout<<sin(pi)<<endl; 
//	cout<<cos(pi)<<endl;
//	freopen("text.txt","w",stdout);
//	mt19937 rng(114515);
//    uniform_real_distribution <long double> distribution(0, pi);
//    long double theta = distribution(rng);
	for(int i=0;i<=n;i++){
		cos_a[i] = cos(pi * i / T);
		sin_a[i] = sin(pi * i / T);
	}
	printf("958\n");
	for(int i=1;i<n;i++){
		cnt++;
		printf("%.0f %.0f\n", 10000000 * cos_a[i] , 10000000 * sin_a[i]);
		printf("%.0f %.0f\n", -10000000 * cos_a[i] , -10000000 * sin_a[i] );
	}
	
//	for(int i=1;i<n;i++){
//		cos_a[i] = cos(pi * (i+0.5) / T);
//		sin_a[i] = sin(pi * (i+0.5) / T);
//	}
//	for(int i=1;i<n;i++){
//		cnt++;
//		printf("%.0f %.0f\n", -10000000 * cos_a[i] , -10000000 * sin_a[i] + 1 );
////		printf("%.0f %.0f\n", -9000000 * cos_a[i] , -9000000 * sin_a[i] );
//	}
//	cnt+=2;
	printf("10000000 0\n");
	printf("-10000000 0");
//	cout<<cnt<<endl;
//	printf("0 0\n");
//	printf("10000 0");
	fclose(stdout);
	return 0;
}
