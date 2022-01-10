#include<bits/stdc++.h>
using namespace std;

long long divide(long long a){
	if(a<10) return a*a*a;
	long long temp = a%10;
	long long ans = temp*temp*temp;
	return ans + divide(a/10);
}

int main(){
	
//	1	153	370	371	407
//	for(long long i=1;i<=100000;i++){
//		if(i == divide(i))
//			cout<<i<<endl;
//	}
	int a,b;
	int num[5] = {1,153,370,371,407};
	bool flag = false;
	scanf("%d%d",&a,&b);
	for(int i=0;i<=4;i++)
		if(num[i]>=a && num[i]<=b){
			flag = true;
			printf("%d ",num[i]);
		}
		else if(num[i]>=b && num[i]<=a){
			flag = true;
			printf("%d ",num[i]);
		}
		
	if(!flag)
		printf("no\n");
	return 0;
}

