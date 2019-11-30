#!/usr/bin/python

def power(x, n):
    s=1

    while n>0:
    	n = n-1
    	s = s*x
    return s

result = power(2,3)
print(power(2,3))