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
///                    6. struct tm *gmtime(const time_t *timer)
/// 使用 timer 的值来填充 tm 结构， 并且使用格林尼治时间（UTC)来表示
#if 0

#include<stdio.h>
#include<time.h>

#define BST (+1)    /* 伦敦时区 */
#define CCT (+8)   /*  北京时区 */

int main()
{
  time_t rawtime;
  struct tm *info;

  time(&rawtime);

  //获取格林尼治时间
  info = gmtime(&rawtime);

  printf("当前的世界时钟：\n");
  printf("伦敦：%2d:%2d\n", (info->tm_hour+BST)%24, info->tm_min);
  printf("北京：%2d:%2d\n", (info->tm_hour+CCT)%24, info->tm_min);

  return 0;
}
#endif
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
///                 7. time_t mktime(struct tm *time)
///  返回一个time_t 值， 该值对应于以参数传递的日历时间
///  输入日期判断是周几
#if 0

#include<iostream>
#include<ctime>

using namespace std;

int main()
{
  time_t rawtime;
  struct tm *info;
  int year, month, day;
  const char * weekday[] = {"周日","周一","周二","周三","周四","周五","周六"};

  /* 用户输入日期*/
  cout<<"年："; cin>> year;
  cout<<"月："; cin>> month;
  cout<<"日："; cin>> day;

  /* 获取当前时间信息， 并修改用户输入的信息*/
  time(&rawtime);
  info = localtime(&rawtime);
  info->tm_year = year - 1900;
  info->tm_mon  = month - 1;
  info->tm_mday  = day;

  /* 调用 mktime: info->tm_wday*/
  mktime(info);

  cout<<"那一天是："<< weekday[info->tm_wday]<<endl;

  return(0);
}

#endif
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////              8. double difftime(time_t time2, time_t time1)
///  返回以 double 型值表示的两个时间之间相差的秒数(time2 - time1)
///  举例： 计算今年以来经过的 秒 数
#if 0

#include<iostream>
#include<iomanip>
#include<ctime>

using namespace std;

int main()
{
  time_t now;
  double diff;
  struct tm  *info;

  time(&now);

  info = localtime(&now);

  info->tm_hour = 0;
  info->tm_min  = 0;
  info->tm_sec  = 0;
  info->tm_mon  = 6;
  info->tm_mday = 27;

  diff = difftime(now, mktime(info));

  cout<< diff << setw(50) <<"seconds since new year in the current timezone."<<endl;

  return 0;
}
#endif
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////              9. size_t strftime()
//// strftime()函数声明：size_t strftime(char *str, size_t maxsize, const char *foemat, const struct tm *timeptr)
#if 1

#include<iostream>
#include<time.h>

using namespace std;

int main()
{
  time_t rawtime;
  struct tm *info;

  char buffer[100];

  time(&rawtime);

  info = localtime(&rawtime);

  strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", info);
  cout<<"格式化的日期 & 时间： |"<< buffer << "|"<< endl;

  return 0;
}

#endif
////////////////////////////////////////////////////////////////////////////////
