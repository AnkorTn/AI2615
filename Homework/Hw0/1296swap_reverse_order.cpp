#include<bits/stdc++.h>
using namespace std;
int a[100005], site[100005], n, tmp;
bool flag[100005];
vector<int>Loops[100005];
vector<int>ans1,ans2;
//�ο���������
//https://blog.csdn.net/liubang00001/article/details/81386852 
//����Ӧ�������һ�
//�ҵ���֮�������2��С����ֱ�ӽ���
//��������˹�ģ��2���û���Ȼ�ܹ���������Ȼ��
//How to prove?->Question. 
int main(){
	scanf("%d",&n);
	//�ж��Ƿ���Ҫ���� 
	bool flaag = true;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		site[a[i]] = i;
		if(a[i]!=i)		flaag = false;
	}
	//����Ҫ�������˳� 
	if(flaag){
		printf("0\n");
		return 0;
	}
	int loop = 1;
	for(int i=1;i<=n;i++){
		//�һ� 
		if(a[i]!=i && !flag[i]){
			int cnt = 0;
			int j = site[i];
			//С���������߽����ͻظ�״̬ 
			if(a[i] == j){
				swap(site[a[i]],site[a[j]]);
				swap(a[i],a[j]);
				flag[i] = true;
				flag[j] = true;
				ans1.push_back(i);
				ans2.push_back(j);
				continue;
			}
			//�ж���һ�ֻ�������
			flaag = true;
			Loops[loop].push_back(i);
			while(a[i]!=j){
				flag[j] = true;
				Loops[loop].push_back(j);
				j = site[j];
			}
			Loops[loop++].push_back(j);
			flag[j] = true;
		}
	}
	if(flaag == false){
		printf("1\n");
		int len = ans1.size();
		printf("%d ",len);
		for(int i=0;i<len;i++)
			printf("%d %d ",ans1[i],ans2[i]);
		return 0;
	}
	else{
		printf("2\n");
		//��ǰ��ӾͿ��Բ����������
		// 7
		// 4 7 2 3 1 6 5
		for(int i=1;i<loop;i++){
			int len = Loops[i].size();
			int j = 0; int k = len-1;
			while(j<k){
				ans1.push_back(Loops[i][j]);
				ans2.push_back(Loops[i][k]);
				swap(site[a[Loops[i][j]]],site[a[Loops[i][k]]]);
				swap(a[Loops[i][j]],a[Loops[i][k]]);	
				j++;
				k--;
			}
		}
		//��һ�ֽ��� 
		int lxn = ans1.size();
		printf("%d ",lxn);
		for(int i=0;i<lxn;i++)
			printf("%d %d ",ans1[i],ans2[i]);
		printf("\n");
		ans1.clear();	ans2.clear();
		//�ڶ��ֽ��� 
		for(int i=1;i<=n;i++)
			if(a[i]!=i){
				int j = site[i];
				ans1.push_back(i);
				ans2.push_back(j);
				swap(site[a[i]],site[a[j]]);
				swap(a[i],a[j]);
			}
		lxn = ans1.size();
		printf("%d ",lxn);
		for(int i=0;i<lxn;i++)
			printf("%d %d ",ans1[i],ans2[i]);
	}
	return 0;
}
