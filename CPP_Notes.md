<div style="text-align: left">
<font face="微软雅黑" size=5 color=#FF00FF>
  小关的读书笔记
</font> 
</div>


<center> C++ 学习笔记 </center>
==============================

> [Google-C++编程风格](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/formatting/)
> 代码编写要注意规范！

目录
=====
[toc]


--------------------------------------------
# <font color=#DC143C> C++ 基础知识 </font>


## 结构体 struct
1.结构体的构造函数 (建议同时使用默认构造函数和自定义构造函数)
<details>
<summary>展开查看</summary>
<pre><code>
struct node
{
  node(): x(),str(),data() {}
  node(int a, string b, char c): x(c), str(b), data(a){}
  char   x;
  string str;
  int    data;

};

//______________
int main()
{
  node aa(1, "hello", 'c');
  node bb;
  bb = node(2, "python", 'D');
  cout<< aa.x <<"  "<< aa.str <<"  "<< aa.data << endl;
  cout<< bb.x <<"  "<< bb.str <<"  "<< bb.data << endl;

}
</code></pre>
</details>




---------------------------------------------
# <font color=#DC143C> C++ 进阶知识 </font>



----------------------------------------------
# <font color=#DC143C> C++ 疑难点 </font>

### <font color=#00BFFF> 关于主函数m main(int argc, char** argv)  </font>
```C++
1. argc表示参数个数, char** argv是存储参数的指针数组
2. 如果没有加任何参数，则argc=1, argv[0]="路径/myc.exe"
3. 如果加了一个参数，argc为2，其实就是表示argv指针数组的大小
      argv[0] 为"路径/myc.exe";
      argv[1] 为 第一个参数
```

