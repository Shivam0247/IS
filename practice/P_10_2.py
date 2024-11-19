def encrypt_with_shift(plaintext,shifts):
    ciphertext=[]
    plaintext_len=len(plaintext)

    for i in range(plaintext_len):
        if plaintext[i].isalpha():
            base=ord('a') if plaintext[i].islower() else ord("A")
            shifterd_char = chr((ord(plaintext[i])-base+shifts[i])%26 + base)
            ciphertext.append(shifterd_char)
        else:
            ciphertext.append(plaintext[i])
    
    return "".join(ciphertext)

plaintext="RAG BABY"
shifts=[1,2,3,0,2,3,4,5]
ciphertext=encrypt_with_shift(plaintext,shifts)
print(f"plain Text: {plaintext}")
print(f"Ciphertext: {ciphertext}") 