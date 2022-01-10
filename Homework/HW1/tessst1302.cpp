#include <iostream>
using namespace std;
int a[1024 + 1];
int query(int x, int y);
//�鲢����
//�鲢������������ 
void merge(int left, int mid, int right){
    int *tmp = new int[right-left+1];
    int i= left, j = mid, k = 0;
    //����δ����
    while (i < mid && j <= right)                          
	    if (query(a[i], a[j])<=0)     tmp[k++] = a[i++]; 
	    else tmp[k++] = a[j++]; 
	//ǰ�벿��û�н���
    while ( i<mid )  tmp[k++] = a[i++];   
    //��벿��û�н���
    while ( j<=right )  tmp[k++] = a[j++];
    for (i=0, k = left; k<=right; ) a[k++] = tmp[i++];
    delete [] tmp;
}
void mergeSort(int left, int right){
     int mid = (left+right)/2;
     if (left == right) return;
     mergeSort(left, mid);
     mergeSort(mid+1, right);
     merge(left,mid+1,right);
}
//�������� 
void optimal_sort(int n) {
	for (int i = 1; i <= n; i++) a[i] = i;
    mergeSort(1,n);
    for (int i = 1; i <= n; i++) printf("%d%c", a[i], i == n ? '\n' : ' ');
}
#include <iostream>
int __qcnt = 0;
int __hidden_array[1025];
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
