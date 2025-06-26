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