#include<iostream>
#include<vector>
using namespace std;
int n;
const int maxn = 1e6;
vector<int>bit(maxn);
int a[maxn];
void add(int i,int x) {
	while(i<maxn) {
		bit[i]+=x;
		i+=i&-i;
	}
}
int sum(int i) {
	int ans=0;
	while(i>0) {
		ans+=bit[i];
		i-=i&-i;
	}
	return ans;
}
int main() {
	cin>>n;
	int res=0;
	for(int i=0; i<n; ++i) {
		int t;
		cin>>a[i];
		res+=i-sum(a[i]);
		printf("i-sum(t) = %d , t = %d\n",i-sum(a[i]),a[i]);
		add(a[i],1);
	}
	for(int i=0;i<n;i++)
		cout<<sum(a[i])<<" ";
	cout<<endl;
	for(int i=1;i<=n;i++)
		cout<<bit[i]<<" ";
	cout<<endl;
	cout<<res;
	return 0;
}
