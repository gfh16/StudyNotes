/*******************************************************************************
                        C++ 模板 (实现泛型编程)

参考链接:
https://blog.csdn.net/liitdar/article/details/80587058


1. 为什么使用C++模板？
   (1)C++无法做到动态语言(如python)那样: 编写出一套通用的逻辑，然后把任意类型的变量传入处理
   (2)泛型编程弥补了C++这个缺点: 通过把通用逻辑设计为模板，摆脱了类型的限制

2. 什么是C++模板
   (1)对C++模板的认识
      <1>模板是泛型编程的基础
      <2>泛型编程是一种代码编写方式，通过使用泛型编程，我们可以编写出独立与任何特定类型的代码
      <3>模板是创建泛型函数或类的蓝图/公式

   (2)函数模板
      <1>把处理不同类型的公共逻辑抽象成函数，就得到了函数模板
      <2>函数模板可以用来创建一个通用的函数，以支持多种不同类型的形参，避免重载函数的函数体重复设计
      <3>函数模板的最大特点: 把函数使用的数据类型作为参数

   (3)类模板
      <1>使用类模板可以使用户为类声明一种模式，使得类中的某些数据成员或者成员函数的参数、返回值
         为任意类型
      <2>模板的声明或定义只能在全局、命名空间或类的范围内进行，不能在局部范围、函数内进行

3. C++模板的格式
(1)函数模板
    template <typename type>
    re-type func_name(parameter list)
    {
        //函数主体
    }

(2)说明
   <1>type是函数所使用的数据类型的占位符名称，这个占位符名称可以在函数定义中使用
   <2>关键字"typename"可替换为"class"，两者作用一样
   <3>ret-type为函数的返回值

(3)实例
    template <typename T>
    T Max(T a, Tb)
    {
       return (a>b?a:b);
    }

4. 类模板的格式
    template <typename type>
    class class-namespace
    {
      //类的主体
    }


*******************************************************************************/
