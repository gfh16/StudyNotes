/*******************************************************************************
                              指针知识点详解(一)
     参考资料： 让你不再害怕指针 —— C 指针详解
             https://blog.csdn.net/soonfly/article/details/51131141


*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
/*
 复杂类型说明
    1. int p;                   // p是整型变量
    2. int *p；                 // p是返回整型数据的指针
    3. int p[3];                // p是由整型数据组成的数组
    4. int *p[3];               // p是由返回整型数据的指针组成的数组   PS：指针数组
    5. int (*p)[3];             // p是指向由整型数据组成的数组的指针   PS: 数组指针
    6. int **p;                 // 二级指针
    7. int p(int);              // p是函数，带有一个整型形参， 函数返回一个整型数据
    8. int (*p)(int)；          // 函数指针
    9. int *(*p(int))[3];       //
*/

/*
***************
一. 细说指针
***************
   1. 需要搞清楚指针四个方面的内容：
      (1) 指针的类型： 把指针声明语句里的指针名字去掉
      (2) 指针所指向的类型： 把指针声明语句中的指针名字和名字左边的指针声明符*去掉
      (3) 指针的值/指针所指向的内存区：
          <1> 在64位系统中，所有类型的指针的值都是一个64位的整数。因为64位系统的内存地址全是64位长的。
          <2> 我们所说的一个指针的值是 XXX, 是说该指针指向了以 XXX 为首地址的一片内存区域
      (4) 指针本身所占据的内存区：在64位系统中，指针本身占据了8个字节(即64位)

    ===================
    32位系统 与 64位系统
    ===================
    a. 32位系统 CPU 一次可处理 32 位数据， 即一次处理 4 个 字节   // l Byte = 8 bit
    b. 寻址能力： 32位cpu含有32跟地址线，寻址能力 2^32 = 4G 内存
                64位cpu含有64跟地址线，寻址能力 2^64 = 16G 内存
    c. 常用数据类型对应字节可用 sizeof()函数查看

    指针声明            指针类型                 指针所指向的类型
    int *p;            int*                          int
    char *p;           char*                         char
    int **p;           int**                         int*
    int(*p)[3];        int(*)[3]                     int()[3]
    int*(*p)[4];       int*(*)[4]                    int*()[4]
*/



/*
****************
二. 指针的算术运算
****************
    1. 指针可以加上或减去一个整数
      <1> 一个指针 pold 加(减)一个整数n后，结果是一个新指针 pnew. pnew的类型和pold相同，pnew
          所指向的类型和pold所指向的类型也相同
      <2> pnew 的值将比 pold的值增加(减少)n*sizeof(pold所指向的类型)个字节.即;
          pnew 所指向的内存区将比 pold 所指向的内存区向高(低)地址方向移动了 n*sizeof(pold所指向的类型)个字节.
      <3> 两个指针不能做加法运算，因为得到的结果指向一个不知去向的地方
      <4> 两个指针可以做减法，但必须类型相同。一般用在数组方面
    2. 指针的算术运算包括：++ 、 -- 、 + 、 -
*/



/*
*******************
三. 运算符 & 和 *
*******************
    1. & 是取址运算符
       (1) &a 的运算结果是一个指针，指针的类型是：a的类型加个*
    2. * 是间接运算符
*/



/*
******************
四. 指针和数组的关系
******************
    1. 声明了一个数组 TYPE array[n]，则数组名称 array 就有了两层含义：
      (1) 它代表整个数组，它的类型的 TYPE[n]
      (2) 它是一个常量指针，该指针的的类型是 TYPE*, 该指针指向的类型是 TYPE
          a. 该指针指向的内存区是数组的第 0 号单元
          b. 该指针自己占有单独的内存区，它与数组第0它与数组第0号单元占据的内存区是不同的
          c. 该指针的值不能被修改， 即 array++ 的表达式是错误的
          array[0]  可以表达为： * array;
          array[1]  可以表达为： * (array+1)
   2. 我们喜欢在程序中使用指针代替数组，因为变量指针可以递增，而数组不能递增，因为数组是一个常量指针

   3. 指针与数组的关系，需要弄清楚下面几个问题：
      (1) 指针与数组互换
      (2) 数组指针    //指向数组的指针
      (3) 指针数组    //用于存放指针的数组
*/
////  指针与数组的互换使用
#if 0

#include<iostream>
using namespace std;

int main()
{
  int array[5] = {1,2,3,4,5};

  for(int i=0; i<5; i++)
    {
    printf("第 %d 个单元是：%d\n", i, *(array+i));
    cout<<"地址："<< &(array+i) << endl;

    *array = i;  // 这是正确的语法
    //array++;     //这是错误的语法

    cout<< *array << endl;
  }

  return 0;
}

#endif


/// 指针与数组的互换使用
#if 0

#include<iostream>
using namespace std;

int main()
{
  int array[5] = {1,2,3,4,5};
  int *ptr;

  ptr = array;
  for(int i=0; i<5; i++)
  {
    cout<<"地址-数组："<< &array[i]<<endl;
    cout<<"地址-指针："<< ptr <<endl;

    cout<<"array["<< i <<"]的取值"<< array[i]<<endl;
    cout<<"array["<< i <<"]的取值"<< *ptr <<endl;

    ptr++;
  }

  return 0;
}
#endif



// 指针函数 与 函数指针
#if 0

#include<iostream>
using namespace std;

int main()
{
  int c[5] = {1,2,3,4,5};
  int *a[5];   // 指针数组
  int (*b)[5]; // 数组指针

  b = &c;

  // 将数组c中的元素赋值给a
  for(int i=0; i<5; i++)
  {
    a[i] = &c[i];
  }

  cout<< *a[2] <<endl;
  cout<< (*b)[3] << endl;

  return 0;
}

#endif


#if 0
#include <iostream>

using namespace std;
const int MAX = 4;

int main ()
{
 const char *names[MAX] = {
                   "Zara Ali",
                   "Hina Ali",
                   "Nuha Ali",
                   "Sara Ali",
   };

   for (int i = 0; i < MAX; i++)
   {
      cout << "Value of names[" << i << "] = ";
      cout << names[i] << endl;
      // 这里需要注意，names[i] 输出“Zara Ali”等，而不是输出地址
      // 这是因为c++ 对 char 类型有特殊处理
   }
   return 0;
}

#endif


/*
******************
五. 指针和函数的关系
******************
   1. C++ 允许传递函数给指针，只需要简单地声明函数参数为指针类型即可
   2. 指针与函数的关系，需要弄清楚一下几个问题：
      (1) 函数形参声明为指针变量
      (2) 指针函数    (本质是一个函数，其返回值是指针)   int* fun(int x, int y);
      (3) 函数指针    (本质是一个指针，其指向一个函数)   int (*fun)(int x, int y);
           *** 函数指针一个典型的应用 ： 回调函数
*/

//  函数的参数为 指针
#if 0

#include<iostream>
#include<ctime>

using namespace std;

void getSeconds(unsigned long *par);

int main()
{
  unsigned long sec;

  getSeconds(&sec);

  cout<<"Number of seconds:"<< sec << endl;

  return 0;
}

void getSeconds(unsigned long *par)
{
  //获取当前的秒数
  *par = time(NULL);
  return;
}

#endif


// 函数的参数为 数组
#if 0

#include<iostream>
using namespace std;

double getAverage(int *arr, int size);

int main()
{
  int balance[5] = {1000, 2, 3, 17, 50};
  double ave;

  // 传递一个指向数组的指针作为参数
  ave = getAverage(balance, 5);

  cout<<"平均值是："<< ave <<endl;

  return 0;
}

double getAverage(int* arr, int size)
{
  int sum = 0;
  double ave = 0;

  for(int i=0; i<size; i++)
  {
    sum += arr[i];
  }
  ave = double (sum)/size;

  return ave;
}
#endif



// 函数指针的应用
#if 0

#include<iostream>
#include<ctime>

using namespace std;

int *getRandom();

int main()
{
  //一个指向整数的指针
  int *p;

  p = getRandom();
  for(int i=0; i<10; i++)
  {
    cout<<"*(p+"<< i <<"):" << *(p+i)<<endl;
    cout<<"(p+"<< i <<"):"<< (p+i) << endl;
  }
  return 0;
}


int *getRandom()
{
  static int r[10];

  //设置种子
  srand((unsigned)time(NULL));

  for(int i=0; i<10; i++)
  {
    r[i] = rand();
    cout<< r[i] <<endl;
  }

  return r;
}

#endif



///  指针函数的应用
#if 0

#include<iostream>
using namespace std;

int max(int a, int b)
{
  return (a > b ? a : b);
}

int main()
{
  int (*p)(int a, int b);  // 定义指针函数

  p = max;  // 初始化

  int ret = p(20, 30);
  // int ret = (*max)(20, 30);   //等效写法
  // int ret = (*p)(20, 30);     //等效写法

  cout<<"max = "<< ret <<endl;

  return 0;
}
#endif
/*





**********************
六. 指针和结构类型的关系
***********************
   1. 可以声明一个指向结构类型对象的指针

*/

#if 0

#include<iostream>
using namespace std;

struct MyStruct
{
  int a;
  int b;
  int c;
};

int main()
{
  struct MyStruct ss = {20, 30, 40};

  struct MyStruct* ptr = &ss;
  // 声明了一个指向结构对象 ss 的指针， 它的类型是 MyStruct* , 它指向的类型是MyStruct


  return 0;
}

#endif



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*                      指针知识点详解(二)

1. 什么是指针？为什么使用指针？
   (1) 指针是一个可以用来存储内存地址的变量
   (2) 指针比数组快；动态分配内存必须使用指针

2. 指针的声明
   (1) int *ptr;

3. 使用指针:
   (1) 地址运算符
       int number;
       int* pnumber;
       pnumber = &number;

   (2) 间接运算符(即解除指针的作用)
        *pnumber = number;

4. 指针的初始化(使用指针一定要初始化)
   (1) 初始化为已定义变量的地址
       int number = 0;
       int* pnumber = &number;

   (2) 使用空指针
        int* pnumber = 0;

   (3) 利用 new 动态分配内存
       int* pnum = 0;
       pnum = new int;

       int* pnum = new pnum(0);

   (4) 把指针初始化为 char 类型
        char* s = "hello world."  // 不要采取这样的方式初始化

        const char* pproverb = "A miss s as good as a mile."  // 推荐采用这种方式

        ===> 输出流cout把指向char的变量看做一个非空字符串，并显示该字符串，而不是显示地址！

 5. 常量指针与指向常量的指针
    (1) 指向常量的指针：内容不能改，地址能改
        const char* pstring = "Some text that cannot be changed."

        const int value = 20;
        const int* pvalue = &value;

    (2) 常量指针：地址不能改，内容能改
        int value = 20;
        int* const pvalue = &value;

    (3) 指向常量的常量指针：地址和内容都不能改
        const int value = 20;
        const int* const pvalue = &value;

  6. 指针和数组
     (1) 指针的算术运算：加、减法，比较指针=>逻辑结果
     (2) 计算两个指针的差
     (3) 使用数组名的指针表示法：data[i] = *(data+i);

****  7. 动态分配内存  --- 指针最重要的作用
     (1) 动态内存分配：在程序运行阶段(而不是编译阶段)进行决策
     (2) 使用 new 来分配内存
         <1> double* pvalue  = 0;
             pvalue = new double;

             double* pvalue = new double(0.0);
     (3) 使用 delete释放内存
         <1> 当指针pvalue使用完毕，释放内存：
            delete pvalue;
     (4) 数组的动态内存分配
         <1> 动态数组初始化:
            a. 对于内置数据类型元素的数组，必须使用()来初始化
               int* pia = new int[10]; //每个元素都没有初始化
               int* pia = new int[10](); //每个元素初始化为0
            b. 类类型的数组，无论是否使用(),都会自动调用其默认构造函数来初始化
              string* psa = new string[10];
              string* psa = new string[10]();
     (5) 动态内存分配的危险
         <1> 内存泄露
         <2> 内存碎块

     (6) 关于new和delete的使用
         <1> 一定要配对使用 new 和 delete，否则将发生内存泄露
         <2> 不能使用 delete 来释放不是 new 分配的内存
         <3> 不要使用delete释放同一块内存两次
         <4> 如果使用 new[]为数组分配内存，则应使用delete[]来释放
         <5> 如果使用 new为一个实体分配内存，则应使用delete来释放
         <6> 对空指针应用 delete 是安全的

*/

// 从键盘上读取一组单词，以预定义的顺序对他们进行排序
#if 0

#include<iostream>
#include<string>
using namespace std;

int main()
{
  string text;
  const string separators = " , . \" \n";
  const int max_words = 1000;
  string words[max_words];
  string* pwords[max_words];

  cout<< endl << "Enter a string terminated by #:" << endl;
  getline(cin, text, '#');

  // Extract all the words from the text
  int start = text.find_first_not_of(separators);
  int end = 0;
  int word_count = 0;
  while(start != string::npos && word_count < max_words)
  {
    end = text.find_first_of(separators, start + 1);
    if(end == string::npos)
       end = text.length();

    words[word_count] = text.substr(start, end - start);
    pwords[word_count] = &words[word_count];
    word_count++;

    // Find the first character of the next word
    start = text.find_first_not_of(separators, end + 1);
  }

  int lowest = 0;
  for(int j=0; j<word_count - 1; j++)
  {
    lowest = j;

    for(int i=j+1; i<word_count; i++)
      if(*pwords[i]< *pwords[lowest])
        lowest = i;

    if(lowest !=j)
    {
      string* ptemp = pwords[j];
      pwords[j] = pwords[lowest];
      pwords[lowest] = ptemp;
    }
  }

    // output the words in ascending sesquence
  for(int i=0; i<word_count; i++)
    cout<< endl << *pwords[i];
    cout << endl;

  return 0;
}

#endif



#if 1

#include<iostream>
using namespace std;

int main()
{
  double* p3 = new double[3]{0};
  p3[0] = 0.2;
  p3[1] = 0.5;
  p3[2] = 0.8;

  cout<<"p3[1] is "<< p3[1] << "." << endl;

  p3 = p3+1;
  cout<<"Now p3[0] is "<< p3[0]<<"." << endl;
  cout<<"p3[1] is "<< p3[1] << "." << endl;
  p3 = p3 -1;
  delete [] p3;

  return 0;
}



#endif
