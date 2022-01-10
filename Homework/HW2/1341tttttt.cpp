#include<bits/stdc++.h>
using namespace std;
int dfn[2000005],low[2000005];
vector<int>g[2000005];
stack<int> s;
int vis[2000005], tot, cnt;
bool ins[2000005];
void tarjan(int u) {
    low[u] = dfn[u] = ++tot;
    s.push(u); ins[u] = true;
    for (const auto &v : g[u]) {
        if (!dfn[v]) tarjan(v), low[u] = std::min(low[u], low[v]);
        else if (ins[v]) low[u] = std::min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++cnt;
        do {
            vis[u] = cnt;
            u = s.top(); s.pop(); ins[u] = false;
        } while (low[u] != dfn[u]);
    }
    return;
}
int main(){
	int n,m;
	int a,b,c,d;
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=m;i++){
		//a->b		Inverse:b->a
		scanf("%d%d%d%d",&a,&b,&c,&d);
		g[c+(1-d)*n].push_back(a+b*n);
		g[a+(1-b)*n].push_back(c+d*n);
	}
	
	for (int i = 1; i <= (n << 1); ++i) 
		if (!dfn[i]) 
			tarjan(i);
	for (int i = 1; i <= n; ++i)
	    if (vis[i] == vis[i + n]) {
	        puts("No");
	        return 0;
	    }
	puts("Yes");
	for (int i = 1; i <= n; ++i){
		if(vis[i] > vis[i+n])
			printf("1 ");
		else
			printf("0 ");
	}
	return 0;
}

