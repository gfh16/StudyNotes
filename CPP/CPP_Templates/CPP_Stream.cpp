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

   (5) 判断文件打开状态


4. stringstream

5. sstream

*/


/*
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
     (1) cin.getline(char* s, streamsize n); // 从istream中读取至多n个字符，包含结束标记符
     (2) cin.getline(char* s, streamsize n, char deline); // 遇到delim或者字数达到了一定的限制，读取就会终止； deline是自定义的终止符


     ********************************
     cin.get() 与 cin.getline() 与 cin
        1. get(char &) 提供不跳过空白的单字符输入功能
        2. get(char*, int, char) 和 getline(char*, int, char)在默认情况下读取整行，不会跳过空白
        3. cin >>;  遇到空格即输出结束
        4. geline() 与 get()的区别：getline()丢弃读取到的分隔符，而get()不会
     ********************************

     ************************************
     cin.getline()与 string类的getline()
        1. cin.getline(char* s， streamsize n)；    //在头文件<istream>中

        2. getline(istream& is, string& str, char delim);  // is 表示一个输入流，如 cin
           ==> getline在while语句中作为判定条件：
           while(getline(cin,name)){};
           while(getline(cin,name,'#')){};
     ************************************

     *********************************************
      输入流作为判断条件使用！
     **********************************************

 3. read()
    (1)作用: 将文件中的数据按照一定的长度读取读取出来并且存放在新的数组中
    (2)用法: read(char* s, streamsize n);

 4. put()
    (1)作用：用于输出字符
    (2)用法：put(ch)
    (3)实例：cout.put(ch); outfile.put(ch)

 5. write()
    (1)作用: Copies a block of data, without checking its contents
    (2)用法：write(const char* s, streamsize n)

 6. precision()
    (1)用法: cout.precision(int n)

 7. good()
    (1)作用: 用来判断当前流的状态是否正常
    (2)用法: bool iso::good() const
            {
              return rdstate() == goodbit;
            }

    (3)实例:while(cin.good()){}

 8. eof()
    (1)作用: 判断文件是否为空，或者判断是否读到文件结尾
    (2)用法: while(file.eof()){ file>> x }
    (3)说明: fstream流的eof()函数会多读一行.可以用peek()函数来避免这个问题
    (4)peek(): while(file.peek()!=EOF){file>>x}

 9. fail()
    (1)作用: fail()用来判断一个流是否"坏掉"了
    (2)用法: cin.fail()
    (3)实例:

 10. !
    (1)作用: Evaluate stream (not)
    (2)用法: if(!filein){ cout<< "Error opening filein"<<endl; }
    (3)实例:

 11. clear()
    (1)作用:
    (2)用法:
    (3)实例:

 12. ignore()
     (1)作用：跳过(忽略)指定字符     // cin要求用"回车"来提交数据
     (2)用法：cin.ignore(int n=1, delim=EOF);
     (3)实例：
        {
          int n;
          cin.ignore(5,'A');
          cin>>n;
          cout<<n;    //输入：abcde34   输出：34
          return 0;   //输入: abA34    输出：34
        }

 13. open()
    (1)作用: 用于打开和创建文件
    (2)用法: ifstream ifs;
            ifs.open("test.txt", mode)
    (3)文件打开模式：
        ios::app         追加模式，所有写入都追加到文件末尾。
        ios::ate         文件打开后定位到文件末尾
        ios::in          打开文件用于读取
        ios::out         打开文件用于写入
        ios::trunc       如果该问价你已经存在，其内容将在打开文件之前被截断，即把文件长度设为0


 14. is_open()
    (1)作用: check if a file is open
    (2)用法:  ifstream ifs("test.txt");
             if(ifs.is_open()){}


 15. close()
    (1)作用: 关闭文件
    (2)用法: ifstream ifs;
            ifs.open("test.txt");
            ...
            ifs.close();


 16. setprecision(int n)
    (1)用法: cout<< setprecision(5) << num <<endl;

 17. setw(int n)
    (1)作用: 用于设置字段宽度为n

 18. fixed
    (1)作用: 以一般的形式输出浮点型
    (2)用法: cout.precision(5);
            cout<< fixed;

 19. scientific
    (1)作用: Use scientific floating-point notation
    (2)用法: cout.precision(5);
            cout<< scientific;

 20. left
    (1)作用: Adjust output to the left

 21. right
    (1)作用: Adjust output to the right


*/

///////////////////////////////////
/// read a file into memory
#if 0

#include<iostream>
#include<fstream>
using namespace std;

int main()
{
  ifstream FileIn("test.txt",ios::app);
  if(FileIn)
  {
    //get length of FileIn
    FileIn.seekg(0, FileIn.end);    //追溯到流的尾部
    int length = FileIn.tellg();    //获取流的长度
    FileIn.seekg(0, FileIn.beg);    //回到流的头部

    char* buffer = new char[length]; //用来暂存内容的数组

    cout<<"Reading "<<length<<" characters..."<<endl;
    // read data as a block
    FileIn.read(buffer, length);    //用来暂存内容的数组

    if(FileIn)
    {
      cout<<"All characters read successfully."<<endl;
    }
    else
    {
      cout<<"error: only"<<FileIn.gcount()<<"could be read"<<endl;
    }

    FileIn.close();

    delete[] buffer;
  }

  return 0;
}

#endif
////////////////////////////////////////////////////////////////////////////////



#if 1

#include<iostream>
#include<fstream>
using namespace std;

int main()
{
  ifstream infile("test.txt");
  ofstream outfile("new.txt",ofstream::binary);

  //get size of file
  infile.seekg(0,infile.end);
  long size = infile.tellg();
  infile.seekg(0);

  // allocate memory for file content
  char* buffer = new char[size];

  //read content of infile
  infile.read(buffer, size);

  //write to outfile
  outfile.write(buffer, size);

  // release dynamically-allocated memory
  delete[] buffer;

  outfile.close();
  infile.close();
  return 0;

}

#endif
