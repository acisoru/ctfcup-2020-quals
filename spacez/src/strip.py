#!/usr/bin/env python3
import os
s = ''
with open('strip', 'r') as f:
	s = f.read()
s = s.split('\n')[:-1]

for i in s:
	os.system('mipsel-linux-gnu-strip --strip-symbol='+i+' spacez')
