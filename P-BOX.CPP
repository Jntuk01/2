#include <stdio.h>
#include <conio.h>

// Convert a byte (8-bit integer) to bit array
void byte_to_bits(unsigned char byte, int bits[8]) {
    int i;
    for (i = 0; i < 8; i++) {
        bits[7 - i] = (byte >> i) & 1;
    }
}

// Convert bit array to byte
unsigned char bits_to_byte(int bits[8]) {
    int i;
    unsigned char result = 0;
    for (i = 0; i < 8; i++) {
        result |= (bits[i] << (7 - i));
    }
    return result;
}

// Perform P-Box permutation
void pbox_permute(int input[], int output[], int map[], int out_size) {
    int i;
    for (i = 0; i < out_size; i++) {
        output[i] = input[map[i]];
    }
}

// Print bit array
void print_bits(int bits[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d", bits[i]);
    }
    printf("\n");
}

void main() {
    clrscr();

    int input_bits[8], output_bits[8];
    int byte_val;
    int i;

    // Example input byte
    printf("Enter 8-bit number (0-255): ");
    scanf("%d", &byte_val);

    byte_to_bits((unsigned char)byte_val, input_bits);

    printf("\nOriginal Bits: ");
    print_bits(input_bits, 8);

    // Straight P-Box (just reverse for example)
    int straight_map[8] = {7, 6, 5, 4, 3, 2, 1, 0};
    pbox_permute(input_bits, output_bits, straight_map, 8);
    printf("Straight P-Box: ");
    print_bits(output_bits, 8);

    // Expansion P-Box (from 4 bits to 8 bits, repeating some)
    int small_input[4] = {1, 0, 1, 1};
    int expansion_map[8] = {0, 1, 2, 3, 2, 1, 3, 0};
    int expanded_output[8];
    pbox_permute(small_input, expanded_output, expansion_map, 8);
    printf("\nExpansion P-Box (4->8): ");
    print_bits(expanded_output, 8);

    // Compression P-Box (from 8 bits to 4 bits)
    int compression_map[4] = {1, 3, 5, 7};
    int compressed_output[4];
    pbox_permute(input_bits, compressed_output, compression_map, 4);
    printf("Compression P-Box (8->4): ");
    print_bits(compressed_output, 4);

    getch();
}
