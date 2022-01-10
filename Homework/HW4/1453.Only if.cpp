#include<bits/stdc++.h>
#define N 1000005
#define M 1000005
#define INF 100000005
using namespace std;
// 确保三件事情：1.第一轮移动不会冲突	2.每个点至少能找到一条匹配路径	3.每个点的最优路径小于或等于k 
// 因此实际上可以构造拆点的思想 
// 把每个点拆成k个时刻，然后源汇连通应该就可以做了。
// 目前最大的问题是：如何判定第一步移动一定不会冲突 
// 把每层的点拆成两个。即，每层的点我如果选了(u,v)我只能(u,mid)走。然后(mid,1)并且代价均为0.5 
struct edge {
    int next, to, flow;
};
edge e[M * 2]; // back edges
int edge_cnt = 2; // to make reverse(e[x]) = e[x ^ 1], and avoid use number 0
int list_head[N]; // init as 0
int source, sink;	// Save the S and T vertex 
void add_edge (int u, int v, int flow);
int cur[N];   // 
int level[N]; // level graph
int n, m, p, k;
int dfs(int x, int flow);
int dinic();
bool make_level();	// return the level graph if have.
int main(){
	scanf("%d%d%d%d",&n,&m,&p,&k);
	int u,v;
	source = 0; sink = 2*n*(k+1)+1;
	// 每个点自己连通一条单向的边
	for(int i=1;i<=k+1;i++)
		for(int j=1;j<=n;j++){
			add_edge(j+2*(i-1)*n,j+(2*i-1)*n,1);
//			printf("Add edge(%d,%d)\n",j+2*(i-1)*n,j+(2*i-1)*n);
		}
	for(int i=1;i<=p;i++){
		scanf("%d",&u);
		add_edge(source,u,1);
//		printf("Add edge(%d,%d)\n",source,u);
		// add_edge(u,source,1);
	}
	for(int i=1;i<=p;i++){
		scanf("%d",&v);
		add_edge(n*(2*k+1)+v,sink,1); 
//		printf("Add edge(%d,%d)\n",n*(2*k+1)+v,sink);
		// add_edge(sink,n*k+v,1); 
	}
	// n vertices and k rounds
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		for(int j=1;j<=k;j++){
			add_edge((2*j-1)*n+u, 2*j*n+v,1);
//			printf("Add edge(%d,%d)\n",(2*j-1)*n+u,2*j*n+v);
//			add_edge((j-1)*n+u,j*n+v,1);
			if(u!=v){
				add_edge((2*j-1)*n+v, 2*j*n+u,1);
//				printf("Add edge(%d,%d)\n",(2*j-1)*n+v,2*j*n+u);
			}
//				add_edge((j-1)*n+v,j*n+u,1);
//			printf("Add edge for(%d,%d) and (%d,%d)\n",(j-1)*n+u,j*n+v,(j-1)*n+v,j*n+u);
		}
	}
	int flag = dinic();
	if(flag==p)
		printf("Yes\n");
	else
		printf("No\n"); 
//    printf("%d\n",flag);
    return 0;
}

void add_edge (int u, int v, int flow) {
    e[edge_cnt] = {list_head[u], v, flow};
    list_head[u] = edge_cnt++;
    e[edge_cnt] = {list_head[v], u, 0};
    list_head[v] = edge_cnt++;
}

bool make_level(){
	for(int i=1;i<=sink;i++)
		level[i] = INF;
	queue<int>q; q.push(source); level[source] = 0; cur[source] = list_head[source];
    while(!q.empty()){
        int x = q.front();q.pop();
//        printf("Start at %d\n",x);
        for(int i = list_head[x];i;i = e[i].next){
//        	printf("Make level at %d\n", i);
            int y = e[i].to;
            if(e[i].flow > 0 && level[y] == INF){
                q.push(y);
//                printf("Output %d\n",y);
                cur[y] = list_head[y];
                level[y] = level[x] + 1;
                if(y == sink) return true;
            }
        }
    }
//    printf("False\n");
	return false;
}

int dfs(int x, int flow) {
    if (x == sink) return flow;
    int used = 0;
    for (int &i = cur[x]; i != 0; i = e[i].next) // i : reference to cur[x]
        if (e[i].flow > 0 && level[x] + 1 == level[e[i].to]) {
    		int ret = dfs(e[i].to, min(e[i].flow, flow - used));
            used += ret;
//            printf("The flow of the edge (%d,%d) to be declined by %d\n",e[i].to, e[i].flow, ret);
            e[i].flow -= ret;
            e[i ^ 1].flow += ret;
            if (used == flow) break;
        }
    return used;
}
int dinic() {
    int ans = 0;
    while (make_level()) {
        for (int i = source; i <= sink; i++) // initialize cur[]
            cur[i] = list_head[i];
        ans += dfs(source, INF);
//        printf("Ans updated by dfs is: %d \n", ans);
    }
    return ans;
}
