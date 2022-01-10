#include<bits/stdc++.h>
using namespace std;
struct homework{
	int start_time;
	int finish_time;
	inline bool operator <(const homework &x)const{return finish_time>x.finish_time;}
}hw[1000005];
int main(){
	int n, ans = 1, ans_time, pre_finish;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&hw[i].start_time, &hw[i].finish_time);
	sort(hw+1,hw+n+1);
	pre_finish = hw[1].finish_time;
	ans_time   = hw[1].finish_time - hw[1].start_time;
	for(int i=2;i<=n;i++){
		if(hw[i].start_time<pre_finish)
			continue;
		pre_finish = hw[i].finish_time;
		ans_time += hw[i].finish_time - hw[i].start_time;
		ans ++;
	}
	printf("%d %d\n",ans,ans_time);
	return 0;
}

