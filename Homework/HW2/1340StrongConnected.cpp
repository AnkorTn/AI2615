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
	//����ڼ������ڴ����ݹ���ǵ㡣
    DFN[x]=LOW[x]=++tot;// �½���ĳ�ʼ����
    s[++ind]=x;//��վ
    vis[x]=1;//��ʾ��ջ��
    for(int i=heads[x];i!=-1;i=edge[i].next){
        if(!DFN[edge[i].v]) {//���û���ʹ�
            tarjan(edge[i].v);//���½������죬��ʼ�ݹ�
            LOW[x]=min(LOW[x],LOW[edge[i].v]);//�ݹ�������Ƚ�˭��˭�Ķ��ӣ����ף��������Ķ�Ӧ��ϵ���漰��ǿ��ͨ����������С�������顣
        }
        else if(vis[edge[i].v ]){  //������ʹ������һ���ջ�
            LOW[x]=min(LOW[x],DFN[edge[i].v]);//�Ƚ�˭��˭�Ķ��ӣ����ס��������Ӷ�Ӧ��ϵ
        }
    }
    if(LOW[x]==DFN[x]) {
	//����������ǿ��ͨ�������������С����
		long long cnt = 0;
        do{
            //printf("%d ",s[ind]);
            vis[s[ind]]=0;
            ind--;
            cnt++;
        }while(x!=s[ind+1]);//��ջ�����������
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
		 	tarjan(i);//�������û�з��ʹ����ʹӴ˵㿪ʼ����ֹͼû����
	printf("%lld\n",ans);
    return 0;
}

//Tarjan�㷨 
//Copyrights:https://blog.csdn.net/qq_34374664/article/details/77488976
