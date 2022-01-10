#include<bits/stdc++.h>
using namespace std;
int graph[300][300], rgraph[300][300], parent[300];
bool visited[300];
int s, t;
int n, m, u, v, c;
bool BFS();
int fordFulkerson();
int main(){
	memset(graph,0,sizeof(graph));
	memset(rgraph,0,sizeof(rgraph));
	scanf("%d%d",&n,&m);
	s = 1; t = n;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&c);
		graph[u][v] += c;
		rgraph[u][v]+= c;
	}
	printf("%d\n", fordFulkerson());
	return 0;
}
bool BFS(){
	// parentÊÇÖ¸ÕëÕÒÂ·¾¶¡£
	memset(parent, -1, sizeof(parent));
	memset(visited, false, sizeof(visited));
	
	queue<int>q;
	q.push(s);	visited[s] = true;	parent[s] = -1;
	// BFS
	while(!q.empty()){
		int tmp = q.front();	q.pop();
		for(int i=1;i<=n;i++)
			if(!visited[i] && rgraph[tmp][i]>0){
				q.push(i);
				parent[i] = tmp;
				visited[i] = true;
			}
	}
	return (visited[t] == true);
}

int fordFulkerson(){
	int ans = 0;
	int u;
	while(BFS() == true){
		int capacity = INT_MAX;
		// find an edge e \in p with minimum capacity.
		for(int i=t; i!=s; i=parent[i]){
			u = parent[i];
			capacity = min(capacity, rgraph[u][i]);
		}
		
		// for each e=(u,v)\in p, update if in E.
		// u,v->+
		// v,u->-
		for(int i=t; i!= s; i=parent[i]){
			u = parent[i];
			rgraph[u][i] -= capacity;
			rgraph[i][u] += capacity;
		}
		
		ans += capacity;
	}
	return ans;
}

