#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int modInverse(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) {
            return i;
        }
    }
    return -1;
}
void encryptAffine(char text[], int a, int b) {
    for (int i = 0; text[i] != '\0'; i++) {
	char ch = text[i];
	if (ch >= 'A' && ch <= 'Z') {
	    text[i] = ((a * (ch - 'A') + b) % 26) + 'A';
	} else if (ch >= 'a' && ch <= 'z') {
	    text[i] = ((a * (ch - 'a') + b) % 26) + 'a';
	}
    }
}
void decryptAffine(char text[], int a, int b) {
    int inverse = modInverse(a, 26);
    if (inverse== -1) {
	printf("Invalid key! No modular inverse exists for a = %d.\n", a);
	return;
    }

    for (int i = 0; text[i] != '\0'; i++) {
	char ch = text[i];
	if (ch >= 'A' && ch <= 'Z') {
	    text[i] = (inverse * (ch - 'A' - b + 26) % 26) + 'A';
	} else if (ch >= 'a' && ch <= 'z') {
	    text[i] = (inverse * (ch - 'a' - b + 26) % 26) + 'a';
	}
    }
}

int main() {
    char text[100];
    int a, b, ch;
	    clrscr();
    printf("Enter text: ");
    scanf(" %[^\n]", text);

    printf("Enter values of a and b (a must be coprime with 26): ");
    scanf("%d %d", &a, &b);

    while (1) {
	printf("\n1. Encrypt\n2. Decrypt\n3. Exit");
	printf("\nEnter your choice: ");
	scanf("%d", &ch);

	switch (ch) {
            case 1:
                encryptAffine(text, a, b);
                printf("Encrypted Text: %s\n", text);
                break;
            case 2:
                decryptAffine(text, a, b);
                printf("Decrypted Text: %s\n", text);
                break;
            case 3:
		exit(0);
	}
    }
    getch();

    return 0;
}
