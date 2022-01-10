// 11618. ¡¾Ô­1618¡¿Interesting Queue
// https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=11618
#include<bits/stdc++.h>
using namespace std;
struct node{
	int value;
	int pos;
}a[100005];
deque<node>q_min, q_max; 
queue<int>ans_min,ans_max;
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i].value);
		a[i].pos = i;
	}
	q_min.push_back(a[0]);
	q_max.push_back(a[0]);
	for(int i=1;i<k;i++){
		while(!q_min.empty() && q_min.back().value>a[i].value)
			q_min.pop_back();
		q_min.push_back(a[i]);
		while(!q_max.empty() && q_max.back().value<a[i].value)
			q_max.pop_back();
		q_max.push_back(a[i]);
	}
	ans_min.push(q_min.front().value);
	ans_max.push(q_max.front().value);
//	printf("%d  %d\n",q_min.front().value, q_max.front().value);
	for(int i=k;i<n;i++){
		//initialize.
		if(i>=q_min.front().pos+k)
			q_min.pop_front();
		if(i>=q_max.front().pos+k)
			q_max.pop_front();
		while(!q_min.empty() && q_min.back().value>a[i].value)
			q_min.pop_back();			
		q_min.push_back(a[i]);
		while(!q_max.empty() && q_max.back().value<a[i].value)
			q_max.pop_back();
		q_max.push_back(a[i]);
		ans_min.push(q_min.front().value);
		ans_max.push(q_max.front().value);
	}
	for(int i=0;i<=n-k;i++){
		printf("%d ",ans_min.front());
		ans_min.pop();
	}
	printf("\n");
	for(int i=0;i<=n-k;i++){
		printf("%d ",ans_max.front());
		ans_max.pop();
	}
	return 0;
}
/*
push_back()£º
push_front()£º
pop_back()£º
pop_front()£º
clear()£º
erase()£º
insert()£º
*/
