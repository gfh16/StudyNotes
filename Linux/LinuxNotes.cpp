
================================================================================
                               基础篇：常用命令
================================================================================


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







================================================================================
                                  提高篇
================================================================================

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
2. Linux下标准的C++程序项目一般把源文件、头文件、目标文件、可执行文件放在不同文件件下：

  bin       可执行文件
  include   头文件
  obj       目标文件
  src       源文件