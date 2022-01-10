#include<bits/stdc++.h>
using namespace std;
struct node{
	int from; int to; int value;
	inline bool operator <(const node &x)const{return value>x.value;}
};
vector<node> graph[200005];
int odd_dis[200005], even_dis[200005];
bool vis[200005];
bool flag = false;
// general parameters.
int n,m,s,e,a,b,c;
long long k;

void bfs();

int main(){
	
	
	scanf("%d%d%d%d%lld",&n,&m,&s,&e,&k);
	//initialize
	for(int i=0;i<=n;i++){
		vis[i] = false;
		even_dis[i] = 214748360;
		odd_dis[i] = 214748360;
	}
	// initialize the boundary
	vis[0] = true;	even_dis[s] = 0; odd_dis[s] = 214748360;
	
	// build a graph.
	for(int i=1;i<=m;i++){
		//a->b		Inverse:b->a
		scanf("%d%d",&a,&b);
		c = 1;
		// One special condition.
		if(a == b && a == s)
			odd_dis[s] = 1;
		graph[a].push_back((node){a,b,c});
		graph[b].push_back((node){b,a,c});
	}
	
	bfs();
	// ����
	if(flag){
		if(((k&1)&&(k>=odd_dis[e]))||(!(k&1) &&(k>=even_dis[e])))
			printf("Yes\n");
		else
			printf("No\n");
	}
	else
		printf("No\n");
	return 0;
}



void bfs(){
	// Main goal: 
	// use the dequeue to drop the "1" at the back and "0" at the front.
	deque<node> deq;
//	deq[ ]����������˫������е�����Ԫ�ء�
//	deq.front()�����ص�һ��Ԫ�ص����á�
//	deq.back()���������һ��Ԫ�ص����á�
//	deq.push_front(x)����Ԫ��x���뵽˫����е�ͷ����
//	deq.pop_front()������˫����еĵ�һ��Ԫ�ء�
//	deq.push_back(x)����Ԫ��x���뵽˫����е�β����
//	deq.pop_back()������˫����е����һ��Ԫ�ء�
	vis[s] = true;
	for(int i=0;i<graph[s].size();i++)
		deq.push_back(graph[s][i]);
	while(!deq.empty()){
		node temp = deq.front();
		deq.pop_front();
		if(vis[temp.to])
			continue;
		vis[temp.to] = true;
		if(temp.to == e) flag = true;
		int tmp_dist = odd_dis[temp.from] + temp.value;
		// ż�� ֻ�����ż����
		if(!(tmp_dist&1)){
			if(even_dis[temp.to]>tmp_dist){
				even_dis[temp.to] = tmp_dist;
				vis[temp.to] = false;
			}
		}
		// ������ֻ����������� 
		tmp_dist = even_dis[temp.from] + temp.value;
		if(tmp_dist&1){
			if(odd_dis[temp.to]>tmp_dist){
				odd_dis[temp.to] = tmp_dist;
				vis[temp.to] = false;
			}
		}
		for(int i=0;i<graph[temp.to].size();i++)
			deq.push_back(graph[temp.to][i]);
	} 	
}
