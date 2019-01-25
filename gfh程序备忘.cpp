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

               /****************************************
                      基础篇： C++语言中的基本概念
               *****************************************/
--------------------------------------------------------------------------------



--------------------------------------------------------------------------------



             /*******************************************
                    使用篇： C++一些有用的用法
             ********************************************/
-------------------------------------------------------------------------------
1. C++ 语言中和提取数据文件中的某行/某列？如何将某几行/列合并称一个文件？
   提示： awk 与 paste de 用法

   用法实例：
   #!/bin/bash
   # Extract assigned rows of files

   awk '{print $3}' SSD1_L1_E_X2.dat > newfile2.dat
   awk '{print $3}' SSD1_L1_E_X4.dat > newfile4.dat
   awk '{print $3}' SSD1_L1_E_X5.dat > newfile5.dat
   awk '{print $3}' SSD1_L1_E_X10.dat > newfile10.dat
   awk '{print $3}' SSD1_L1_E_X20.dat > newfile20.dat

   #!/bin/bash
   # Combine saveral files into one, by rows
   paste  newfile2.dat newfile4.dat newfile5.dat  newfile10.dat newfile20.dat > result5.dat

//------------------------------------------------------------------------------
2. 如何读取一个数据文件？
   提示: 文件流的 iofstream 的使用

   用法举例：
   //______________________________________________________________________________
   ////////////////////////////////////////////////////////////////////////////////
   // Read data from a file
   ===========
   ifstream
   ===========
   ifstream infile("input.txt");
   while(1)
   {
         infile>>var1>>var2>>var3>>var4>>var5>>var6;  //var1...可以是任何类型变量
         if (!infile.good() || infile.eof())  break;
         ...
         ...
   }
   infile.Close();

   /*******************************************************************************
    * Notes: It is an infinite loop which will run till a break statement
    * is issued explicitly. 只要是非零的整数（正数、负数皆可），true, 所得结果都和 1 相同；
    * 0 则不执行循环
    *******************************************************************************/
   //______________________________________________________________________________

   //______________________________________________________________________________
   =====================================================
   void open(const char *filename, ios::openmode mode)
   =====================================================
   ifstream infile;
   infile.open("input.txt",ios::app);

   /****************************************************************************
    * ios::app  追加模式。所有写入都追加到文件的末尾。
    ****************************************************************************/

3. 如何使用 Vector 来存储数据？
   提示：vector 的使用

   用法举例：

   //_____________________________________________________________________________
   =====================
   Date: October 11 2018
   =====================
   case 1: when I try to store data in the following vector, crash happens:
   ================================================================================
   /*******************************************************************************
    *  Sulotion:
    *     _________________________________________________________________________
    *         LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    *         if(LineRead.empty()) continue;
    *         if(LineRead.find_first_not_of(' ')==std::string::npos) continue;
    *      ________________________________________________________________________
    *  ============================================================================
    *  Reason: I retrive the data with if(LineRead.find('*')==0) continue, it does
    *  not work when ind('*') is unequal to 0. Actully I read the first comment line,
    *  which is outside the vector, giving a random number. If another unused vector
    *  is definited, this random numbers will be stored in this vector.
    ********************************************************************************/

   {
     std::vector<double> CsIV_He3[12][4];
     std::vector<double> CsIE_He3[12][4];
   //  std::vector<double> ZA_He3[12][4];  // when I comment this third definition, the program break !!!

     while(!FileIn_He3.eof())
     {
       std::string LineRead;
       std::getline(FileIn_He3, LineRead);
       if(LineRead.empty()) continue;
       if(LineRead.find('*')==0) continue;

       std::istringstream LineStream(LineRead);

       int telnum;
       int csinum;
       double V;
       double errV;
       double E;
       double errE;

       LineStream >> telnum >> csinum >> V >> errV >> E >> errE;
       cout<< telnum << setw(10)<< csinum << setw(20) << V <<endl;

       CsIV_He3[telnum][csinum].push_back(V);
       CsIE_He3[telnum][csinum].push_back(E);
     }
   }
   //________________________________________________________________________



--------------------------------------------------------------------------------
