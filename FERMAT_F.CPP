#include <stdio.h>
#include <conio.h>
#include <math.h>

// Function to check if a number is a perfect square
int isPerfectSquare(int w) {
    int s = (int)sqrt(w);
    return (s * s == w);
}

// Fermat Factorization function
void Fermat_Factorization(int n) {
    // x <- square root of n (smallest integer greater than or equal to sqrt(n))
    int x = (int)ceil(sqrt(n));
    int w, y, a, b;

    while (x < n) {
	// w <- (x^2) - n
	w = x * x - n;

	// if w is a perfect square
	if (isPerfectSquare(w)) {
	    // y <- square root of w
	    y = (int)sqrt(w);

	    // a <- x + y
	    a = x + y;

	    // b <- x - y
	    b = x - y;

	    // return a and b
	    printf("Factors of %d are: %d and %d\n", n, a, b);
	    return;
	}

	// x <- x + 1
	x++;
    }

    printf("Factors not found using Fermat's method.\n");
}

int main() {
    int n;
    clrscr();
    printf("Enter an odd number to factorize: ");
    scanf("%d", &n);

    if (n <= 0 || n % 2 == 0) {
	printf("Please enter a positive odd number.\n");
    } else {
	Fermat_Factorization(n);
    }
getch();
    return 0;
}
