#include<bits/stdc++.h>
using namespace std;
// i: even			i+n: odd
vector<int> graph[400005];
int dis[400005];
int vis[200005];
// general parameters.
int n,m,s,e,a,b,c;
long long k;

void bfs();

int main(){	
	scanf("%d%d%d%d%lld",&n,&m,&s,&e,&k);
	//initialize
	for(int i=1;i<=n;i++){
		vis[i] = false;	vis[i+n] = false;
		dis[i] = 214748360; dis[i+n] = 214748360;
	}
	// build a graph.
	for(int i=1;i<=m;i++){
		//a->b		Inverse:b->a
		scanf("%d%d",&a,&b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	bfs();
	// key problem:自环 自环需要处理，因为自环已经不能简单地从奇偶性判断了。 
	// key problem2: 不能到达终点
	 
//	printf("%d %d\n",even_dis[e], odd_dis[e]);
//	printf("%d %d\n",dis[e], dis[e+n]);
	if(k&1){
		if(dis[e+n]>=214748360)
			printf("No\n");
		else if(dis[e+n]<=k)
			printf("Yes\n");
		else printf("No\n");
	}
	else{
		if(dis[e]>=214748360)
			printf("No\n");
		else if(dis[e]<=k)
			printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}



void bfs(){
	queue<int>q;	dis[s] = 0;		q.push(s);
	while(!q.empty()){
		int tmp = q.front();	q.pop();
		if(vis[tmp]>3)
			continue;
		for(int i=0;i<graph[tmp].size();i++){
			int flag = 0;
			if(dis[graph[tmp][i] + n]>dis[tmp] + 1){
				dis[graph[tmp][i] + n] = dis[tmp] + 1;
				vis[graph[tmp][i]] ++;
				flag = 1;
			}
			if(dis[graph[tmp][i]]>dis[tmp+n] + 1){
				dis[graph[tmp][i]] = dis[tmp+n] + 1;
				vis[graph[tmp][i]] ++;
				flag = 1;
			}
			if(flag)	q.push(graph[tmp][i]);
		}
	} 
}
