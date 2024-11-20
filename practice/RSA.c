#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Global variables
int prime[100];
int prime_count = 0;
int public_key;
int private_key;
int n;

// Function Prototypes
void primefiller();
int pickrandomprime();
void setkeys();
long long int encrypt(double message);
long long int decrypt(int encrypted_text);
void encoder(char *message, int encoded[]);
void decoder(int encoded[], int length, char *decoded_message);

// Helper Functions
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int is_prime(int num)
{
    if (num <= 1)
        return 0;
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

// Fill prime numbers using sieve of Eratosthenes
void primefiller()
{
    int i, j;
    int sieve[250] = {0};

    for (i = 2; i < 250; i++)
        sieve[i] = 1;

    for (i = 2; i * i < 250; i++)
    {
        if (sieve[i])
        {
            for (j = i * i; j < 250; j += i)
                sieve[j] = 0;
        }
    }

    for (i = 2; i < 250; i++)
    {
        if (sieve[i] && is_prime(i))
        {
            prime[prime_count++] = i;
        }
    }
}

// Pick a random prime and remove it from the prime list
int pickrandomprime()
{
    int index = rand() % prime_count;
    int ret = prime[index];

    for (int i = index; i < prime_count - 1; i++)
    {
        prime[i] = prime[i + 1];
    }
    prime_count--;

    return ret;
}

// Generate public and private keys
void setkeys()
{
    int prime1 = pickrandomprime();
    int prime2 = pickrandomprime();

    n = prime1 * prime2;
    int fi = (prime1 - 1) * (prime2 - 1);
    int e = 2;

    while (1)
    {
        if (gcd(e, fi) == 1)
            break;
        e++;
    }

    public_key = e;
    int d = 2;
    while (1)
    {
        if ((d * e) % fi == 1)
            break;
        d++;
    }
    private_key = d;
}

// Encrypt the message
long long int encrypt(double message)
{
    int e = public_key;
    long long int encrypted_text = 1;

    while (e--)
    {
        encrypted_text *= message;
        encrypted_text %= n;
    }

    return encrypted_text;
}

// Decrypt the message
long long int decrypt(int encrypted_text)
{
    int d = private_key;
    long long int decrypted = 1;

    while (d--)
    {
        decrypted *= encrypted_text;
        decrypted %= n;
    }

    return decrypted;
}

// Encode the message
void encoder(char *message, int encoded[])
{
    int i, len = strlen(message);

    for (i = 0; i < len; i++)
    {
        encoded[i] = encrypt((int)message[i]);
    }
}

// Decode the message
void decoder(int encoded[], int length, char *decoded_message)
{
    int i;

    for (i = 0; i < length; i++)
    {
        decoded_message[i] = decrypt(encoded[i]);
    }
    decoded_message[length] = '\0';
}

int main()
{
    primefiller();
    setkeys();

    char message[] = "shivam patel";
    int coded[100];
    char decoded_message[100];

    // Encode the message
    encoder(message, coded);

    printf("Initial message:\n%s\n\n", message);
    printf("The encoded message (encrypted by public key):\n");
    for (int i = 0; i < strlen(message); i++)
    {
        printf("%d ", coded[i]);
    }

    // Decode the message
    decoder(coded, strlen(message), decoded_message);
    printf("\n\nThe decoded message (decrypted by private key):\n%s\n", decoded_message);

    return 0;
}
