#include <iostream>
using namespace std;
int a[1024 + 1];
int query(int x, int y);
void Merge(int l, int q, int r){
    int n=r-l+1;
    int* tmp=new int[n];
    int i=0;
    int left=l;
    int right=q+1;
    while(left<=q && right<=r){
    	if(query(left,right)<=0)
			tmp[i++] = a[left++];
		else
			tmp[i++] = a[right++]; 
	} 
    while(left<=q)
        tmp[i++]=a[left++];
    while(right<=r)
        tmp[i++]=a[right++];
    for(int j=0;j<n;++j)
        a[l+j]=tmp[j];
    delete [] tmp;//删掉堆区的内存
}
void MergeSort(int l, int r){
    if(l==r)
        return;  //递归基是让数组中的每个数单独成为长度为1的区间
    int q = (l + r)/2;
    MergeSort(l, q);
    MergeSort(q + 1, r);
    Merge(l, q, r);
}
void optimal_sort(int n) {
    MergeSort(1,n);
    for (int i = 1; i <= n; i++) printf("%d%c", a[i], i == n ? '\n' : ' ');
}
int __qcnt = 0;
int __hidden_array[1024];
void optimal_sort(int n);
int query (int x, int y) {
    __qcnt ++;
    int d = __hidden_array[x] - __hidden_array[y];
    return d > 0 ? 1 : (d == 0 ? 0 : -1);
}
int main() {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> __hidden_array[i];
    optimal_sort(n);
    std::cout << "number of queries : " << __qcnt << std::endl;
}
