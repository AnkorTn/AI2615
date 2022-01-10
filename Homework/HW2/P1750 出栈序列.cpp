#include<bits/stdc++.h>
using namespace std;
priority_queue<int>q;
int main(){
	int n, c, temp, tot = 0;
	scanf("%d%d",&n,&c);
	while(n--){
		scanf("%d",&temp);
		q.push(-1 * temp);
		tot++;
		if(tot == c){
			tot--;
			printf("%d ",-1 * q.top());
			q.pop();
		}
	}
	while(!q.empty()){
		printf("%d ",-1 * q.top());
		q.pop();
	}
	return 0;
}

