#include <iostream>
using namespace std;
struct Points{
	int cur;
	int ori;
}a[1024 + 1];
int query(int x, int y);
//�鲢����
//�鲢������������ 
int query (int x, int y) {
    int d = a[x].cur - a[y].cur;
    return d > 0 ? 1 : (d == 0 ? 0 : -1);
}
void merge(int left, int mid, int right){
    Points *tmp = new Points[right-left+1];
    int i= left, j = mid, k = 0;
    //����δ����
    while (i < mid && j <= right)                          
	    if (query(i,j)<=0)     tmp[k++] = a[i++]; 
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
    mergeSort(1,n);
    for (int i = 1; i <= n; i++) printf("%d%c", a[i].ori, i == n ? '\n' : ' ');
}
int main() {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++){
    	std::cin >> a[i].cur;
    	a[i].ori = i;
	} 
    optimal_sort(n);
}
