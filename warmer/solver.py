#!/usr/bin/env python3.7

import sys
import socket

from ast import literal_eval
from gmpy2 import gcdext


def read_data(file):
    return file.readline().decode().split(':')[-1].strip()


def main():
    IP = sys.argv[1] if len(sys.argv) > 1 else '0.0.0.0'
    PORT = 7702

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.settimeout(30)
        sock.connect((IP, PORT))
        file = sock.makefile('rwb')

        print(file.readline().strip().decode())
        print(file.readline().strip().decode())

        sender_n, sender_e = literal_eval(read_data(file))
        receiver_n, receiver_e = literal_eval(read_data(file))
        assert sender_n == receiver_n
        n = sender_n
        
        message1 = int(read_data(file))
        message2 = int(read_data(file))
        message3 = int(read_data(file))

    g, x, y = gcdext(sender_e, receiver_e)
    if g > 1:
        return main()

    flag = int((pow(message1, x, n) * pow(message3, y, n)) % n)
    print(flag.to_bytes((n.bit_length() + 7) // 8, 'big').strip(b'\x00'))

    return


if __name__ == '__main__':
    main()
