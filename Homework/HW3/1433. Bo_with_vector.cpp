#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 7;
int a[MAX_N];
int n;
ll sum;
map<int, int> mp;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i), sum += a[i];
	for (int i = 1; i <= n; ++i) {
		mp[a[i]] += 2;
		int u = mp.begin()->first;
		sum -= u;
		--mp[u];
		if (!mp[u]) mp.erase(u);
	}
	printf("%lld\n", sum);
	return 0;
}
