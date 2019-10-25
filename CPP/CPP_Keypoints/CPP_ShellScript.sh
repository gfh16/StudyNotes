/*******************************************************************************
               Linux Shell 教程



********************************************************************************/

1. Shell简单介绍
   (1)Shell是一个用C语言编写的程序.它既是一种命令语言，又是一种程序设计语言
   (2)Shell脚本，是一种为shell编写的脚本程序. 我们说的shell通常是shell脚本
   (3)脚本语言是什么：
      <1> 脚本语言是指不需要编译成二进制文件，从而直接运行的语言
      <2> 脚本实际上就是程序，它是批处理文件的延伸，是一种纯文本保存的程序
      <3> 脚本其实就是短小的、用来让计算机自动化完成一系列工作的程序，这类程序可以用文本编辑器
          修改，不需要编译，通常是解释运行的。

   (3)Shell环境
      <1> Bourne Shell (/usr/bin/sh 或 /bin/sh)
      <2> Bourne Again Shell (/bin/bash)
      <3> C Shell(/usr/bin/csh)
      ...

2. shell脚本实例
   (1) 格式：
       #!/bin/bash
      echo "Hello World !"

   (2) shell脚本格式说明
       <1> #! 是一个约定标记，它告诉系统这个脚本使用的是哪一种 Shell
           echo 命令用于向窗口输出文本
       <2> 运行shell脚本的两种方法
           《1》作为可执行文件
                chmod +x ./test.sh   //使脚本具有执行权限
                ./test.sh            // 执行脚本

           《2》作为解释器参数 -- 不需要在第一行指定解释器信息
              /bin/sh test.sh

       <3> UBuntu(Linux)下 source, sh, bash, ./执行脚本的区别
           source Filename / . Filenmae     //Filename文件可以无"执行权限"
           sh Filename/ bash Filename       //Filename文件可以无"执行权限"
           ./Filename                       //Filename文件需要有"执行权限"

3. shell变量
   (1) 定义变量：定义变量时，变量名不加美元符号
         your_name="runoob.com"
         **** 变量名与等号之间不能有空格

   (2) 使用变量时，要在变量前加美元符号
         your_name="guanfh"
         echo ${yourname}

   (3) 只读变量
        <1> 使用 readonly 命令可以将变量定义为只读
        <2> 语法：readonly Variable_name

   (4) 删除变量
        <1> 使用unset命令删除变量
        <2> 语法：unset Variable_name

   (5) 变量类型
       <1> 局部变量
       <2> 环境变量
       <3> shell变量

   (6) Shell字符串
       **** 字符串是shell编程中最常用最有用的数据类型. 字符串可以用单引号,双引号,也可以不用引号
       <1> 单引号: 任何字符串都会原样输出,单引号字符串内的变量是无效的
       <2> 双引号: 双引号可以有变量，双引号可以出现转义字符
       <3> 获取字符串长度:
           string="abcdefg"
           echo ${#string}    //输出7

       <4> 提取子字符串
           string="runoob is a great site"
           echo ${string:1:4}  //输出 unoo

       <5> 查找子字符串


   (7) Shell注释
       <1> 以"#"开头的行就是注释,会被解释器忽略
       <2> 多行注释
           :<<EOF
           注释内容
           注释内容
           ...
           EOF

3. Shell传递参数
   <1> 脚本内获取参数的格式：$n   n代表一个数字
   <2> 处理参数的特殊字符
       $#    传递到脚本的参数个数
       $*    以一个单字符串显示所有向脚本传递额参数
       $@    与 $* 相同，但是使用时加引号，并在引号中返回每个参数

      #############################################################
      #   $* 与 $@ 的区别：                                         #
      # 相同点: 都是引用所有参数                                      #
      # 不同点：只有在双引号中体现出来                                 #
      #############################################################

4. Shell数组 --  bash 仅支持一维数组

   <1> 定义数组: 用括号表示数组,数组元素用"空格"符号隔开
       array_name=(val0 val1 val2 val3)

   <2> 读取数组:
       valuen=${array_name[index]}

   <3> 获取数组所有元素
       echo ${array_name[@]}   //读取数组所有元素
       echo ${array_name[*]}

   <4> 获取数组的长度
       echo ${#array_name[*]}
       echo ${#array_name[@]}


5. Shell运算符
   <1> 算术运算符
   <2> 关系运算符
   <3> 布尔运算符
   <4> 字符串运算符
   <5> 文件测试运算符

   #############################################################################
   # 1. 两个数的算术运算，使用的是反引号，而不是单引号'
   # 2. 表达式和运算符之间要有空格
   # 3. 条件表达式要放在方括号之间，并且要有空格 [ $a == $b ]
   # 4. 乘号(*)前必须加反斜杠(\)才能实现乘法
   #############################################################################

6. echo 命令
   <1> 显示普通字符串:
       echo "It is a test"

   <2> 显示转义字符
       echo "\"It is a test\""

   <3> 显示变量
       read命令从标准输入中读取一行，并把输入行的每个字段的值指定个shell变量

   <4> 显示换行
       echo -e "OK! \n"  # -e 开启转义， \n 换行

   <5> 显示不换行
       echo -e "OK! \c"  # -e 开启转义， \c 不换行

   <6> 显示结果定向至文件
       echo "It is a test" > myfile

   <7> 原样输出字符串，不进行转义或取变量(用单引号)
       echo '$name\"'

   <8> 显示命令执行结果
       echo `date`

  ##############################################################################
    source 命令：
    1. source 命令是bash shell的内置命令，与.命令等价
    2. 作用：在当前bash环境下读取并执行Filename中的命令.source命令通常用于重新执行刚修改的
            的初始化文件，使之立即生效，而不必注销并重新登录

    export命令：
    1. 设置或显示环境变量
    2. 用export设置环境变量:
       export PATH=$PATH:/opt/au1200_rm/build_tools/bin
  ##############################################################################

7. printf 命令
   (1) 使用 printf的脚本比使用echo移植性好. printf不会像echo自动添加换行符，可手动添加\n
   (2) 语法:
       printf format-string [arguments...]
       format-string: 格式控制字符串
       arguments:参数列表

   (3) printf的格式替代符
       %s    输出整个字符串
       %c    输出一个字符
       %nd   输出含有n个数字的整数，不写n则输出完整的整数
       %m.nf 输出浮点宽度为m,小数点后保留n位的小数
       %-    表示输出左对齐

8. test 命令
   *** shell中的test命令用于检查某个条件是否成立，可进行数值、字符、文件三个方面的测试
   (1) 数值测试:

   (2) 字符串测试:

   (3) 文件测试:


9. 流程控制
   (1) if
       语法：
       if condition
       then
         command1
         command2
         ...
         commandN
       fi

   (2) if else
       语法：
       if condition
       then
         command1
         command2
         ...
         commandN
       else
         command
       fi

   (3) if else-if else
       语法：
       if condition
       then
         command1
       else if condition2
       then
         command2
       else
         commandN
       fi

   (4) for循环
       语法：
       for var in item1 item2...itemN
       do
         command1
         command2
         ...
         commandN
       done

   (5) while语句
       <1> 语法：
           while condition
           do
             command
           done

       <2> 无限循环
           while   ### 或者  while true
           do
             command
           done


   (6) until循环
       <1> until循环执行一系列命令直至条件为true时停止
       <2> 语法：
           until condition
           do
             command
           done
       <3> 一般while循环优于until循环，但在某些时候,until循环更加有用


   (7) case
       <1> case语句为多选择语句. 可以用case语句匹配一个值与一个模式，如果匹配成功，执行相匹配的
           的命令.
       <2> 语法：

   (8) 跳出循环
       <1> break: break命令允许跳出所有循环(终止执行后面的所有循环)
       <2> continue: 仅仅跳出当前循环

10. 函数
    <1> 函数的定义
        [function] funname[()]
        {
          action;
          [return int;]
        }
    ** 可以带function fun()定义, 也可以直接fun()定义，不带任何参数
    ** 参数返回，可以显示加: return返回，如果不加，将以最后一条命令运行结果，作为返回值
    ** 函数返回值在调用该函数后通过 $? 来获得

    <2> 函数参数
        《1》在函数体内部，通过$n的形式来获取参数的值

    <3> 处理参数的特殊字符
        $#     传递到脚本的参数个数
        $*     以一个单字符串显示所有向脚本传递额参数
        $!     后台运行的最后一个进程的ID号
        $?     显示最后命令的退出状态. 0表示没有错误，其他任何值表明有错误

11. 输入输出重定向
    <1> 重定向命令列表
        命令                   说明
        command>file         将输出重定向到file
        command<file         将输入重定向到file
        command>>file        将输出以追加的形式重定向到file
        n>file               将文件描述符为n的文件重定向到file
        n>>file              将文件描述符为n的文件以追加的方式重定向到file
        n>&m                  将输出文件m和n合并
        n<&m                  将输入文件m和n合并
        <<tag                  将开始标记tag和结束标记tag之间的内容作为输入

    <2> /dev/null 文件
        如果希望执行某个命令，但又不希望在屏幕上显示输出结果，则可将速出重定向到/dev/null
        command > /dev/null

12. 文件包含
    (1) 文件包含的语法：
        . filename  ## 注意点好(.)和文件名中间有一空格
        source filename
