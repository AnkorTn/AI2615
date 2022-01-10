#include<bits/stdc++.h>
using namespace std;
vector<int> tree[500005];
int ans[500005], ans_cnt = 0;
int rev_tree[500005];
int radius[500005];	// ���뾶Բ 
int order[500005];
int n,k,u,v,rt, tree_root, total_cost = 0;
bool parent[500005];
bool vis[500005];
int dfs(int rt, int level);		// �����ϵĵ�k���� 
void dfs_rev(int rt, int level);	// ������������Ⱦɫ 
void level_order();
void radius_drawing1();
void radius_drawing();
void init();
void enforce();
int main(){
	init(); // read data;
//	cout<<end_time-start_time<<endl;
	level_order();	// �ҵ����ڵ㣬������ȵ����� 
	
	// Ȼ����order�����������ı�����
	if(n<=500000) 
		radius_drawing1();
	else 
		radius_drawing();
	
	// �������ܽ�� 
	printf("%d\n",ans_cnt);
	for(int i=0;i<ans_cnt;i++)
		printf("%d ",ans[i]);		
	return 0;
}
void init(){
	scanf("%d%d",&n,&k);
	for(register int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		if(!parent[v]){
			tree[u].push_back(v);
			rev_tree[v]=u;
			parent[v] = true;
		}
		else{
			tree[v].push_back(u);
			rev_tree[u]=v;
		}
	}
}
void level_order(){
	for(int i=1;i<=n;i++)
		if(!parent[i]){
			tree_root = i;
			break;
		}
	int tmp, cnt = n;
	queue<int>q;
	q.push(tree_root);
	while(!q.empty()){
		tmp = q.front();	q.pop();	order[cnt--] = tmp;
		for(int i=0;i<tree[tmp].size();i++)
			q.push(tree[tmp][i]);
	}
//	for(int i=1;i<=n;i++)
//		printf("%d ",order[i]);	printf("\n");
}
//void dfs(int rt, int level);		// �����ϵĵ�k���� 
//void dfs_rev(int rt, int level);	// ������������Ⱦɫ 
int dfs(int rt, int level){
	total_cost++;
	while(level!=0 && rt!=tree_root){
		rt = rev_tree[rt];
		level--;
	}
	return rt;
}
void dfs_rev(int rt, int level){
	total_cost++;
	vis[rt] = true;
	if(level <= 0) return;
	if(radius[rt]>=level) return;
	radius[rt] = level;
	for(register int i=0;i<tree[rt].size();i++)
//		if(!vis[tree[rt][i]])//�����ǰ�ڵ㻹û�����ǣ������� 
			dfs_rev(tree[rt][i], level-1);
//	if(!vis[rev_tree[rt][i]])//�����ǰ�ڵ㻹û�����ǣ������� 
	if(rt!=tree_root)
		dfs_rev(rev_tree[rt],level-1);
	return;
}
void radius_drawing1(){
	memset(radius, 0, sizeof(radius));
	memset(parent, 0, sizeof(parent));
	int rt;
	for(register int i=1;i<=n;i++){
		
		if(total_cost > 1e7)
			enforce();//��ʱֹ�� 
		
		if(vis[order[i]])	continue;
		rt = dfs(order[i],k);
		if(!parent[rt]){
			parent[rt] = true;
			ans[ans_cnt++] = rt;
		}
		dfs_rev(rt,k);
	}
}
void radius_drawing(){
	ans_cnt = 0;
	memset(radius, -1, sizeof(radius));
	for(int i=1;i<=n;i++){
		// ����������Ҷ�ӣ����Ǵ�2*k��ʼ 
		if(radius[order[i]] == -1)
			radius[order[i]] = 2 * k;
		// ����������Բ�ģ������𰸼� 
		if(radius[order[i]] == k)
			ans[ans_cnt++] = order[i];
		if(i==n)
			continue;
		// all the sizes of the rev_tree is equal to 1.
//		printf("size = %d\n",rev_tree[order[i]].size());
		if(radius[rev_tree[order[i]]] == 0)	continue;
		// ��û��ֵ 
		if(radius[rev_tree[order[i]]] == -1)
			radius[rev_tree[order[i]]] = radius[order[i]] - 1;
		// ��������ͻ����� 
		else{
			int nw = radius[order[i]];
			int nxt = radius[rev_tree[order[i]]];
			if(nw >= nxt){
				if(nxt >= k)
					radius[rev_tree[order[i]]] = max(nxt, nw);
				else{
					if(nxt+nw>2*k)
						continue;
					radius[rev_tree[order[i]]] = max(nxt, nw-1);
				}
			}
			else{
				if(nxt >= k){
					if(nw>k)
						radius[rev_tree[order[i]]] = min(nxt, nw-1);
					else{
						if(nxt+nw<=2*k)
							continue;
						radius[rev_tree[order[i]]] = 0;
					}
				}
			}
		}
	}
	if(radius[rt]>k)
		ans[ans_cnt++] = rt;
}
void enforce(){
	radius_drawing();
	printf("%d\n",ans_cnt);
	for(int i=0;i<ans_cnt;i++)
		printf("%d ",ans[i]);		
	exit(0);
}
