#include<bits/stdc++.h>
using namespace std;
const int N = 4e7 + 1;
int n, k;
int a[N];
void read_input_data() {
    int m;
    cin >> n >> k >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    unsigned int z = a[m];
    for (int i = m + 1; i <= n; i++) {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        a[i] = z & 0x7fffffff;
    }
}

int divide(int l, int r){
	int mid = (l+r)>>1;
	swap(a[mid], a[r]);
	int i = l;
	for(int j=l;j<r;j++)
		if(a[j]<=a[r])
			swap(a[j],a[i++]);
	swap(a[i],a[r]);
	return i;
}

int solve(int l, int r, int goal){
	int mid = divide(l,r);
	if(mid == goal)
		return a[mid];
	if(mid <= goal)
		return solve(mid+1, r, goal);
	return solve(l, mid-1, goal);
}

int main(){
	read_input_data();
	printf("%d\n",solve(1, n, k));
	return 0;
}
