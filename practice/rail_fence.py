def rail_fence_encrypt(plaintext, rails):
    # Create a matrix for zig-zag pattern
    rail_matrix = [['' for _ in range(len(plaintext))] for _ in range(rails)]
    direction_down = False
    row, col = 0, 0

    for char in plaintext:
        # Place the character in the matrix
        rail_matrix[row][col] = char
        col += 1

        # Change direction if top or bottom rail is reached
        if row == 0 or row == rails - 1:
            direction_down = not direction_down

        # Move up or down
        row += 1 if direction_down else -1

    # Read the matrix row by row to get the ciphertext
    ciphertext = ''.join([''.join(row) for row in rail_matrix])
    return ciphertext


def rail_fence_decrypt(ciphertext, rails):
    # Create a matrix to mark positions for characters
    rail_matrix = [['' for _ in range(len(ciphertext))] for _ in range(rails)]
    direction_down = None
    row, col = 0, 0

    # Mark the positions
    for _ in ciphertext:
        rail_matrix[row][col] = '*'
        col += 1

        if row == 0:
            direction_down = True
        elif row == rails - 1:
            direction_down = False

        row += 1 if direction_down else -1

    # Fill the marked positions with ciphertext characters
    index = 0
    for r in range(rails):
        for c in range(len(ciphertext)):
            if rail_matrix[r][c] == '*' and index < len(ciphertext):
                rail_matrix[r][c] = ciphertext[index]
                index += 1

    # Read the matrix in a zig-zag pattern to decrypt
    plaintext = []
    row, col = 0, 0
    for _ in ciphertext:
        plaintext.append(rail_matrix[row][col])
        col += 1

        if row == 0:
            direction_down = True
        elif row == rails - 1:
            direction_down = False

        row += 1 if direction_down else -1

    return ''.join(plaintext)


# Example Usage
message = "HELLO WORLD"
rails = 3

# Encrypt the message
ciphertext = rail_fence_encrypt(message.replace(" ", ""), rails)
print(f"Ciphertext: {ciphertext}")

# Decrypt the ciphertext
decrypted_text = rail_fence_decrypt(ciphertext, rails)
print(f"Decrypted Text: {decrypted_text}")
