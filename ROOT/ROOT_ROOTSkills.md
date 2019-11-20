# ROOT 有用并且有趣的代码实现
> 记录一些在 ROOT 使用过程中遇到的有意思的技巧
  好记性不如烂笔头！
  从程序技巧中体会写代码的乐趣

 作者： 小关

[toc]


## 显示程序完成进度-1
```C++
  if(jentry%100000==0)
  {
    std::cout << "  Percentage = " << std::fixed << >> std::setprecision(1) << std::setw(5) << (100*double(jentry)/nentries) << " %";
    std::cout << "   [";
    int printindex=0;
    for(; printindex<int(100*double(jentry)/nentries); printindex+=5) std::cout << "=";
    for(; printindex<100; printindex+=5) std::cout << " ";
    std::cout << "]\r"; std::cout.flush();
}
```


## 显示程序完成进度-2
```C++
 #include <time.h>
 for(Long64_t jentry=0; jentry<nentries; jentry++)
 {
   if(jentry%100000==0)
   {
     double time_elapsed = (double)(clock() - fStartTime)/CLOCKS_PER_SEC;
     std::cout << "  Percentage = " << std::fixed << std::setprecision(1) << std::setw(5) << (100*double(jentry)/nentries) << " %";
     std::cout << "   [";
     int printindex=0;
     for(; printindex<int(100*double(jentry)/nentries); printindex+=5) std::cout << "=";
     for(; printindex<100; printindex+=5) >> std::cout << " ";
     std::cout << "]   " << "elapsed time " << std::setprecision(1) <<
     (time_elapsed<60 ? time_elapsed : (time_elapsed<3600 ? time_elapsed/60 : time_elapsed/3600)) <<
     (time_elapsed<60 ? " s; " : (time_elapsed<3600 ? " m; " : " h; "));
     if(jentry>0) {
     double time_remaining = (time_elapsed/jentry)*(nentries-jentry);
     std::cout << " estimated remaining time " << std::setprecision(1) <<
     (time_remaining<60 ? time_remaining : (time_remaining<3600 ? time_remaining/60 : time_remaining/3600)) <<
     (time_remaining<60 ? " s      " : (time_remaining<3600 ? " m      " : " h      "));
  }
   std::cout << "\r";
   std::cout.flush();
 }
```


## 写手动GUI界面
```C++
 c1->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",0,0,"SetPoints(Int_t,Int_t,Int_t,TObject*)");
 while(Index!=1)
{
  usleep(100);
  gClient->HandleInput();
}
 c1->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)");
```


## 求导数

 > 在 ROOT User's Guide 中 TMath 一章有详细介绍
 [Link to TMath Class](https://root.cern.ch/root/htmldoc/guides/users-guide/ROOTUsersGuide.html#math-libraries-in-root)

 
* <font color=#DC143C > 插值法： Interpolator </font>
```C++
  * 创建插值的对象： ROOT::Math::Interpolator SplineInterpolator;
  * 插入数据点： SplineInterpolator.SetData();
  * 计算每个插值点的位置x
  * 求导: SplineInterpolator.Deriv(x);
```

* <font color=#DC143C > RichardsonDerivator </font>
[Link to Function Derivation](https://root.cern.ch/function-derivation)
```C++
  * 定义需要求导的函数： Double_t myfunc(Double_t x) { };
  * 创建函数：         ROOT::Math::Functor1D f1D(&myfunc);
  * 创建求导的对象：    ROOT::Math::RichardsonDerivator rd;
  * rd.SetFunction(f1D);
  * 求导：
        rd.Derivative1(x0);  // myfunc在 x0 处的一阶导数
        rd.Derivative2(x0);  // myfunc在 x0 处的二阶导数
        rd.Derivative3(x0);  // myfunc在 x0 处的三阶导数
```

* <font color=#DC143C > Derivator </font>
```C++
  * 定义需要求导的函数: Double_t myfunc(Double_t x) { };
  * 创建函数:         ROOT::Math::Functor1D f1D(&myfunc);
  * 创建求导的对象:    ROOT::Math::Derivator der;
  * 求导数值:         Double_t result = der.Eval(x0);
```


## 求积分
> See the detials: tutorials/hist/cumulative.C
[Link to cumulative.C](https://root.cern/doc/master/cumulative_8C.html)
```C++
* 求直方图的积分分布：hist->GetCumulative();  // 结果返回 hist 的积分分布
```


## 打开文件

 <font color=#DC143C > ifstream filein(path);  </font>
```C++
 ifstream infile("input.txt");
 while(1)   // while(infile.good()){}
 {
    infile>>var1>>var2>>var3>>var4>>var5>>var6;  //var1...可以是任何类型变量
    if (!infile.good() || infile.eof())  break;
    ...
    ...
 }
 infile.Close();
```

<font color=#DC143C>ifstream filein;
  filein.open(path,ios::mode) </font>
[Link to ifstream open open mode](https://www.runoob.com/cplusplus/cpp-files-streams.html)
```C++
ifstream infile;
infile.open("input.txt",ios::app);// open(const char *filename, ios::openmode mode)
```

<font color=#DC143C> TFile </font>
> 仅限于打开 .root 文件
```C++
TFile * filein = new TFile("test.root");
TFile filein("test.root")
```

<font color=#DC143C> FILE </font>
```C++
FILE * FileOut = fopen(Form("output/PulserCali_%s.dat", FileTag3.c_str()),"w");
fprintf(FileOut,"# itel  icsi \n");
fflush(FileOut); // 需要加上这句！！！ 否则由于缓存问题，内容不被写入
```