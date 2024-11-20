def columnar_encrypt(plaintext, key):
    # Remove spaces and convert to uppercase
    plaintext = plaintext.replace(" ", "").upper()
    key_order = sorted(range(len(key)), key=lambda k: key[k])

    # Create the encryption grid
    grid = [plaintext[i:i + len(key)] for i in range(0, len(plaintext), len(key))]
    if len(grid[-1]) < len(key):
        grid[-1] += 'X' * (len(key) - len(grid[-1]))  # Pad the last row with 'X'

    # Read columns based on key order
    ciphertext = ''
    for col in key_order:
        for row in grid:
            ciphertext += row[col]
    return ciphertext


def columnar_decrypt(ciphertext, key):
    key_order = sorted(range(len(key)), key=lambda k: key[k])
    num_rows = len(ciphertext) // len(key)
    grid = ['' for _ in range(len(key))]

    # Fill the grid column by column based on the key order
    index = 0
    for col in key_order:
        grid[col] = ciphertext[index:index + num_rows]
        index += num_rows

    # Read the grid row by row to reconstruct plaintext
    plaintext = ''
    for i in range(num_rows):
        for col in range(len(key)):
            plaintext += grid[col][i]
    return plaintext.rstrip('X')  # Remove padding


# Example Usage
message = "HELLO WORLD"
key = "ZEBRAS"  # Key for column order

# Encrypt
ciphertext = columnar_encrypt(message, key)
print(f"Ciphertext: {ciphertext}")

# Decrypt
decrypted_text = columnar_decrypt(ciphertext, key)
print(f"Decrypted Text: {decrypted_text}")
