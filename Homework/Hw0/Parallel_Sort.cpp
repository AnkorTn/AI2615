#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int n, a[N], s[N], flag[N];
//s数组用来记录每个数当前所在位置，flag数组用来标记该数该轮被交换过
struct point
{
	int x, y;
};
vector<point> v;//记录需要交换的两个数
vector<int> b[N];//存放每一个大环中的数
void sp(int &x, int &y)//要将该数和其位置都交换
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
	//flag1用来判断有无大环，p用来记下大环的个数
	for(int i = 1; i <= n; i++)
		if(a[i] != i && !flag[i])
		{
			int j = s[i], cnt = 0;
			if(j == a[i])//如果是小环就直接交换
			{
				v.push_back({i, j});
				flag[i] = flag[j] = 1;
				sp(i, j);
				continue;
			}
			flag1 = 1;
			b[++p].push_back(i);
			while(j != a[i])//找大环并存下来
			{
				flag[j] = 1;
				b[p].push_back(j);
				j = s[j];
			}
			b[p].push_back(j);
			flag[j] = 1;
		}
	if(!flag1)//无大环的情况
	{
		if(!v.size()) puts("0");//已经是升序了，则无需交换
		else
		{
			puts("1");
			int sz = v.size();
			cout << sz;
			for(int i = 0; i < sz; i++)
				cout << ' ' << v[i].x << ' ' << v[i].y;
		}
	}
	else//有大环的情况
	{
		puts("2");
		for(int i = 1; i <= p; i++)
		{
			int sz = b[i].size();
			for(int j = 0, k = sz - 1; j < k; j++, k--)
			{
				v.push_back({b[i][j], b[i][k]});//将大环第一轮要交换的数存入v数组中
				sp(b[i][j], b[i][k]);
			}
		}
		cout << v.size();
		for(int i = 0; i < v.size(); i++)
			cout << ' ' << v[i].x << ' ' << v[i].y;
		cout << endl;
		v.clear();//将v数组清空，进行第二轮交换
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

