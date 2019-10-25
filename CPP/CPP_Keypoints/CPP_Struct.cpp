/**********************************************************
                 结构体
      1. 结构是C++中用户自定义的可用的数据类型，允许储存不同类型的数据
      2. 为了定义结构，必须使用 struct 语句
      3. 为了访问结构的成员，使用成员访问运算符(.)
      4. 在C++中, 结构体可以包含函数，具有类的功能
      5. typedef关键字
      6. 结构体嵌套

参考书籍：
1. C++ 入门经典（第3版） Ivor Horton 著； 李予敏 译
2. C++ Primer Plus 中文第六版
3. C++ 菜鸟教程
************************************************************/
/*         结构体知识详解

1. 结构的概念
   ：结构是一种用户自定义的数据类型，它实际上是不同数据类型的数据项的一个指定集合。

2. 结构的定义(同时也是结构的声明)
   struct Book
   {
      char title[100];
      char author[100];
      char subject[100];
      int  book_id;
   };

 3. 创建结构类型的对象，同时初始化
   (1) 使用初始化列表 （按顺序初始化非常重要）
   (2) 使用构造函数

  e.g.  Book Book1 = {"C++ 教程", “Runoob”, "编程语言", "12345"};
  e.g.  Book Book2;
        strcpy(Book2.title, "C++ 教程");
        strcpy(Book2.author, "Runoob");
        strcpy(Book2.subject, "编程语言");
        strcpy(Book2.book_id, "12345");

 4. 访问结构对象的成员
    (1) 结构的数据成员：使用成员访问运算符(.)
        e.g. Book1.title;

    (2) 结构的成员函数：两种定义方式
        <1> 方式1
         struct Box
           {
             double length;
             double width;
             double height;

             double volume()
             {
                return length * width * height;
             }
           };

        <2> 方式2 (建议采用这种方式)
        struct Box
        {
           double length;
           double width;
           double height;

           double volume();
        }

        double Box::volume
        {
          return length*width*height;
        }

    5. 对结构使用指针(对象指针)
      (1) 使用 new 运算符， 在自由存储区创建对象
          Book novel = new Book;

          // 使用完这个对象，需要将之从自由存储区中删除
          delete novel;

      (2) 通过指针访问结构成员(不常用)
           Box aBox = {80.0, 50.0, 40.0};
           Box* pBox = &aBox;

          // 访问方式：先解除指针的引用，获得对象，再访问数据成员
          （*pBox).height += 10.0;

      (3) 指针成员访问运算符
          pBox->height += 10.0；

  6. 结构数组
      (1) 创建结构数组：
           Book book[10];
      (2) 访问结构数组：
           book[0].title;
      (3) 初始化


  7. 把结构作为成员
     struct Person
     {
       Name name;
       Date birthday;
       Phone number;
     };

     struct Name
     {
       char firstname[80];
       char surname[80];
     };

     struct Date
     {
       int day;
       int month;
       int year;
     };

     Struct Phone
     {
       int areacode;
       int number;
     };
*/


#if 1

#include<iostream>
using namespace std;

struct Box
{
  double length;
  double width;
  double height;

  double volume();
};

double Box::volume()
{
  return length*width*height;
}

int main()
{
  Box abox = {10, 20, 30};
  Box* pbox = &abox;

  cout<<"volume of abox is："<< abox.volume()<<endl;

  Box* cbox = new Box;
  cbox->length = pbox->length - 3.0;
  cbox->height = pbox->height + 5.0;
  cbox->width = pbox->width - 2.0;

  cout<<"volume of Box in the free store is:"<< cbox->volume()<<endl;

  delete cbox;
  return 0;

}

#endif
