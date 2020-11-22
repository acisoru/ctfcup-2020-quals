#!/usr/bin/env python3.7

from os import urandom
from random import getrandbits
from operator import mul
from functools import reduce

from gmpy2 import is_prime


def generate_modulus() -> int:
    primes = []
    values = [3, 11, 19, 43, 67, 163]

    for value in values:
        while True:
            multiplier = getrandbits(512) ** 2
            prime = (value * multiplier + 1) // 4
            if is_prime(prime):
                primes.append(prime)
                break

    return reduce(mul, primes, 1)

    
def pad(message: bytes, length: int) -> bytes:
    padding = urandom(length - len(message) - 1).replace(b'\x00', b'\x01')
    return padding + b'\x00' + message


def unpad(message: bytes) -> bytes:
    return message.split(b'\x00', 1)[1]


def main(flag: bytes):
    print('Hello, please wait...')
    
    modulus = generate_modulus()
    message = pad(flag, modulus.bit_length() // 8 - 1)
    secret = int.from_bytes(message, 'big')

    assert secret < modulus and secret ** 2 > modulus
    
    print(modulus)
    print(pow(secret, 2, modulus))

    return


if __name__ == '__main__':
    with open('flag.txt', 'rb') as file:
        flag = file.read().strip()

    main(flag)
