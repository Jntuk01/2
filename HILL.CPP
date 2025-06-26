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
