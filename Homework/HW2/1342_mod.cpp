#include<bits/stdc++.h>
#define LL long long
using namespace std;
inline int read(){
    int x=0,k=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')k=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*k;
}
struct Edge{
    long long u,v,w,next;
}e[500005];
struct node{
    long long w,now;
    inline bool operator <(const node &x)const{
        return w>x.w;
    }
};
priority_queue<node>q;
long long head[500005],cnt,n,m,s,t,vis[500005];
double dis[500005];
namespace qaq{
	inline void add(int u,int v,int w){
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
    	n=read(),m=read(),s=read(),t=read();
	    for(int i=1,x,y,z;i<=m;i++){
	        x=read(),y=read(),z=read();
	        add(x,y,z);
	        add(y,x,z);
	    }
	    dijkstra();
	    printf("%lld", dis[t]);
	    return 0;
    }
}
int main(){
    qaq::main();
    return 0;
}
