def power(a, b, P):
    if b == 1:
        return a % P
    else:
        return pow(a, b, P)  


def main():
    # Public keys agreed upon by Alice and Bob
    P = 23  # A prime number
    G = 9   # A primitive root of P

    print(f"The value of P: {P}")
    print(f"The value of G: {G}\n")

    # Private keys chosen by Alice and Bob
    a = 4  # Alice's private key
    b = 3  # Bob's private key
    print(f"The private key a for Alice: {a}")
    print(f"The private key b for Bob: {b}\n")

    # Calculate public keys
    x = power(G, a, P)  # Alice's public key
    y = power(G, b, P)  # Bob's public key

    # Generate the secret keys
    ka = power(y, a, P)  # Secret key for Alice
    kb = power(x, b, P)  # Secret key for Bob

    print(f"Secret key for Alice: {ka}")
    print(f"Secret key for Bob: {kb}")


if __name__ == "__main__":
    main()
