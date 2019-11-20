#  ROOT 学习笔记
### ROOT 是粒子物理与核物理数据分析的好工具！！！      
> ROOT的学习不是一朝一夕的事情,需要反复反复再反复使用，才可能较好地掌握它.             
这里是我学习使用ROOT的总结、感悟. 本文档的出发点是给初学者提供一种学习ROOT的思路如果C++基础好,学习ROOT会很快上手！这里简单介绍ROOT里面几个
最常用到的类,以及这些类的基本操作方法对于一些重要的类,仔细研读源程序会
有很大收获！              
每个类更加详细的介绍请参照下面的链接：                    
新版本： https://root.cern/doc/master/annotated.html  
旧版本： https://root.cern.ch/root/html304/


>  <font color=#DC143C >一个快速学习ROOT的好方法!!!</font>
> 1. 了解阶段： 大致了解Root常用的Class,知道Root有这个Class,这个Class可以用来做真么
> 2. 善用Tab补全： 当忘记某个Class的用法时，在Root环境下使用Tag键不全可以快速查到  
> 3. 也可以通过Root环境下的Tag不全学习每个Class都有哪些成员函数 
  
作者：小关                                            

[toc]


## rootlogon
* This script without a function declaration is executed automatically when ROOT is launched from the same directory as the file
```C++
{
   gStyle->SetPalette(1);                                      // 使画图颜色更加好看
   cout << "Salut " << gSystem->Getenv("USER") << "!" << endl;
   gSystem->Exec("date");                                      // 显示系统时间日期
}
```

## TCanvas
* TCanvas用法
```C++
gROOT->GetListOfCanvas()->FindObject("c1");  
gROOT->FindObject("c1");
```

## TCutG  
> <font color=#DC143C> Int_t TCutG::IsInside(Double_t x, Double_t y) const  </font>

#### 1. 用法
```C++ 
if(mycut->IsInside(x,y)==1) // (x,y) is inside the cut region
if(mycut->IsInside(x,y)==0) // (x,y) is outside the cut region
```

#### 2. TFile
```C++
TFile * file = new TFile("basic.root");
TH1F  * Hist = (TH1F*)file->Get("h1");    // copy the object "h1" into the memory
```


## TF1 Data Fitting
```C++
 gStyle->SetOptFit(kTRUE);           // 显示拟合参数
 hist->Fit("gaus","V","E1",-1,1.5); 
// Fit("function name","fit options","drawing options",fit limits) 
``` 

#### 1. Use_predefined_funtion
```C++
* Root 中自带的四类拟合函数： "gaus","expo","polN","landau"
* 获取拟合参数
  Get the function: TF1 * gfit = (TF1*)h->GetFunction("gaus");
  Get the parameters:
  gfit->GetParameter(0);
  gfit->GetParameter(1);
  gFit->GetParError(0);
  ......
  double par[3];
  gfit->GetParameter(par);
```


#### 2. Use user-defined function
> 自定义函数必须初始化才能使用
```C++
* Define the function 
* Include it in a TF1 
* Set parameters  : mw->SetParNames(); mw->SetParameter(1); mv->SetParameters(par);
* Make the fit    
* Sensitive to the initial values: mw->SetParLimits(0,lowlimit, highlimit);
* Get fit results : mw->GetChisquare();mw->GetNDF(); // Number of Degrees of Freedom
```


#### 3. Use mixing functions
```C++
* Pre-defined functions : TF1 *fc=new TF1("f5","pol3(0)+[4]*sin(gaus(5)+[8])",0,10)
* User-defined functions: 

    Double_t DeuxMaxwell(Double_t *x, Double_t *par)
    {
      /// Sum of 2 Maxwellian functions
      return Maxwell(x,&par[0])+Maxwell(x,&par[3]); 
    }

注意两点：
a.使用自定义函数拟合时，拟合结果对参数初始化很敏感  
b.一般需要给参数设定边界   
```


#### 4. Fittting options
```C++
* "Q"   Quite model,终端不输出拟合结果
* "V"   Verbose model, 详细的输出    <font color=#DC143C>//(默认的模式介于两者之间) </font>
* "R"   使用函数定义时给定的区间进行拟合 (用于多区间拟合)
* "+"   在不删除前一个函数的情况下，将当前的拟合函数添加到list里面 <font color=#DC143C>     //默认情况是只保留最后一个拟合函数 </font>
* "N"   不存储拟合函数，也不画图显示   <font color=#DC143C  > //(默认情况是既保存又画图) </font>
* "0"   不画出拟合结果
* "LL"  An Improved Log Likelihood fit for low statistics   <font color=#DC143C> //(当Bin content大于100时，不要使用这种方式)</font> 
```


#### 5. Set Bounds for Parameters
```C++
func->SetParameter();    // 单独给某一个参数赋初值
func->SetParameters();   // 同时给所有的参数赋初值
func->SetParLimits();    // 给某一个参数设定边界
func->FixParameter();    // 固定某个参数
```


#### 6. Get the associated function
```C++
* TF1 *myfunc = h->GetFunction("myfunc");  // 从直方图的拟合函数中提取
* Fit Statistics: gStyle->SetOptFit(mode)  mode = pcev (defaul = 0111)
      p=1   打印 probability
      c=1   打印 Chi2/NDF
      e=1   打印 errors (if e=1, v must be 1)
      v=1   打印参数 name/values   
* FUMILI Minimization Package**
  * To minimize Chi-square functio  <font color=#DC143C>   //(ROOT中默认的拟合方式是最小Chi2)  </font>
  * To search maximum of likelihood function
```


#### 7. 利用神经网络进行数据拟合



## TGraph
#### 1. TGraph2DErrors
> I use TGraph2DErrors() to draw data(error value equal to 0), i try to fit with TF2 function, error happens: "fill data empty"  <font color=#DC143C>  // Reason: Reason: TF2 fit ignore data without an error </font>


## THistogram

#### 1. TH1
* 从已有root文件中读取histogram
```C++
 TFile * in = new TFile("文件路径");
 TH1F  * h1 = (TH1F*)in->Get("ObjectName");
 TF1F  * h1 = (TH1F*)gROOT->FindObject("ObjectName"); //在ROOT环境下使用
```

* 创建并保存root文件
```C++
h1->GetNbinsX();          // get the number of bins in X axis
h1->GetBinCenter(i);      // get the center of bin NO.i
h1->GetBinContent(i);     // get the Y value of bin NO.i
h1->GetEntries();         // get the number of entry
```

* 直方图有用的用法
```C++
TH1F *hist = (TH1F*)h1->Clone();  // 克隆一个直方图
h->Scale(1./h->Integral());       // 归一化
```

* 直方图的画图技巧
```C++
hs->GetXaxis()->SetNdivisions(-505);   // 设置坐标值分度值
h->SetStats(0);                        // 关闭直方图右上方显示的box
h->SetOptStat(0);                      //
```



#### 2. TH2


#### 3. THStack

* 同时画出多个直方图：THStack
```C++
THStack *hs = new THStack("hs","title");
hs->Add(h1);
hs->Add(h2);
```


## TLatex


## TLegend

* How to add a legend to a figure
```C++
* 新建一个TLegend: TLegend * legend = new TLegend();
* Fit function linked to the hist: TF1 * fun = hist->GetFunction();
* 创建legend内容 :      sprintf(message,"#chi^{2}=%.2f", fun->GetChisquare())
* AddEntry:            legend->AddEntry(fun,message);
* Drawing the TLegend: legend->Draw();
```


## TLine



## TList
```C++
TList * list = gPad->GetLIstOfPrimitives();   // List of objects in the current canvas
```


## TMath



## TPad

* TPad的有用用法
```C++
gPad->SetLogy();            // 设置Log坐标
gPad->Modified();           //
gPad->Update();
gPad->SetLogy(1);           // 设置对数坐标
gPad->SetTicky(1);          // 给坐标轴设置网格
gPad->SetLeftMargin(0.15);  //设置 pad 的偏置
```



## TStyle
```C++
gStyle->SetOptFit(kTRUE);  // 显示拟合参数
gStyle->SetPalette(1)；    // To plot with nice colors
```


## TSystem
```C++
gSystem->Getenv("USER")  // returns the value of the system enviroment variable 'USER' 
```


## TTree









































