#!/usr/bin/env python3
import sys

f = open(sys.argv[1], 'r')
o = open(sys.argv[2], 'w')

regs = {'a':0, 'b':1, 'c':2, 'd':3}

for line in f:
	d = line.strip().replace(',','').split(' ')
	if len(line) <= 2:
		continue
	c = d[0]
	if c == 'clear':
		o.write('\n')
	elif c == 'push':
		o.write(' \n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'push1':
		o.write('  \n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'push2':
		o.write('   \n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'pop':
		o.write(' '*4 + '\n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'pop1':
		o.write(' '*5 + '\n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'pop2':
		o.write(' '*6 + '\n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'mov':
		try:
			regs[d[2]]
			o.write(' '*8 + '\n')
			o.write(' '*regs[d[2]] + '\n')
			o.write(' '*regs[d[1]] + '\n')
		except Exception:
			o.write(' '*7 + '\n')
			o.write(' '*int(d[2]) + '\n')
			o.write(' '*regs[d[1]] + '\n')
	elif c == 'add':
		o.write(' '*9 + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'sub':
		o.write(' '*10 + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'mul':
		o.write(' '*11 + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'div':
		o.write(' '*12 + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'mod':
		o.write(' '*13 + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'and':
		o.write(' '*14 + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'or':
		o.write(' '*15 + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'xor':
		o.write(' '*16 + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*regs[d[1]] + '\n')
	elif c == 'jmp':
		o.write(' '*17 + '\n')
		o.write(' '*int(d[1]) + '\n')
	elif c == 'je':
		o.write(' '*18 + '\n')
		o.write('\n')
		o.write(' '*regs[d[1]] + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*int(d[3]) + '\n')
	elif c == 'jne':
		o.write(' '*18 + '\n')
		o.write(' \n')
		o.write(' '*regs[d[1]] + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*int(d[3]) + '\n')
	elif c == 'jl':
		o.write(' '*18 + '\n')
		o.write('  \n')
		o.write(' '*regs[d[1]] + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*int(d[3]) + '\n')
	elif c == 'jg':
		o.write(' '*18 + '\n')
		o.write('   \n')
		o.write(' '*regs[d[1]] + '\n')
		o.write(' '*regs[d[2]] + '\n')
		o.write(' '*int(d[3]) + '\n')
	elif c == 'input':
		o.write(' '*19 + '\n')
		o.write(' '*int(d[1]) + '\n')
	elif c == 'print':
		o.write(' '*20 + '\n')
	elif c == 'exit':
		o.write(' '*21 + '\n')

f.close()
o.close()
