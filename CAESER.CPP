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
