#include <iostream>
using namespace std;
int n,m;
int ysf(int n, int m){
    if(n == 1)  return 0;
    return (ysf(n-1,m)+m)%n;
}
int main(){
    scanf("%d%d",&n,&m);
    printf("%d\n",ysf(n,m)+1);
    return 0;
}
