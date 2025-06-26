#include<stdio.h>
#include<conio.h>
int gcd(int a,int b)
{
	if(b==0)
	{
		return a;
	}
	return gcd(b,a%b);
}
int modInverse(int a,int m)
{
	int t,newT,r,newR;
	int q,temp;
	t=0;
	newT=1;
	r=m;
	newR=a;
	while(newR!=0)
	{
		q=r/newR;
		temp=t;
		t=newT;
		newT=temp-q*newT;
		temp=r;
		r=newR;
		newR=temp-q*newR;
	}
	if(r>1)
	{
		return -1;
	}
	if(t<0)
	{
		t=t+m;
	}
	return t;
}
int main()
{
	int a,m,inv;
	clrscr();
	printf("Enter the number:");
	scanf("%d",&a);
	printf("Enter the modulus:");
	scanf("%d",&m);
	if(gcd(a,m)!=1)
	{
		printf("Inverse does not exist as gcd(%d,%d)!=1\n",a,m);
	}
	else
	{
		inv=modInverse(a,m);
		if(inv==-1)
		{
			printf("inverse does not exist");
		}
		else
		{
			printf("Modular inverse of %d modulo %d is : %d\n",a,m,inv);
		}
	}
	getch();
	return 0;
}
