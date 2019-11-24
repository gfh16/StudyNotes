C++知识重点
===========
> [Google-C++编程风格](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/formatting/)
>+ 代码编写要注意规范！

目录
=====
[toc]


### 结构体 struct
1. 结构体的构造函数 (建议同时使用默认构造函数和自定义构造函数)
```C++
struct node
{
  node(): x(),str(),data() {}
  node(int a, string b, char c): x(c), str(b), data(a){}
  char   x;
  string str;
  int    data;

};

//_______________________
int main()
{
  node aa(1, "hello", 'c');
  node bb;
  bb = node(2, "python", 'D');
  cout<< aa.x <<"  "<< aa.str <<"  "<< aa.data << endl;
  cout<< bb.x <<"  "<< bb.str <<"  "<< bb.data << endl;

}


```

