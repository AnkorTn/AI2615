#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int n, a[N], s[N], flag[N];
//s����������¼ÿ������ǰ����λ�ã�flag����������Ǹ������ֱ�������
struct point
{
	int x, y;
};
vector<point> v;//��¼��Ҫ������������
vector<int> b[N];//���ÿһ�����е���
void sp(int &x, int &y)//Ҫ����������λ�ö�����
{
	swap(s[a[x]], s[a[y]]);
	swap(a[x], a[y]);
}
int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
    	cin >> a[i];
    	s[a[i]] = i;
	}
	int flag1 = 0, p = 0;
	//flag1�����ж����޴󻷣�p�������´󻷵ĸ���
	for(int i = 1; i <= n; i++)
		if(a[i] != i && !flag[i])
		{
			int j = s[i], cnt = 0;
			if(j == a[i])//�����С����ֱ�ӽ���
			{
				v.push_back({i, j});
				flag[i] = flag[j] = 1;
				sp(i, j);
				continue;
			}
			flag1 = 1;
			b[++p].push_back(i);
			while(j != a[i])//�Ҵ󻷲�������
			{
				flag[j] = 1;
				b[p].push_back(j);
				j = s[j];
			}
			b[p].push_back(j);
			flag[j] = 1;
		}
	if(!flag1)//�޴󻷵����
	{
		if(!v.size()) puts("0");//�Ѿ��������ˣ������轻��
		else
		{
			puts("1");
			int sz = v.size();
			cout << sz;
			for(int i = 0; i < sz; i++)
				cout << ' ' << v[i].x << ' ' << v[i].y;
		}
	}
	else//�д󻷵����
	{
		puts("2");
		for(int i = 1; i <= p; i++)
		{
			int sz = b[i].size();
			for(int j = 0, k = sz - 1; j < k; j++, k--)
			{
				v.push_back({b[i][j], b[i][k]});//���󻷵�һ��Ҫ������������v������
				sp(b[i][j], b[i][k]);
			}
		}
		cout << v.size();
		for(int i = 0; i < v.size(); i++)
			cout << ' ' << v[i].x << ' ' << v[i].y;
		cout << endl;
		v.clear();//��v������գ����еڶ��ֽ���
		for(int i = 1; i <= n; i++)
			if(a[i] != i)
			{
				int j = s[i];
				v.push_back({i, j});
				sp(i, j);
			}
		cout << v.size();
		for(int i = 0; i < v.size(); i++)
			cout << ' ' << v[i].x << ' ' << v[i].y;
	}
	return 0;
}

