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