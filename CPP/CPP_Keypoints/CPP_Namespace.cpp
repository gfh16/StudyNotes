/*******************************************************************************
                   C++ 命名空间


********************************************************************************/




******************************************************************************
/*
1. 定义命名空间
   (1) 关键字 namespace
       namespace namespace_name
       {
           //代码声明
       }

    (2) 调用命名空间中的函数或变量
         name::code;

2. using 指令
   (1)使用using namespace 指令，可以在使用命名空间时就可以不用在前面加上命名空间的名称

*/
#if 1

#include<iostream>
using namespace std;

//第一个命名空间
namespace first_space
{
  void func()
  {
    cout<<"Inside first_space"<<endl;
  }
}

//第二个命名空间
namespace second_space
{
  void func()
  {
    cout<<"Inside second_space"<<endl;
  }
}

int main()
{
  //调用第一个命名空间中的函数
  first_space::func();

  //调用第二个命名空间中的函数
  second_space::func();

  return 0;

}

#endif

*******************************************************************************
