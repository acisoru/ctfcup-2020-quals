#!/usr/bin/env python3.7

import ctypes


def syscall(number, arguments):
    libc = ctypes.CDLL(None)
    return libc.syscall(number, *arguments)


def main():
    number = input('[?] syscall number: ')
    arguments = input('[?] syscall arguments: ').split(' ')
    number, arguments = int(number), list(map(int, arguments))
    result = syscall(number, arguments)
    print(f'[+] result: {result}')
    return


if __name__ == '__main__':
    main()
