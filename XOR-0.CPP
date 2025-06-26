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
