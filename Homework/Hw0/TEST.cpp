#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3;
int n,ans,jc[13],s[N];
bool check(int x)//check��������Ƿ����
{
	for(int i=1;i<=(1<<(n-x));i++)
		if(s[(i-1)*(1<<x)+1]+(1<<(x-1))!=s[(i-1)*(1<<x)+(1<<(x-1))+1])
		return false;
	return true;
}
void swap(int i,int j,int k)//��������
{
	for(int l=1;l<=k;l++)
		swap(s[i+l-1],s[j+l-1]);
}
void dfs(int x,int num)//����������
{
	if(x&&!check(x))//�����Ϸ���
		return ;
	if(x==n)//�ۼ�
	{
		ans+=jc[num];
		return ;
	}
	dfs(x+1,num);
	int t[5],tot=0;
	for(int i=1;i<=(1<<(n-x));i+=2)
		if(s[i*(1<<x)+1]!=s[(i-1)*(1<<x)+1]+(1<<x))
		{
			if(tot==4)
				break;
			t[++tot]=i;
			t[++tot]=i+1;
		}
	if(!tot)
		return ;
	for(int i=1;i<=tot;i++)
		for(int j=i+1;j<=tot;j++)
		{
			swap((1<<x)*(t[i]-1)+1,(1<<x)*(t[j]-1)+1,1<<x);
			dfs(x+1,num+1);		
			swap((1<<x)*(t[i]-1)+1,(1<<x)*(t[j]-1)+1,1<<x);
		}
}
#undef int
int main()
{
	#define int long long
	scanf("%lld",&n);
	jc[0]=1;
	for(int i=1;i<=n;i++)//Ԥ����׳�
		jc[i]=jc[i-1]*i;
	for(int i=1;i<=n;i++)
		scanf("%lld",&s[i]);
	dfs(0,0);//����
	printf("%lld",ans);
	return 0;
}
