#include <bits/stdc++.h>
 
using namespace std;
const int maxn = 1000;
int pre[maxn];//�洢���ڵ�
bool visit[maxn];//DFS�������
int newpos[maxn];//��������
int now;
int n, m;
 
int head[maxn];//��ʽǰ����
struct Node
{
    int to;
    int next;
};
Node edge[maxn];
 
void DFS(int x)
{
    newpos[now ++] = x;//��¼��������
    for(int k = head[x]; k != -1; k = edge[k].next)
    {
        if(!visit[ edge[k].to ])
        {
            visit[ edge[k].to ] = true;
            pre[edge[k].to] = x;//��¼���ڵ�
            DFS(edge[k].to);
        }
    }
}
 
int MVC()
{
    bool s[maxn] = {0};
    bool set[maxn] = {0};
    int ans = 0;
    for(int i = n - 1; i >= 1; i--)  //�������̰��,�ų�������ڵ�
    {
        int t = newpos[i];
        if(!s[t] && !s[ pre[t] ])  //�����ǰ�ڵ���丸�ڵ㶼�����ڶ��㸲�Ǽ���
        {
            set[ pre[t] ] = true;//���丸�ڵ���뵽���㸲�Ǽ���
            ans ++; //�����ڶ�������� 1
            s[t] = true;//��ǵ�ǰ�ڵ㱻����
            s[ pre[t] ] = true;//����丸�ڵ㱻����
        }
    }
    return ans;
}
 
int main()
{
    /* read Graph message*/ //��ͼ
    memset(visit, false, sizeof(visit));//��ʼ��
    now = 0;
    visit[1] = true;
    pre[1] = 1;
    DFS(1);//�ӵ�һ�����ڵ㿪ʼѰ�ұ�������
    MDS();
    return 0;
}
