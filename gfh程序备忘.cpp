//================================================================================
//*
//*               Ububtu/Linux 常用命令以及用法备忘
//*
//===============================================================================

         /****************************************************
                          Linux基础篇：常用命令
         ****************************************************/
--------------------------------------------------------------------------------
1. 在科研中可能会遇到的小问题
  (1) $ find . -name ex33.C    //查找当前目录下名字为ex33.C的文件
  (2) $ grep -srn "void" .   //查找当前目录下所有包含“void”字符的文件名称，该字符出现的行号（n）和该行的内容
  (3) $ wc -l ex33.C   //计算ex33.C文件有多少行
  (4) $ date   //输出系统当前的日期、时间、星期等  （date +%B 截取当前时间中的月份）
  (5) $ date --help //查看date命令的用法


2. Linux 终端的常用命令
  pwd          //显示当前目录(print working dir)
  passwd       //修改当前用户的密码
  mkdir dfoo       //新建文件夹 dfoo
  rm [-rf] foo     //删除文件foo (-rf表示强制删除)
  rmdir dfoo       //删除文件夹dfoo
  cp foo bar      //将foo复制到bar下
  mv foo bar      //更改文件foo的名称为bar
  history        //列出最近使用过的指令
  ./foo          //在当前目录运行可执行文件foo
  ps           //显示正在运行的进程
  locate foo    //在所有目录中寻找有文件名foo的路径
  find . -name file1  //在当前目录下寻找文件名为file1的路径
  sed -e "s/str1/str2/g" foo > bar
      //将文件foo中字符串“str1”改为“str2”并将修改后的文件写到新文件bar上,foo保持不变
  diff  file1 file2  //比较file1与file2的不同
  tar -zcvf 1.tgz file1 file2   //压缩file1和file2为1.tgz
  tar -zxvf  1.tgz   //解压缩1.tgz
  gcc test.C -o try1  //用C编译器编译test.C,生成可执行文件try1
  g++ test.cpp -o try2   //用C++B编译器编译程序
  date     //显示系统当前的时间
  echo “Welcome to Linux World!”   //屏幕显示指定字符串
  file file1   //显示文件file1的属性

3. 一些常用的命令
 (1) g++ -o HelloWorld HelloWorld.cc // g++ 调用编译器gcc，HelloWorld 输出的文件名，HelloWorld.cc 源代码
    //或者： g++ HelloWorld.cc -o HelloWorld
 (2) 运行： 在终端输入：./HelloWorld
 (3) (1)中的命令，事实上是下面两条命令的组合：
     g++ -c HelloWorld.cc  //编译器(-c)先产生HelloEorld.o目标文件
     g++ -o HelloWorld HelloWorld.o

--------------------------------------------------------------------------------




           /****************************************************
                      Linux 提高篇: 基本概念与常用用法
           ****************************************************/
--------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
1. the usage of echo, source, export



//------------------------------------------------------------------------------
2. make && cmake




//------------------------------------------------------------------------------
3. display settings for ubunutu subsystem on win10

   // configure bash to use the local X server
   $ echo "export DISPLAY= localhost:0.0" >> ~./bashrc
   $ . ~/.bashrc   //to have the configuration take effect


//______________________________________________________________________________
4. 脚本（script）

  （1） 脚本： 用于实现某种目的的命令集合。这些命令集合放在一个文件夹中，有shell来解析执行
  （2） 执行脚本：./tesh.sh
  （3） 运行前确保用户对test.sh有可执行权限：chmod u+x test.sh
  （4） 脚本的格式：
      #！/bin/bash
      # This is a simple test shell script

      echo "Hello World!"
      ls /home/sea/B5
      date
      echo $PWD

     说明: (1) 标准的脚本都以“#！”开头，后面跟随bash/tcsh（或其他脚本程序）的路径
               // 查询bash的路径的路径：which bash
           (2) 注释行以“#”开头（第一行的#！除外）
           (3) 需要执行的指令，一般每行一个指令

//______________________________________________________________________________
5. Linux下标准的C++程序项目一般把源文件、头文件、目标文件、可执行文件放在不同文件件下：

  bin       可执行文件
  include   头文件
  obj       目标文件
  src       源文件


-------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////










////////////////////////////////////////////////////////////////////////////////
//==============================================================================
//*
//*                             C++ 程序语言备忘
//*
//==============================================================================

///////// 学习内容来自 ‘菜鸟教程’ www.runoob.com



               /****************************************
                             C++ 基础教程
               *****************************************/
--------------------------------------------------------------------------------
1. C++ 简介
* 标准的C++的组成：
  * 核心语言，提供了所有的构件块，包括变量、常亮，数据类型等
  * C++ 标准库，提供大量的函数，用于操作文件、字符串等
  * 标准模板库(STL),提供了大量的方法，用于操作数据结构等


2. C++ 环境设置
* 文本编辑
  * 文本编辑器用于创建源文件，源文件包括程序代码

* C++编译器
  * 源文件需要“编译”之后，转化为机器语言(可执行程序),这样CPU才能按给定指令执行程序
    ----------------------------------------------
     文本编辑器 -> 源程序 -> C++编译器 -> 可执行程序
    ----------------------------------------------

* 常用的C++编译器
 GNU
 gcc
 g++
 GCC



--------------------------------------------------------------------------------


              /****************************************
                             C++ 面向对象
              *****************************************/
--------------------------------------------------------------------------------





--------------------------------------------------------------------------------









              /****************************************
                           程序中遇到的问题解答
              *****************************************/

Q1. 在使用RIBLLDAQ的时候，make的时候，出现"未定义的引用"问题，例如：
  
   对‘TString::TString(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)’未定义的引用

   问题的来源：C++ 版本库不兼容的问题。从GCC5 版本开始，就默认启用C++11. 但是由于C++11相对于C++03很多实现的数据结构都发生了改变，两者
             不能完全混用
            
   解决办法：
   0. 如果是在GCC5下使用了非GCC5编译的库，编译时关闭C++11特性
   1. 在makefile里面增加下面的内容：
      CXXFLAGS= -D_GLIBCXX_USE_CXX11_ABI=0
      将他应用于每一个编译过程！！！
      DAQPC:DIC $(OBJS) VMEDAQPC.o
	$(CPP) -o $@ VMEDAQPC.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs)

      ControlPC:DIC $(OBJS) ControlPC.o
	$(CPP) -o ControlPC ControlPC.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs) $(CXXFLAGS)

      OnlinePC:DIC $(OBJS) OnlinePC.o
	$(CPP) -o $@ OnlinePC.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs) $(CXXFLAGS)

      MonOnline:DIC $(OBJS) MonOnline.o
	$(CPP) -o $@ MonOnline.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs) $(CXXFLAGS)

      Raw2ROOT:DIC $(OBJS) Raw2ROOT.o
	$(CPP) -o $@ Raw2ROOT.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs) $(CXXFLAGS)

      ReadRootFile2D:DIC $(OBJS) ReadRootFile2D.o
	$(CPP) -o $@ ReadRootFile2D.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs)  $(CXXFLAGS)


      %.o: %.cpp
	$(CPP) -c $(CFLAG) $(CRFLAG) $(CXXFLAGS) -o $@ $<
      

	      
Q2. 在编译DEEFIT的时候，遇到了问题：
 【1】ROOT版本问题：在ROOT6版本下，主要问题在于：
      deedict.cxx:163:65: error: ‘DefineBehavior’ was not declared in this scope
      
 【2】在ROOT6中，‘DefineBehavior’等函数定义在命名空间ROOT::Internal中
 
 【3】解决办法：在 deedict.cxx 文件中，加入命名空间：
      using namesapce ROOT::Internal;

 【4】至此，还可能出现 "未定义的引用" 问题， 解决方法如 Q1 所述。 
 
 【5】编译成功！





