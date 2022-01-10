#include<bits/stdc++.h>
using namespace std;
// 矩阵快速幂 
// 这里我直接用我以前写过的模板就好了 
// Ref:https://www.luogu.com.cn/record/4136393
using namespace std;
struct Mat{
	__float128 mat[4][4];
}x,res,goal;
long long nn;
int n=3;
double pp, f[4];
Mat operator *(Mat a,Mat b){
	Mat c;
	memset(c.mat,0,sizeof(c.mat));
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				c.mat[i][j]+=a.mat[i][k]*b.mat[k][j];
	return c;
}
namespace qaq{
/*主要架构如下：
|f(k)  |     |1-p  p  1|^(k-2)  |f(2)|
|f(k-1)|  =  | 1   0  0|        |f(1)|
|1     |     | 0   0  1|        | 1  |
*/	
	int main(){
		scanf("%lld%lf",&nn,&pp);
		__float128 p = pp;
		if(nn==1){
			cout<<setprecision(20)<<(long double)(2-p)<<endl;
			return 0;
		}
		f[0] = 0; f[1] = 1;	f[2] = (1-p) * f[1] + 1;
		x.mat[0][0] = 1-p;	x.mat[0][1] = p;	x.mat[0][2] = 1;	x.mat[1][0] = 1;	x.mat[2][2] = 1;
		res.mat[0][0] = 1;	res.mat[1][1] = 1;	res.mat[2][2] = 1;		
		nn*=2;	nn-=2;
		while(nn){
			if(nn&1)	res=res*x;
			nn>>=1;
			x=x*x;
		}
		goal.mat[0][0] = f[2];	goal.mat[1][0] = 1;	goal.mat[2][0] = 1;
		goal = res*goal;
		cout<<setprecision(20)<<(long double)goal.mat[0][0]<<endl;
//		printf("%0.7lf\n",goal.mat[0][0]);
		return 0;
	}
}
int main(){
	qaq::main();
    return 0;
}
