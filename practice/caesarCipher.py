def Enc(text, shift):
    encrypted_text = []

    for char in text:
        if char.isalpha():
            shift_base = 65 if char.isupper() else 97
            encrypted_char = chr((ord(char) - shift_base + shift) % 26 + shift_base)
            encrypted_text.append(encrypted_char)
        else:
            encrypted_text.append(char)

    return ''.join(encrypted_text)

def Dec(text, shift):
    decrypted_text = []

    for char in text:
        if char.isalpha():
            shift_base = 65 if char.isupper() else 97
            decrypted_char = chr((ord(char) - shift_base - shift) % 26 + shift_base)
            decrypted_text.append(decrypted_char)
        else:
            decrypted_text.append(char)

    return ''.join(decrypted_text)

text = "Hello, World!"
shift = 4

encrypted_text = Enc(text, shift)
decrypted_text = Dec(encrypted_text, shift)

print(f"Original text: {text}")
print(f"Encrypted text: {encrypted_text}")
print(f"Decrypted text: {decrypted_text}")
