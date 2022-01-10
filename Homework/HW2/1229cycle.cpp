#include<bits/stdc++.h>
using namespace std; 
vector<int> Parent;
vector<int> edges[100005];
int findSet(int x){
    if(Parent[x] == -1)
        return x; // x is root
    Parent[x] = findSet(Parent[x]);
    return Parent[x];
}
void UnionSet(int x, int y){
    int a = findSet(x);
    int b = findSet(y);
    Parent[b] = a;
}
int main(){
    int n, m, a, b;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    	Parent.push_back(-1);
    for(int i = 0; i < m; i++){
        scanf("%d%d",&a,&b);
        edges[a].push_back(b);
    }
    
    for(int v = 1; v <= n; v++){
        for(int i = 0; i < edges[v].size(); i++){
            int w = edges[v][i];
            int f_v = findSet(v);
            int f_w = findSet(w);
//            printf("xp = %d   and yp = %d   \n",xp,yp);
            UnionSet(v,w);
            if(f_v == f_w){
                printf("Yes\n");
                return 0;
            }
        }
    }
    printf("No\n");
    return 0;
}


//����flag�ǻ������ģ����磺  2-4, 9-16,  4-9���ж��ǻ�Ȼ����û��
//��ѻ����ò��鼯ȥ���ɡ� 
//��һ����������nn��mm�ֱ��ʾͼGG�ĵ����ͱ�����
//������mm�У�ÿ����������xx��yy����ʾxx��yy֮����һ���ߡ�
