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
