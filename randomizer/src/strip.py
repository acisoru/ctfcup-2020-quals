#!/usr/bin/env python3
import os
import sys

s = ''
with open('strip', 'r') as f:
	s = f.read()
s = s.split('\n')[:-1]

for i in s:
	os.system('strip --strip-symbol='+i+' '+sys.argv[1])
