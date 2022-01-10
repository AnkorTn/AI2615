#include<bits/stdc++.h>
using namespace std;
struct edge{	long long value;
	inline bool operator <(const edge &x)const{
        return value>x.value;
    }
};
priority_queue<edge>q;
int main(){
	q.push((edge){1});
	q.push((edge){2});
	q.push((edge){3});
	q.push((edge){4});
	while(!q.empty()){
		cout<<q.top().value<<endl;;
		q.pop();
	}
	return 0;
}

