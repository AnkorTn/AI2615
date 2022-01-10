#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL read(){
    int x=0,k=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')k=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*k;
}
LL n,m,s,t,k;

// dijkstra algorithm.
LL dis[100005];
bool vis[100005];

struct node{
	LL w, v;
	inline bool operator < (const node &a)const{
		return w > a.w;
	}
};
vector<node>graph[100005],graph_reverse[100005];

// A star algorithm.
struct edge{
	LL v , Fx , Gx;
	inline bool operator <(const edge &a)const{
		return Fx + Gx > a.Fx + a.Gx;
	}
};

priority_queue<node>q;
void Dijkstra(){
	long long u, v, w;
	memset(vis, false, sizeof(vis));
	for(LL i=1;i<=n;i++)
	    dis[i]=214748364700000;
	dis[t]=0;
    q.push((node){0,t});
    while(!q.empty()){
        node x=q.top();		q.pop();	u=x.v;
        if(vis[u]) continue; 	vis[u]=1;
        for(LL i=0;i<graph_reverse[u].size();i++){
            v = graph_reverse[u][i].v;
            w = graph_reverse[u][i].w + x.w;
            if(dis[v]>w){
            	dis[v]=w;
            	q.push((node){w,v});
            }
        }
    }
}

// BFS algorithm based on some property.
// 判断这个点被访问了多少次，及时止损退出。 
LL cnt[100005], ans_cnt;
LL ans[100005], ans_front = 0;
priority_queue<edge>que;
void Astar(){
	ans_cnt = 0;
	memset(cnt,0,sizeof(cnt));
	que.push((edge){s,0,0});
	edge tmp;	LL v , Fx , Gx;
	LL prev = -1;
	while(!que.empty()){
		tmp = que.top(); que.pop();
		v = tmp.v , Fx = tmp.Fx , Gx = tmp.Gx;
		cnt[v]++;
		if(v == t){
			if(prev != Fx + Gx){
				prev = Fx + Gx;
				ans[ans_front++] = prev;
				ans_cnt++;
			}
			else
				cnt[v]--;
		}
		if(cnt[v] == k)
			break;
		if(cnt[v] > k)	continue;
		LL to_v , to_fx , to_gx;
		for(LL i=0;i<graph[v].size();i++){
			to_v = graph[v][i].v;
			to_fx = Fx + graph[v][i].w;
			to_gx = dis[to_v];
			que.push((edge){to_v , to_fx , to_gx});
		}
	}
	return;
}

// Combination
struct Edge{
    long long u,v,w,next;
}e[200005];
struct Node{
    long long w,now;
    inline bool operator <(const Node &x)const{
        return w>x.w;
    }
};
priority_queue<Node>qq;
LL head[200005],ccnt=0,dist[12][100005];
inline void add(LL u,LL v,LL w){
    e[++ccnt].u=u;
    e[ccnt].v=v;
    e[ccnt].w=w;
    e[ccnt].next=head[u];
    head[u]=ccnt;
}
void new_dijkstra(){
	for(int j=1;j<=k;j++)
    	for(int i=1;i<=n;i++)
        	dist[j][i]=210000000000000;
    dist[1][s]=0;
    qq.push((Node){0,s});
    while(!qq.empty()){
        Node x=qq.top();
        qq.pop();
        LL u=x.now;
        if(dist[k][u]<x.w)
        	continue;
        for(int i=head[u];i;i=e[i].next){
            LL v   = e[i].v;
            LL tes = x.w + e[i].w;
			for(int j=1;j<=k;j++){
				if(dist[j][v] == tes)
					break;
				if(dist[j][v] > tes){
					for(int ii = k;ii>=j+1;ii--)
						dist[ii][v] = dist[ii-1][v];
					dist[j][v] = tes;
					qq.push((Node){dist[j][v],v});
					break;
				}
			}
        }
    }
}
int main(){
	scanf("%lld%lld%lld%lld%lld",&n,&m,&s,&t,&k);
	LL u, v, w;
	for(int i = 1 ; i <= m ; i++){
		scanf("%lld%lld%lld",&u,&v,&w);
		add(u,v,w);
		graph[u].push_back((node){w, v});
		graph_reverse[v].push_back((node){w, u});
	}
	Dijkstra();
	Astar();
	new_dijkstra();
	for(int i=1;i<=k;i++)
		if(dist[i][t]!=210000000000000)
			ans[ans_front++] = dist[i][t];
	sort(ans,ans+ans_front);
	int anss_cnt = 0;
	printf("%lld ",ans[anss_cnt++]);
	for(int i=1;i<ans_front;i++){
		if(ans[i]!=ans[i-1]){
			printf("%lld ",ans[i]);
			anss_cnt++;
		}
		if(anss_cnt>=k)
			break;
	}
	for(;anss_cnt<k;anss_cnt++)
		printf("-1 ");
	return 0;
}
/*
0的情况需要考虑这个数据 
3 8 1 3 10
1 2 0
2 3 0
1 3 1
1 2 1
1 2 1
2 1 0
1 2 1
2 1 1

终点到达后不应该进行额外拓展
2 8 1 2 10
1 2 1
2 1 1
1 2 2
2 1 2
1 2 3
2 1 3
1 2 5
2 1 5

1 2 1
1 2 1
1 2 3
1 2 1
2 3 1
2 1 1
1 3 2
*/
