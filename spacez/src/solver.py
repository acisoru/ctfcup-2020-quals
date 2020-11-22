#!/usr/bin/env python3

data = [99, 16, 120, 14, 103, 52, 101, 2, 11, 70, 116, 108, 89, 78, 29, 46, 106, 105, 38, 147, 113, 189, 75, 166, 58, 251, 42, 226, 18, 190, 9, 173]

cur = data[0]
f = [cur]
for i in range(1, len(data)):
	tmp = 6*i+i
	cur ^= tmp
	f.append(data[i] ^ cur)
	cur = data[i]

print(f)
flag = ''.join([str(chr(i)) for i in f])
print(flag)
