#include<bits/stdc++.h>
using namespace std;
struct node{
	int from; int to; int value;
	inline bool operator <(const node &x)const{return value>x.value;}
};
vector<node> graph[1000005];
int dis[1000005];
bool vis[1000005];
// general parameters.
int n,m,s,e,a,b,c;

void bfs();

int main(){
	
	
	scanf("%d%d%d%d",&n,&m,&s,&e);
	//initialize
	for(int i=0;i<=n;i++){
		vis[i] = false;
		dis[i] = 214748360;
	}
	// initialize the boundary
	vis[0] = true;	dis[s] = 0;
	
	// build a graph.
	for(int i=1;i<=m;i++){
		//a->b		Inverse:b->a
		scanf("%d%d%d",&a,&b,&c);
		if(a==b)
			continue;
		graph[a].push_back((node){a,b,c});
		graph[b].push_back((node){b,a,c});
	}
	
	bfs();
	
	printf("%d\n",dis[e]);
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
		if(graph[s][i].value == 0)
			deq.push_front(graph[s][i]);
		else
			deq.push_back(graph[s][i]);
	while(!deq.empty()){
		node temp = deq.front();
		deq.pop_front();
		if(vis[temp.to])
			continue;
		vis[temp.to] = true;
		dis[temp.to] = min(dis[temp.to], dis[temp.from] + temp.value);
		for(int i=0;i<graph[temp.to].size();i++)
			if(graph[temp.to][i].value == 0)
				deq.push_front(graph[temp.to][i]);
			else
				deq.push_back(graph[temp.to][i]);
	} 	
}
