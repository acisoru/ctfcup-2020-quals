#!/usr/bin/env sage

from random import randrange


p = 509
h = 24

F.<x> = GF(p^h)
q = F.order() - 1


def generate_key():
    while True:
        t = F.random_element()
        if t.minpoly().degree() == h:
            break

    while True:
        g = F.random_element()
        if g.multiplicative_order() == q:
            break

    d = randrange(1, q)
    c = [(d + (t + i).log(g)) % q for i in range(p)]

    return c


def encrypt(text, key):
    message = int.from_bytes(text.encode(), 'big')
    ciphertexts = []

    size = binomial(p, h)

    while message > 0:
        part = message % size
        message //= size

        bits = []
        left = h

        for i in range(p):
            bound = binomial(p - (i + 1), left)

            if part >= bound:
                bits.append(1)
                part -= bound
                left -= 1
            else:
                bits.append(0)

        assert sum(bits) == h

        ciphertext = sum((bits[i] * key[i]) % q for i in range(p))
        ciphertexts.append(ciphertext)

    return ciphertexts


def main():
    print('Please, wait. Key generation is a bit long...')
    key = generate_key()

    with open('flag.txt', 'r') as file:
        flag = file.read().strip()

    ciphertexts = encrypt(flag, key)

    print(key)
    print(ciphertexts)

    return


if __name__ == '__main__':
    main()
