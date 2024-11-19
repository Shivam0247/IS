def create_playfair_matrix(key):
    # Remove duplicates and non-alphabetic characters from the key
    key = ''.join(dict.fromkeys(key.upper().replace('J', 'I')))
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"  # Note: J is replaced by I in the Playfair cipher
    matrix = []
    
    # Add the key characters to the matrix
    for char in key:
        if char not in matrix and char in alphabet:
            matrix.append(char)
    
    # Add the remaining letters to the matrix
    for char in alphabet:
        if char not in matrix:
            matrix.append(char)
    
    # Convert the 1D list into a 5x5 grid
    return [matrix[i:i+5] for i in range(0, 25, 5)]

def preprocess_message(message):
    message = message.upper().replace('J', 'I').replace(" ", "")
    digraphs = []
    i = 0

    while i < len(message):
        # Form digraphs (pairs of letters)
        if i+1 < len(message) and message[i] != message[i+1]:
            digraphs.append(message[i] + message[i+1])
            i += 2
        else:
            # Add a filler character 'X' if letters are the same or message length is odd
            digraphs.append(message[i] + 'X')
            i += 1

    return digraphs

def find_position(matrix, char):
    for row in range(5):
        for col in range(5):
            if matrix[row][col] == char:
                return row, col
    return None, None

def encrypt_digraph(matrix, digraph):
    row1, col1 = find_position(matrix, digraph[0])
    row2, col2 = find_position(matrix, digraph[1])

    if row1 == row2:  # Same row
        return matrix[row1][(col1 + 1) % 5] + matrix[row2][(col2 + 1) % 5]
    elif col1 == col2:  # Same column
        return matrix[(row1 + 1) % 5][col1] + matrix[(row2 + 1) % 5][col2]
    else:  # Rectangle rule
        return matrix[row1][col2] + matrix[row2][col1]

def playfair_encrypt(message, key):
    matrix = create_playfair_matrix(key)
    digraphs = preprocess_message(message)
    ciphertext = ""

    for digraph in digraphs:
        ciphertext += encrypt_digraph(matrix, digraph)

    return ciphertext

# Example Usage
message = "HELLO WORLD"
key = "SECRET"

ciphertext = playfair_encrypt(message, key)
print("Key Matrix:")
for row in create_playfair_matrix(key):
    print(row)
print(f"Plaintext: {message}")
print(f"Ciphertext: {ciphertext}")
