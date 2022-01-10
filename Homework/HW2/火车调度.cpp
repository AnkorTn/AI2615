#include <bits/stdc++.h>
using namespace std;
int s[1200000], cmp[1200000];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n;
        int top = -1, cnt = 0;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&cmp[i]);
        // simulation
        int i = 0;
        while(cnt<n){
            s[++top] = i++;
            while(top>=0 && s[top] == cmp[cnt]){
//            	printf("%d ", s[top]);
                top--; cnt++;
            }
        }
//        printf("\n");
        if(cnt<n || top >= n)
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}
