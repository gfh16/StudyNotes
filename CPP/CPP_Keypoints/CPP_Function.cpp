/****************************************************************************

                       C++ 函数

    1. 一个函数的组成部分：返回类型、函数名称、参数、函数主体
    2. C++ 中函数定义的一般形式：
       return_type function_name( parameter list)
       {
          body of the function
       }
    3. 调用函数时，向函数传递参数的方式：
        <1> 传值调用：把参数实际值复制给函数的形参。修改函数内的形参对实际参数无影响。
        <2> 指针调用：把参数的地址复制给形参。修改形参会影响实际值。
        <3> 引用调用：把参数的引用复制给形参。修改形参会影响实际参数

****************************************************************************/

/*******************************************************************************
1. C++ 函数的返回类型
  (1) C++ 代码主函数的写法
      int main()
      {
         // 代码
         return 0;
      }

      int main(int argc, char* argv[])
      {
        //代码
        return 0;
      }

      void main()
      {
         //代码
      }

      void main()
      {
        //代码
        return;
      }

  // 尽量采用返回值为整型的写法


*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
///   函数的调用
#if 0

#include<iostream>
using namespace std;

int max(int num1, int num2);

int main()
{
  int a =100;
  int b =200;
  int ret;

  ret = max(a,b);

  cout<< "Max value is: "<< ret << endl;

  return 0;
}


int max(int num1, int num2)
{
  int result;

  if(num1 > num2)
    result = num1;
  else
    result = num2;

  return result;
}

#endif

////////////////////////////////////////////////////////////////////////////////
///                         1) 函数的传值调用
///  把参数的实际值复制给函数的形参，修改函数的形参不会影响实际参数

#if 0

#include<iostream>
using namespace std;

void swap(int x, int y);

int main()
{
  int a = 100;
  int b = 200;

  cout<<"交换前，a的值："<< a << endl;
  cout<<"交换前，b的值："<< b << endl;

  swap(a,b);

  cout<<"交换后，a的值："<< a << endl;
  cout<<"交换后，b的值："<< b << endl;

  return 0;
}

void swap(int x, int y)
{
  int temp;

  temp = x;
  x = y;
  y = temp;

  return;
}

#endif

////////////////////////////////////////////////////////////////////////////////
////                 2) 函数的指针调用
//// 把参数的地址复制给形参， 修改形参会改变实际参数

#if 0

#include<iostream>
using namespace std;

void swap(int *x, int *y);

int main()
{
  int a = 100;
  int b = 200;

  cout<<"交换前，a的值："<< a << endl;
  cout<<"交换前，b的值："<< b << endl;

  swap(&a, &b);

  cout<<"交换后，a的值："<< a << endl;
  cout<<"交换后，b的值："<< b << endl;

  return 0;
}

void swap(int *x, int *y)
{
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;

  return;
}


#endif

////////////////////////////////////////////////////////////////////////////////
////      3) 函数的引用调用
////  把引用的地址复制给形参，需改形参会影响实际参数

#if 1

#include<iostream>
using namespace std;

void swap(int &x, int &y);

int main()
{
  int a = 201;
  int b = 100;

  cout<<"交换前， a的值："<< a << endl;
  cout<<"交换前， b的值："<< b << endl;

  swap(a,b);

  cout<<"交换后， a的值："<< a << endl;
  cout<<"交换后， b的值："<< b << endl;
}


void swap(int &x, int &y)
{
  int temp;
  temp = x;
  x = y;
  y = temp;

  return;
}


#endif
