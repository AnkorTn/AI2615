#include<bits/stdc++.h>
using namespace std;
int n;
struct Point{
	int x;//x is the number.
	int y;//y is the inverse condition.
}a[1000005];

void merge(int left, int mid, int right){
    Point *tmp = new Point[right-left+1];
    int i= left, j = mid, k = 0;
    int base_l = 0;
    //两表都未结束
    while (i < mid && j <= right)
	    if (a[i].x<=a[j].x){
	    	a[i].y += base_l;
	    	tmp[k++] = a[i++]; 
		}     
	    else{
	    	a[j].y += (mid-i);	// +=One number
	    	base_l++;	// +=One number
	    	tmp[k++] = a[j++];
		}
	//前半部分没有结束
    while ( i<mid ){
    	a[i].y += base_l;
    	tmp[k++] = a[i++];	
	}
    //后半部分没有结束
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

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].x);
		a[i].y = 0;
	}
	
	// Main function.
	mergeSort(1,n);
	
	
	
//	for(int i=1;i<=n;i++)
//		printf("%d ",a[i].x);
//	printf("\n");
	for(int i=1;i<=n;i++)
		printf("%d ",a[i].y);
	printf("\n");
	return 0;
}
