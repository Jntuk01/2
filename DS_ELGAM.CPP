#include<stdio.h>
#include<conio.h>
#include<math.h>
long long modexp(long long base,long long exp,long long mod)
{
	long long result=1;
	int i;
	for(i=0;i<exp;i++)
	{
		result=(result*base)%mod;
	}
	return result;
}
long long gcd(long long a,long long b)
{
	if(b==0)
	{
		return a;
	}
	return gcd(b,a%b);
}
long long modinv(long long a, long long m)
{
	long long m0=m,t,q;
	long long x0=0,x1=1;
	if(m==1)
	   return 0;
	while(a>1)
	{
		q=a/m;
		t=m;
		m=a%m;
		a=t;
		t=x0;
		x0=x1-q*x0;
		x1=t;
	}
	if(x1<0)
	     x1+=m0;
	return x1;
}
int main()
{
	long long p,g,m,k,r,s,x,y;
	clrscr();
	printf("Enter the prime number p:");
	scanf("%lld",&p);
	printf("Enter the primitive root g:");
	scanf("%lld",&g);
	printf("Enter the private key x(1<x<p):");
	scanf("%lld",&x);
	y=modexp(g,x,p);
	printf("Public key y= %lld",y);
	printf("\nEnter the message m(either an integer or hash):");
	scanf("%lld",&m);
	do
	{
		printf("Enter random integer k(1<k<p),gcd(k,p-1)=1:");
		scanf("%lld",&k);
		if(gcd(k,p-1)!=1)
		  printf("Invalid k. It must be relatively prime to p-1.\n");
    }while(gcd(k,p-1)!=1);
    r=modexp(g,k,p);
    long long k_inv=modinv(k,p-1);
    s=(k_inv * (m-x*r))%(p-1);
    if(s<0)
       s+=(p-1);
    printf("\n Generated signature:\n");
    printf("r=%lld\n s=%lld\n",r,s);
    char verifyChoice;
    printf("Do you wan to verify with the same message(valid signature)?(y/n):");
    getchar();
    scanf("%c",&verifyChoice);
    if(verifyChoice=='n'||verifyChoice=='N')
    {
    	printf("\nEnter a modified message for verification(different from the original):");
    	scanf("%lld",m);
	}
	long long v1=(modexp(y,r,p)*modexp(r,s,p))%p;
	long long v2=modexp(g,m,p);
	printf("\n Verifying signature...\n");
	printf("v1=%lld \n v2=%lld \n",v1,v2);
	if(v1==v2)
	printf("Signature is valid");
	else
	printf("signature is invalid");
	getch();
	return 0;
}
