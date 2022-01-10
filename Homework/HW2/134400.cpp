#include<bits/stdc++.h>
using namespace std;
struct node{
	int from; int to; int value;
	inline bool operator <(const node &x)const{return value>x.value;}
};
vector<node>edge;
vector<int>ans;
int n,m,a,b,c;
long long dis[6800];
bool vis[2600];
int pre[2600];
bool BellmanFord();
int main(){
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		vis[i] = false;
		pre[i] = -1;
	}		
	// build a graph.
	for(int i=1;i<=m;i++){
		//a->b		Inverse:b->a
		scanf("%d%d%d",&a,&b,&c);
		// 反向建边才是关键啊！！我是傻狗 
		edge.push_back((node){b,a,c});
	}
	bool fla = BellmanFord();
	if(!fla){
		printf("No\n");
		return 0;
	}
	printf("Yes\n");
	int l = 0;
	while(ans[n-1]!=ans[l])	l++;
	if(l == n-1) l=0;
	if(ans[l] == ans[n-1]){
		if(l == n-1)
			printf("1\n%d\n",ans[l]);
		else{
			printf("%d\n",n-l-1);
			for(int i=l+1;i<n;i++)
				printf("%d ",ans[i]);
		}
		return 0;
	}
	printf("%d\n",n-l);
	for(int i=l;i<n;i++)
		printf("%d ",ans[i]);
//	if(fla){
//		//exist
//		printf("Yes\n");
//		//Key problem: How to find one circle at least;
//		printf("%d\n",ans.size());
//		for(int i=0;i<ans.size();i++)
//			printf("%d ",ans[i].to);
//	}
//	else{
//		//not
//		printf("No\n");
//		return 0;
//	}
	return 0;
}
// return true if exist
// return false if not
bool BellmanFord(){
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	for(int i=1;i<n;i++)
		for(int j=0;j<m;j++)
			if(dis[edge[j].to] > dis[edge[j].from] + edge[j].value){
				dis[edge[j].to] = dis[edge[j].from] + edge[j].value;
				pre[edge[j].to] = edge[j].from;
			}
				
	bool flag = false;
	for(int j=0;j<m;j++)
		if(dis[edge[j].to] > dis[edge[j].from] + edge[j].value){
			flag = true;
			dis[edge[j].to] = dis[edge[j].from] + edge[j].value;
			pre[edge[j].to] = edge[j].from;
		}
	for(int j=0;j<m;j++)
		if(dis[edge[j].to] > dis[edge[j].from] + edge[j].value){
			int tmp = edge[j].to;
			for(int i=1;i<=n;i++){
				ans.push_back(tmp);
				tmp = pre[tmp];
			}
			break;
		}
	return flag;
}
/*
6 10
1 5 1
5 1 -1
5 2 100
6 1 -2
5 6 0
6 2 2
2 6 -2
2 3 1
3 4 1
4 2 -2

6 10
1 2 3
1 6 1
2 3 -6
3 2 3
3 4 1
3 5 1
3 6 1
5 4 1
5 2 1
5 1 1


Sample Input
1 1
1 1 -1


3 3
1 2 1
2 3 2
3 1 -4



3 3
1 2 1
2 3 2
3 1 -3
Sample Output
Yes
1
1
Yes
3
1 2 3
No
*/
