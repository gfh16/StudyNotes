ROOT 有用并且有趣的代码实现
========================
> 记录一些在 ROOT 使用过程中遇到的有意思的技巧
  好记性不如烂笔头！
  从程序技巧中体会写代码的乐趣

 作者： 小关


目录
-----
[toc]

----------------------------------------------------------------------
### 显示程序完成进度-1
```C++
//_______________________________________________________
void PrintPercentage(Long64_t ientry, Long64_t nentries)
{
  std::cout<<" Percentage = "<<std::fixed<<std::setprecision(1)<<std::setw(5)
           <<(100*Double_t(ientry)/nentries)<<" %";
  std::cout<<" [";
  for (Int_t index=0; index<Int_t(100*Double_t(ientry)/nentries); index+=5) {
    std::cout<<"=";
  }
  std::cout<<"]\r";
  std::cout.flush();
}
```

### 显示程序完成进度-2
```C++
//____________________________________________________________________
void PrintPercentageAndRemainingTime(Long64_t ientry, Long64_t nentries)
{
  Double_t time_elapsed = (Double_t)(clock()-fBeginTime)/CLOCKS_PER_SEC;
  std::cout<<" Percentage = "<<std::fixed<<std::setprecision(1)<<std::setw(5)
           <<(100*Double_t(ientry)/nentries)<<" %";
  std::cout<<" [";
  for (Int_t index=0; index<Int_t(100*Double_t(ientry)/nentries); index+=5) {
    std::cout<<"=";
  }
  std::cout<<"]   "<<"elapsed time "<<setprecision(1)
           <<(time_elapsed<60 ? time_elapsed : 
             (time_elapsed<3600 ? time_elapsed/60 : time_elapsed/3600))
           <<(time_elapsed<60 ? "s; " : (time_elapsed<3600 ? "m; " : "h; "));
  if (ientry>0)
  {
    Double_t time_remaining = (time_elapsed/ientry)*(nentries-ientry);
    std::cout<<" estimated remaining time "<<setprecision(1)
             <<(time_remaining<60 ? time_remaining : 
               (time_remaining<3600 ? time_remaining/60 : time_remaining/3600))
             <<(time_remaining<60 ? "s; " : (time_remaining<3600 ? "m; " : "h; "));
  }
  std::cout<<"\r";
  std::cout.flush();
}
```

----------------------------------------------------------------
### 写手动GUI界面
```C++
 c1->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",0,0,
             "SetPoints(Int_t,Int_t,Int_t,TObject*)");
 while(Index!=1)
{
  usleep(100);
  gClient->HandleInput();
}
 c1->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)");
```

---------------------------------------------------------------
### 求导数

 > 在 ROOT User's Guide 中 TMath 一章有详细介绍
 [Link to TMath Class](https://root.cern.ch/root/htmldoc/guides/users-guide/ROOTUsersGuide.html#math-libraries-in-root)

 
#### <font color=#DC143C > 插值法： Interpolator </font>
```C++
  * 创建插值的对象： ROOT::Math::Interpolator SplineInterpolator;
  * 插入数据点： SplineInterpolator.SetData();
  * 计算每个插值点的位置x
  * 求导: SplineInterpolator.Deriv(x);
```

#### <font color=#DC143C > RichardsonDerivator </font>
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

#### <font color=#DC143C > Derivator </font>
```C++
  * 定义需要求导的函数: Double_t myfunc(Double_t x) { };
  * 创建函数:         ROOT::Math::Functor1D f1D(&myfunc);
  * 创建求导的对象:    ROOT::Math::Derivator der;
  * 求导数值:         Double_t result = der.Eval(x0);
```


-----------------------------------------------------------------
### 求积分分布
> See the detials: tutorials/hist/cumulative.C
[Link to cumulative.C](https://root.cern/doc/master/cumulative_8C.html)
```C++
* 求直方图的积分分布：hist->GetCumulative();  // 结果返回 hist 的积分分布
```

----------------------------------------------------------------
### 打开文件

#### <font color=#DC143C > ifstream filein(path);  </font>
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

#### <font color=#DC143C>ifstream filein; filein.open(path,ios::mode) </font>
[Link to ifstream open open mode](https://www.runoob.com/cplusplus/cpp-files-streams.html)
```C++
ifstream infile;
infile.open("input.txt",ios::app);// open(const char *filename, ios::openmode mode)
```

#### <font color=#DC143C> TFile </font>
> 仅限于打开 .root 文件
```C++
TFile * filein = new TFile("test.root");
TFile filein("test.root")
```

#### <font color=#DC143C> FILE </font>
```C++
FILE * FileOut = fopen(Form("output/PulserCali_%s.dat", FileTag3.c_str()),"w");
fprintf(FileOut,"# itel  icsi \n");
fflush(FileOut); // 需要加上这句！！！ 否则由于缓存问题，内容不被写入
```

----------------------------------------------------------
### Fitting 2 histograms with the same function
```C++
#include "Fit/Fitter.h"
#include "Fit/BinData.h"
#include "TH1.h"
#include "Math/WrappedTF1.h"
#include "HFitInterface.h"

// example of fitting 2 histograms with the same function
void Fit_SameFunc_2Hist() 
{ 

  TH1D * h1 = new TH1D("h1","histo 1",100,-3,0);
  TH1D * h2 = new TH1D("h2","histo 2",100, 0,3);

  h1->FillRandom("gaus");
  h2->FillRandom("gaus");

  ROOT::Fit::BinData data;
  ROOT::Fit::FillData(data, h1);
  ROOT::Fit::FillData(data, h2);

  cout << "data size is " << data.Size() << endl;

  TF1 * f1 = new TF1("f1","gaus",-3,3);
  f1->SetParameters(1,0,1);

  ROOT::Math::WrappedTF1 wf(*f1);

  ROOT::Fit::Fitter fitter;
  fitter.SetFunction(wf);

  fitter.Fit(data);
  ROOT::Fit::FitResult result = fitter.Result();
  result.Print(std::cout);
}
```

-----------------------------------------------------------------
### 手动选择Cut范围
```C++
void Step1_DEEPoints_1st_CutsForDEELines()
{
  std::string path_to_file ("RootData/HiRA_DECal_CsIRaw_Pixelization.root");
  TFile * FileIn = new TFile(path_to_file.c_str());

  TFile * fileout = new TFile("RootData/DECal_CsIRaw_Cut.root", "UPDATE");

  TIter next(FileIn->GetListOfKeys());
  TKey *key;

  while ((key = (TKey*)next()))
  {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH2D")) continue;
    TH2D *hist = (TH2D*)key->ReadObj();

    std::string HistName(hist->GetName());
    if(HistName.find("DECal_ERaw")==std::string::npos) continue;

    for(int i=0; i<8; i++)
    {
    std::string CutName;
    if(i==0 && fileout->Get(Form("%s_Z%02d_A%02d",HistName.c_str(),1,1))==0) {
      printf("Please Draw cut on protons\n");
      CutName.assign(HistName+Form("_Z%02d_A%02d",1,1));
    }
    if(i==1 && fileout->Get(Form("%s_Z%02d_A%02d",HistName.c_str(),1,2))==0) {
      printf("Please Draw cut on deuterons\n");
      CutName.assign(HistName+Form("_Z%02d_A%02d",1,2));
    }
    if(i==2 && fileout->Get(Form("%s_Z%02d_A%02d",HistName.c_str(),1,3))==0) {
      printf("Please Draw cut on tritons\n");
      CutName.assign(HistName+Form("_Z%02d_A%02d",1,3));
    }
    if(i==3 && fileout->Get(Form("%s_Z%02d_A%02d",HistName.c_str(),2,3))==0) {
      printf("Please Draw cut on 3He\n");
      CutName.assign(HistName+Form("_Z%02d_A%02d",2,3));
    }
    if(i==4 && fileout->Get(Form("%s_Z%02d_A%02d",HistName.c_str(),2,4))==0) {
      printf("Please Draw cut on 4He\n");
      CutName.assign(HistName+Form("_Z%02d_A%02d",2,4));
    }
    if(i==5 && fileout->Get(Form("%s_Z%02d_A%02d",HistName.c_str(),3,6))==0) {
      continue;
      printf("Please Draw cut on 6Li\n");
      CutName.assign(HistName+Form("_Z%02d_A%02d",3,6));
    }
    if(i==6 && fileout->Get(Form("%s_Z%02d_A%02d",HistName.c_str(),3,7))==0) {
      continue;
      printf("Please Draw cut on 7Li\n");
      CutName.assign(HistName+Form("_Z%02d_A%02d",3,7));
    }
    if(i==7 && fileout->Get(Form("%s_Z%02d_A%02d",HistName.c_str(),4,7))==0) {
      continue;
      printf("Please Draw cut on 7Be\n");
      CutName.assign(HistName+Form("_Z%02d_A%02d",4,7));
    }
    if(fileout->Get(CutName.c_str()) || CutName.empty()) continue; //cut already existing

    hist->Draw("colz");
    gPad->SetLogz(kTRUE);

    TCutG * mycut = (TCutG*)gPad->WaitPrimitive("CUTG");

    mycut->SetName(CutName.c_str());

    printf("%s cut created\n", CutName.c_str());
    printf("S - save the cut\nR - retry\nF - skip this cut\nD - delete a cut\nE - exit\n");
    char input;
    input=getchar();
    getchar();
    printf("you typed %c\n", input);
    if (input=='S' || input=='s') {
      fileout->WriteTObject(mycut, mycut->GetName());
      fileout->WriteTObject(hist, hist->GetName());
      printf ("%s cut saved to file\n", CutName.c_str());
    }
    else if (input == 'R' || input =='r') {
      i--;
    }
    else if (input == 'F' || input == 'f') {
    }
    else if (input == 'D' || input == 'd') {
      printf("Please type the cut to delete: \n");
      std::string CutToDelete;
      std::cin>>CutToDelete;
      CutToDelete.append(";*");
      fileout->Delete(CutToDelete.c_str());
      printf("deleted %s cut\n", CutToDelete.c_str());
      i--;
      std::cin.get();
    }
    else if (input == 'E' || input == 'e'){
      printf("Goodbye\n");
      fileout->Close();
      return;
    }
    else i--;
    }
  }
  fileout->Close();
  return;
}
```

------------------------------------------------------------
### make的时候，出现"未定义的引用"问题
```C++

* 在使用RIBLLDAQ的时候，make的时候，出现"未定义的引用"问题，例如
  //对‘TString::TString(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)’未定义的引用

1. 问题的来源：C++ 版本库不兼容的问题。从GCC5 版本开始，就默认启用C++11. 但是由于C++11相对于C++03很多实现的数据结构都发生了改变，两者不能完全混用

2. 解决办法：
   2.1 如果是在GCC5下使用了非GCC5编译的库，编译时关闭C++11特性
   2.2 在makefile里面增加下面的内容：
       CXXFLAGS= -D_GLIBCXX_USE_CXX11_ABI=0
       将他应用于每一个编译过程！！！

    DAQPC:DIC $(OBJS) VMEDAQPC.o
    $(CPP) -o $@ VMEDAQPC.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs) $(CXXFLAGS)

    ControlPC:DIC $(OBJS) ControlPC.o
    $(CPP) -o ControlPC ControlPC.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs) $(CXXFLAGS)

    OnlinePC:DIC $(OBJS) OnlinePC.o
    $(CPP) -o $@ OnlinePC.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs) $(CXXFLAGS)

    MonOnline:DIC $(OBJS) MonOnline.o
    $(CPP) -o $@ MonOnline.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs) $(CXXFLAGS)

    Raw2ROOT:DIC $(OBJS) Raw2ROOT.o
    $(CPP) -o $@ Raw2ROOT.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs) $(CXXFLAGS)

    ReadRootFile2D:DIC $(OBJS) ReadRootFile2D.o
    $(CPP) -o $@ ReadRootFile2D.o $(OBJS) $(CFLAG) $(ROOTLIB) $(SYSLIB) $(CAENLibs)  $(CXXFLAGS)

    %.o: %.cpp
    $(CPP) -c $(CFLAG) $(CRFLAG) $(CXXFLAGS) -o $@ $<
```

---------------------------------------------------------------
### ROOT 版本问题导致编译出错
```C++
1. ROOT版本问题：在ROOT6版本下，主要问题在于：
   deedict.cxx:163:65: error: ‘DefineBehavior’ was not declared in this scope

2. 在ROOT6中，‘DefineBehavior’等函数定义在命名空间ROOT::Internal中

3. 解决办法：在 deedict.cxx 文件中，加入命名空间：
   using namespace ROOT::Internal;

4. 至此，还可能出现 "未定义的引用" 问题， 解决方法如 Q1 所述。

5. 编译成功！

```

-------------------------------------------------------------
### Error in <TBufferFile::CheckByteCount>: object of class TProtoClass read too many bytes
> 使用 DEEFIT 时, make 成功, 但执行 ./deefit_S 时, 报错
```C++
Error in <TBufferFile::CheckByteCount>: object of class TProtoClass read too many bytes
```

 
