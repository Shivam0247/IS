#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// Function to check whether the given number is prime or not
int check_prime(int n)
{
    if (n <= 1)
        return 0;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

// Function to calculate gcd
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to generate a random e such that gcd(e, totient) == 1
int calculate_e(int totient)
{
    int e;
    do
    {
        e = rand() % (totient - 2) + 2; // Generate random e in range [2, totient-1]
    } while (gcd(e, totient) != 1);
    return e;
}

// Extended Euclidean Algorithm to find d
int extended_euclidean_algo(int a, int b, int t1, int t2)
{
    if (b == 0)
        return t1;
    return extended_euclidean_algo(b, a % b, t2, t1 - t2 * (a / b));
}

// Function to convert a string to an integer (simple hashing)
unsigned long long string_to_int(const char *text, int n)
{
    unsigned long long result = 0;
    while (*text)
    {
        result = (result * 256 + (unsigned char)(*text++)) % n; // Use n to keep it within bounds
    }
    return result;
}

// Function to perform modular exponentiation
unsigned long long modular_exponentiation(unsigned long long base, unsigned long long exp, unsigned long long mod)
{
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod;
    }
    return result;
}

int main()
{
    srand((unsigned int)time(0)); // Seed for random number generation

    int p, q;
    char plaintext[256]; // Adjust size as needed

    // Take inputs for two prime numbers
    printf("Enter the First Prime Number: ");
    scanf("%d", &p);
    printf("Enter the Second Prime Number: ");
    scanf("%d", &q);
    printf("Enter the plaintext: ");
    getchar(); // To ignore the newline character after the previous input
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Remove newline character

    // Check if p and q are prime
    if (!check_prime(p) || !check_prime(q))
    {
        printf("One of the numbers is not prime.\n");
        return 1;
    }
    else
    {
        printf("%d and %d are prime numbers.\n", p, q);
    }

    // Calculate n
    int n = p * q;
    printf("n = %d\n", n);

    // Calculate totient
    int totient = (p - 1) * (q - 1);
    printf("Totient = %d\n", totient);

    // Calculate e
    int e = calculate_e(totient);
    printf("e = %d\n", e);

    // Calculate d
    int t1 = 0, t2 = 1;
    int d = (extended_euclidean_algo(totient, e, t1, t2) % totient + totient) % totient;
    printf("d = %d\n", d);

    // Convert plaintext to integer
    unsigned long long M = string_to_int(plaintext, n);
    printf("Message (M) = %llu\n", M);

    // Signing
    unsigned long long S = modular_exponentiation(M, d, n);
    printf("Signature (S) = %llu\n", S);

    // Verification
    unsigned long long M2 = modular_exponentiation(S, e, n);
    printf("M2 = %llu\n", M2);

    if (M2 == M)
    {
        printf("Signature is verified.\n");
    }
    else
    {
        printf("Signature is not verified.\n");
    }

    return 0;
}
