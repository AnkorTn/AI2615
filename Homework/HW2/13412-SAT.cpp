#include<bits/stdc++.h>
#define LL long long
using namespace std;
typedef pair<int,int> pill;
struct Edge{
	int to;
	int next;
	int dis;
}edge[500005];
int tot=0,head[500005],vis[500005],dis[500005],n,m,s,numb,x,y,z;
priority_queue<pill,vector<pill>,greater<pill> >q;
namespace qaq{
	inline void add(int u,int v,int dis){
		edge[++tot].next=head[u];
		edge[tot].to=v;
		edge[tot].dis=dis;
		head[u]=tot;
	}
    int main(){
    	scanf("%d%d%d",&n,&m,&s);
    	for(register int i=0;i<=n;i++)	head[i]=-1;
    	for(register int i=0;i<=n;i++)	dis[i]=2147483647;
    	for(register int i=0;i<=n;i++)	vis[i]=0;
    	for(register int i=1;i<=m;i++){
    		scanf("%d%d%d",&x,&y,&z);
    		add(x,y,z);
    	}
    	dis[s]=0;
    	q.push(make_pair(dis[s],s));
    	while(!q.empty()){
    		pill temp=q.top();
    		q.pop();
    		numb=temp.second;
    		if(vis[numb])continue;
    		vis[numb]=1;
    		for(int i=head[numb];i!=-1;i=edge[i].next){
    			if(dis[edge[i].to]>dis[numb]+edge[i].dis){
    				dis[edge[i].to]=dis[numb]+edge[i].dis;
    				q.push(make_pair(dis[edge[i].to],edge[i].to));
    			}
    		}
    	}
    	for(register int i=1;i<n;i++)	printf("%d ",dis[i]);
    	printf("%d\n",dis[n]);
        return 0;
    }
}
int main(){
    qaq::main();
    return 0;
}
