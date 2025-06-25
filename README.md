1(a)Affine cipher
#include <stdio.h>
#include <string.h>
int modInverse(int a, int m) {
    for (int i = 1; i < m; i++)
        if ((a * i) % m == 1)
            return i;
    return -1;
}
void encrypt(char *text, int a, int b) {
    for (int i = 0; text[i] != '\0'; i++)
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = ((a * (text[i] - 'A') + b) % 26) + 'A';
}
void decrypt(char *text, int a, int b) {
    int a_inv = modInverse(a, 26);
    for (int i = 0; text[i] != '\0'; i++)
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = ((a_inv * ((text[i] - 'A') - b + 26)) % 26) + 'A';
}
int main() {
    char msg[100] = "HELLO";
    int a = 5, b = 8;
    encrypt(msg, a, b);
    printf("Encrypted: %s\n", msg);
    decrypt(msg, a, b);
    printf("Decrypted: %s\n", msg);
  return 0;
}
1(b)  XOR-127
#include<stdio.h>
#include<conio.h>
void main()
{
char *str="Hello World";
int i;
char result;
clrscr();
printf("Original String: %s\n",str);
printf("After AND with 127:");
for(i=0;str[i]!='\0';i++)
{
 result=str[i]&127;
 printf("%c",result);
}
printf("\n");
printf("After OR with 127:");
for(i=0;i<str[i]!='\0';i++)
{
 result=str[i]|127;
 printf("%c",result);
}
printf("\n");
printf("After XOR with 127:");
for(i=0;str[i]!='\0';i++)
{
 result=str[i]^127;
 printf("%c",result);
}
printf("\n");
getch();
}

2(a) RAIL FENCE

#include<stdio.h>
#include<conio.h>
#include<string.h>
void main()
{
 char a[20],c[20],d[20];
 int i,j,k,l;
 clrscr();
 printf("Enter the input string:");
 gets(a);
 l=strlen(a);
 for(i=0,j=0;i<l;i++)
 {
  if(i%2==0)
   c[j++]=a[i];
 }
 for(i=0;i<l;i++)
 {
  if(i%2==1)
   c[j++]=a[i];
 }
 c[j]='\0';
 printf("\nCipher text after applying rail fence:");
 printf("%s\n",c);
 if(l%2==0)
  k=l/2;
 else
  k=(l/2)+1;
 for(i=0,j=0;i<k;i++)
 {
  d[j]=c[i];
  j=j+2;
 }
 for(i=k,j=1;i<l;i++)
 {
  d[j]=c[i];
  j=j+2;
 }
 d[l]='\0';
 printf("\n Text after decryption:");
 printf("%s",d);
 getch();
}

2(b)BITSTUFFING

#include<stdio.h>
#include<conio.h>
#include<string.h>
void bitstuffing(char *data)
{
 char result[50];
 int i=0,j=0,count=0;
 int length=strlen(data);
 for(i=0,j=0;i<8 && i<length;i++)
 {
  result[j++]=data[i];
 }
 for(;i<length-8;i++)
 {
  result[j++]=data[i];
  if(data[i]=='1')
    count++;
  else
    count=0;
  if(count==5)
  {
   result[j++]='0';
   count=0;
   }
 }
 for(;i<length;i++)
 {
   result[j++]=data[i];
 }
 result[j]='\0';
 printf("\nStuffed output is: %s",result);
}
int main()
{ char input[]="01111110001010111111001001111110";
 clrscr();
 printf("Original string: %s", input);
 bitstuffing(input);
 getch();
 return 0;
}
3(a) HILLCHIPHER
#include <stdio.h>
#include <conio.h>
#define SIZE 3
void matrixMultiply(int key[SIZE][SIZE], int input[SIZE], int output[SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        output[i] = 0;
        for (j = 0; j < SIZE; j++) {
            output[i] += key[i][j] * input[j];
        }
        output[i] = (output[i] % 26 + 26) % 26;  // Ensure non-negative mod
    }
}
void textToNumbers(char text[], int numbers[], int len) {
    int i;
    for (i = 0; i < len; i++)
        numbers[i] = text[i] - 'A';
}

void numbersToText(int numbers[], char text[], int len) {
    int i;
    for (i = 0; i < len; i++)
        text[i] = numbers[i] + 'A';
    text[len] = '\0';
}
int modInverse(int a) {
    int i;
    for (i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1;
}
int matrixInverse(int key[SIZE][SIZE], int inverse[SIZE][SIZE]) {
    int determinant = 0, i, j;
determinant = (key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1])
                 - key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0])
                 + key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0])) % 26;
    if (determinant < 0) determinant += 26;
    determinant = modInverse(determinant);
    if (determinant == -1) {
        printf("Matrix has no modular inverse.\n");
        return 0;
    }
    inverse[0][0] = (key[1][1] * key[2][2] - key[1][2] * key[2][1]) % 26;
    inverse[0][1] = (key[0][2] * key[2][1] - key[0][1] * key[2][2]) % 26;
    inverse[0][2] = (key[0][1] * key[1][2] - key[0][2] * key[1][1]) % 26;
    inverse[1][0] = (key[1][2] * key[2][0] - key[1][0] * key[2][2]) % 26;
    inverse[1][1] = (key[0][0] * key[2][2] - key[0][2] * key[2][0]) % 26;
    inverse[1][2] = (key[0][2] * key[1][0] - key[0][0] * key[1][2]) % 26;
    inverse[2][0] = (key[1][0] * key[2][1] - key[1][1] * key[2][0]) % 26;
    inverse[2][1] = (key[0][1] * key[2][0] - key[0][0] * key[2][1]) % 26;
    inverse[2][2] = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    for (i = 0; i < SIZE; i++) 
        for (j = 0; j < SIZE; j++) 
            inverse[i][j] = (inverse[i][j] * determinant) % 26;
    return 1;
}

void decrypt(int inverse[SIZE][SIZE], int cipher[SIZE], int message[SIZE]) {
    matrixMultiply(inverse, cipher, message);
}

void main() {
    int key[SIZE][SIZE], inverse[SIZE][SIZE], message[SIZE], cipher[SIZE];
    char plaintext[SIZE + 1], ciphertext[SIZE + 1];
    clrscr();
    printf("Enter the 3x3 key matrix:\n");
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) 
            scanf("%d", &key[i][j]);
    printf("\nEnter a 3-letter uppercase plaintext: ");
    scanf("%s", plaintext);
    textToNumbers(plaintext, message, SIZE);
    matrixMultiply(key, message, cipher);
    numbersToText(cipher, ciphertext, SIZE);
    printf("\nCiphertext: %s\n", ciphertext);
    if (matrixInverse(key, inverse)) {
        decrypt(inverse, cipher, message);
        numbersToText(message, plaintext, SIZE);
        printf("\nDecrypted text: %s\n", plaintext);
    }
    getch();
}

3(b)XOR-0
#include<stdio.h>
#include<conio.h>
void main()
{
 char *str="Hello World";
 int i;
 char result;
 clrscr();
 printf("Original string is: %s",str);
 printf("\nAfter XOR with 0:");
 for(i=0;str[i]!='\0';i++)
 {
  result=str[i] ^ 0;
  printf("%c",result);
 }
 getch();
 }

4. P-BOX

#include <stdio.h>
#include <conio.h>
void byte_to_bits(unsigned char byte, int bits[8]) {
    int i;
    for (i = 0; i < 8; i++) {
        bits[7 - i] = (byte >> i) & 1;
    }
}
unsigned char bits_to_byte(int bits[8]) {
    int i;
    unsigned char result = 0;
    for (i = 0; i < 8; i++) {
        result |= (bits[i] << (7 - i));
    }
    return result;
}
void pbox_permute(int input[], int output[], int map[], int out_size) {
    int i;
    for (i = 0; i < out_size; i++) {
        output[i] = input[map[i]];
    }
}
void print_bits(int bits[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d", bits[i]);
    }
    printf("\n");
}
void main() {
    clrscr();
    int input_bits[8], output_bits[8];
    int byte_val;
    int i;
    printf("Enter 8-bit number (0-255): ");
    scanf("%d", &byte_val);
    byte_to_bits((unsigned char)byte_val, input_bits);
    printf("\nOriginal Bits: ");
    print_bits(input_bits, 8);
    int straight_map[8] = {7, 6, 5, 4, 3, 2, 1, 0};
    pbox_permute(input_bits, output_bits, straight_map, 8);
    printf("Straight P-Box: ");
    print_bits(output_bits, 8);
    int small_input[4] = {1, 0, 1, 1};
    int expansion_map[8] = {0, 1, 2, 3, 2, 1, 3, 0};
    int expanded_output[8];
    pbox_permute(small_input, expanded_output, expansion_map, 8);
    printf("\nExpansion P-Box (4->8): ");
    print_bits(expanded_output, 8);
    int compression_map[4] = {1, 3, 5, 7};
    int compressed_output[4];
    pbox_permute(input_bits, compressed_output, compression_map, 4);
    printf("Compression P-Box (8->4): ");
    print_bits(compressed_output, 4);
    getch();
}

5(a) S-BOX

#include <stdio.h>
#define SBOX_SIZE 16
int sbox[SBOX_SIZE]={0,14,4,13,1,2,15,11,8,3,10,6,12,5,9,7};
int inv_sbox[SBOX_SIZE];
void buildInverseSbox(){
    for(int i=1;i<SBOX_SIZE;i++){
        inv_sbox[sbox[i]]=i;
    }
}
void displaySbox(int box[],const char* name){
    printf("\n%s:\n",name);
    for(int i=1;i<SBOX_SIZE;i++){
        printf("%2d→%2d\n",i,box[i]);
    }
}
int main(){
    displaySbox(sbox,"S-Box");
    buildInverseSbox();
    displaySbox(inv_sbox,"Inverse S-Box");
    int input=9;
    int encrypted=sbox[input];
    int decrypted=inv_sbox[encrypted];
    printf("\nTest:\nInput:%d→Substituted:%d→Inverse:%d\n",input,encrypted,decrypted);
    return 0;
}
5(b)CRC-CCIT                                                    CRC-16
#define POLY 0x1021                                            #define POLY 0x8005
#define CRC_BITS 16                                             #define CRC_BITS 16
#define DATA_BITS 16                                           #define DATA_BITS 16
unsigned int computeCRC(unsigned int data, int totalBits) {
    for (int i = totalBits - 1; i >= CRC_BITS; i--) {
        if ((data >> i) & 1)
            data ^= (POLY << (i - CRC_BITS));
    }
    return data;
}
int main() {
    int choice;
    unsigned int data, codeword;
    while(1){
        printf("0. Exit\n1. Calculate CRC\n2. Verify Received Data\nChoice: ");
        scanf("%d", &choice);
        if (choice == 0) break;
        else if (choice == 1) {
            printf("Enter hex data (up to 0xFFF): ");
            scanf("%x", &data);
            unsigned int full = computeCRC(data << CRC_BITS, DATA_BITS + CRC_BITS);
            unsigned int crc = full & 0xFFF;
            codeword = (data << CRC_BITS) | crc;
            printf("CRC-12: %03X\n", crc);
            printf("Codeword: %06X\n", codeword);
        } else if (choice == 2) {
            printf("Enter received codeword: ");
            scanf("%x", &codeword);
            unsigned int result = computeCRC(codeword, DATA_BITS + CRC_BITS);
            if ((result & 0xFFF) == 0)
                printf("CRC Valid\n");
            else
                printf("CRC Error\n");
        } else {
            printf("Invalid choice\n");
        }
    }
    return 0;}
CRC-12
#include <stdio.h>
#define POLY 0x180F
#define CRC_BITS 12
#define DATA_BITS 12
6(a) BROADCAST
#include<stdio.h>
int findGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;  // remainder becomes new b
        a = temp;       }
    return a;  
}
int main() {
    int num1, num2;
    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);
    int gcd = findGCD(num1, num2);
    printf("GCD of %d and %d is: %d\n", num1, num2, gcd);
    return 0;
}

6(b) GCD-ECULIDEAN
#include <stdio.h>
#include <conio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
void main() {
    int num1, num2, result;
    clrscr();
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    result = gcd(num1, num2);
    printf("GCD of %d and %d is: %d", num1, num2, result);
    getch();
}

7(a) Recommended primality test.
#include <stdio.h>
long long power(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
int millerTest(long long d, long long n) {
    long long a = 2 + rand() % (n - 4);
    long long x = power(a, d, n);
    if (x == 1 || x == n - 1) return 1;
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;
        if (x == 1) return 0;
        if (x == n - 1) return 1;
    }
    return 0;
}
int isPrime(long long n) {
    if (n < 2) return 0;
    int small[] = {2,3,5,7,11,13,17,19,23};
    for (int i = 0; i < 9; i++) {
        if (n == small[i]) return 1;
        if (n % small[i] == 0) return 0;
    }
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    for (int i = 0; i < 5; i++)
        if (!millerTest(d, n)) return 0;
    return 1;
}
int main() {
    long long n;
    printf("Enter number: ");
    scanf("%lld", &n);
    if (isPrime(n))
        printf("probably Prime\n");
    else
        printf("composite\n");
    return 0;
}

7(b)CAESER CIPHER
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
void encrypt(char text[], int key)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
	char ch = text[i];
	if (ch >= 'A' && ch <= 'Z')
	{
	    text[i] = (ch - 'A' + key) % 26 + 'A';
	}
	else if (ch >= 'a' && ch <= 'z')
	{
	    text[i] = (ch - 'a' + key) % 26 + 'a';
	}
    }
}
void decrypt(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
	char ch = text[i];
	if (ch >= 'A' && ch <= 'Z') {
	    text[i] = (ch - 'A' - key + 26) % 26 + 'A';
	}
	else if (ch >= 'a' && ch <= 'z') {
	    text[i] = (ch - 'a' - key + 26) % 26 + 'a';
	}
    }
}
void main()
{
    char text[100];
    int key, ch;
    clrscr();
    printf("Enter text: ");
    scanf("%s",&text);
    printf("Enter key value: ");
    scanf("%d", &key);
   while(1)
   {
    printf("\n1. Encrypt\n2. Decrypt\n3.Exit\nChoose an option: ");
    scanf("%d", &ch);
    switch(ch)
    {
    case 1:
	encrypt(text, key);
	printf("Encrypted Text: %s", text);
	break;
    case 2:
	decrypt(text, key);
	printf("Decrypted Text: %s", text);
	break;
    case 3:
	exit(0);
    }
   }
   getch();
}

8(a) Fermat Factorization primality test
#include <stdio.h>
#include <conio.h>
#include <math.h>
int isPerfectSquare(int w) {
    int s = (int)sqrt(w);
    return (s * s == w);
}
void Fermat_Factorization(int n) {
    int x = (int)ceil(sqrt(n));
    int w, y, a, b;
    while (x < n) {
	w = x * x - n;
	if (isPerfectSquare(w)) {
	    y = (int)sqrt(w);
	    a = x + y;
	    b = x - y;
	    printf("Factors of %d are: %d and %d\n", n, a, b);
	    return;
	}
	x++;
    }
    printf("Factors not found using Fermat's method.\n");
}
int main() {
    int n;
    clrscr();
    printf("Enter an odd number to factorize: ");
    scanf("%d", &n);
    if (n <= 0 || n % 2 == 0) {
	printf("Please enter a positive odd number.\n");
    } else {
	Fermat_Factorization(n);
    }
getch();
    return 0;
}
8(b) Multiplicative Cipher
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int modInverse(int key, int mod) {
    for (int i = 1; i < mod; i++) {
        if ((key * i) % mod == 1) {
            return i;
        }
    }
    return -1;
}
void encrypt(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (ch >= 'A' && ch <= 'Z') {
            text[i] = ((ch - 'A') * key) % 26 + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            text[i] = ((ch - 'a') * key) % 26 + 'a';
        }
    }
}
void decrypt(char text[], int key) {
    int keyInverse = modInverse(key, 26);
    if (keyInverse == -1) {
        printf("Invalid key! No modular inverse exists.\n");
        return;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (ch >= 'A' && ch <= 'Z') {
            text[i] = ((ch - 'A') * keyInverse) % 26 + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            text[i] = ((ch - 'a') * keyInverse) % 26 + 'a';
        }
    }
}

void main() {
    char text[100];
    int key, ch;
    
    clrscr();  

    printf("Enter text: ");
    scanf(" %[^\n]", text);  
    
    printf("Enter key (must be coprime with 26): ");
    scanf("%d", &key);

    while (1) {
        printf("\n1. Encrypt\n2. Decrypt\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                encrypt(text, key);
                printf("Encrypted Text: %s\n", text);
                break;
            case 2:
                decrypt(text, key);
                printf("Decrypted Text: %s\n", text);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    getch();  
}

9(a) Public key Algorithm El Gamal.
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

9(b)Modular Inverse.
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

10(a) Rabin cryptosystem                                                                                                                   
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}
int modPow(int base, int exp, int mod) {
    int result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
int main() {
    int p,q,n;
    printf("enter p,q values : ", p,q);
    scanf("%d%d", &p,&q);
    n = p * q;
    int message, ciphertext;
    printf("Public key (n = p * q): %d\n", n);
    printf("Enter message (M < %d): ", n);
    scanf("%d", &message);
    ciphertext = (message * message) % n;
    printf("Encrypted ciphertext (C = M^2 mod n): %d\n", ciphertext);
    int m1 = modPow(ciphertext, (p + 1) / 4, p);
    int m2 = modPow(ciphertext, (q + 1) / 4, q);
    int yp = modInverse(p, q);
    int yq = modInverse(q, p);
    int r = (yp * p * m2 + yq * q * m1) % n;
    int s = (yp * p * m2 - yq * q * m1) % n;
    if (r < 0) r += n;
    if (s < 0) s += n;
    printf("\nPossible decrypted messages:\n");
    printf("1. %d\n", r);
    printf("2. %d\n", n - r);
    printf("3. %d\n", s);
    printf("4. %d\n", n - s);
    return 0;
}

11(a) RSA
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int modInverse(int e, int phi) {
    int t = 0, newt = 1;
    int r = phi, newr = e;
    while (newr != 0) {
        int q = r / newr;
        int temp = newt;
        newt = t - q * newt;
        t = temp;
        temp = newr;
        newr = r - q * newr;
        r = temp;
    }
    if (r > 1) return -1;
    if (t < 0) t += phi;
    return t;
}

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        exp /= 2;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    int p, q;
    printf("Enter two prime numbers: ");
    scanf("%d %d", &p, &q);
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e;
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1) break;
    }
    int d = modInverse(e, phi);
    if (d == -1) {
        printf("Modular inverse not found.\n");
        return 1;
    }
    printf("Public Key: (%d, %d)\n", e, n);
    printf("Private Key: (%d, %d)\n", d, n);
    int msg;
    printf("Enter message to encrypt (as number): ");
    scanf("%d", &msg);
    long long enc = modExp(msg, e, n);
    printf("Encrypted message: %lld\n", enc);
    long long dec = modExp(enc, d, n);
    printf("Decrypted message: %lld\n", dec);
    return 0;
}
11(b) CHARACTER STUFFING
#include <stdio.h>
#include <conio.h>
int main() {
	char start[]="dlestx",mid[]="dle",end[]="dleetx",frame[30];
	int i;
	clrscr();
	printf("Enter the data:");
	scanf("%s",&frame);
	printf("\nAfter stuffing:");
	printf("%s",start);
	for(i=0;frame[i]!='\0';i+3)
	 {
	  if(frame[i]=='d'&& frame[i+1]=='l'&& frame[i+2]=='e')
	    printf("%s",mid);
	  printf("%c",frame[i]);
	  i++;
	}
	printf("%s",end);
	getch();
	return 0;
}

 

12(a)ElGamal DS Algorithm
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

12(b) DSS                                                                                                                           
#include <stdio.h>
int power(int b, int e, int m) {
    int r = 1;
    while (e) {
        if (e % 2) r = (r * b) % m;
        b = (b * b) % m; e /= 2;
    }
    return r;
}

int inv(int a, int m) {
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1) return x;
    return -1;
}
int main() {
    int p, q, g, x, y, k, m, r, s, w, u1, u2, v;
    scanf("%d%d%d%d%d%d", &p, &q, &g, &x, &m, &k);
    y = power(g, x, p);
    r = power(g, k, p) % q;
    s = (inv(k, q) * (m + x * r)) % q;
    printf("%d %d\n", r, s);
    w = inv(s, q);
    u1 = (m * w) % q;
    u2 = (r * w) % q;
    v = (power(g, u1, p) * power(y, u2, p)) % p % q;
    printf("%s\n", v == r ? "Valid" : "Invalid");
    return 0;
}


