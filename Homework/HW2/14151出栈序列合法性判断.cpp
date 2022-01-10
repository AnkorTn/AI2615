#include<stdio.h>
 
int m,n,k;
int stack[1000007];       //栈 
int top=0;             //栈顶下标 
int index1=1,index2=1;     //index1来表示1-n的数字 ，index2来表示数组b的下标 
int b[1000007];           //存放出栈序列 
 
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
    		//判断给出的出栈序列如果和1到n增长顺序相同，那就是入栈一个元素，然后立即出栈。 
    		if(index1==b[index2])
    		{
    			index1++;
    			index2++;
			}
			//判断如果栈中有元素，然后栈顶元素也与此时的出栈序列元素相同，那么就继续出栈来判断 
			else if(top!=0&&stack[top-1]==b[index2])
			{
				top--;
				index2++; 
			}
			else
			{
				if(index1>n)break;  //已经判断结束，就跳出循环 
				stack[top]=index1;  //元素入栈 
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

