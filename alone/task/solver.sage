#!/usr/bin/env sage

from ast import literal_eval


p = 509
h = 24

F.<x> = GF(p^h)
q = F.order() - 1


def decrypt_one(ciphertext, t, g, d):
    V = F.vector_space(map=False)
    Fp = GF(p)
    R.<y> = PolynomialRing(Fp)
    
    r = ciphertext - h * d
    transformation = matrix(Fp, [V(t^i) for i in range(h)]).transpose().inverse()
    pol = R(list(transformation * V(g^r))) + R(t.minpoly())
    
    indexes = [p - pol.roots()[i][0] for i in range(h)]
    bits = [1 if i in indexes else 0 for i in range(p)]

    plaintext = 0
    left = h

    for i in range(p):
        if bits[i] == 1:
            plaintext += binomial(p - (i + 1), left)
            left -= 1

    return plaintext


def decrypt(ciphertexts, t, g, d):
    message = 0
    bound = binomial(p, h)

    for ciphertext in reversed(ciphertexts):
        plaintext = decrypt_one(ciphertext, t, g, d)
        message = message * bound + plaintext

    message = int(message)
    return message.to_bytes((message.bit_length() + 7) // 8, 'big')


def recover_t(c):
    # a little hack to speed up LLL and roots computations
    _p = 50

    M = matrix.identity(ZZ, _p)

    # 1234, 200 are magic constants
    column = [c[i] - c[0] for i in range(1, _p)] + [-(1234 * q)]
    accuracy = 200

    for i in range(accuracy):
        M = M.augment(vector(ZZ, column))

    print('LLL...')
    B = M.LLL()
    print('LLL done.')

    for row in B:
        if row[-1] != 0:
            continue
        
        status = row[-(accuracy + 1)]

        if abs(status) == 1:
            powers = list(row * status)[:(_p - 1)]
            break
    
    # print(powers)

    I = [i for i in range(_p - 1) if powers[i] >= 0]
    J = [i for i in range(_p - 1) if powers[i] < 0]
    S = sum(powers)

    R.<y> = PolynomialRing(F)
    
    left = prod(pow(y + (i + 1), powers[i]) for i in I)
    right = prod(pow(y + (i + 1), abs(powers[i])) for i in J)
    middle = pow(y, abs(S))
    
    if S >= 0:
        pol = left - middle * right
    else:
        pol = left * middle - right

    print('Roots...')
    roots = pol.roots(multiplicities=False)
    print('Roots done.')

    # print(roots)

    for root in roots:
        if root.minpoly().degree() == h:
            yield root


def recover_g(c, t):
    r = F.multiplicative_generator()

    for i in range(1, p):
        c_diff = (c[i] - c[0]) % q
        
        if gcd(int(c_diff), int(q)) > 1:
            continue
        
        power = (1 + i / t).log(r) * inverse_mod(c_diff, q)
        g = r ^ power

        if g.multiplicative_order() != q:
            continue
    
        if (1 + (i + 1) / t).log(g) == c[i + 1] - c[0]:
            return g


def recover_d(c, t, g):
    return (c[0] - t.log(g)) % q


def main():
    with open('output.txt', 'r') as file:
        file.readline()
        key = literal_eval(file.readline().strip())
        ciphertexts = literal_eval(file.readline().strip())

    for t in recover_t(key):
        g = recover_g(key, t)
        if g is None:
            continue

        d = recover_d(key, t, g)
        
        if key[2] != (d + (t + 2).log(g)) % q:
            continue
        
        plaintext = decrypt(ciphertexts, t, g, d)
        print(plaintext)
        break

    return


if __name__ == '__main__':
    main()
