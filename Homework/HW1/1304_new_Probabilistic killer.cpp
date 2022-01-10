#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 1;
const long double pi = acosl(-1);
struct point{
	long long x;
	long long y;
	long double nx;
	long double ny;
	bool operator < (const point &a) const {
    	if(nx == a.nx) return ny < a.ny;
        return nx < a.nx;
    }
}a[N], temp1, temp2;
int n;
//int prime_table[13] = {2,3,5,7,11,13,17,19,23,29,31,37,41}; 
long double prime_table[13] = {1.5,1.7,5,11.5}; 
//int prime_table[13] = {2,3,5,7,11,13,17,19,23,29,31,37,41}; 
long long ans = LLONG_MAX, temp3;
long long dist(point x1, point x2){
	long long tmp1 = x1.x - x2.x;	tmp1*=tmp1;
	long long tmp2 = x1.y - x2.y;	tmp2*=tmp2;
	return tmp1+tmp2;
}
long double fact[13];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%lld%lld",&a[i].x,&a[i].y);
	for(int kkk=0;kkk<=3;kkk++)
		fact[kkk] = pi / prime_table[kkk];
	for(int kkk = 0;kkk<=3;kkk++){
		long double t_cos = cos(fact[kkk]),	t_sin = sin(fact[kkk]); 
		for(int i=0;i<n;i++){
			a[i].nx = t_cos * a[i].x + t_sin * a[i].y;
			a[i].ny = t_sin * a[i].x - t_cos * a[i].y;
		}
		sort(a,a+n);
		for(int i=0;i<n;i++){
			temp1 = a[i];
			for(int j=1;j<=200;j++){
				if(i+j>=n)
					break;
				temp2 = a[i+j];
				temp3 = dist(temp1,temp2);
				if(temp3<ans)
					ans = temp3;
			}
			
			
			for(int j=201;j<=400;j+=3){
				if(i+j>=n)
					break;
				temp2 = a[i+j];
				temp3 = dist(temp1,temp2);
				if(temp3<ans)
					ans = temp3;
			}
		}
	}
	

	printf("%lld\n",ans);
	return 0;
}
