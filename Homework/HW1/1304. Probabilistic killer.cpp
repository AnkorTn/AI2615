#include <bits/stdc++.h>
using namespace std;
int T = 10;
int prime_table[13] = {2,3,5,7,11,13,17,19,23,29,31,37,41}; 
const int SEED = 114514;
const int N = 4e5;
const long double pi = acosl(-1);
int n, X[N], Y[N], cnt=0;
struct point {
    long double x, y;
    int i;
    bool operator < (const point &a) const {
    	if(x == a.x) return y < a.y;
        return x < a.x;
    }
    long long distance_2(const point &a) {
    	long long tmp1 = X[a.i] - X[i]; tmp1*=tmp1;
    	long long tmp2 = Y[a.i] - Y[i]; tmp2*=tmp2;
        return tmp1+tmp2;
    }
}a[N];
int main() {
	scanf("%d",&n);
    for (int i = 0; i < n; i++)
		scanf("%d%d",&X[i],&Y[i]);
    long long ans = LLONG_MAX;
	default_random_engine e(time(0));
	uniform_real_distribution<long double> u(0,pi);
	long double theta = u(e);
    for(int kkk = 0;kkk<=11;kkk++){
    	T = prime_table[kkk];
		int totals = T % 30; 	
	    for (int i = 0; i < totals; i++) {
	    	cnt = 0;
	        long double angle = theta + pi * i / T;
	        for (int j = 0; j < n; j++) {
	            long double x = X[j], y = Y[j];
	            long double nx = cos(angle) * x + sin(angle) * y, ny = -sin(angle) * x + cos(angle) * y;
	            a[cnt].x = nx;
	            a[cnt].y = ny;
	            a[cnt].i = j;
	            cnt++;
	        }
	        sort(a, a+cnt);
	        for (int j = 1; j < n; j++) 
	            ans = min(ans, a[j - 1].distance_2(a[j]));
	    }	
	}
    printf("%lld\n",ans);
    return 0;
}
