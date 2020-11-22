f = open('task.exe', 'rb')

s = f.read()

f.close()

s = ', '.join([hex(i) for i in s])
i = 0
c = 0

while i < len(s):
    if c == 10000000:
        tmp = s.index(',', i)
        s = s[:tmp] + '\n\t\t\t' + s[tmp:]
        c = 0
        i += 3
    i+=1
    c += 1
print(len(s.split('\n')))

f = open('data.txt', 'w')
f.write(s)
f.close()
