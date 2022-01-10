#include <iostream>
#include <algorithm>
using namespace std;
int a[1024 + 1];
int query(int x, int y);
bool cmp(int x, int y){
	if(query(x,y)<=0)	return true;
	return false;
}
void optimal_sort(int n) {
	for (int i = 1; i <= n; i++) a[i] = i;
    sort(a+1,a+n+1,cmp);
    for (int i = 1; i <= n; i++) printf("%d%c", a[i], i == n ? '\n' : ' ');
}
#include <iostream>
int __qcnt = 0;
int __hidden_array[1024];
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
