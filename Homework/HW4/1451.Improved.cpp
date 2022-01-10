#include<bits/stdc++.h>
using namespace std;
vector<int> tree[500005], rev_tree[500005];
vector<int> ans;
int radius[500005];	// ���뾶Բ 
int order[500005];
int n,k,u,v,rt;
bool parent[500005];
void level_order(int root);
void radius_drawing();
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		if(!parent[v]){
			tree[u].push_back(v);
			rev_tree[v].push_back(u);
			parent[v] = true;
		}
		else{
			tree[v].push_back(u);
			rev_tree[u].push_back(v);
		}
	}
	// �ҵ����ڵ� 
	for(int i=1;i<=n;i++)
		if(!parent[i]){
//			printf("%d\n",i);
			rt = i;
			// ����ͨ����α����ҵ���ײ㣬����order
			// level_order(i);
			level_order(rt);
			break;
		}
	
	
	// Ȼ����order�����������ı����� 
	radius_drawing();
	
	// �������ܽ�� 
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++)
		printf("%d ",ans[i]);		
	return 0;
}
void level_order(int root){
	int tmp, cnt = n;
	queue<int>q;
	q.push(root);
	while(!q.empty()){
		tmp = q.front();	q.pop();	order[cnt--] = tmp;
		for(int i=0;i<tree[tmp].size();i++)
			q.push(tree[tmp][i]);
	}
//	for(int i=1;i<=n;i++)
//		printf("%d ",order[i]);	printf("\n");
}
void radius_drawing(){
	memset(radius, -1, sizeof(radius));
	for(int i=1;i<=n;i++){
		// ����������Ҷ�ӣ����Ǵ�2*k��ʼ 
		if(radius[order[i]] == -1)
			radius[order[i]] = 2 * k;
		// ����������Բ�ģ������𰸼� 
		if(radius[order[i]] == k)
			ans.push_back(order[i]);
		if(i==n)
			continue;
		// all the sizes of the rev_tree is equal to 1.
//		printf("size = %d\n",rev_tree[order[i]].size());
		if(radius[rev_tree[order[i]][0]] == 0)	continue;
		// ��û��ֵ 
		if(radius[rev_tree[order[i]][0]] == -1)
			radius[rev_tree[order[i]][0]] = radius[order[i]] - 1;
		// ��������ͻ����� 
		else{
			int nw = radius[order[i]];
			int nxt = radius[rev_tree[order[i]][0]];
			if(nw >= nxt){
				if(nxt >= k)
					radius[rev_tree[order[i]][0]] = max(nxt, nw);
				else{
					if(nxt+nw>2*k)
						continue;
					radius[rev_tree[order[i]][0]] = max(nxt, nw-1);
				}
			}
			else{
				if(nxt >= k){
					if(nw>k)
						radius[rev_tree[order[i]][0]] = min(nxt, nw-1);
					else{
						if(nxt+nw<=2*k)
							continue;
						radius[rev_tree[order[i]][0]] = 0;
					}
				}
			}
//			
//			// �ϰ�Ȧ
//			if (radius[rev_tree[order[i]][0]] >= k)
//				radius[rev_tree[order[i]][0]] = min(radius[rev_tree[order[i]][0]], radius[order[i]] - 1);
//			// �°�Ȧ 
//			else
//				radius[rev_tree[order[i]][0]] = max(radius[rev_tree[order[i]][0]], radius[order[i]] - 1);
		}
	}
	if(radius[rt]>=k)
		ans.push_back(rt);
}
