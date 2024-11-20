#include <stdio.h>
#include <string.h>

#define N 2

// Function to generate the key matrix from the key string
void getKeyMatrix(char key[], int keyMatrix[N][N])
{
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            keyMatrix[i][j] = (key[k]) % 65; // Convert key character to matrix value
            k++;
        }
    }

    // Print the key matrix for verification
    printf("Key Matrix:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", keyMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to encrypt a block of text using the key matrix
void encryptBlock(int cipherMatrix[N][1], int keyMatrix[N][N], int messageVector[N][1])
{
    for (int i = 0; i < N; i++)
    {
        cipherMatrix[i][0] = 0;
        for (int j = 0; j < N; j++)
        {
            cipherMatrix[i][0] += keyMatrix[i][j] * messageVector[j][0]; // Matrix multiplication
        }
        cipherMatrix[i][0] = cipherMatrix[i][0] % 26; // Apply modulo 26 to get the encrypted value
    }
}

// Function to calculate the modular inverse of a 2x2 matrix
void getInverseKeyMatrix(int keyMatrix[N][N], int inverseKeyMatrix[N][N])
{
    int determinant = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
    determinant = (determinant % 26 + 26) % 26; // Ensure positive determinant

    // Calculate modular inverse of the determinant
    int invDeterminant = 0;
    for (int i = 1; i < 26; i++)
    {
        if ((determinant * i) % 26 == 1)
        {
            invDeterminant = i;
            break;
        }
    }

    // Calculate the inverse matrix
    inverseKeyMatrix[0][0] = (keyMatrix[1][1] * invDeterminant) % 26;
    inverseKeyMatrix[0][1] = (-keyMatrix[0][1] * invDeterminant) % 26;
    inverseKeyMatrix[1][0] = (-keyMatrix[1][0] * invDeterminant) % 26;
    inverseKeyMatrix[1][1] = (keyMatrix[0][0] * invDeterminant) % 26;

    // Ensure positive values in the inverse matrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (inverseKeyMatrix[i][j] < 0)
            {
                inverseKeyMatrix[i][j] += 26;
            }
        }
    }
}

// Function to decrypt a block of text using the inverse key matrix
void decryptBlock(int messageMatrix[N][1], int inverseKeyMatrix[N][N], int cipherMatrix[N][1])
{
    for (int i = 0; i < N; i++)
    {
        messageMatrix[i][0] = 0;
        for (int j = 0; j < N; j++)
        {
            messageMatrix[i][0] += inverseKeyMatrix[i][j] * cipherMatrix[j][0]; // Matrix multiplication
        }
        messageMatrix[i][0] = messageMatrix[i][0] % 26; // Apply modulo 26 to get the decrypted value
    }
}

// Function to perform Hill Cipher encryption on the message using the key
void HillCipher(char message[], char key[], char cipherText[])
{
    int keyMatrix[N][N];
    getKeyMatrix(key, keyMatrix); // Generate the key matrix

    int messageLength = strlen(message);

    int paddedLength = messageLength;
    if (messageLength % N != 0)
    {
        paddedLength += (N - messageLength % N); // Pad the message if necessary
    }

    for (int i = 0; i < paddedLength; i += N)
    {
        int messageVector[N][1];
        int cipherMatrix[N][1];

        for (int j = 0; j < N; j++)
        {
            if (i + j < messageLength)
            {
                messageVector[j][0] = (message[i + j]) % 65; // Convert character to vector value
            }
            else
            {
                messageVector[j][0] = 'X' % 65; // Padding character
            }
        }

        encryptBlock(cipherMatrix, keyMatrix, messageVector); // Encrypt the block

        for (int j = 0; j < N; j++)
        {
            cipherText[i + j] = cipherMatrix[j][0] + 65; // Convert encrypted values back to characters
        }
    }

    cipherText[paddedLength] = '\0'; // Null-terminate the ciphertext
}

// Function to perform Hill Cipher decryption on the ciphertext using the key
void HillDecipher(char cipherText[], char key[])
{
    int keyMatrix[N][N];
    int inverseKeyMatrix[N][N];
    getKeyMatrix(key, keyMatrix);                     // Generate the key matrix
    getInverseKeyMatrix(keyMatrix, inverseKeyMatrix); // Calculate the inverse key matrix

    int cipherLength = strlen(cipherText);

    char PlainText[cipherLength + 1];
    PlainText[cipherLength] = '\0';

    for (int i = 0; i < cipherLength; i += N)
    {
        int cipherMatrix[N][1];
        int messageMatrix[N][1];

        for (int j = 0; j < N; j++)
        {
            cipherMatrix[j][0] = (cipherText[i + j]) % 65; // Convert character to matrix value
        }

        decryptBlock(messageMatrix, inverseKeyMatrix, cipherMatrix); // Decrypt the block

        for (int j = 0; j < N; j++)
        {
            PlainText[i + j] = messageMatrix[j][0] + 65; // Convert decrypted values back to characters
        }
    }

    // Print the final plaintext
    printf("Plaintext: %s\n", PlainText);
}

int main()
{
    char message[] = "HELP";
    char key[] = "HILL";
    char cipherText[100]; // Ensure the array is large enough for ciphertext

    HillCipher(message, key, cipherText);   // Encrypt the message
    printf("Ciphertext: %s\n", cipherText); // Print the generated ciphertext

    HillDecipher(cipherText, key); // Decrypt the ciphertext

    return 0;
}
