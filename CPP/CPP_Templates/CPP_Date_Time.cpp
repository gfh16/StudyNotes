/*******************************************************************************
                  C++ 日期 && 时间
    1. C++ 标准库没有提供日期类型。继承了C语言中的相关结构和函数
    2. 需要在C++程序中引用<ctime>头文件
    3. C Time Library 包含下面内容：（ 9 个函数， 4 种数据类型， 2 个常量）
    (1) Functions
        <1> clock                 // Clock program
        <2> difftime              // Return difference between two times
        <3> mktime                // Convert tm structure to time_t
        <4> time                  // Get current time

    (2) Conversion
        <1> asctime              // Convert tm structure to string
        <2> ctime                // Convert time_t value to string
        <3> gmtime               // Convert time_t to tm as UTC time
        <4> localtime            // Convert time_t to tm as local time
        <5> strftime             // Format time as string

    (3) Macro constants
        <1> CLOCKS_PER_SEC       // Clock ticks per second
        <2> NULL                 // Null pointer

    (4) types
        <1> clock_t              // Clock type
        <2> size_t               // Unsigned integral type
        <3> time_t               // Time type
        <4> struct tm            // Time structure

   4. 结构类型tm的定义：
      structure tm
      {
         int tm_sec;          // 秒， 正常范围从 0 - 59， 但允许至 61
         int tm_min;          // 分， 范围从 0 - 59
         int tm_hour;         // 小时， 范围从 0 - 23
         int tm_mday;         // 一月中的第几天， 范围从 1 - 31
         int tm_mon;          // 月， 范围从 0 到 11
         int tm_year;         // 自 1900 年 起的年数
         int tm_wday;         // 一周的第几天， 范围从 0 到 6， 从星期日算起
         int tm_yday;         // 一年中的第几天， 范围从 0 到 365， 从 1 月 1 日算起
         int tm_isdst;        // 夏令时
      }
*******************************************************************************/
////  当前日期和时间
#if 0

#include<iostream>
#include<ctime>

using namespace std;

int main()
{
  // 基于当前系统的当前日期、时间
  //time_t now = time(0);
  //time_t now = time(NULL);

  time_t now;
  time(&now);  /* get current time,; same as: now = time(NULL) */

  // 把now转换为字符串形式
  char *dt = ctime(&now);

  cout<<"本地的日期和时间："<< dt << endl;

  //把now转换成 tm 结构
  tm *gmtm = gmtime(&now);
  dt = asctime(gmtm);
  cout<< "UTC 日期和时间："<< dt << endl;

  return 0;

}
#endif
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////   使用结构 tm 格式化时间
#if 0

#include<iostream>
#include<ctime>

using namespace std;

int main()
{
  //基于系统当前的时间
  time_t now = time(NULL);

  cout<<"1970 到目前经过的秒数："<< now << endl;

  tm *ltm = localtime(&now);

  //输出 tm 结构的各个组成部分
  cout<<"年："<< 1900+ltm->tm_year<<endl;
  cout<<"月："<< ltm->tm_mon<<endl;
  cout<<"日："<<ltm->tm_mday<<endl;
  cout<<"时间："<<ltm->tm_hour<<":"<<ltm->tm_min<<":"<<ltm->tm_sec<<endl;
  cout<<"夏令时："<<ltm->tm_isdst<<endl;

  return 0;
}

#endif
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
///                  1.  time_t time(time_t *t)
///  返回自1970-01-01 00:00:00 UTC 经过的时间，以秒为单位
#if 0

#include<stdio.h>
#include<time.h>

int main()
{
  time_t seconds;

  seconds = time(NULL);
  printf("自1970-01-01起的小时数 = %ld\n", seconds/3600);

  return 0;
}

#endif
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////                 2. char *ctime(const time_t *timer)
///  返回一个表示当地时间的字符串,显示格式：Mon Aug 13 08:23:14 2019
#if 0

#include<iostream>
#include<ctime>

using namespace std;

int main()
{
  time_t curtime;
  time(&curtime);

  char *loctime = ctime(&curtime);

  cout<<"当前时间是："<< loctime <<endl;

  return 0;
}

#endif

////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
////                  3. struct tm *localtime(const time_t *timer)
///  使用 timer 的值来填充 tm 结构。 timer的值被分解为 tm 结构，并用本地时区表示
#if 0

#include<stdio.h>
#include<time.h>

int main()
{
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  printf("当前的本地时间和日期：%s", asctime(timeinfo));

  return 0;
}
#endif

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
///                        4. clock_t clock(void)
///  返回程序执行起(一般为程序的开头),处理器时钟所使用的时间。
///  为了获取CPU所使用的时间，需要除以 CLOCKS_PER_SEC
///  实践证明， 使用CLOCK()来计算CPU运行时间比 time()精确得多
#if 0

#include<iostream>
#include<time.h>

using namespace std;

int main()
{
//  time_t t1;
//  time_t t2;
  clock_t start_t;
  clock_t end_t;
  double total_t;

//  time(&t1);
  start_t = clock();
//  cout<<"程序启动，t1="<< t1 << endl;
  cout<<"程序启动，start_t="<< start_t << endl;

//  cout<<"开始一个大循环，t1="<< t1 << endl;
  cout<<"开始一个大循环，start_t="<< start_t << endl;

  srand((unsigned)time(NULL));
  for(int i=0; i<100000000; i++)
  {
    rand();
  }

//  time(&t2);
  end_t = clock();

//  cout<<"大循环结束，t2="<< t2 << endl;
  cout<<"大循环结束，end_t="<< end_t << endl;

  total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
//  cout<<"CPU 占用的总时间 = "<< t2-t1<<"s"<<endl;
  cout<<"CPU 占用的总时间 = "<< total_t <<"s"<<endl;

  return 0;


}
#endif
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
///                   5. char *asctime(const struct tm *timeptr)
///  返回一个指向字符串的指针，包含结构structure 的日期和时间
#if 0

#include<stdio.h>
#include<string.h>
#include<time.h>

int main()
{
  struct tm t;

  t.tm_sec    =  20;
  t.tm_min    =  10;
  t.tm_hour   =  2;
  t.tm_mday   =  18;
  t.tm_mon    =  7;
  t.tm_year   =  2020;
  t.tm_wday   =  5;

  printf("时间：%s", asctime(&t));

  return 0;


}


#endif
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
///                    6. struct tm *gmtime(const time_t *time)






////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
///                 7. time_t mktime(struct tm *time)







////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////              8. double difftime(time_t time2, time_t time1)






////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////              9. size_t strftime()







////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////
