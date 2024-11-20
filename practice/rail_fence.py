def rail_encrypt(plaintext,rails):
    plaintext=plaintext.replace(" ","")
    rails_pattern=[""]*rails
    row=0
    direction=1

    for char in plaintext:
        rails_pattern[row]+=char

        if row==0:
            direction=1
        elif row == rails - 1:
            direction=-1
        row+=direction
    
    return "".join(rails_pattern)

def rail_fence_decrypt(ciphertext, rails):
    zigzag = [[] for _ in range(rails)]
    row, direction = 0, 1

    for char in ciphertext:
        zigzag[row].append('*')
        if row == 0:
            direction = 1
        elif row == rails - 1:
            direction = -1
        row += direction

    index = 0
    for row in zigzag:
        for i in range(len(row)):
            row[i] = ciphertext[index]
            index += 1

    result = []
    row, direction = 0, 1
    for _ in ciphertext:
        result.append(zigzag[row].pop(0))  
        if row == 0:
            direction = 1
        elif row == rails - 1:
            direction = -1
        row += direction

    return ''.join(result)

plaintext="HELLO WORLD"
rails=3
Encrypt=rail_encrypt(plaintext,rails) 
print(f"Encrpt text: {Encrypt}")

decypt=rail_fence_decrypt(Encrypt,rails)
print(f"decypt text: {decypt}")
