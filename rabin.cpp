#include <stdio.h>
#include <stdlib.h>

// Modular exponentiation: base^exp % mod
int modpow(int base, int exp, int mod) {
    long long result = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * b) % mod;
        b = (b * b) % mod;
        exp >>= 1;
    }
    return (int)result;
}

// Modular inverse using Extended Euclidean Algorithm
int modinverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    return (x1 + m0) % m0;
}

// Tonelli-Shanks algorithm (assumes solution exists)
int modsqrt(int a, int p) {
    if (p % 4 == 3) {
        return modpow(a, (p + 1) / 4, p);
    }

    int q = p - 1;
    int s = 0;
    while (q % 2 == 0) {
        q /= 2;
        s++;
    }

    int z = 2;
    while (modpow(z, (p - 1) / 2, p) != p - 1) z++;

    int c = modpow(z, q, p);
    int x = modpow(a, (q + 1) / 2, p);
    int t = modpow(a, q, p);
    int m = s;

    while (t != 1) {
        int i = 0;
        int temp = t;
        while (temp != 1 && i < m) {
            temp = (temp * temp) % p;
            i++;
        }

        int b = modpow(c, 1 << (m - i - 1), p);
        x = ((long long)x * b) % p;
        t = ((long long)t * b * b) % p;
        c = ((long long)b * b) % p;
        m = i;
    }

    return x;
}

// Chinese Remainder Theorem
int crt(int r1, int r2, int p, int q) {
    int n = p * q;
    int m1 = q, m2 = p;
    int inv1 = modinverse(q, p);
    int inv2 = modinverse(p, q);

    int x1 = ((long long)r1 * m1 * inv1) % n;
    int x2 = ((long long)r2 * m2 * inv2) % n;

    return (x1 + x2) % n;
}

// Primality test (basic)
int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return 0;
    return 1;
}

// Encryption using void
void encrypt(int m, int n, int *c) {
    *c = (m * m) % n;
}

// Decryption using void
void decrypt(int c, int p, int q) {
    int r = modsqrt(c, p);
    int s = modsqrt(c, q);

    int m1 = crt(r, s, p, q);
    int m2 = crt(p - r, s, p, q);
    int m3 = crt(r, q - s, p, q);
    int m4 = crt(p - r, q - s, p, q);

    printf("Decryption yields 4 possible messages:\n");
    printf("%d, %d, %d, %d\n", m1, m2, m3, m4);
}

// Main function
int main() {
    int p, q, m, c;

    printf("Enter prime number p: ");
    scanf("%d", &p);
    printf("Enter prime number q: ");
    scanf("%d", &q);

    if (!is_prime(p) || !is_prime(q)) {
        printf("Both numbers must be prime.\n");
        return 1;
    }

    int n = p * q;

    printf("Enter message m (integer less than %d): ", n);
    scanf("%d", &m);

    if (m >= n) {
        printf("Message must be less than %d.\n", n);
        return 1;
    }

    encrypt(m, n, &c);
    printf("Encrypted ciphertext: %d\n", c);

    decrypt(c, p, q);

    return 0;
}
