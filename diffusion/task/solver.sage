#!/usr/bin/env sage

from operator import xor


# a little hack to speed up factorization
pari.addprimes([
    2,
    3,
    5,
    7,
    19,
    863,
    340889,
    3137699,
    7039399,
    329458369,
    146135397294919,
    361106839180393,
    2640909700557703,
    4790534701115227849,
    2782566926133529156279321,
    18132961002242963664087101647,
    206370177957870661324930260629439611748658717,
    385205923506325066779773926632087418148996108557,
    57488757415240467571970037282902062673065930424307567122589633654317379990461241056811128236408903
])


p = 1087794216881885390138846882837616653854818246740871308701
F = GF(p^2)
R.<x> = PolynomialRing(F)

g = F([
    499524925025645388489421127971489515554608533244574043991, 
    658768966855664872254556763316988398868872805109306786651
])


def Trace(c):
    return c + c^(p - 1) + c^(-p)


def Poly(c):
    return x^3 - c * x^2 + c^p * x - 1


def S(c, n):
    def _S(c, n):
        if n < 0:
            s1, s2, s3 = S(c, -n)
            return (s1^p, s2^p, s3^p)
        
        elif n == 0:
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


def pohlig_hellman(order, g, h):
    factors = [prime ^ exponent for prime, exponent in factor(order)]
    dlogs = []
    for fac in factors:
        print(fac)
        t = int(order) // int(fac)
        dlog = bsgs(g ^ t, h ^ t, (0, fac))
        dlogs.append(dlog)
    return crt(dlogs, factors)


def main():
    order = p^2 - p + 1
    cf = 7^2 * 7039399 * 329458369
    assert order % cf == 0 and S(g, cf) == 3

    A = F([367935335505535060627309666349148153467979281147737790082, 218371444261849661095396342421821471659401943961450259855])
    B = F([59595543606292026458984403561257712799025227343892736303, 188230934221532063646826075641142510522780269791408894474])
    message = 182382483418410333581242367496418581683567465113581948293736146952948061097311531748555967675697323468853663541789

    F_s = GF(p^6)
    R_s.<y> = PolynomialRing(F_s)

    g_s = F_s(Poly(g).change_ring(R_s).roots(multiplicities=False)[0])
    A_s = F_s(Poly(A).change_ring(R_s).roots(multiplicities=False)[0])
    assert Trace(g_s) == g and Trace(A_s) == A

    a = pohlig_hellman(cf, g_s, A_s)
    assert S(g, a) == A

    K = S(B, a)
    print(decrypt(K, message))


if __name__ == '__main__':
    main()
