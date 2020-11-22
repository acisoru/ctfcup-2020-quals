#!/usr/bin/env python3.7

from gmpy2 import next_prime, gcdext
from random import getrandbits


class Cryptoanalyst:
    def __init__(self, p, q):
        self._n = p * q
        self._phi = (p - 1) * (q - 1)
        self._e, self._d = self.generate_key()
        return

    def generate_key(self):
        bits = self._n.bit_length()
        
        while True:
            e = getrandbits(bits) % self._phi
            g, d, _ = gcdext(e, self._phi)
            if g == 1 and d.bit_length() == e.bit_length():
                break
        
        return e, d

    def encrypt(self, plaintext):
        return pow(plaintext, self._e, self._n)

    def decrypt(self, ciphertext):
        return pow(ciphertext, self._d, self._n)

    def get_key(self):
        return (self._n, self._e)


def secure_transmission(sender, receiver, secret):
    print(f'> sender: hello')
    print(f'> receiver: hello')

    print(f'> sender: {sender.get_key()}')
    print(f'> receiver: {receiver.get_key()}')

    message1 = sender.encrypt(secret)
    print(f'> sender: {message1}')

    message2 = receiver.encrypt(message1)
    print(f'> receiver: {message2}')
    
    message3 = sender.decrypt(message2)
    print(f'> sender: {message3}')

    message4 = receiver.decrypt(message3)    
    assert message4 == secret

    return


def main():
    bits = 1024
    p, q = map(int, map(next_prime, map(getrandbits, [bits] * 2)))

    sender = Cryptoanalyst(p, q)
    receiver = Cryptoanalyst(p, q)

    with open('flag.txt', 'r') as file:
        flag = file.read().strip()

    message = int.from_bytes(flag.encode(), 'big')
    secure_transmission(sender, receiver, message)

    return


if __name__ == '__main__':
    main()
