#include<stdio.h>
 
int m,n,k;
int stack[1000007];       //ջ 
int top=0;             //ջ���±� 
int index1=1,index2=1;     //index1����ʾ1-n������ ��index2����ʾ����b���±� 
int b[1000007];           //��ų�ջ���� 
 
int main()
{
	scanf("%d",&k);
    while(k--)
    {
    	scanf("%d",&n);
    	m = n;
    	int flag=1; 
    	index1=1;index2=1;
    	top=0; 
    	int i;
    	for(i=1;i<=n;i++)
    	  scanf("%d",&b[i]);
    	while(1)
    	{
    		//�жϸ����ĳ�ջ���������1��n����˳����ͬ���Ǿ�����ջһ��Ԫ�أ�Ȼ��������ջ�� 
    		if(index1==b[index2])
    		{
    			index1++;
    			index2++;
			}
			//�ж����ջ����Ԫ�أ�Ȼ��ջ��Ԫ��Ҳ���ʱ�ĳ�ջ����Ԫ����ͬ����ô�ͼ�����ջ���ж� 
			else if(top!=0&&stack[top-1]==b[index2])
			{
				top--;
				index2++; 
			}
			else
			{
				if(index1>n)break;  //�Ѿ��жϽ�����������ѭ�� 
				stack[top]=index1;  //Ԫ����ջ 
				top++;
				index1++;
				if(top>=m) //
				{
					flag=0;
					break;
				}
			}
		}
		if(flag==0||top!=0)printf("No\n");
		else printf("Yes\n");
	}
    
	return 0;
}

