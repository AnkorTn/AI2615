#include<bits/stdc++.h>
using namespace std;
int n,m,ans=0,father[5001];
struct fkt{int x;int y;int value;}a[200001];
bool cmp(fkt xx,fkt yy){
	return xx.value<yy.value;
}
int find_fa(int x){
	if(father[x]!=x) 
		father[x]=find_fa(father[x]);
	return father[x];
}
void unionn(int x,int y){
	x=find_fa(x);
	y=find_fa(y);
	father[y]=x;
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	father[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].value);
	sort(a+1,a+m+1,cmp);
	n--;
	for(int i=1;i<=m;i++){
		int xxx=find_fa(a[i].x),yyy=find_fa(a[i].y);
		if(xxx!=yyy){
			ans+=a[i].value;
			unionn(a[i].x,a[i].y);
			n--;
		}
		if(n==0)break;
	}
	printf("%d\n",ans);
	return 0;
}
