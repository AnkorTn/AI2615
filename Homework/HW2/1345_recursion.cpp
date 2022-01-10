#include<bits/stdc++.h>
#define LL long long
using namespace std;
inline LL read(){
    LL x=0,k=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')k=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*k;
}
struct Edge{
    long long u,v,w,next;
}e[200005];
struct node{
    long long w,now;
    inline bool operator <(const node &x)const{
        return w>x.w;
    }
};
priority_queue<node>q;
LL head[200005],cnt,n,m,s,t,k,vis[200005],dis[12][200005];

// collecting the same edge and push only one edge in the graph.
struct tmp{
	long long u, v, w;
	inline bool operator <(const tmp &x)const{
		if(u == x.u){
			if(v == x.v)
        		return w > x.w;
        	else
        		return v > x.v;
		}
        return u > x.u;
    }
}temprs[200005];

namespace qaq{
	inline void add(LL u,LL v,LL w){
	    e[++cnt].u=u;
	    e[cnt].v=v;
	    e[cnt].w=w;
	    e[cnt].next=head[u];
	    head[u]=cnt;
	}
	void dijkstra(){
		for(int j=1;j<=k;j++)
	    	for(int i=1;i<=n;i++)
	        	dis[j][i]=210000000000000;
	    dis[1][s]=0;
	    q.push((node){0,s});
	    while(!q.empty()){
	        node x=q.top();
	        q.pop();
	        LL u=x.now;
	        if(dis[k][u]<x.w)
	        	continue;
	        for(int i=head[u];i;i=e[i].next){
	            LL v   = e[i].v;
	            LL tes = x.w + e[i].w;
//	            printf("\t\t tes = %lld\n", tes);
				for(int j=1;j<=k;j++){
					if(dis[j][v] == tes)
						break;
					if(dis[j][v] > tes){
						
						for(int ii = k;ii>=j+1;ii--)
							dis[ii][v] = dis[ii-1][v];
						if(v == t){
//							printf("This time we update the final path with value tes = %lld and the place is %d %d = %d:\n",tes,j,v,dis[j][v] > tes);
//							for(int jj=1;jj<=k;jj++)
//								printf("%lld  ",dis[jj][t]);
//							printf("\n");
						}
						dis[j][v] = tes;
						q.push((node){dis[j][v],v});
						break;
					}
				}
	        }
	    }
	}
    int main(){
       	n=read(),m=read(),s=read(),t=read(),k=read();
//    	for(int i=0;i<m;i++)
//	    	scanf("%lld%lld%lld",&temprs[i].u,&temprs[i].v,&temprs[i].w);
//	    sort(temprs,temprs+m);
//	    add(temprs[0].u,temprs[0].v,temprs[0].w);
////	    printf("%lld\t%lld\t%lld\n",temprs[0].u,temprs[0].v,temprs[0].w);
//	    for(int i=1;i<m;i++){
//	    	if(temprs[i].u == temprs[i-1].u && temprs[i].v == temprs[i-1].v && temprs[i].w == temprs[i-1].w)
//	    		continue;
//	    	add(temprs[i].u,temprs[i].v,temprs[i].w);
////	    	printf("%lld\t%lld\t%lld\n",temprs[i].u,temprs[i].v,temprs[i].w);
//		}
//
	    for(int i=1,x,y,z;i<=m;i++){
	        x=read(),y=read(),z=read();
	        add(x,y,z);
	    }
	    dijkstra();
	    int i=2, cnt_i = 1;
	    printf("%lld ",dis[1][t]);
	    for(;i<=k;i++){
	    	if(dis[i][t]!=210000000000000){
	    		if(dis[i][t] != dis[i-1][t]){
	    			printf("%lld ", dis[i][t]);
	    			cnt_i++;
				}
			}
	    	else
	    		break;
		} 	
		for(;cnt_i<k;cnt_i++)
			printf("-1 ");
	    return 0;
    }
}
int main(){
    qaq::main();
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
