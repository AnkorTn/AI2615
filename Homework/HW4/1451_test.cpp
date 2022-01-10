#include <bits/stdc++.h>
 
using namespace std;
const int maxn = 1000;
int pre[maxn];//存储父节点
bool visit[maxn];//DFS标记数组
int newpos[maxn];//遍历序列
int now;
int n, m;
 
int head[maxn];//链式前向星
struct Node
{
    int to;
    int next;
};
Node edge[maxn];
 
void DFS(int x)
{
    newpos[now ++] = x;//记录遍历序列
    for(int k = head[x]; k != -1; k = edge[k].next)
    {
        if(!visit[ edge[k].to ])
        {
            visit[ edge[k].to ] = true;
            pre[edge[k].to] = x;//记录父节点
            DFS(edge[k].to);
        }
    }
}
 
int MVC()
{
    bool s[maxn] = {0};
    bool set[maxn] = {0};
    int ans = 0;
    for(int i = n - 1; i >= 1; i--)  //逆序进行贪心,排除掉其根节点
    {
        int t = newpos[i];
        if(!s[t] && !s[ pre[t] ])  //如果当前节点和其父节点都不属于顶点覆盖集合
        {
            set[ pre[t] ] = true;//把其父节点加入到顶点覆盖集合
            ans ++; //集合内顶点个数加 1
            s[t] = true;//标记当前节点被覆盖
            s[ pre[t] ] = true;//标记其父节点被覆盖
        }
    }
    return ans;
}
 
int main()
{
    /* read Graph message*/ //建图
    memset(visit, false, sizeof(visit));//初始化
    now = 0;
    visit[1] = true;
    pre[1] = 1;
    DFS(1);//从第一个根节点开始寻找遍历序列
    MDS();
    return 0;
}
