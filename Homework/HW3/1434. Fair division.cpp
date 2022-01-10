#include<bits/stdc++.h>
using namespace std;
priority_queue<long long,vector<long long>,greater<long long>>q;
int main(){
	// Ref: Huffman Tree
	// n: people; w: weight; p:percent to cutdown.
	int n,w;
	long long tmp1,tmp2,p;
	long long ans = 0;
	scanf("%d%d%lld",&n,&w,&p);
	for(int i=1;i<=n;i++){
		scanf("%lld",&tmp1);
		q.push(tmp1);
	}
	for(int i=1;i<n;i++){
		tmp1 = q.top();	q.pop();
		tmp2 = q.top(); q.pop();
//		printf("POP: %d  %d\n",tmp1,tmp2);
		tmp2+=tmp1;
//		printf("%d ",tmp2*p);
		ans+=tmp2*p;
		q.push(tmp2);
	}
	ans+=99;
	ans/=100;
	printf("%lld\n",ans);
	return 0;
}

