#include <stdio.h>
#include <conio.h>

// Safe modular multiplication to prevent overflow
unsigned long long int mod_mul(unsigned long long int a, unsigned long long int b, unsigned long long int mod) {
    unsigned long long int result = 0;
    a = a % mod;

    while (b > 0) {
        if (b % 2 == 1)
            result = (result + a) % mod;
        a = (a * 2) % mod;
        b = b / 2;
    }

    return result;
}

// Fast modular exponentiation
unsigned long long int power(unsigned long long int base, unsigned long long int exp, unsigned long long int mod) {
    unsigned long long int result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = mod_mul(result, base, mod);
        base = mod_mul(base, base, mod);
        exp = exp / 2;
    }

    return result;
}

// Miller-Rabin test for one base
int miller_rabin(unsigned long long int n, unsigned long long int a) {
    unsigned long long int m = n - 1;
    int k = 0;
    int i;
    unsigned long long int t;

    while (m % 2 == 0) {
        m = m / 2;
        k++;
    }

    t = power(a, m, n);
    if (t == 1 || t == n - 1)
        return 1;

    for (i = 1; i < k; i++) {
        t = mod_mul(t, t, n);
        if (t == 1)
            return 0;
        if (t == n - 1)
            return 1;
    }

    return 0;
}

// Divisibility test on small known primes
int is_obviously_composite(unsigned long long int n) {
    int small_primes[] = {3, 5, 7, 11, 13, 17};
    int i;
    for (i = 0; i < 6; i++) {
        if (n % small_primes[i] == 0 && n != small_primes[i])
            return 1;
    }
    return 0;
}

// Recommended Primality Test
int is_probably_prime(unsigned long long int n) {
    unsigned long long int bases[] = {2, 3, 5};
    int i;

    if (n < 2)
        return 0;
    if (n % 2 == 0 && n != 2)
        return 0;
    if (is_obviously_composite(n))
        return 0;

    for (i = 0; i < 3; i++) {
        if (bases[i] >= n)
            continue;
        if (!miller_rabin(n, bases[i]))
            return 0;
    }

    return 1;
}

void main() {
    unsigned long long int n;
    clrscr();

    printf("Enter an odd number greater than 2 to test for primality:\n");
    scanf("%llu", &n);

    if (n % 2 == 0 && n != 2) {
        printf("Even numbers other than 2 are not prime.\n");
    } else {
        if (is_probably_prime(n))
            printf("%llu is a strong pseudoprime (probably prime).\n", n);
        else
            printf("%llu is composite.\n", n);
    }

    getch();
}

