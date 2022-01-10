#include<bits/stdc++.h>
#define LL long long
using namespace std;
struct Edge{
    long long u,v,w,next;
}e[1000005];
struct node{
    long long w,now;
    inline bool operator <(const node &x)const{
        return w>x.w;
    }
};
priority_queue<node>q;
long long head[1000005],cnt,n,m,s,t,vis[1000005],dis[1000005];
void add(int u,int v,int w){
    e[++cnt].u=u;
    e[cnt].v=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void dijkstra(){
    for(int i=1;i<=n;i++)
        dis[i]=214748364700000;
    dis[s]=0;
    q.push((node){0,s});
    while(!q.empty()){
        node x=q.top();
        q.pop();
        long long u=x.now;
        if(vis[u]) continue; 
        vis[u]=1;
        for(int i=head[u];i;i=e[i].next){
            long long v=e[i].v;
            if(dis[v]>dis[u]+e[i].w){
            	dis[v]=dis[u]+e[i].w;
            	q.push((node){dis[v],v});
            }
        }
    }
}
int main(){
	scanf("%lld%lld%lld%lld",&n,&m,&s,&t);
	long long x,y,z;
    for(int i=1;i<=m;i++){
    	scanf("%lld%lld%lld",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
    dijkstra();
    printf("%lld\n", dis[t]);
    return 0;
}
