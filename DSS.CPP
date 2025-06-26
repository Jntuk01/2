#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

long long gcd(long long a, long long b)
{
	if (b == 0)
	{
		return a;
	}
	return gcd(b, a % b);
}

long long modinv(long long a, long long m)
{
	long long m0 = m, t, q;
	long long x0 = 0, x1 = 1;
	if (m == 1)
		return 0;
	while (a > 1)
	{
		q = a / m;
		t = m;
		m = a % m;
		a = t;

		t = x0;
		x0 = x1 - q * x0;
		x1 = t;
	}
	if (x1 < 0)
		x1 += m0;
	return x1;
}

int simple_hash(const char* message)
{
	int i, hash = 0;
	for (i = 0; message[i] != '\0'; i++)
	{
		hash = (hash + message[i] * (i + 1)) % 1000;
	}
	return hash;
}

int main()
{
	char message[256];
	int privatekey, publickey, mod = 1000;
	int hash, signature, verify;

	clrscr();  // ? Clears screen (works in Turbo C)

	printf("Enter the message: ");
	fgets(message, sizeof(message), stdin);

	// Remove trailing newline from fgets
	message[strlen(message) - 1] = '\0';

	printf("Enter private key (must be coprime with %d): ", mod);
	scanf("%d", &privatekey);

	if (gcd(privatekey, mod) != 1)
	{
		printf("Error: private key must be coprime with %d to have a modular inverse", mod);
		return 1;
	}

	publickey = modinv(privatekey, mod);
	hash = simple_hash(message);
	signature = (hash * privatekey) % mod;

	printf("\n-- Digital Signature Structure --\n");
	printf("Message: %s\n", message);
	printf("Hash: %d\n", hash);
	printf("Private Key: %d\n", privatekey);
	printf("Public Key (modular inverse): %d\n", publickey);
	printf("Generated Signature: %d\n", signature);

	verify = (signature * publickey) % mod;

	if (verify == hash)
		printf("Signature Verification: Valid\n");
	else
		printf("Signature Verification: Invalid\n");

	getch();  // ? Pause at the end (works in Turbo C)
	return 0;
}

