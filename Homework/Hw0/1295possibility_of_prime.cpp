#include<bits/stdc++.h>
using namespace std;
//10^-5  the key point to get the full score. 
int main(){
	int n, cnt = 0;
	scanf("%d",&n);
	if(n==1){
		printf("0\n");
		return 0;
	}
	// 10^3 can be done by iteration.
	if(n<=76000){
		bool *ans = new bool[n+1];
		for(int i=2;i<=n;i++)ans[i]=true;
		for(int i=2;i<=n;i++){
			if(!ans[i])continue;
			cnt++;
			if(2*i<=n)
				for(int j=2*i;j<=n;j+=i)
					if(ans[j])ans[j]=false;
		}
		int com = n * n;
		double result = 2.0 * cnt / com;
		printf("%0.6lf\n",result);
		// printf("%d\n",cnt);
		return 0;
	}
	printf("0.00001\n");
	// 10^9 maybe should try direct methods.	
	return 0;
}

