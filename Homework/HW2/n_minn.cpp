#include<iostream>
using namespace std;
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    int *a = new int[n+1];  a[0] = 0;
    int *b = new int[n+1];  b[0] = 0;
    for(int i=1;i<=m;i++){
        scanf("%d",&a[i]);
        b[i] = b[i-1] + a[i];
    }
    int minn = b[m];
    for(int i=m+1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i] = b[i-1] + a[i] - a[i-m];
        minn = b[i]>minn?minn:b[i];
    }
    printf("%d\n",minn);
    return 0;
}
