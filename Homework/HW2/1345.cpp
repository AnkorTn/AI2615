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
bool vis[200005];		//�Ƿ���ʹ���������DJ�ķ����� 
priority_queue<node>q;	//������dj�Ҵ�t->s�����· 
int n,m,s,t,k;


struct new_node{
	long long w, now;
	inline bool operator <(const new_node &x)const{
        return w + dis[now] >x.w + dis[x.now];
    }
};
priority_queue<new_node>p;	//����һ������������������
int cnt_new[200005];
int ans[200005], ans_cnt = 0;
namespace qaq{
	inline void add(int u,int v,int w){
		// ���� 
	    e[++cnt].u=u;		e[cnt].v=v;			e[cnt].w=w;			e[cnt].next=head[u];			head[u]=cnt;
	    // ���� 
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
	
	
        if(zz.f>W)return;//�ж��Ƿ��˳�
        int u=zz.d;
        shrt[u]++;//����u�Ĵ�����1
        if(u==n)//������յ��Ҫ��һ��·�����ȣ��ۼ�һ���ģ�ֻҪ��һ��ǰ����жϾͺ���
        {
            W-=zz.f;ans++;continue;
        }
        if(shrt[u]>kk)continue;//�����м�ĳ���㳬��K��Ҳ�˳�
        for(int i=head[u];i;i=l[i].next)
        {
            mm.d=l[i].to,mm.h=zz.h+l[i].w,mm.f=mm.h+ch[l[i].to];//�������е�·��
            q.push(mm);//�������
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
