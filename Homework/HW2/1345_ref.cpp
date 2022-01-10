#include<bits/stdc++.h>
#define db double
#define ll long long
using namespace std;
template<typename T> inline void read(T &x){
	x=0;bool f=0;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())x=x*(T)10+c-'0';
	x=f?-x:x;
}
int n,m,s,t,k;
int head[100005],en;
struct edge{
	int u,v,w,nxt;
}e[200005];
void adde(int u,int v,int w){
	e[++en].u=u,e[en].v=v,e[en].w=w;
	e[en].nxt=head[u],head[u]=en;
//	cerr<<"adde_"<<en<<" "<<e[en].u<<" "<<e[en].v<<" "<<e[en].w<<endl;
}
#define pii pair<int,int>
#define MP(a,b) make_pair(a,b)
#define fi first
#define se second

priority_queue<pii,vector<pii>,greater<pii> > q;
void Dij(){
	q.push(MP(0,s));int cnt=1;
	for(;!q.empty();){
//		pii p=q.pop();
		pii p=q.top();q.pop();
//		cerr<<" now dealing with "<<p.se<<" "<<p.fi<<endl;
		for(int ed=head[p.se],dis;ed;/*cerr<<"	"<<ed<<" "<<e[ed].u<<" "<<e[ed].v<<" "<<e[ed].w<<endl,*/ed=e[ed].nxt){
			dis=p.fi+e[ed].w;
			q.push(MP(dis,e[ed].v));
		}
		if(p.se==t){
			printf("%d ", p.fi);
			if(++cnt>k)return;
		}
	}
//	for(int i=1;i<=n;i++)printf("%d ", dis[i]);puts("");
	for(;cnt<=k;cnt++)printf("-1 ");
}
int main(){
	read(n),read(m),read(s),read(t),read(k);
	for(int i=0,u,v,w;i<m;i++)
		read(u),read(v),read(w),adde(u,v,w);
	Dij();
	return 0;
}
