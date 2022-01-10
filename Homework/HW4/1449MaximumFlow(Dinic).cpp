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
