#include<bits/stdc++.h>
using namespace std; 
struct node {
    int v,next;
}edge[100005];
int DFN[100005],LOW[100005];
int s[100005],heads[100005],vis[100005],cnt,tot,ind;
long long ans = 0;
void add(int x,int y){
    edge[++cnt].next=heads[x];
    edge[cnt].v = y;
    heads[x]=cnt;
    return ;
}
void tarjan(int x){
	//代表第几个点在处理。递归的是点。
    DFN[x]=LOW[x]=++tot;// 新进点的初始化。
    s[++ind]=x;//进站
    vis[x]=1;//表示在栈里
    for(int i=heads[x];i!=-1;i=edge[i].next){
        if(!DFN[edge[i].v]) {//如果没访问过
            tarjan(edge[i].v);//往下进行延伸，开始递归
            LOW[x]=min(LOW[x],LOW[edge[i].v]);//递归出来，比较谁是谁的儿子／父亲，就是树的对应关系，涉及到强连通分量子树最小根的事情。
        }
        else if(vis[edge[i].v ]){  //如果访问过，并且还在栈里。
            LOW[x]=min(LOW[x],DFN[edge[i].v]);//比较谁是谁的儿子／父亲。就是链接对应关系
        }
    }
    if(LOW[x]==DFN[x]) {
	//发现是整个强连通分量子树里的最小根。
		long long cnt = 0;
        do{
            //printf("%d ",s[ind]);
            vis[s[ind]]=0;
            ind--;
            cnt++;
        }while(x!=s[ind+1]);//出栈，并且输出。
        ans += (cnt*(cnt-1))/2;
        //printf("\n");
    }
    return ;
 }
int main(){
    memset(heads,-1,sizeof(heads));
    int n, m, x, y;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    for(int i=1;i<=n;i++)
        if(!DFN[i])
		 	tarjan(i);//当这个点没有访问过，就从此点开始。防止图没走完
	printf("%lld\n",ans);
    return 0;
}

//Tarjan算法 
//Copyrights:https://blog.csdn.net/qq_34374664/article/details/77488976
