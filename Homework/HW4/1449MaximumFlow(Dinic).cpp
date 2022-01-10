#include<bits/stdc++.h>
#define N 10005
#define M 1000005
#define INF 100000005
using namespace std;
// Codes provided by TA. fstqwq. url: https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1449 
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
int n, m;
int dfs(int x, int flow);
int dinic();
bool make_level();	// return the level graph if have.
int main(){
	scanf("%d%d",&n,&m);
	int u,v,c;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&c);
		add_edge(u,v,c);
	}
	source = 1; sink = n;
    printf("%d\n",dinic());
    return 0;
}

void add_edge (int u, int v, int flow) {
    e[edge_cnt] = {list_head[u], v, flow};
    list_head[u] = edge_cnt++;
    e[edge_cnt] = {list_head[v], u, 0};
    list_head[v] = edge_cnt++;
}

bool make_level(){
	for(int i=1;i<=n;i++)
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
            e[i].flow -= ret;
            e[i ^ 1].flow += ret;
            if (used == flow) break;
        }
    return used;
}
int dinic() {
    int ans = 0;
    while (make_level()) {
        for (int i = 1; i <= n; i++) // initialize cur[]
            cur[i] = list_head[i];
        ans += dfs(source, INF);
    }
    return ans;
}
// Dinic's Algorithm
/* Refferrence: https://blog.csdn.net/weixin_30729609/article/details/99581407
初始化，计算剩余图;
while （BFS()）{　　　　 // BFS过程的作用：1，计算层次图；2，当汇点不再层次图内时返回0
	path.clear();
	源点入栈path;　　　 // 栈path保存层次图内从原点到终点的可行路径
	while (源点的出度不为0){
		u <- path.top;
		if  (u != 汇点){　　　　　　　 // 在层次图内寻找一条从起点到终点的路径
			if  (u出度大于0)
				将层次图内与u相连的点v入栈；
			else{
				u出栈；　　　　　　 // 从path中删除
				u的level = 正无穷；    // 从层次图中删除
			}
		}
		else{　　　　　　　　　 // 对路径增广
			在剩余图中沿P增广；
			令path.top为从起点可到达的最后一个顶点；
		}
	}
}
*/
