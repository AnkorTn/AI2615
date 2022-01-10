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
	// 奇数
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
//	deq[ ]：用来访问双向队列中单个的元素。
//	deq.front()：返回第一个元素的引用。
//	deq.back()：返回最后一个元素的引用。
//	deq.push_front(x)：把元素x插入到双向队列的头部。
//	deq.pop_front()：弹出双向队列的第一个元素。
//	deq.push_back(x)：把元素x插入到双向队列的尾部。
//	deq.pop_back()：弹出双向队列的最后一个元素。
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
		// 偶数 只会更新偶数边
		if(!(tmp_dist&1)){
			if(even_dis[temp.to]>tmp_dist){
				even_dis[temp.to] = tmp_dist;
				vis[temp.to] = false;
			}
		}
		// 奇数，只会更新奇数边 
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
