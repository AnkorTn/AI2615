#include<bits/stdc++.h>
#define LL long long
using namespace std;
struct Edge{
    long long u,v,w,next;
}e[200005], e_rev[200005];
struct node{
    long long w,now;
    inline bool operator <(const node &x)const{
        return w>x.w;
    }
};
long long head[200005],head_rev[200005],cnt,dis[200005];
bool vis[200005];		//是否访问过，逆向跑DJ的方法。 
priority_queue<node>q;	//逆向跑dj找从t->s的最短路 
int n,m,s,t,k;


struct new_node{
	long long w, now;
	inline bool operator <(const new_node &x)const{
        return w + dis[now] >x.w + dis[x.now];
    }
};
priority_queue<new_node>p;	//根据一定的搜索规则来遍历
int cnt_new[200005];
int ans[200005], ans_cnt = 0;
namespace qaq{
	inline void add(int u,int v,int w){
		// 正向 
	    e[++cnt].u=u;		e[cnt].v=v;			e[cnt].w=w;			e[cnt].next=head[u];			head[u]=cnt;
	    // 逆向 
	    e_rev[cnt].u=v;		e_rev[cnt].v=u;		e_rev[cnt].w=w;		e_rev[cnt].next=head_rev[v];	head_rev[v]=cnt;
	}
	void dijkstra(){
		memset(vis, false, sizeof(vis));
	    for(int i=1;i<=n;i++)
	        dis[i]=214748364700000;
	    dis[t]=0;
	    q.push((node){0,t});
	    while(!q.empty()){
	        node x=q.top();
	        q.pop();
	        long long u=x.now;
	        if(vis[u]) continue; 
	        vis[u]=1;
	        for(int i=head_rev[u];i;i=e_rev[i].next){
	            long long v=e_rev[i].v;
	            if(dis[v]>dis[u]+e_rev[i].w){
	            	dis[v]=dis[u]+e_rev[i].w;
	            	q.push((node){dis[v],v});
	            }
	        }
	    }
	    for(int i=1;i<=n;i++)
			printf("%lld ",dis[i]); 
	}
	
	void new_dijkstra(int maxn){
		memset(cnt_new,0,sizeof(cnt_new));
		p.push((new_node){0,s});
		int pre = s;
		while(!p.empty()){
			new_node x = p.top();	p.pop();
			long long u = x.now;	cnt_new[u]++;
			if(cnt_new[u] > k) continue;
			if(u == t){
				ans[ans_cnt++] = x.w;
				continue;
			}
			for(int i=head[u]; i; i=e[i].next)
				p.push((node){x.w + e[i].w});			
			
		}
	}
	
	
        if(zz.f>W)return;//判断是否退出
        int u=zz.d;
        shrt[u]++;//到达u的次数加1
        if(u==n)//如果是终点就要减一下路径长度，累加一样的，只要改一改前面的判断就好了
        {
            W-=zz.f;ans++;continue;
        }
        if(shrt[u]>kk)continue;//到达中间某个点超过K次也退出
        for(int i=head[u];i;i=l[i].next)
        {
            mm.d=l[i].to,mm.h=zz.h+l[i].w,mm.f=mm.h+ch[l[i].to];//保留所有的路径
            q.push(mm);//丢入堆中
        }
    }
}
    int main(){
    	scanf("%d%d%d%d%d",&n,&m,&s,&t,&k);
    	int x,y; long long z;
	    for(int i=1;i<=m;i++){
	    	scanf("%d%d%lld",&x,&y,&z);
	        add(x,y,z);
	    }
	    dijkstra();
	    return 0;
    }
}
int main(){
    qaq::main();
    return 0;
}
