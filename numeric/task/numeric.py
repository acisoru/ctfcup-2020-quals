#!/usr/bin/env python3.7

import numpy as np
import secret


def encrypt(key, message):
    n = len(message)

    assert len(key.shape) == 2 and min(key.shape) >= n
    assert abs(128 ** 2 / 2 - key.mean()) < 128

    M = key[:n, :n]
    P = np.array(list(message))
    I = np.identity(n, dtype=int)
    
    M += I * (np.square(P) - np.diag(M))
    M += M.T
    C = np.tril(M) @ np.triu(M)
    
    return C.tobytes()


def main():
    with open('flag.txt', 'rb') as file:
        flag = file.read().strip()
    
    ciphertext = encrypt(secret.key, flag)
    
    with open('flag.enc', 'wb') as file:
        file.write(ciphertext)
    
    return


if __name__ == '__main__':    
    main()
