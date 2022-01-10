#include <iostream>
using namespace std;
int main(){
    int n,m, tmp, mid, l, r;
    scanf("%d%d",&n,&m);
    int *a = new int[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    while(m--){
        scanf("%d",&tmp);
        l = 1; r = n;
        while(l<=r){
            mid = (l+r)>>1;
            if(a[mid]==tmp)
                break;
            else if(a[mid]<tmp)                
                l = mid+1;
            else
                r = mid-1;
        }
        if(a[mid] == tmp)
            printf("1\n");
        else
            printf("0\n");
    }
    delete[]a;
    return 0;
}
