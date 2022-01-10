#include<iostream>
using namespace std;
int main(){
    int n1, n2;
    scanf("%d%d",&n1,&n2);
    int *fac1 = new int[n1+1];
    int *pri1 = new int[n1+1];
    int pnt1 = 1;
    for(int i=1;i<=n1;i++)
        scanf("%d%d",&fac1[i],&pri1[i]);
    int *fac2 = new int[n2+1];
    int *pri2 = new int[n2+1];
    int pnt2 = 1;
    for(int i=1;i<=n2;i++)
        scanf("%d%d",&fac2[i],&pri2[i]);
    int *fac3 = new int[n1+n2+1];
    int *pri3 = new int[n1+n2+1];
    int pnt3 = 1;
    int tmp;
    while(pnt1<=n1 && pnt2<=n2){
        // 相等次数则计算
        if(pri1[pnt1] == pri2[pnt2]){
            tmp = fac1[pnt1] + fac2[pnt2];
            if(tmp != 0){
                fac3[pnt3] = tmp;
                pri3[pnt3++] = pri1[pnt1];
            }
            pnt1++; pnt2++;
            continue;
        }
        // 不等次数则直接赋值
        if(pri1[pnt1] > pri2[pnt2]){
            if(fac1[pnt1]!=0){
                fac3[pnt3] = fac1[pnt1];
                pri3[pnt3++] = pri1[pnt1];
            }
            pnt1++;
            continue;
        }
        if(fac2[pnt2]!=0){
            fac3[pnt3] = fac2[pnt2];
            pri3[pnt3++] = pri2[pnt2];
        }
        pnt2++;
    }

    while(pnt1<=n1){
        if(fac1[pnt1]!=0){
            fac3[pnt3] = fac1[pnt1];
            pri3[pnt3++] = pri1[pnt1];
        }
        pnt1++;
    }

    while(pnt2<=n2){
        if(fac2[pnt2]!=0){
            fac3[pnt3] = fac2[pnt2];
            pri3[pnt3++] = pri2[pnt2];
        }
        pnt2++;
    }
    // 程序完结后应判断最后的内容是否完全为0

    if(pnt3 == 1){
        printf("0 0\n");
        return 0;
    }
    for(int i=1;i<pnt3;i++)
        printf("%d %d ",fac3[i],pri3[i]);


    return 0;
}
