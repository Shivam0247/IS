def convert_to_cipher(plaintext,shift):
    ciphertext=[]
    plain_len = len(plaintext)
    shift_key = [int(digit) for digit in passkey]
    for i in range(plain_len):
        if plaintext[i].isalpha():
            base=ord('a') if plaintext[i].islower() else ord("A")
            cipher= chr((ord(plaintext[i])-base+shift_key[i%4])%26+base)
            ciphertext.append(cipher)
        else:
            ciphertext.append(plaintext[i])

    return ''.join(ciphertext)

plaintext="GRONSFELD"
passkey="1234"

cipher=convert_to_cipher(plaintext,passkey)

print(f"plain Text: {plaintext}")
print(f"Ciphertext: {cipher}") 