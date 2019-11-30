#!/usr/bin/python

#########################################################
# 菜鸟教程python实践实例:
# https://www.runoob.com/python3/python3-examples.html
#########################################################
# 30个常用python实现
# https://www.jianshu.com/p/246ffcfcd2ca
#########################################################


print("Hello World!")

#========================================================
## 1.计算平方和1~n的平方和： 1^2+2^2+3^2+...+n^2
def calc(n):
  sum = 0
  for i in range(1, n+1):
    sum += pow(i,2)
  return sum

#print(calc(10))

#========================================================
## 2.计算数组中数据的平方和
def cal1(*numbers):
  sum = 0
  for i in numbers:
  	sum += i*i
  return sum

aa = [1,2,3]
result = sum([c*c for c in aa])
result1 = cal1(*aa)
#print(result)
#print(result1)

#========================================================
## 3.排序问题
## 参见Python实现十大常用排序算法 
## http://www.sohu.com/a/304883839_571478
lis = [56, 12, 1, 6, 222, 34, 444]
def sortport():
	for i in range(len(lis)-1):
		for j in range(len(lis)-1-i):
			if lis[j]<lis[j+1]:
				lis[j],lis[j+1] = lis[j+1], lis[j]
	return lis

#print(sortport())

#========================================================  
## 4.计算阶乘
## 方法1
def fac(n):
	if n==1:
		return 1
	else:
		return n*fac(n-1)
#print(fac(5))

## 方法2
def fac1(n):
	result = n
	for i in range(1,n):
		result *= i
	return result
#print(fac1(5))

## 输入一个数, 计算它的阶乘
def fac2():
	num = int(input("请输入一个数字:"))
	factorial = 1

	## 判断数字是否为负数，0，或正数
	if num < 0:
		print("抱歉，负数没有阶乘")

	elif num == 0:
		print("0 的阶乘为1")

	else:
		for i in range(1, num+1):
			factorial *= i
		print("%d 的阶乘为 %d" % (num, factorial))
#fac2()

#=======================================================
## 5.列出当前目录下的所有我呢见和目录
###  python 中 os 模块的使用
import os
list = [d for d in os.listdir('.')]
#print(list)

#=======================================================
## 6.把一个list中所有的字符串变成小写
L1 = ['Hello']
L2 = [s.lower() for s in L1]
#print(L1)

#=======================================================
## 7.输出某个路径下的所有文件和文件夹的路径
def print_dir():
	filepath = input("请输入一个路径:")
	if filepath == "":
		print("请输入一个正确的路径")
	else:
		for i in os.listdir(filepath):      ##获取目录中的文件以及子目录列表
			print(os.path.join(filepath,i)) ##把路径与文件名结合起来
#print(print_dir())

#========================================================
## 8.输出某个路径及其子目录下的所有文件路径
def show_dir(filepath):
	for i in os.listdir(filepath):
		path = (os.path.join(filepath,i))
		print(path)
		if os.path.isdir(path):
		    show_dir(path)

filepath="C:\Program Files\Internet Explorer"
#show_dir(filepath)


#=======================================================
## 9.输出某路径及其子目录下所有以.html为后缀的文件
def print_dir1(filepath):
	for i in os.listdir(filepath):
		path = os.path.join(filepath,i)
		if os.path.isdir(path):
			print_dir1(path)
		if path.endswith(".html"):
			print(path)

filepath = "C:\Program Files\Git"
#print_dir1(filepath)


#=======================================================
## 10.把原字典的键值对颠倒并产生新的字典
dict1 = {"A":"a", "B":"b", "C":"c"}
dict2 = {y:x for x,y in dict1.items()}
#print(dict1)
#print(dict2)


#=====================================================
## 11.打印九九乘法表
#for i in range(1,10):
#	for j in range(1,i+1):
#		print('%d x %d = %d \t'%(i,j,i*j), end='')
#	print()


##===================================================
## 12.替换列表中的 3 为 3a
num=["harden","lampard",3,34,45,56,76,78,3,3,3,877]
#print(num.count(3))
#print(num.index(3))
for i in range(num.count(3)):     ##获取3出现的次数
	ele_index = num.index(3)      ##获取首次出现的坐标
	num[ele_index]="3a"
#print(num)


#===================================================
## 13.打印每个名字
#L = ["James","Meng","Xin"]
#for i in range(len(L)):
#	print("Hello,%s"%L[i])


#==================================================
## 14.合并去重
list1 = [2,3,8,4,5,6]
list2 = [5,6,10,17,11,2]

list3 = list1 + list2
print(list3)
print(set(list3))






