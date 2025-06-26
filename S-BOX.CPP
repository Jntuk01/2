#include<stdio.h>
#include<conio.h>
int s_box[4][4]={
{12,10,6,9},{1,15,13,0},{11,5,3,14},{7,8,0,2}
};
int binary_to_decimal(char binary[])
{
	int decimal=0,i;
	for(i=0;i<4;i++)
	{
		decimal=(decimal*2)+(binary[i]-'0');
	}
	return decimal;
}
void decimal_to_binary(int num)
{
	int i,bin[4];
	for(i=3;i>=0;i--)
	{
		bin[i]=num%2;
		num/=2;
	}
	for(i=0;i<4;i++)
	{
		printf("%d",bin[i]);
	}
}
int main()
{
	char b[5];
	int input, row,col,output;
	clrscr();
	printf("Enter a 4 bit binary input(e.g., 1010):");
	scanf("%s",b);
	if(b[0]!='0' && b[0]!='1'||
	   b[1]!='0' && b[1]!='1'||
	   b[2]!='0' && b[2]!='1'||
	   b[3]!='0' && b[3]!='1'||
	   b[4]!='\0')
	   {
	   	printf("Invalid input! please enter a four-bit binary number.\n");
	   	getch();
	   	return 1;
	   }
	   input=binary_to_decimal(b);
	   row=(input>>2)&3;
	   col=input & 3;
	   output=s_box[row][col];
	   printf("S-box substitution output:");
	   decimal_to_binary(output);
	   printf("\n");
	   getch();
	   return 0;
	
}
