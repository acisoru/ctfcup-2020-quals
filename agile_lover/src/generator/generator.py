def encrypt(text, secret):
    key = secret*int(len(text)/len(secret))
    key += secret[:len(text)%len(secret)]
    k = [ord(i) for i in key]
    m = [ord(i) for i in text]
    l = len(text)
    for i in range(l):
        m[i] = ((m[i] << 4) & 0xff) | ((m[i] >> 4) & 0xff)
        m[i] = ((m[i] << 6) & 0xff) | ((m[i] >> 2) & 0xff)
        m[i] = ((m[i] << 7) & 0xff) | ((m[i] >> 1) & 0xff)
        m[i] ^= k[i]
        k[i] = ((k[i] << 4) & 0xff) | ((k[i] >> 4) & 0xff)
        k[i] = ((k[i] << 6) & 0xff) | ((k[i] >> 2) & 0xff)
        k[i] = ((k[i] << 7) & 0xff) | ((k[i] >> 1) & 0xff)
        m[i] ^= k[i]
        m[i] = ((m[i] << 4) & 0xff) | ((m[i] >> 4) & 0xff)
        m[i] = ((m[i] << 6) & 0xff) | ((m[i] >> 2) & 0xff)
        m[i] = ((m[i] << 7) & 0xff) | ((m[i] >> 1) & 0xff)
    return m

def decrypt(atext, secret):
    key = secret*int(len(atext)/len(secret))
    key += secret[:len(atext)%len(secret)]
    k = [ord(i) for i in key]
    m = atext
    l = len(m)
    for i in range(l):
        m[i] = ((m[i] >> 7) & 0xff) | ((m[i] << 1) & 0xff)
        m[i] = ((m[i] >> 6) & 0xff) | ((m[i] << 2) & 0xff)
        m[i] = ((m[i] >> 4) & 0xff) | ((m[i] << 4) & 0xff)
        m[i] ^= k[i]
        k[i] = ((k[i] << 4) & 0xff) | ((k[i] >> 4) & 0xff)
        k[i] = ((k[i] << 6) & 0xff) | ((k[i] >> 2) & 0xff)
        k[i] = ((k[i] << 7) & 0xff) | ((k[i] >> 1) & 0xff)
        m[i] ^= k[i]
        m[i] = ((m[i] >> 7) & 0xff) | ((m[i] << 1) & 0xff)
        m[i] = ((m[i] >> 6) & 0xff) | ((m[i] << 2) & 0xff)
        m[i] = ((m[i] >> 4) & 0xff) | ((m[i] << 4) & 0xff)
    print(m)
    return ''.join([str(chr(i)) for i in m])

flag = "ctfcup{cut3_kUt3_Qt_cppR3}"
password = "@g1l3tHeB3sT"
enc = encrypt(flag, password)
print(enc)
dec = decrypt(enc, password)
print(dec)
