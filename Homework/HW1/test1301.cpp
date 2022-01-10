#include<bits/stdc++.h>
using namespace std;
int n, tot=0;
int a[1000006];
int b[1000006];
void bubble_sort() {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (a[j] > a[j+1]) {
            	b[a[j+1]]++;
            	b[a[j]]++;
            	printf("swap   %d  and  %d\n",a[j+1],a[j]);
                swap(a[j+1], a[j]);
            }
        } // after i-th inner iteration, a[n - 1 - i] is correct
    }
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	bubble_sort();
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	for(int i=1;i<=n;i++)
		cout<<b[i]<<" ";
	return 0;
}

