#include <stdio.h>
#include <string.h>
#include <conio.h>
#define MAX 100

char data[MAX] = "10001000000100001";  // Default data
char gen[28], rem[28], codeword[MAX];
int datalen, genlen, original_len;

// Perform XOR between rem and gen when rem[0] is '1'
void xor_operation() {
    int i;
    for (i = 0; i < genlen; i++) {
        rem[i] = (rem[i] == gen[i]) ? '0' : '1';
    }
}

// CRC calculation function
void crc_calculate() {
    int i, j;

    // Initialize rem with first genlen bits of data
    for (i = 0; i < genlen; i++) {
        rem[i] = data[i];
    }

    for (i = 0; i < datalen; i++) {
        if (rem[0] == '1') {
            xor_operation();
        }

        // Shift rem left by 1 bit
        for (j = 0; j < genlen - 1; j++) {
            rem[j] = rem[j + 1];
        }

        // Bring down next bit from data or '0' if no more bits
        rem[genlen - 1] = (i + genlen < strlen(data)) ? data[i + genlen] : '0';
    }
}

// Receiver function to check error in received codeword
void receiver() {
    printf("\nEnter received codeword: ");
    scanf("%s", data);
    datalen = strlen(data) - (genlen - 1);
    crc_calculate();

    int i;
    for (i = 0; i < genlen - 1; i++) {
        if (rem[i] != '0') {
            printf("\nError detected in received codeword.\n");
            return;
        }
    }
    printf("\nNo error detected in received codeword.\n");
}

int main() {
    int i;
     clrscr();
    printf("Default binary data: %s\n", data);

    printf("Enter generating polynomial (binary): ");
    scanf("%s", gen);

    original_len = strlen(data);  // Save original data length
    genlen = strlen(gen);

    // Append (genlen - 1) zeros to data
    for (i = 0; i < genlen - 1; i++) {
        data[original_len + i] = '0';
    }
    data[original_len + genlen - 1] = '\0';

    datalen = original_len;  // datalen is original data length

    printf("\nModified data (with zeros): %s\n", data);

    crc_calculate();

    printf("CRC Checksum: ");
    for (i = 0; i < genlen - 1; i++) {
        printf("%c", rem[i]);
        codeword[original_len + i] = rem[i];
    }

    // Copy original data into codeword
    for (i = 0; i < original_len; i++) {
        codeword[i] = data[i];
    }
    codeword[original_len + genlen - 1] = '\0';

    printf("\nFinal Codeword: %s\n", codeword);

    receiver();
getch();
    return 0;
}

