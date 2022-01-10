#include<bits/stdc++.h>
#define LL long long
using namespace std;
inline long long read(){
    long long x=0,k=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')k=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*k;
}
struct Edge{
    long long u,v,w,next;
}e[200005], e_inv[200005];
struct nodde{
    long long w,now;
    inline bool operator <(const nodde &x)const{
        return w >x.w;
    }
};
priority_queue<nodde>qq,qw;

long long head[200005],head_inv[200005],cnt,n,m,s,t,k,dis[200005], diss[200005];

struct node{
    long long w,now;
    inline bool operator <(const node &x)const{
        return w + dis[now] >x.w + dis[x.now];
    }
};
priority_queue<node>q;

int vis_cnt[200005];

int ans_cnt = 0;
long long ans[100005];
bool vis[200005];

namespace qaq{
	
	bool finnd(long long x){
		for(int i=0;i<ans_cnt;i++)
			if(x == ans[i])
				return true;
		return false;
	}
	
	inline void add(int u,int v,int w){
	    e[++cnt].u=u;
	    e[cnt].v=v;
	    e[cnt].w=w;
	    e[cnt].next=head[u];
	    head[u]=cnt;
	    e_inv[cnt].u = v;
	    e_inv[cnt].v = u;
	    e_inv[cnt].w = w;
	    e_inv[cnt].next = head[v];
	    head_inv[v] = cnt;
	}
	void dijkstra_inv(){
	    for(int i=1;i<=n;i++)
	        dis[i]=214748364700000;
	    dis[t]=0;
	    qq.push((nodde){0,t});
	    while(!qq.empty()){
	        nodde x=qq.top();
	        qq.pop();
	        long long u=x.now;
	        if(vis[u]) continue; 
	        vis[u]=true;
	        for(int i=head[u];i;i=e[i].next){
	            long long v=e[i].v;
	            if(dis[v]>dis[u]+e[i].w){
	            	dis[v]=dis[u]+e[i].w;
	            	qq.push((nodde){dis[v],v});
	            }
	        }
	    }
	}
	void dijkstra(){
	    q.push((node){0,s});
	    while(!q.empty()){
	        node x=q.top();	q.pop();
	        long long u=x.now;
//	        printf("Choose the node %d to expend:\n", u);
	        for(int i=head[u];i;i=e[i].next){
//	        	if(vis_cnt[e[i].v] <= 50){
//	        		printf("\tPush_node: %d\n",e[i].v);
	        		q.push((node){x.w+e[i].w,e[i].v});
//	        		vis_cnt[e[i].v]++;
//				}
	        }
	        if(x.now == t){
//	        	if(finnd(x.w))
//	        		continue;
//	        	printf("\t\t%lld\n",x.w);
	        	ans[ans_cnt++] = x.w;
	        	if(ans_cnt >= k) return;
			}
	    }
	    return;
	}
	
    int main(){
    	memset(vis, false, sizeof(vis));
    	memset(vis_cnt, 0, sizeof(vis_cnt));
    	n=read(),m=read(),k=read();
    	s = 1; t = n;
	    for(int i=1,x,y,z;i<=m;i++){
	        x=read(),y=read(),z=read();
	        add(y,x,z);
	    }
	    dijkstra_inv();
	    dijkstra();
	    sort(ans, ans+ans_cnt);
	    if(ans_cnt>= k)
	    	ans_cnt = k;
	    for(int i=0;i<ans_cnt;i++)
	    	printf("%lld\n",ans[i]);
	    if(k-ans_cnt>0)
	    	printf("-1\n");
	    return 0;
    }
}
int main(){
    qaq::main();
    return 0;
}
