#include<bits/stdc++.h>
using namespace std;
vector<int> graph[100005],graph_reserve[100005];
struct fi{
	int fin;
	int pos;
}finish_time[100005];
int finish_t = 0, linke[100005];
long long tot, ans = 0;
bool vis[100005], marked[100005];

bool cmp(fi x, fi y){	return x.fin > y.fin;	}

void dfs(int num);

void explore(int num);

int main(){
	int n,m;
	int a,b;
	scanf("%d%d",&n,&m);
	//initialize
	for(int i=1;i<=n;i++)
		vis[i] = false, finish_time[i].pos = i, marked[i] = false;
	vis[0] = true;
	
	// build a graph.
	for(int i=1;i<=m;i++){
		//a->b		Inverse:b->a
		scanf("%d%d",&a,&b);
		if(a==b)
			continue;
		graph[a].push_back(b);
		graph_reserve[b].push_back(a);
	}
	
//	printf("test\n");
	// dfs the graph and set the finish time.
	for(int i=1;i<=n;i++)
		if(!vis[i])
			dfs(i);
	// after dfs, we maintain a list of finish_time
	sort(finish_time+1,finish_time+n+1,cmp);
	
	for(int i=1;i<=n;i++){
//		printf("Finish_time(%d) = %d\n",i,finish_time[i].fin);
		linke[finish_time[i].pos] = i;
	}
		
	
	
	int cnt = 1;
	while(cnt<=n){
//		printf("Finish_time(%d) = %d, pos = %d\n",cnt,finish_time[cnt].fin,finish_time[cnt].pos);
		if(finish_time[cnt].fin == 0){
			cnt++;
			continue;
		}
		tot = 0;
		// explore to find each scc;
		explore(finish_time[cnt].pos);
//		printf("Explore the point %d, total num = %d, cnt = %d\n",finish_time[cnt].pos, tot, cnt);
		ans += (tot * (tot-1) / 2);
		cnt++;
	}
	printf("%lld\n",ans);
	return 0;
}

void dfs(int num){
	if(vis[num])
		return;
	vis[num] = true;
	for(int i=0;i<graph_reserve[num].size();i++)
		if(!vis[graph_reserve[num][i]])
//			printf("DFS THE NODE %d\n", graph[num][i]);
			dfs(graph_reserve[num][i]);
	finish_time[num].fin = ++finish_t;
	return;
}

void explore(int num){
//	printf("\t\t Explore the point %d\n",num);
	if(marked[num])
		return;
	finish_time[linke[num]].fin = 0;
	marked[num] = true;
	for(int i=0;i<graph[num].size();i++)
		if(!marked[graph[num][i]])
			explore(graph[num][i]);
	tot++;
	return;
}
