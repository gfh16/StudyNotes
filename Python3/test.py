#!/usr/bin/python

print("Hello World!")

## 1.计算平方和1~n的平方和： 1^2+2^2+3^2+...+n^2
def calc(n):
  sum = 0
  for i in range(1, n+1):
    sum += pow(i,2)
  return sum

print(calc(10))


## 2.计算数组中数据的平方和
def cal1(*numbers):
  sum = 0
  for i in numbers:
  	sum += i*i
  return sum

aa = [1,2,3]
result = sum([c*c for c in aa])
result1 = cal1(*aa)
print(result)
print(result1)

## 3.排序问题
lis = [56, 12, 1, 6, 222, 34, 444]
def sortport():
	for i in range(len(lis)-1):
		for j in range(len(lis)-1-i):
			if lis[j]<lis[j+1]:
				lis[j],lis[j+1] = lis[j+1], lis[j]
	return lis

print(sortport())

  
