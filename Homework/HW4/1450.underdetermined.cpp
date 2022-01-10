#include<bits/stdc++.h>
#define N 205
#define M 100005
#define INF 100000005
using namespace std;
// Codes provided by TA. fstqwq. url: https://acm.sjtu.edu.cn/OnlineJudge/problem?problem_id=1449 
// Main idea is provided by Biaoshuai Tao. He told me that this is a matching problem.
struct edge {
    int next, to, flow, from;
};
edge e[M * 2]; // back edges
int edge_cnt = 2; // to make reverse(e[x]) = e[x ^ 1], and avoid use number 0
int list_head[N]; // init as 0
int source, sink;	// Save the S and T vertex 
void add_edge (int u, int v, int flow);
int cur[N];   // 
int level[N]; // level graph
int n;
int dfs(int x, int flow);
int dinic();
int graph[N][N];
bool vis1[N], vis2[N];
bool make_level();	// return the level graph if have.
int main(){
	scanf("%d",&n);
	int c;
	for(int u=1;u<=n;u++)
		for(int v=1;v<=n;v++){
			scanf("%d",&c);
			graph[u][v] = 0;
			if(c){
				if(!vis1[u]){
					add_edge(0,u,1);
					vis1[u] = true;
				}
				add_edge(u,n+v,1);
				if(!vis2[n+v]){
					add_edge(n+v,2*n+1,1);
					vis2[n+v] = true;
				}
			}				
		}
	source = 0; sink = 2*n+1;
	if(dinic()<n)
		printf("No\n");
	else{
		// Exists solution and I should print it out.
		// Edge from 2 to 6 has capacity 1
		for(int i=2;i<=edge_cnt;i++)
			if(e[i].flow == 1 && e[i].from > e[i].to){
//				printf("Edge from %d to %d has capacity %d\n",e[i].from,e[i].to,e[i].flow);
				graph[e[i].to][e[i].from-n] = 1;
			}
		printf("Yes\n");
		for(int u=1;u<=n;u++){
			for(int v=1;v<n;v++)
				printf("%d ",graph[u][v]);
			printf("%d\n",graph[u][n]);
		}
			
//				printf("Edge from %d to %d has capacity %d\n",e[i].from,e[i].to,e[i].flow);
	}
    return 0;
}

void add_edge (int u, int v, int flow) {
    e[edge_cnt] = {list_head[u], v, flow, u};
    list_head[u] = edge_cnt++;
    e[edge_cnt] = {list_head[v], u, 0, v};
    list_head[v] = edge_cnt++;
}

bool make_level(){
	for(int i=1;i<=2*n+1;i++)
		level[i] = INF;
	queue<int>q; q.push(source); level[source] = 0; cur[source] = list_head[source];
    while(!q.empty()){
        int x = q.front();q.pop();
//        printf("Start at %d\n",x);
        for(int i = list_head[x];i;i = e[i].next){
            int y = e[i].to;
//            printf("Make level at %d, the edge is (%d,%d,%d), level[%d] = %d\n", i, x, y, e[i].flow,x, level[x]);
            if(e[i].flow > 0 && level[y] == INF){
                q.push(y);
//                printf("Output %d\n",y);
                cur[y] = list_head[y];
                level[y] = level[x] + 1;
//                printf("Correctly Make level at %d, the edge is (%d,%d,%d), level[%d] = %d\n", i, x, y, e[i].flow, y, level[y]);
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
//    	printf("Yes and continue\n");
        for (int i = 0; i <= 2*n+1; i++) // initialize cur[]
            cur[i] = list_head[i];
        ans += dfs(source, INF);
    }
    return ans;
}
// Dinic's Algorithm
/* Refferrence: https://blog.csdn.net/weixin_30729609/article/details/99581407
��ʼ��������ʣ��ͼ;
while ��BFS()��{�������� // BFS���̵����ã�1��������ͼ��2������㲻�ٲ��ͼ��ʱ����0
	path.clear();
	Դ����ջpath;������ // ջpath������ͼ�ڴ�ԭ�㵽�յ�Ŀ���·��
	while (Դ��ĳ��Ȳ�Ϊ0){
		u <- path.top;
		if  (u != ���){�������������� // �ڲ��ͼ��Ѱ��һ������㵽�յ��·��
			if  (u���ȴ���0)
				�����ͼ����u�����ĵ�v��ջ��
			else{
				u��ջ�������������� // ��path��ɾ��
				u��level = �����    // �Ӳ��ͼ��ɾ��
			}
		}
		else{������������������ // ��·������
			��ʣ��ͼ����P���㣻
			��path.topΪ�����ɵ�������һ�����㣻
		}
	}
}
*/
