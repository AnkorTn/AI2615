#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 1e6 + 7;
const int Inf = 1e9 + 7;
int n , m , k;
int start , End;
int ans_cnt;
 
//���·����
int dis[maxn];
bool vis[maxn];
struct node{
	int v , w;
	friend bool operator < (node a , node b){
		return a.w > b.w;
	}
};
 
/*
 * A* ����ʽ�������� F[x] = H[x] + G[x]
 * ���� Hx ��ʾ��������ǰ�� ���õĴ���
 * ���� Gx �ǹ��ۺ��� �����ۺ���ҪС�ڵ���ʵ��ֵ���������
 */
struct edge{
	int v , Hx , Gx;
	friend bool operator < (edge a , edge b){
		return a.Hx + a.Gx > b.Hx + b.Gx;
	}
};
/*
 * count ��¼�ڼ���BFS��չ���˵�
 * �� count == k ʱ  ���ٶԴ˵����������չ����Ϊ��չ�ĵ�ض����� ��k��·��
 */
int Count[maxn];

vector <node> G[maxn] , G2[maxn];

/*
 * ����Ϊ������ͼ���Է���ͼ��
 * ��End��ÿ��������·
 */
void Dijkstra(){
	fill(vis , vis+n+1 , false);
	fill(dis , dis+n+1 , Inf);
	priority_queue <node> que;
	que.push((node){End , 0});
	dis[End] = 0;
	node q;
	int v , w;
	while(!que.empty()){
		q = que.top(); que.pop();
		v = q.v , w = q.w;
		if(vis[v])	continue;
		vis[v] = true;
		int to_v , to_w;
		for(int i = 0 ; i < G2[v].size() ; i++){
			to_v = G2[v][i].v , to_w = G2[v][i].w + w;
			if(dis[to_v] > to_w){
				dis[to_v] = to_w;
				que.push((node){to_v , to_w});
			}
		}
	}
}
/*
 * ��k��·�㷨 = A* + BFS
 */
void Astar(){
	ans_cnt = 0;
	fill(Count , Count+n+1 , 0);
	priority_queue <edge> que;
	que.push((edge){start , 0 , 0});
	edge q;
	int v , Hx , Gx;
	int prev = -1;
	while(!que.empty()){
		q = que.top(); que.pop();
		v = q.v , Hx = q.Hx , Gx = q.Gx;
		Count[v]++;
		if(v == End){
			if(prev != Hx + Gx){
				prev = Hx + Gx;
				printf("%d ",prev);
				ans_cnt++;
			}
			else
				Count[v]--;
		}
		if(Count[v] == k)
			break;
//		if(Count[v] == k && v == End){
//			ans = Hx + Gx;
//			break;
//		}
		if(Count[v] > k)	continue;
		int to_v , to_hx , to_gx;
		for(int i = 0 ; i < G[v].size() ; i++){
			to_v = G[v][i].v;
			to_hx = Hx + G[v][i].w;
			to_gx = dis[to_v];
			que.push((edge){to_v , to_hx , to_gx});
		}
	}
	while(!que.empty())	que.pop();
	return;
}

int main(){
	scanf("%d%d%d%d%d",&n,&m,&start,&End,&k);
		for(int i = 1 ; i <= n ; i++)	G[i].clear();
		for(int i = 1 ; i <= m ; i++){
			int u , v , w;	scanf("%d%d%d",&u,&v,&w);
			G[u].push_back((node){v, w});
			G2[v].push_back((node){u, w});
		}
		Dijkstra();
		Astar();
		for(;ans_cnt<k;ans_cnt++)
			printf("-1 ");
	return 0;
}
