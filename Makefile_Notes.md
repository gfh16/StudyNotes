<div style="text-align: left">
<font face="微软雅黑" size=5 color=#FF00FF>
  小关的读书笔记
</font> 
</div>


<center> 零基础学写 Makefile </center>
===================================

>+ [Makefile 简易教程](https://www.cnblogs.com/owlman/p/5514724.html)
>+ [Makefile 经典教程(全)(建议选读)](https://blog.csdn.net/weixin_38391755/article/details/80380786)
>+ [GNU Make教程(中文)(建议通读)](https://cloud.tsinghua.edu.cn/f/f4ca480ccc354a83ada6/)

>+ `make` 主要用来编译源代码,生成结果代码,然后把结果代码连接起来生成可执行文件或库文件.
>+ `make`可以自动识别并推导命令. 利用这一点能够使得makefile变得简洁高效
>+ makefile 实质是用来管理`make`命令的特殊文件.
>+ makefile 的好处是"自动化编译",一旦写好,只需一个`make`命令,整个工程可完成自动编译. `make` 并不管命令是怎么工作的,它只管执行所定义的命令.`make`只管文件的依赖性.


目录
-----
[toc]


### <font color=#DC143C> 一. Makefile 基础知识 </font>

#### <font color=#FF00FF> 1.1 make 工作原理</font>
>+ **程序的编译原理**
编译: 把源程序编译成中间代码, LINUX 下为 Object File, 即`.o`文件
链接: 把大量的 Object File 合成执行文件
1.源文件首先会生成中间目标文件,再由中间目标文件生成执行文件.
2.编译时,编译器只检测程序语法、函数、变量是否被声明. 如果函数未被声明,编译器会给一个警告,但可以生成Object File.
3.链接时,链接器会在所有的Object File中寻找函数的实现,如果找不到,就会报链接错误.

>+ **Makefile 的规则(核心思想):** 当依赖文件列表`prerequisites`中有一个以上的文件比目标文件`target`要新时,`command`所定义的命令就会被执行.
```Makefile
target...: prerequisites ...

command
...
... 
```  

>+ **make 的工作原理简述**
1.`make`会在当前目录下寻找名字叫 "Makefile"或"makefile"的文件
2.如果找到,它会找到文件中的第一个目标文件(`calc`), 并把`calc`作为最终的目标文件
3.如果`calc`文件不存在,或是其所依赖的`.o`文件的修改时间要比`calc`这个文件要新,则会执行后面定义的命令来生成`calc`文件
4.如果`calc`所依赖的`.o`文件也存在,那么`make`会在当前文件中寻找目标为`.o`文件的依赖性,如果找到则根据其规则生成对应的`.o`文件
5.在 C文件与 H文件都存在的情况下,`make`会生成`.o`文件,然后将`.o`文件链接成目标文件,即可执行文件

```Makefile
calc: main.C getch.C getop.C stack.C
	gcc -o calc main.C getch.C getop.C stack.C
```


#### <font color=#FF00FF> 1.2 Makefile 简介 </font>
>+ **Makefile 的n内容大致分为五部分:** 显式规则、隐含规则、变量定义、文件指示、注释
1.<u>显式规则.</u> 由Makefile书写着明确指出的,包括要生成的文件、文件的依赖关系、生成的命令.
2.<u>隐含规则.</u> 由`make`的自动推导功能完成.
3.<u>变量定义.</u> Makefile 的变量实际上是一个字符串,相当于C语言中的宏.
4.<u>文件指示.</u> 类似于C语言中的`include`或预编译`#if`
5.<u>注释.</u> Makefile用`"#"`字符注释. Makefile中只有行注释.

>+ **Makefile的文件名**
1.默认情况下,`make`命令会在当前目录寻找文件名为`"GNUmakefile"`、`"makefile"`、`"Makefile"`的文件
2.建议使用`"Makefile"`命名,最好不要用`"GNUmakefile"`.
3.也可以使用别的文件名来书写 Makefile，如`"Make.Linux"`,使用时需要指定Makefile，如`make -f Make.Linux`或`make --file Make.Linux`

>+ **引用其他的Makefile**
在Makefile使用include关键字可以把别的Makefile包含进来.

>+ **make 的工作方式**
1.读入所有的 Makefile
2.读入被 include 的其他 Makefile
3.初始化文件中的变量
4.推导隐含规则,并分析所有规则
5.为所有的目标的文件创建依赖关系链
6.根据依赖关系,决定哪些目标要重新生成
7.执行生成命令


#### <font color=#FF00FF> 1.3 Makefile 书写规则 </font>
>+ **Makefile 的规则**
1.规则包括: (1)依赖关系, (2)生成目标的方法
2.<font color=#FF0000>在Makefile中,规则的顺序非常重要!</font> 因为, Makefile中只应该有一个目标程序.
3.一般来说,定义在 Makefile 中的目标可能会有很多,但是第一条规则中的目标将被确立为最终的目标.
4.如果第一条规则中的目标有很多个,那么第一个目标会成为最终的目标.
```Makefile
# 规则举例
foo.o: foo.c defs.h
	cc -c -g foo.c
```

>+ **规则的语法**
1.targets 是文件名,以空格分开,可以使用通配符.
2.prerequisites 是目标所依赖的文件. 
3.command 是命令行.
4.如果命令太长,可以使用反斜杠(`"\"`)作为换行符.但是注意反斜杠之后不能有空格.
```Makefile
targets: prerequisites
	commands
	...
```

>+ **使用通配符**
`make`支持三个通配符: `"*"`,`"?"`,`[...]`
`"~"` 如果是`"~/test"`,则表示当前用户的`$HOME`目录下的`test`目录.
`"*"` 代替一系列文件,如`"*.C"`表示所有以`C`为后缀的文件

>+ **文件搜索**
Makefile文件中的特殊变量`"VPATH"`可完成自动寻找文件.
1.vpath \<pattern\> \<directories\>  &emsp;为符合模式\<pattern\>的文件指定搜索目录\<directories\>
2.vpath \<pattern\> &emsp;  清除符合模式\<pattern\>的文件的搜索目录
3.vpath &emsp;清除所有已被设置好了的文件搜索目录

>+ **伪目标**
1.Makefile中把那些没有任何依赖只有执行动作的目标称为"伪目标"
2."伪目标"并不是一个文件,只是一个标签. 
3."伪目标"的取名不能和文件名重名.为此,我们可以使用一个特殊的标记`".PHONY"`来显式地指明一个目标是"伪目标".
```Makefile
.PHONY: clean
clean:
	rm *.o temp
```

>+ **多目标**
Makefile的规则中的目标可以不止一个,一般可以使用自动化变量`"$@"`来实现.

>+ **静态模式**
静态模式可以更加容易地定义多目标的规则，可以让我们的规则变得更加的有弹性和灵活
```shell
## "目标模式"或"依赖模式"中都应该有"%"

objects = foo.o bar.o

all: $(objects)

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
```



>+ **自动生成依赖性**
1.大多数的 C/C++ 编译器都支持`"-M"`选项,即自动寻找源文件中包含的头文件,并生成一个依赖关系
2.如此一来,我们就不必手动书写文件的依赖关系,而由编译器自动生成
3.如果使用GNU的 C/C++ 编译器,我们需要用`"-MM"`参数,不然，`"-M"`参数会把一些标准库的头文件也包含进来.



#### <font color=#FF00FF> 1.4 Makefile 书写命令 </font>
>+ 每条规则中的命令和操作系统Shell的命令行相同.
>+ `make`会按顺序一条一条地执行命令,每条命令的开头必须以`[Tab]`键开头.

>+ **显示命令**
```shell
@echo 正在编译XXX模块...
输出结果: 正在编译XXX模块...

echo 正在编译XXX模块...
输出结果:
echo 正在编译XXX模块...
正在编译XXX模块...
```

>+ **命令执行**
1.如果希望第二条命令在第一条命令的基础上执行,则需要两条命令写在一行上,同时用分号隔开.
```shell
exec:
	cd /home/hchen;pwd
```

>+ **命令出错**
1.有时候,命令的出错不代表是错误的.
2.忽略命令的出错,可以使用如下方法
```shell
# 命令行前加一个减号 "-"
clean:
	-rm -f *.o

# make 加上 "-i"或者"--ignore-errors"参数
```

>+ **嵌套执行 make**
1.对于一个大工程,不同模块放在不同的目录中,可以在每个目录中都写一个该目录的 Makefile
2.这样,我们可以用一个总控的 Makefile 来管理这些子目录的 Makefile
```shell
subsystem:
	cd subdir && $(MAKE)
```



### <font color=#DC143C> 二. Makefile 知识点详解 </font>
#### <font color=#FF00FF> 2.1 Makefile 中的变量 </font>
>1.Makefile 的变量实际上是一个字符串,相当于C语言中的宏.
>2.变量的命名字可以包含字符、数字，下划线（可以是数字开头），但不应该含有“:”、“#”、“=”或是空字符（空格、回车等）
>3.变量是大小写敏感的，“foo”、“Foo”和“FOO”是三个不同的变量名
4.传统的Makefile的变量名是全大写的命名方式，但推荐使用大小写搭配的变量名，如：MakeFlags.这样可以避免和系统的变量冲突.

>+ **变量的基础**
1.变量在声明时需要给定初值
2.使用时需要在变量前加`"$"`,同时最好用小括号`()`或大括号`{}`将变量包括起来.

>+ **变量中的变量**
Makefile 中有两种方法来用变量来定义变量的值

> 1.使用`"="`.`"="`左侧是变量，右侧是变量的值.这种方式可以使用后面定义的值.
```shell
## a)这种方式的好处是可以把变量的真实值推到后面来定义
## b)不好指出在于, 当使用递归定义时会出错
##
foo = $(bar)
bar = $(ugh)
ugh = Huh?

all:
echo $(foo)

输出结果: Huh
```
> 2.使用`":="`操作符.这种方式前面的变量不能使用后面的变量
```shell
x := foo
y := $(x) bar
x := later

等价于:
y := foo bar
x := later
```

> 3.使用`"?="`操作符
```shell
## 如果 FOO 没有被定义过，那么变量 FOO 的值就是`"bar"`
## 如果 FOO 先前被定义过,则这条语句什么都不做

FOO ?= bar

等价于:
ifeq($(origin FOO), undefined)
FOO = bar
endif
```

>+ **变量值的替换**
```shell
## 方式1: 替换变量中的共有部分, 格式是 $(var: a=b)
## 其意思是: 把变量 "var" 中所有以 "a" 字串结尾的的 "a" 替换成 "b" 字串.

foo := a.o b.o c.o
bar := $(foo:.o=.c)

## 方式2: 静态模式定义
foo := a.o b.o c.o
bar := $(foo:%.o=%.c)
```

>+ **把变量的值再当变量**
```shell
x  = y
y  = z
a := $($(x))

理解: $(x)的值是"y", $($(x))就是$(y)
```

>+ **追加变量值**
使用`"+="`操作符给变量追加值

```shell
variable := value 
variable += more

等价于:

variable := value
variable := $(variable) more 
```

>+ **多行变量**
使用define关键字设置变量的值可以有换行
```shell
define two-lines
echo foo
echo $(bar)
endef
```


#### <font color=#FF00FF> 2.2 Makefile 中的函数 </font>
>+ **函数调用语法**
1.Makefile 中函数的调用跟变量相似,都是用`"$"`来标识.
2.格式: `$(<function> <arguments> ) ` 或 `${<function> <arguments>} `
3.函数中的参数可以使用变量，为了风格的统一，函数和变量的括号最好一样.
推荐使用: `$(subst a,b,$(x))`, 而不是 `$(subst a,b,${x})`


>+ **字符串处理函数**
```shell
$(subst <from>,<to>,<text>) 
## 名称: 字符串替换函数 subst
## 功能: 把字串<text>中的<from>字符串替换成<to>
## 返回: 函数返回被替换过后的字符串。

示例:
$(subst ee,EE,feet on the street)，
把"feet on the street"中的"ee"替换成"EE"，返回结果是"fEEt on the strEEt"
```

```shell
$(patsubst <pattern>,<replacement>,<text>) 
## 名称: 模式字符串替换函数——patsubst
## 功能: 查找<text>中的单词（单词以“空格”、“Tab”或“回车”“换行”分隔）是否符合模式
## <pattern>，如果匹配的话，则以<replacement>替换
## 返回: 函数返回被替换过后的字符串

示例:
$(patsubst %.c,%.o,x.c.c bar.c)
把字串“x.c.c bar.c”符合模式[%.c]的单词替换成[%.o]，返回结果是“x.c.o bar.o” 
```

```shell
$(strip <string>)
## 名称: 去空格函数——strip
## 功能: 去掉<string>字串中开头和结尾的空字符
## 返回: 返回被去掉空格的字符串值
```

```shell
$(findstring <find>,<in>) 
## 名称: 查找字符串函数——findstring
## 功能: 在字串<in>中查找<find>字串
## 返回: 如果找到，那么返回<find>，否则返回空字符串

示例:
$(findstring a,a b c)
$(findstring a,b c)
第一个函数返回“a”字符串，第二个返回“”字符串（空字符串）
```

```shell
$(filter <pattern...>,<text>) 
## 名称: 过滤函数——filter
## 功能: 以<pattern>模式过滤<text>字符串中的单词，保留符合模式<pattern>的单词
## 返回: 返回符合模式<pattern>的字串

示例:
sources := foo.c bar.c baz.s ugh.h 
(filter %.c %.s,$(sources))
$(filter %.c %.s,$(sources))返回的值是“foo.c bar.c baz.s”

```

```shell
$(filter-out <pattern...>,<text>) 
## 名称: 反过滤函数——filter-out
## 功能: 以<pattern>模式过滤<text>字符串中的单词，去除符合模式<pattern>的单词
## 返回: 返回不符合模式<pattern>的字串

示例:
objects=main1.o foo.o main2.o bar.o
mains=main1.o main2.o
$(filter-out $(mains),$(objects)) 返回值是“foo.o bar.o”
```

```shell
$(sort <list>) 
## 名称: 排序函数——sort
## 功能: 给字符串<list>中的单词排序(升序),sort函数会去掉<list>中相同的单词.
## 返回: 返回排序后的字符串

示例: $(sort foo bar lose)返回“bar foo lose” 
```

```shell
$(word <n>,<text>)
## 名称: 取单词函数——word
## 功能: 取字符串<text>中第<n>个单词.(从一开始)
## 返回: 返回字符串<text>中第<n>个单词.如果<n>比<text>中的单词数要大，则返回空字符串

示例：$(word 2, foo bar baz)返回值是“bar”.
```

```shell
$(wordlist <s>,<e>,<text>) 
## 名称: 取单词串函数——wordlist
## 功能: 从字符串<text>中取从<s>开始到<e>的单词串.<s>和<e>是一个数字.
## 返回: 返回字符串<text>中从<s>到<e>的单词字串.

示例：$(wordlist 2, 3, foo bar baz)返回值是“bar baz”.
```

```shell
$(words <text>) 
## 名称: 单词个数统计函数——words
## 功能: 统计<text>中字符串中的单词个数
## 返回: 返回<text>中的单词数

示例：$(words, foo bar baz)返回值是“3”
```

```shell
$(firstword <text>) 
## 名称: 首单词函数——firstword
## 功能: 取字符串<text>中的第一个单词
## 返回: 返回字符串<text>的第一个单词

示例：$(firstword foo bar)返回值是“foo”
```

>+ **文件名操作函数**
```shell
$(dir <names...>)
## 名称: 取目录函数——dir
## 功能: 从文件名序列<names>中取出目录部分
##       目录部分是指最后一个反斜杠（“/”）之前的部分,如果没有反斜杠，那么返回“./”.
## 返回: 返回文件名序列<names>的目录部分

示例： $(dir src/foo.c hacks)返回值是“src/ ./”.
```

```shell
$(notdir <names...>) 
## 名称: 取文件函数——notdir
## 功能: 从文件名序列<names>中取出非目录部分
## 返回: 返回文件名序列<names>的非目录部分

示例： $(notdir src/foo.c hacks)返回值是“foo.c hacks”.
```

```shell
$(suffix <names...>) 
## 名称: 取后缀函数——suffix
## 功能: 从文件名序列<names>中取出各个文件名的后缀
## 返回: 返回文件名序列<names>的后缀序列，如果文件没有后缀，则返回空字串

示例：$(suffix src/foo.c src-1.0/bar.c hacks)返回值是“.c .c”.
```

```shell
$(basename <names...>) 
## 名称: 取前缀函数——basename
## 功能: 从文件名序列<names>中取出各个文件名的前缀部分
## 返回: 返回文件名序列<names>的前缀序列，如果文件没有前缀，则返回空字串

示例：$(basename src/foo.c src-1.0/bar.c hacks)返回值是“src/foo src-1.0/bar h
acks”.
```

```shell
$(addsuffix <suffix>,<names...>)
## 名称: 加后缀函数——addsuffix
## 功能: 把后缀<suffix>加到<names>中的每个单词后面
## 返回: 返回加过后缀的文件名序列

示例：$(addsuffix .c,foo bar)返回值是“foo.c bar.c”.
```

```shell
$(addprefix <prefix>,<names...>) 
## 名称: 加前缀函数——addprefix
## 功能: 把前缀<prefix>加到<names>中的每个单词后面
## 返回: 返回加过前缀的文件名序列
示例：$(addprefix src/,foo bar)返回值是“src/foo src/bar”.
```

```shell
$(join <list1>,<list2>) 
## 名称: 连接函数——join
## 功能: 把<list2>中的单词对应地加到<list1>的单词后面
## 返回: 返回连接过后的字符串

示例：$(join aaa bbb , 111 222 333)返回值是“aaa111 bbb222 333”.
```

>+ **foreach 函数**
```shell
$(foreach <var>,<list>,<text>)
## 功能: 把参数<list>中的单词逐一取出放到参数<var>所指定的变量中，
##       然后再执行<text>所包含的表达式

示例:
names := a b c d
files := $(foreach n,$(names),$(n).o)
files 返回结果: a.o b.o c.o d.o
```

>+ **call 函数**
```shell
## call函数是唯一一个可以用来创建新的参数化的函数
$(call <expression>,<parm1>,<parm2>,<parm3>...) 
## 功能: 当 make执行这个函数时，<expression>参数中的变量，
##       如$(1)，$(2)，$(3)等，会被参数<parm1>，<parm2>，<parm3>依次取代

示例:
reverse = $(1) $(2)
foo = $(call reverse,a,b) 
foo的值就是"a b"
```

>+ **origin 函数**
```shell
$(origin <variable>)
## 功能: origin函数并不操作变量的值，他只是告诉你你的这个变量是哪里来的 

返回值: 
"undefined"   如果<variable>从来没有定义过，origin函数返回这个值"undefined".
"default"     如果<variable>是一个默认的定义，比如“CC”这个变量.
"environment" 如果<variable>是一个环境变量，并且当Makefile被执行时，“-e”参数没有被打开
"file"        如果<variable>这个变量被定义在Makefile中
...
```

>+ **shell 函数**
shell函数的功能与反引号 "\`" 的作用是相同的.
```shell
contents := $(shell cat foo)
files := $(shell echo *.c) 
## shell 函数也不像其它的函数. 顾名思义，它的参数应该就是操作系统Shell的命令.
## 该函数会新生成一个Shell程序来执行命令,如果Makefile有比较复杂的规则,会使运行性能变差
```

>+ **wildcard 函数**
```shell
$(wildcard PATTERN...)
## 功能: 被展开为已经存在的、使用空格分开的、匹配此模式的所有文件列表.

示例:
##sample Makefile
objects := $(patsubst %.c, %.o, $(wildcard *.c))
foo: $(objects)
	cc -o foo $(objects)
```


#### <font color=#FF00FF> 2.3 Makefile 中的条件判断 </font>
使用条件判断,可以让`make`根据运行时的不同情况选择不同的执行分支.

>+ **条件表达式的语法**
```shell
<conditional-directive>
<text-if-true>
endif 

以及:

<conditional-directive>
<text-if-true>
else
<text-if-false>
endif
```

>+ **条件关键字 -- ifeq**
```shell
## 比较参数"arg1"和"arg2"的值是否相同,相同则为真.
ifeq(<arg1>,<arg2>)
```

>+ **条件关键字 -- ifneq**
```shell
## 比较参数"arg1"和"arg2"的值是否相同,不同则为真.
ifneq(<arg1>,<arg2>)
```

>+ **条件关键字 -- ifdef**
```shell
## 如果变量<variable-name>的值非空，那到表达式为真.否则，表达式为假
ifdef <variable-name> 
```

>+ **条件关键字 -- ifndef**
```shell
## 如果变量<variable-name>的值为空，那到表达式为真.否则，表达式为假
ifndef <variable-name> 
```


#### <font color=#FF00FF> 2.4 make 的运行 </font>
>+ **指定Makefile**
1.GNU make找寻默认的Makefile的规则是在当前目录下依次找三个文件: `"GNUmakefile"`、`"makefile"`和`"Makefile“`.
2.按顺序找这三个文件，一旦找到，就开始读取这个文件并执行.
3.可以给`make`命令指定一个特殊名字的Makefile. 如`make -f myMakefile`.

>+ **指定目标**
1.一般来说，`make`的最终目标是Makefile中的第一个目标，它目标一般是由这个目标连带出来的.
2.使用指定终极目标的方法可以很方便地让我们编译我们的程序.
```shell
.PHONY: all
all: prog1 prog2 prog3 prog4 

## 上述Makefile中有四个需要编译的程序——“prog1”， “prog2”， “prog3”和 “prog4”,
## 我们可以使用`"make all"`命令来编译所有的目标 
```

>+ **Makefile 常用的伪目标**
```shell
"all"     : 该伪目标是所有目标的目标，其功能一般是编译所有的目标.         
"clean"   : 该伪目标功能是删除所有被make创建的文件.
"install" : 该伪目标功能是安装已编译好的程序，即把目标执行文件拷贝到指定的目标中去
"print"   : 该伪目标的功能是例出改变过的源文件
"tar"     : 该伪目标功能是把源程序打包备份.也就是一个tar文件.
"dist"    : 该伪目标功能是创建一个压缩文件，一般是把tar文件压成Z文件.或是gz文件.
"TAGS"    : 该伪目标功能是更新所有的目标，以备完整地重编译使用.
"check"和"test": 这两个伪目标一般用来测试Makefile的流程.
```

>+ **检查规则**
此功能对于调试 Makefile 很有用. 具体参数可以在Linux终端输入`"make -h"`查看.

>+ **make 的参数**
具体参数可以在Linux终端输入`"make -h"`查看.


#### <font color=#FF00FF> 2.5 Makefile 中的隐含规则 </font>
> 隐含规则,即在Makefile中的"隐含的"，早先约定了的，不需要我们再写出来的规则.

>+ **使用隐含规则**
1.使用隐含规则,最大的便利是可以利用`make`的自动推导功能.
2.如果我们为[.o]文件书写了自己的规则，那么make就不会自动推导并调用隐含规则，
  它会按照我们写好的规则忠实地执行
```shell
## 隐含规则举例
foo : foo.o bar.o
cc –o foo foo.o bar.o $(CFLAGS) $(LDFLAGS) 
## 该Makefile并没有写出如何生成 foo.o和bar.o这两个目标的规则和命令
## make 的隐含规则功能会自动为我们自动去推导这两个目标的依赖目标和生成命令

有了隐含规则,我们就没有必要写下一下的规则:
foo.o : foo.c
cc –c foo.c $(CFLAGS)
bar.o : bar.c
cc –c bar.c $(CFLAGS) 
```

>+ **常用的隐含规则**
以下仅列出在 C/C++ 下常用的隐含规则. 其余隐含规则请见 [Makefile 简易教程](https://www.cnblogs.com/owlman/p/5514724.html).
```shell
1.编译C程序的隐含规则
"<n>.o"的目标的依赖目标会自动推导为"<n>.c"
其生成命令: $(CC) –c $(CPPFLAGS) $(CFLAGS)
```
```shell
2.编译C++程序的隐含规则
"<n>.o" 的目标的依赖目标会自动推导为"<n>.cc"或是"<n>.C"
其生成命令: $(CXX) –c $(CPPFLAGS) $(CFLAGS)
```

```shell
3.链接Object文件的隐含规则
"<n>" 目标依赖于"<n>.o"，通过运行C的编译器来运行链接程序生成（一般是"ld"）
其生成命令：$(CC) $(LDFLAGS) <n>.o $(LOADLIBES)

示例:
x : y.o z.o 
并且 "x.c" "y.c" "z.c" 都存在时, 隐含规则将执行以下命令:
cc -c x.c -o x.o
cc -c y.c -o y.o
cc -c z.c -o z.o
cc x.o y.o z.o -o x
rm -f x.o
rm -f y.o
rm -f z.o 

如果没有一个源文件（如上例中的x.c）和你的目标名字（如上例中的x）相关联，
那么，你最好写出自己的生成规则，不然，隐含规则会报错.
```

>+ **隐含规则常用的变量**
在隐含规则中的命令中，基本上都是使用一些预先设置的变量.
以下仅列出在 C/C++ 下常用的变量. 其余变量请见 [Makefile 简易教程](https://www.cnblogs.com/owlman/p/5514724.html).

```shell
## 1.关于命令的变量
CC    C语言编译程序.默认命令是“cc”.
CXX   C++语言编译程序.默认命令是“g++”.
CPP   C程序的预处理器(输出是标准输出设备).默认命令是“$(CC) –E”.
```

```shell
## 2.关于命令参数的变量
## 下面的这些变量都是相关上面的命令的参数.若没有指明其默认值，则其默认值都是空
CFLAGS     C语言编译器参数
CXXFLAGS   C++语言编译器参数
CPPFLAGS   C预处理器参数
LDFLAGS    链接器参数(如："ld") 
```

>+ **GCC 编译选项**
```shell
1. -c   编译或汇编源文件，但不进行连接
gcc -c hello.c ===> hello.o  
gcc hello.o  
```
```shell
2. -o   指定输出文件file
gcc hello.c -o hello.o  或
gcc hello.c -o hello 
```
```shell
3. -g   指明编译程序在编译的输出中应产生调试信息
```
```shell
4. -D   允许从编译程序命令行定义宏符号
```
```shell
5. -I   大写的i, 可指定查找include文件的其他位置.
gcc -c -I/usr/local/include -I/opt/include hello.c 
```
```shell
6. -E 	预处理后即停止，不进行编译、汇编及连接
gcc -c -E hello.c >cpp.out 
```
```shell
7. -O   优化选项
-O 和-O1 指定1级优化
-O2      指定2级优化
-O3      指定3级优化
-O0      指定不优化
gcc -c O3 -O0 hello.c 
## 当出现多个优化时,以最后一个为准!!
```
```shell
8. -Wall  以最高级别使用GNU编译程序,专门用于显示警告用!!
```
```shell
9. -L    指定连接库的搜索目录,-l(小写L)指定连接库的名字.
```
```shell
10.-share 此选项将尽量使用动态库，所以生成文件比较小，但是需要系统由动态库
```
```shell
11. -static 　此选项将禁止使用动态库
```

>+ **定义模式规则**
>**1.模式规则介绍**
1.1 可以使用模式规则来定义一个隐含规则
1.2 一个模式规则就好像一个一般的规则，只是在规则中，目标的定义需要有"%"字符
1.3 "%"的意思是表示一个或多个任意字符
1.4 在依赖目标中同样可以使用"%"，只是依赖目标中的"%"的取值，取决于其目标
1.5 模式规则中，至少在规则的目标定义中要包含"%"，否则，就是一般的规则
1.6 一旦依赖目标中的"%"模式被确定，那么，make会被要求去匹配当前目录下所有的文
    件名，一旦找到，make就会规则下的命令
&emsp;
>**2.模式规则示例**
```shell
%.o : %.c
$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ 

其含义: 把所有的[.c]文件都编译成[.o]文件
其中，"$@"表示所有的目标的挨个值，"$<"表示了所有依赖目标的挨个值
```
>**3.自动化变量**
自动化变量，就是这种变量会把模式中所定义的一系列的文件自动地挨个取出，直至所有
的符合模式的文件都取完
```shell
$@  ##表示规则中的目标文件集.在模式规则中，若有多个目标，则"$@"就是匹配于目标中模式定义的集合

$%  ##仅当目标是函数库文件中，表示规则中的目标成员名

$<  ##依赖目标中的第一个目标名字.如果依赖目标是以模式（即"%"）定义的，那么
    ##"$<"将是符合模式的一系列的文件集.注意，其是一个一个取出来的.

$^  ##所有的依赖目标的集合.去除重复.

$?  ##所有比目标新的依赖目标的集合.以空格分隔.

$+  ##所有依赖目标的集合.只是它不去除重复的依赖目标.

$*  ##表示目标模式中"%"及其之前的部分.如果目标是"dir/a.foo.b"，并且目标的
    ##模式是"a.%.b"，那么，"$*"的值就是"dir /a.foo"

以上7个变量搭配 "D" 或 "F" 使用可以实现多种功能. 
```

>**4.模式的匹配**
1.定义好了的模式中，我们把"%"所匹配的内容叫做"茎".例如"%.c"所匹配的文件"test.c"中"test"就是"茎".
2.在目标和依赖目标中同时有"%"时，依赖目标的"茎"会传给目标，当做目标中的"茎".


>+ **老式风格的"后缀规则"**
1.后缀规则是一个比较老式的定义隐含规则的方法.
2.后缀规则有两种方式: '双后缀' 和 '单后缀'
```shell
## 1)双后缀规则定义了一对后缀: 目标文件的后缀和依赖目标(源文件)的后缀
".c.o" 相当于 "%o:%c"

## 2)单后缀规则只定义一个后缀: 源文件的后缀
".c" 相当于 "%:%.c"

.c.o:
$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

## 3)后缀规则不允许任何的依赖文件,如果有依赖文件的话,那就不是后缀规则,那些后缀统统被认为是文件名
.c.o: foo.h
$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 
##上面的例子是说,文件".c.o"依赖于文件"foo.h"
##正确写法应该是:
%.o: %.c foo.h
$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 
```


### <font color=#DC143C> 三. Makefile 实例 </font>
#### <font color=#FF00FF> 3.1 从一个简单的例子认识 Makefile </font>
>+ **例子: 主程序代码(main.C), 源代码(getop.C,stack.C,getch.C), 头文件(calc.h)**  
`编译命令: gcc -o calc main.C getch.C getop.C stack.C`
> *每当重新编译时,都需要手动输入上述命令*

>+ **一个最简单的 Makefile** 
第一部分: 目标 calc. 在冒号之前,为所要编译的目标程序.
第二部分: 依赖关系表. 冒号后的部分(main.C getch.C getop.C stack.C)
第三部分: 编译命令. gcc -o calc main.C getch.C getop.C stack.C
>+ <u>依赖关系中的文件,只要有一个发生了变化,就会触发编译命令.</u>
>+ <u>语法规定 Makefile 中的任何命令之前都必须要有一个tab缩进.</u>
```Makefile
calc: main.C getch.C getop.C stack.C
	gcc -o calc main.C getch.C getop.C stack.C
```

>+ **Makefile 改进 -- 效率提高**
> 将编译器、目标文件、源文件定义为宏, 即字符串替换.
```Makefile
cc    = gcc
prom  = calc
source = main.C getch.C getop.C stack.C

$(prom): $(source)
	$(cc) -o $(prom) $(source)
```

>+ **Makefile 改进 -- 添加头文件依赖**
```Makefile
cc   = gcc
prom = calc
deps = calc.h
obj  = main.o getch.o getop.o stack.o

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)

main.o: main.C $(deps)
	$(cc) -c main.C

getch.o: getch.C $(deps)
	$(cc) -c getch.C

getop.o: getop.C $(deps)
	$(cc) -c getop.C

stack.o: stack.C $(deps)
	$(cc) -c stack.C
```

>+ **Makefile 改进 -- 效率提高**
> 使用特殊的宏命令,使 Makefile 更加简洁
> `%.o: %.C $(deps)` 表示所有的.o 目标文件都依赖于与它同名的.C文件,以及deps中的头文件
> `$<` 代表依赖关系中的第一项. 本例子中是 `%.C`
> `$^` 代表整个依赖关系表
> `$@` 代表当前语句的目标,即 `%.o`
```Makefile
cc   = gcc
prom = calc
deps = calc.h
obj  = main.o getch.o getop.o stack.o

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)

%.o: %.C $(deps)
	$(cc) -c $< -o $@
```

>+ **Makefile 改进 -- 添加伪目标与函数规则**
> 例如,添加自动清理编译结果的功能,即可定义一个带伪目标的规则
```Makefile
cc   = gcc
prom = calc
deps = calc.h
obj  = main.o getch.o getop.o stack.o

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)

%.o: %.C $(deps)
	$(cc) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)
```

>+ **Makefile 改进 -- 自动添加依赖文件**
> 为了使得 Makefile 可以自动添加依赖文件, 同时使得 Makefile 更加简洁
> `src:.%.C=%.o` 字符替换函数,将`src`中所有的`.C`字符串替换成`.o`
```Makefile
cc   = gcc
prom = calc
deps = $(shell find ./ -name "*.h")
src  = $(shell find ./ -name "*.C")
obj  = $(src:.%.C=%.o)

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)

%.o: %.C $(deps)
	$(cc) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)
```


#### <font color=#FF00FF> 3.2 如何在 Makefile 里面链接 ROOT </font>

>+ [Linking ROOT Libraries to a MakeFile install](https://root-forum.cern.ch/t/linking-root-libraries-to-a-makefile-install/12233)

```C++
// Makefile
CC         = g++
CFLAGS     = -c -g -Wall `root-config --cflags`
LDFLAGS    = `root-config --glibs`
SOURCES    = test.C
OBJECTS    = $(SOURCES:.C=.o)
EXECUTABLE = test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 
//## 注意: $(CC) $(LDFLAGS) $(OBJECTS) -o $@ 可能会报以下错误:
//##  Undefined reference to `TVersionCheck::TVersionCheck(int) 

.C.o:
	$(CC) $(CFLAGS) $< -o $@  

clean:
	rm ./*~ ./*.o ./test

```


