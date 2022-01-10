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
    bool selected;
}e[200005];
struct node{
	// place is used to find the selected edge.
    long long w,now, place;
    inline bool operator <(const node &x)const{
        return w>x.w;
    }
};
priority_queue<node>q;
long long head[200005],cnt,n,m,s,t,vis[200005],dis[200005];
int path[200005];
stack<int>stk;
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
	    q.push((node){0,s,0});
	    while(!q.empty()){
	        node x=q.top();
	        q.pop();
	        long long u=x.now;
	        if(vis[u]) continue; 
	        vis[u]=1;
	        for(int i=head[u];i;i=e[i].next){
	            long long v=e[i].v;
	            if(dis[v]>dis[u]+e[i].w){
					path[v] = e[i].u;
	            	dis[v]=dis[u]+e[i].w;
	            	q.push((node){dis[v],v,i});
	            }
	        }
	    }
	}
	// This is a program showing the shortest path from s to t and give the exact path.
    int main(){
    	memset(path,-1,sizeof(path));
    	n=read(),m=read(),s=read(),t=read();
	    for(int i=1,x,y,z;i<=m;i++){
	        x=read(),y=read(),z=read();
	        add(x,y,z);
	    }
	    dijkstra();
	    printf("%lld\n", dis[t]);
	    stk.push(t);
	    int tmp = path[t];
	    while(tmp != s){
	    	stk.push(tmp);
	    	tmp = path[tmp];
		}
		stk.push(s);
		while(!stk.empty()){
			tmp = stk.top();
			stk.pop();
			if(!stk.empty())
				printf("%d---->",tmp);
			else
				printf("%d\n",tmp);
		}
	    return 0;
    }
}
int main(){
    qaq::main();
    return 0;
}
