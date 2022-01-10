#include<bits/stdc++.h>
using namespace std;
struct node{
	int l;
	int r;
	int ori;
	int fa;
	int value;
	int level;
	inline bool operator <(const node &x)const{return value>x.value;}
}Huffman[1000005];
priority_queue<node>q;
int main(){
	int n;	node tmp1, tmp2;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&Huffman[i].value);
		Huffman[i].l = -1; Huffman[i].r = -1; Huffman[i].ori = i; Huffman[i].fa = -1; Huffman[i].level = 0;
		q.push(Huffman[i]);
	}
	int r = n+n;
	for(int i=n+1;i<r;i++){
		tmp1 = q.top(); q.pop(); tmp2 = q.top(); q.pop();
		Huffman[i].l = tmp1.ori; Huffman[i].r = tmp2.ori; Huffman[i].ori = i; Huffman[i].fa = -1; 
		Huffman[i].level = max(Huffman[tmp1.ori].level,Huffman[tmp2.ori].level) + 1;
		Huffman[tmp1.ori].fa = i;	Huffman[tmp2.ori].fa = i; Huffman[i].value = tmp1.value + tmp2.value;
		q.push(Huffman[i]);
	}
	// ans 是计算了相应长度乘积的一个结果 
	// 真要算权重那又是很麻烦的一件事情了。
	// 要考虑很多的细节 
	int ans;
	printf("%d\n",ans);
	return 0;
}
