#include<bits/stdc++.h>
using namespace std;
//edge 1000000
struct node {
    int v,next;
}graph[2000005],graph_reserve[2000005];
vector<int> graphff[2000005],graph_reserveff[2000005];
int heads[2000005],heads_reserve[2000005];
struct fi{
	int fin;
	int pos;
}finish_time[2000005];
int finish_t = 0;
int vis[2000005];
int cnt = 1, tot=0,n,m,a,b,c,d;

bool cmp(fi x, fi y){	return x.fin > y.fin;	}

void add(int x,int y){
    graph[++tot].next=heads[x];
    graph[tot].v = y;
    heads[x]=tot;
    graph_reserve[tot-1].next=heads_reserve[y];
    graph_reserve[tot].v = x;
    heads_reserve[y]=tot;
    return ;
}

void dfs(int num);

void explore(int num);

int main(){
	scanf("%d%d",&n,&m);
	//initialize
	for(int i=1;i<=2*n;i++){
		vis[i] = 0;
		finish_time[i].pos = i;
	}
	vis[0] = 1;
	memset(heads,-1,sizeof(heads));
	memset(heads_reserve,-1,sizeof(heads_reserve));
	
	// build a graph.
	for(int i=1;i<=m;i++){
		//a->b		Inverse:b->a
		scanf("%d%d%d%d",&a,&b,&c,&d);
		add(c+(1-d)*n,a+b*n);
		add(a+(1-b)*n,c+d*n);
		graphff[c+(1-d)*n].push_back(a+b*n);
//		printf("Build edge:  %d  %d  \n",c+(1-d)*n,a+b*n);
		graphff[a+(1-b)*n].push_back(c+d*n);
//		printf("Build edge:  %d  %d  \n",a+(1-b)*n,c+d*n);
		graph_reserveff[a+b*n].push_back(c+(1-d)*n);
		graph_reserveff[c+d*n].push_back(a+(1-b)*n);
	}
	
//	printf("test\n");
	// dfs the graph and set the finish time.
	for(int i=1;i<=2*n;i++)
		if(!vis[i])
			dfs(i);
	// after dfs, we maintain a list of finish_time
	sort(finish_time+1,finish_time+2*n+1,cmp);
	
	for(int i=1;i<=2*n;i++)
		vis[i] = 0;		
	
	
	
	
	while(cnt<=2*n){
//		printf("Finish_time(%d) = %d, pos = %d, vis[i] = %d\n",cnt,finish_time[cnt].fin,finish_time[cnt].pos, vis[finish_time[cnt].pos]);
		if(vis[finish_time[cnt].pos] > 0){
			cnt++;
			continue;
		}
		// explore to find each scc;
		explore(finish_time[cnt].pos);
//		printf("Explore the point %d, cnt = %d\n",finish_time[cnt].pos, cnt);
		cnt++;
	}
	
//	for(int i=1;i<=2*n;i++)
//		printf("%d ",vis[i]);
//	printf("\n");
	for(int i=1;i<=n;i++)
		if(vis[i] == vis[i+n]){
			printf("IMPOSSIBLE\n");
			return 0;
		}
			
	printf("POSSIBLE\n");
	for(int i=1;i<=n;i++)
		if(vis[i] > vis[i+n])
			printf("1 ");
		else
			printf("0 ");
	return 0;
}


//void dfs(int num){
//	if(vis[num])
//		return;
//	vis[num] = true;
//	for(int i=0;i<graph_reserveff[num].size();i++)
//		if(!vis[graph_reserveff[num][i]]){
////			printf("DFS THE NODE %d\n", graph_reserve[num][i]);
//			dfs(graph_reserveff[num][i]);
//		}
//	finish_time[num].fin = ++finish_t;
//	return;
//}

void dfs(int num){
	vis[num] = true;
	for(int i=heads_reserve[num];i!=-1;i=graph_reserve[i].next)
		if(!vis[graph_reserve[i].v])
//			printf("DFS THE NODE %d\n", graph_reserve[i].v);
			dfs(graph_reserve[i].v);
	finish_time[num].fin = ++finish_t;
	return;
}


//void explore(int num){
//	vis[num] = cnt;
//	for(int i=0;i<graphff[num].size();i++)
//		if(vis[graphff[num][i]] == 0){
////			printf("\t\t Explore the point %d, cnt = %d\n",graph[num][i],cnt);
//			explore(graphff[num][i]);
//		}
//		
//	return;
//}


void explore(int num){
	vis[num] = cnt;
	for(int i=heads[num];i!=-1;i=graph[i].next)
		if(vis[graph[i].v] == 0){
//			printf("\t\t Explore the point %d, cnt = %d\n",graph[i].v,cnt);
			explore(graph[i].v);		
		}
			
	return;
}
