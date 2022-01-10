#include<bits/stdc++.h>
using namespace std;
struct edge{
	int v;
	int value;
	inline bool operator <(const edge &x)const{return value>x.value;}
};
vector<edge>graph[1000005];

//这个算法有BUG，具体题目应用的时候需要调整Prim算法。 

void Prim(int n, int &ans);
int main(){
	int n,m,a,b,c;
	int ans = 0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		graph[a].push_back((edge){b,c});
		graph[b].push_back((edge){a,c});
	}
	Prim(n, ans);
	printf("%d\n",ans);
	return 0;
}
void Prim(int n, int &ans){
	priority_queue<edge>q;
	edge tmp;
	int v, cnt = 1;
	bool vis[1000005];
	//这里有个小BUG，就是初始选点不一定是1，可能1不连通。 
	memset(vis, false, sizeof(vis));
	vis[1] = true;
	for(int i=0; i<graph[1].size();i++)
		q.push(graph[1][i]);
	while(!q.empty()){
		tmp = q.top();	q.pop();
		while(vis[tmp.v] && !q.empty()){	tmp = q.top(); q.pop();	}
		v = tmp.v;
		if(q.empty() && vis[v])			break;
		
		cnt++;
		vis[v] = true;	ans += tmp.value;
		for(int i=0; i<graph[v].size();i++)
			q.push(graph[v][i]);
	}
	if(cnt!=n){
		printf("orz\n");
		exit(0);
	}
	
}
