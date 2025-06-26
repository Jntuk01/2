#include<stdio.h>
#include<conio.h>
#include<math.h>
long long modexp(long long base,long long exp,long long mod)
{
	long long result=1;
	int i;
	for( i=0;i<exp;i++)
	{
		result=(result*base)%mod;
	}
	return result;
}
long long inverse(long long a,long long m)
{
	long long i;
	for(i=1;i<m;i++)
	{
		if((a*i)%m==1) 
		  return i;
	}
	return -1;
}
void main()
{
	long long x,y,g,p,m,k,c1,c2,decrypted;
	clrscr();
	printf("Enter the prime number p:");
	scanf("%lld",&p);
	printf("Enter the primitive root g:");
	scanf("%lld",&g);
	printf("Enter the private key x(1<x<p):");
	scanf("%lld",&x);
	y=modexp(g,x,p);
	printf("public key y=%d",y);
	printf("Enter the message m:");
	scanf("%lld",&m);
	printf("Enter the random k(1<k<p):");
	scanf("%lld",&k);
	c1=modexp(g,k,p);
	c2=(m*modexp(y,k,p))%p;
	printf("\nEncrypted: c1=%lld, c2=%lld",c1,c2);
	decrypted=(c2*inverse(modexp(c1,x,p),p))%p;
	printf("\nDecrypted message:%lld",decrypted);
	getch();
}
