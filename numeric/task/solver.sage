#!/usr/bin/env sage

import struct


def main():
    with open('flag.enc', 'rb') as file:
        data = file.read()
    
    n = isqrt(len(data) // 8)
    values = struct.unpack('<' + 'Q' * n * n, data)
    
    M = []

    for y in range(n):
        M.append([])
        for x in range(n):
            M[y].append(values[n * y + x])
    
    R = matrix(M).cholesky().diagonal()
    flag = ''.join(chr(isqrt(x // 2)) for x in R)

    print(flag.strip())


if __name__ == '__main__':
    main()
