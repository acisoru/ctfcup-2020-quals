#!/usr/bin/env sage

import sys
import socket
import libnum


# https://eprint.iacr.org/2017/403.pdf
# https://eprint.iacr.org/2002/109.pdf


sys.setrecursionlimit(1024000)


def get_prime(n, i):
    if is_prime(n):
        return ZZ(n)

    ZmodN = Zmod(n)
    B1, B2 = 10, 5

    j = [
        0,
        (-2^5)^3, 
        (-2^5 * 3)^3, 
        (-2^5 * 3 * 5 * 11)^3, 
        (-2^6 * 3 * 5 * 23 * 29)^3
    ][i]
    
    a = ZZ(ZmodN(j) / ZmodN(1728 - j))
    cs = [ZZ(ZmodN.random_element()) for _ in range(B1)]
    xs = [ZZ(ZmodN.random_element()) for _ in range(B2)]

    for c in cs:
        if j == 0:
            E = EllipticCurve(ZmodN, [0, c])
        else:
            E = EllipticCurve(ZmodN, [3*a*c^2, 2*a*c^3])
        for x in xs:
            z = E.division_polynomial(n, x=x)
            p = gcd(z, n)
            if p > 1:
                return ZZ(p)


def main():
    IP = sys.argv[1] if len(sys.argv) > 1 else '0.0.0.0'
    PORT = 7701

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.settimeout(30)
        sock.connect((IP, PORT))
        file = sock.makefile('rwb')
        print(file.readline())
        n = int(file.readline().strip().decode())
        ct = int(file.readline().strip().decode())

    print(f'n: {n}')
    print(f'ct: {ct}')

    primes, i = [], 0

    while n > 1:
        prime = get_prime(n, i)
        primes.append(prime)
        n = n // prime
        print(f'factor: {prime}')
        i += 1

    print(primes)
    factors = {prime: 1 for prime in primes}

    for root in libnum.sqrtmod(ct, factors):
        message = root.to_bytes(1024, 'big').strip(b'\x00')
        if b'ctfcup' in message:
            flag = message.split(b'\x00', 1)[1].decode()
            print(f'flag: {flag}')


if __name__ == '__main__':
    main()
