#!/usr/bin/env sage

from operator import xor


p = 1087794216881885390138846882837616653854818246740871308701
F = GF(p^2)

g = F([
    499524925025645388489421127971489515554608533244574043991, 
    658768966855664872254556763316988398868872805109306786651
])


def S(c, n):
    def _S(c, n):
        if n == 0:
            return (c^p, F(3), c)

        elif n % 2:
            s1, s2, s3 = _S(c, n - 1)
            return (s2, s3, s3 * c - c^p * s2 + s1)
        
        else:
            s1, s2, s3 = _S(c, n // 2)
            return (s1 * s2 - c^p * s2^p + s3^p, s2^2 - 2 * s2^p, s3 * s2 - c * s2^p + s1^p)

    return _S(c, n)[1]


def tolist(c):
    return list(map(int, c.polynomial()))


def encrypt(c, message):
    key = mul(tolist(c))
    plaintext = int.from_bytes(message.encode(), 'big')
    assert plaintext < key
    return int(xor(plaintext, key))


def decrypt(c, ciphertext):
    key = mul(tolist(c))
    plaintext = int(xor(ciphertext, key))
    message = plaintext.to_bytes((key.bit_length() + 7) // 8, 'big').strip(b'\x00')
    return message.decode()


def main():
    a = randrange(2, p - 2)
    b = randrange(2, p - 2)
    
    A = S(g, a)
    B = S(g, b)
    
    Ka = S(A, b)
    Kb = S(B, a)
    
    assert Ka == Kb
    
    print(f'A: {tolist(A)}')
    print(f'B: {tolist(B)}')

    with open('flag.txt', 'r') as file:
        flag = file.read().strip()

    print(f'message: {encrypt(Ka, flag)}')

    return


if __name__ == '__main__':
    main()
