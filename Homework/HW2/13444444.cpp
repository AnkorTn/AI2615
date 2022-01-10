#include<bits/stdc++.h>
using namespace std;

// edge class
struct edge{	int from;	int	to; 	long long value;
	inline bool operator <(const edge &x)const{
        return value>x.value;
    }
};
// to find the best choice of pr_q;
priority_queue<edge>pr_q;
edge tmp;

// graph class
vector<edge>graph[2502];
// edge storage.
edge que[6202];
// total aims at collecting the total sum of the circle.
// return the sum in O(1)
long long total[6202];
// the place is used to quickly find the first node that is in the queue
// return the place in O(1)
int place[2502];
int cnt = -1;

// n vertexes, m edges.
int n, m, a, b;
long long c;
bool vis[2502];
int marked[2502];

void dfs(int num);

void print(int st, int ed);

// to output all the result.
void check();

int main(){
	// initialize.
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		vis[i] = false; marked[i] = false;
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%lld",&a,&b,&c);
		if(a == b){
			if(c<0){
				printf("Yes\n1\n%d\n",a);
				return 0;
			}
			continue;			
		}
		graph[a].push_back((edge){a,b,c});
		if(c<0)
			pr_q.push((edge){a,b,c});
	}
	
	// find circle.
	while(!pr_q.empty()){
		tmp = pr_q.top();	pr_q.pop();
		if(marked[tmp.to]>22000)
			continue;
		dfs(tmp.to);
		marked[tmp.to] = 22550;
	}
	
//	for(int i=1;i<=n;i++){
//		if(marked[i]>22000)
//			continue;
//		dfs(i);
//		marked[i] = 22550;
//	}

	printf("No\n");
	return 0;
}

void dfs(int num){
	if(marked[num]>22000)
		return;
		
	vis[num] = true;
	int tmp = graph[num].size();
	for(int i=0;i<tmp;i++){
		// if we haven't visited it, we visit it.
		int u = graph[num][i].from, v = graph[num][i].to, f = graph[num][i].value;
		if(marked[v]>22000)
			continue; 
		if(!vis[v]){
			que[++cnt] = graph[num][i];
			place[u] = cnt;
			total[cnt] = cnt == 0? f: total[cnt-1] + f;
//			check();
//			printf("\t\t Now we dfs the point %d\n", graph[num][i].to);
			dfs(v);
			// search_back.
			cnt--;			
		}
		// else, we find one circle.
		else{
			// find the initial point of the circle.
			que[++cnt] = graph[num][i];
			total[cnt] = cnt == 0? f: total[cnt-1] + f;
//			check();
//			printf("\t\t Now we dfs the point %d\n", graph[num][i].to);
			int j = place[v];
			// this iteration method costs much time.
			// The best way: j = place[graph[num][i].to];
//			while(cnt-j>=0 && que[cnt-j].from != graph[num][i].to)	j++;
			if(j>cnt){
				cnt--;
				continue;
			}
			if((j==0 && total[cnt]<0) || (j>0 && total[cnt]-total[j-1]<0))
				print(j,cnt);
			cnt--;
		}
	}
	marked[num]++;
	vis[num] = false;
}

void print(int st, int ed){
	printf("Yes\n%d\n", ed-st+1);
	for(int i=st;i<ed;i++)
		printf("%d ",que[i].to);	printf("%d\n",que[ed].to);
	exit(0);
}

void check(){
	printf("Now edges in queue are:{from, to, value, total}\n");
	for(int i=0;i<=cnt;i++)
		printf("{ %d, %d, %lld, %lld}\t",que[i].from,que[i].to,que[i].value, total[i]);	printf("\n");
	printf("And the visit bool arrays are:\n");
	for(int i=1;i<=n;i++)
		cout<<vis[i]<<"  ";	cout<<endl;
	return;
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
