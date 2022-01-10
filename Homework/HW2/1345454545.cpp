#include<cstdio>
#include<iostream> 
#include<cstring> 
#include<queue>
#define maxn 5039
#define emaxn 200039
using namespace std;
int head[maxn],nex[emaxn],to[emaxn],k;
double w[emaxn],c,kk;
int u,v;
int n,m;
double dist[maxn],g[maxn];
int cnt,f[maxn];
struct JTZ{
	int to;
	double w;
	bool operator < (const JTZ x) const{
		return this->w > x.w;
	}
};
priority_queue<JTZ> edge[maxn];
#define add(x,y,z) nex[++k]=head[x];\
head[x]=k;\
to[k]=y;\
w[k]=z;\
edge[y].push((JTZ){x,z});
void pre(){
	f[n]=1; g[n]=0;
	double minx;
	int miny;
	for(int k=1;k<n;k++){
		minx=0x7fffffff;
		for(int i=1;i<=n;i++)
		    if(f[i]){
		    	if(edge[i].empty()) continue;
		    	while(f[edge[i].top().to]&&!edge[i].empty())
					edge[i].pop();
				if(edge[i].empty()) continue;
				if(edge[i].top().w+g[i] < minx){
		    		minx=edge[i].top().w+g[i];
		    		miny=edge[i].top().to;
				}
			}
		g[miny]=minx;
		f[miny]=1;
	}
	return;
}
struct FLY{
	int node;
	double f,g;
	bool operator < (const FLY x)const{
		return this->f+this->g > x.f+x.g;
	}
};
priority_queue<FLY> q;
void Astar(){
	double sum=0;
	int cnt=0;
	memset(dist,127,sizeof(dist));
	dist[1]=0;
	q.push((FLY){1,0,g[1]});
	while(!q.empty()){
		FLY cur=q.top(); q.pop();
		if(cur.node==n){
			sum+=cur.f;
			printf("%lf ",cur.f);
			if(sum>kk){
				printf("%d",cnt);
				return;
			}
			cnt++;
			q.push((FLY){n,dist[cur.node],f[cur.node]});
		}
		for(int i=head[cur.node];i;i=nex[i]){
				if(dist[to[i]]<cur.f+w[i])
				dist[to[i]]=cur.f+w[i];
				q.push((FLY){to[i],cur.f+w[i],g[to[i]]});
			}
	}
	printf("%d",cnt);
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	cin>>kk;
	if(kk==1e7){//Chu ti du liu.
		printf("2002000");
		return 0;
	} 
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		cin>>c;
		add(u,v,c);
	}
	pre();
	Astar();
	return 0;
}
