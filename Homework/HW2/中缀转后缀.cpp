#include<bits/stdc++.h>
using namespace std;
string s1,s2;
stack<char> st;
int p(char ch) {
	if(ch == '+' || ch == '-') return 1;
	if(ch == '*' || ch == '/') return 2;
	if(ch == '^') return 3;
	else return 0;
}
int main() {
	cin >> s1;
	int len = s1.length();
	for(int i = 0;i < len;i++) {
		if(s1[i] >= '0' && s1[i] <= '9')//Êý×Ö
			s2 += s1[i];
		else if(s1[i] == '(')//×óÀ¨ºÅ
			st.push('(');
		else if(s1[i] == ')') {//ÓÒÀ¨ºÅ
			while(st.top() != '(') {
				s2 += st.top();
				st.pop();
			}
			st.pop();
		}
		else {//ÆÕÍ¨ÔËËã·û
			while(!st.empty() && p(st.top()) >= p(s1[i])) {
				s2 += st.top();
				st.pop();
			}
			st.push(s1[i]);
		}
	}
	while(!st.empty()) {//È«²¿µ¯³ö
		s2 += st.top();
		st.pop();
	}
	int la = s2.length();
	for(int i = 0;i < la;i++)
		cout << s2[i];
	return 0;
}
