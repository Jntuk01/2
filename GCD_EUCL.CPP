#include <stdio.h>
#include <conio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void main() {
    int num1, num2, result;
    clrscr();

    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    result = gcd(num1, num2);

    printf("GCD of %d and %d is: %d", num1, num2, result);

    getch();
}

