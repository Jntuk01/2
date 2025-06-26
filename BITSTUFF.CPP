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
{
 char input[]="01111110001010111111001001111110";
 clrscr();
 printf("Original string: %s", input);
 bitstuffing(input);
 getch();
 return 0;
}
