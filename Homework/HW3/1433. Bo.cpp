#include<bits/stdc++.h>
using namespace std;
long long a, f[2][100005];
int main(){
	int n, mid;
	int f1=0, f2=1;
	scanf("%d",&n);
	// mid = n / 2;
	// ����ռ临�ӶȻ���û�����ˣ��ؼ�����ʱ�临�Ӷ�����Ż�
	// Ŀǰ���㷨���Ӷ�O(N^2)����ĿҪ���Ӧ����O(NlogN)����O(N)
	// �ؼ���������������г���i֧��Ʊʱ��������
	// ��ʲôʱ��һ���������룿ʲôʱ��һ������������
	// ���²��������²����룿���� 
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);
		memset(f[f2],-0x3f3f3f3f,sizeof(f[f2]));
		f[f2][0] = 0;		f[f2][1] = -1 * a;
		for(int j=0;j<=i;j++)
			f[f2][j] = max(f[f2][j],f[f1][j]); 
		// ����
		for(int j=1;j<=i;j++)
			f[f2][j] = max(f[f2][j],f[f1][j-1]-a);
		// ����
		for(int j=0;j<=i;j++)
			f[f2][j] = max(f[f2][j],f[f1][j+1]+a);
		f1 = 1 - f1; f2 = 1 - f2;
	}
	printf("%lld\n",max(f[0][0],f[1][0]));
	return 0;
}
