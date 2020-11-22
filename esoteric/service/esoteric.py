#!/usr/bin/env python3.7

import random
import string


def generate_payload(seed, length):
    random.seed(seed)

    return ''.join(random.choices(string.printable, k=length))


def main():
    print(f'[!] Hello!')

    try:
        seed = int(input(f'[?] Input seed: '))
        length = int(input(f'[?] Input length: '))
    except ValueError:
        print(f'[-] Incorrect parameters.')
        return

    command = generate_payload(seed, length)
    print(f'[*] Executing: {repr(command)}')

    output = eval(command)
    print(repr(output))

    return


if __name__ == '__main__':
    main()
