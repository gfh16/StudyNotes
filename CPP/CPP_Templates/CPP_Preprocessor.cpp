/*****************************************************************
               C++ 预处理语句
   1. 预处理语句以 # 作为起始标记， 其后紧跟预处理命令关键字， 之后是空格，空格之后是预处理命令的内容
   2.
******************************************************************/

////////////////////////////////////////////////////////////////////////////////
////    1. #define
////  用来生成宏定义常量
///   一般格式: #define macro-name replacement-text
///   在宏定义值之后陆续出现的的所有宏都会在程序编译之前被替换成 valaue
#if 0

#include<iostream>
using namespace std;

#define PI 3.14159

int main()
{
  cout<<"Value of PI: "<< PI << endl;

  return 0;
}

#endif
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////     2. 参数宏、宏函数
#if 0

#include<iostream>
using namespace std;

#define MIN(a,b) (a<b ? a:b)

int main()
{
  int i, j;
  i = 100;
  j= 50;

  cout<<"较小的值为："<< MIN(i,j) <<endl;

  return 0;
}
#endif
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////       3. 条件编译
///   与 if 选择很像

#if 0

#include<iostream>
using namespace std;

#define VALUE    // 这里 VALUE被定义，不管取值是什么

#ifdef VALUE
    #define PI 3.14
#endif

int main()
{

  cout<<"PI = "<< PI <<endl;
}
#endif

//==============================================================================

#if 0

#include<iostream>
using namespace std;

//#define VALUE    // 这里 VALUE被定义，不管取值是什么

#ifndef VALUE
    #define PI 3.14
#endif

int main()
{

  cout<<"PI = "<< PI <<endl;
}


#endif

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///    4. C++ 中的预定义宏
///  __LINE__       在编译时包含当前行号
///  __FILE__       在编译时包含当前文件名
///  __DATE__       包含日期
///  __TIME__       包含时间

#if 1

#include<iostream>
using namespace std;

int main()
{
  cout<<"Line:"<<__LINE__<<endl;
  cout<<"File:"<<__FILE__<<endl;
  cout<<"Date:"<<__DATE__<<endl;
  cout<<"TIME:"<<__TIME__<<endl;

  return 0;
}

#endif
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////