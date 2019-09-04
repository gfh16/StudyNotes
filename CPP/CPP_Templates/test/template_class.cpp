#include<iostream>
#include "template_class.h"

using namespace std;

template <typename T>
CTmpl<T>::CTmpl()
{
}

//成员函数的巨日实现
template <typename T>
T CTmpl<T>::FunA(T a, T b)
{
  return (a+b);
}

int main()
{
  CTmpl<int> tmpl_int;
  cout<<"tmpl_int.FunA(1,2) is:"<<tmpl_int.FunA(1,2)<<endl;

  CTmpl<float> tmpl_float;
  cout<<"tmpl_float.FunA(1.1, 1,2) is:"<< tmpl_float.FunA(1.1, 2.2)<<endl;

  return 0;

}

