/*******************************************************************************
                   C++ 基本的输入输出
          1. <iostream>    定义了cin、cout、cerr和clog对象
          2. <iomanip>     该文件通过参数化的流操纵器, 来声明对执行标准化的I/O有用的服务
          3. <fstream>     该文件为用户控制的文件处理声明服务。
          4. <stringstream>
          5. <sstream>

*******************************************************************************/
/*
1. iostream
   (1) istream 成员函数
       <1> get()               // 从流中提取字符，作为未格式化的输入
       <2> getline()           // 从流中提取字符直到遇到分隔符
           getline(string)
       <3> read                // 提取若干个字符并存入数组

   (2) ostream 成员函数
       <1> put()               // 将字符c插入流中
       <2> write()             // 将s指向的数组的前n个字符插入到流中
       <3> precision()         // 获取/设置浮点小数精度

   (3) iostream
       <1> good()              // 检查stream的状态是否正常
       <2> eof()               // 检查是否设置了eofbit, 即是否正常读到文件结尾
       <3> fail()              // 检查是否设置了failbit 或 badbit， 即非正常结束
       <4> !                   // 评估流打开状态，如果返回true即设置了failbit 或 badbit
       <5> clear()             // 清除 flags
       <6> ignore()             // 提取特定字符并丢弃

   (4) 基本操纵程序 (manipulators)
       <1> fixed()
       <2> scientific()
       <3> left()
       <4> right()


2. iomanip
  (1) setprecision(int n)
  (2) setw(int n)


3. fstream
   (1) Public member functions
       <1> open()
       <2> is_open()
       <3> close()

   (2) istream
       同上

   (3) ostream
       同上

   (4) iostream
       同上


4. stringstream

5. sstream

*/



////////////////////////////////////////////////////////////////////////////////
                                   常用成员函数讲解

  1. cin.get()
     (1) 用来接收字符
         char ch;
         ch = cin.get(); // cin.get(ch);
         cout<< ch << endl; //   输入：abcdef    输出：a

      (2) 用来接收一行字符串，可以接收空格
          char a[20];
          cin.get(a,20);
          cout<< a << endl;

  2. cin.getline()
     (1)




     ********************************
     cin.get() 与 cin.getline()的区别
     ********************************

     ************************************
     cin.getline()与 string类的getline()
     ************************************
