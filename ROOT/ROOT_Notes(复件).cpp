//////////////////////////////////////////////////////////////
//                                                          //
//     ROOT 是粒子物理与核物理数据分析的好工具！！！               //
//                                                          //
//     ROOT的学习不是一朝一夕的事情,需要反复反复再                 //
//     反复使用，才可能较好地掌握它                              //
//     这里是我学习使用ROOT的总结、感悟                          //
//     本文档的出发点是给初学者提供一种学习ROOT的思路              //
//                                                          //
//     如果C++基础好,学习ROOT会很快上手！                       //
//     这里简单介绍ROOT里面几个最常用到的类,                     //
//     以及这些类的基本操作方法                                 //
//     对于一些重要的类,仔细研读源程序会有很大收获！               //
//                                                          //
//     每个类更加详细的介绍请参照下面的链接：                     //
//     新版本： https://root.cern/doc/master/annotated.html  //
//     旧版本： https://root.cern.ch/root/html304/           //
//                                                         //
//    \作者：小关                                            //
//////////////////////////////////////////////////////////////
________________________________________________________________________________
----------
TCanvas
----------
gROOT->GetListOfCanvas()->FindObject("c1");
gROOT->FindObject("c1");


_______________________________________________________________________________
---------
TStyle
---------
gStyle->SetOptFit(kTRUE);  // 显示拟合参数
gStyle->SetPalette(1)；    // To plot with nice colors



________________________________________________________________________________
----------
TSystem
----------
gSystem->Getenv("USER")  // returns the value of the system enviroment variable 'USER'


________________________________________________________________________________
----------
TPad
----------
gPad->SetLogy();     // 设置Log坐标
gPad->Modified();    //
gPad->Update();
gPad->SetLogy(1);    // 设置对数坐标
gPad->SetTicky(1);   // 给坐标轴设置网格
gPad->SetLeftMargin(0.15);  //设置 pad 的偏置

_______________________________________________________________________________
----------
TTree
----------



_______________________________________________________________________________
----------
TFile
----------
TFile * file = new TFile("basic.root");
file->ls();                              // print the contents of the file
TH1F *Hist = (TH1F*)file->Get("h1");     // copy the object "h1" into the memory

_______________________________________________________________________________
-------------
rootlogon.C
-------------
** This script without a function declaration is executed
automatically when ROOT is launched from the same
directory as the file
//////////
{
gStyle->SetPalette(1);
cout << "Salut " << gSystem->Getenv("USER") << "!" << endl;
gSystem->Exec("date");
}
/////////


_______________________________________________________________________________
---------------------
TF1 and data fitting
---------------------
gStyle->SetOptFit(kTRUE);  // 显示拟合参数
hist->Fit("gaus","V","E1",-1,1.5); // Fit("function name","fit options","drawing options",fit limits)

* Use predefined funtion
  (1)"gaus","expo","polN","landau"
  (2)Get the parameters:
     TF1 * gfit = (TF1*)h->GetFunction("gaus");
     gFit->GetParameter(0);
     gFit->GetParameter(1);
     gFit->GetParError(0);
     ......
     double par[3];
     gfit->GetParameter(par);

* Use user-defined function
  // 自定义函数必须初始化才能使用
  (1) Define the function :
  (2) Include it in a TF1 :
  (3) Set parameters  : mw->SetParNames(); mw->SetParameter(1); mv->SetParameters(par);
  (4) Make the fit    :
  (5) Sensitive to the initial values: mw->SetParLimits(0,lowlimit, highlimit);
  (6) Get fit results : mw->GetChisquare();mw->GetNDF() // Number of Degrees of Freedom

* Use mixing functions
  (1) Pre-defined functions : TF1 *fc=new TF1("f5","pol3(0)+[4]*sin(gaus(5)+[8])",0,10)
  (2) User-defined functions:
   /// Sum of 2 Maxwellian functions
    Double_t DeuxMaxwell(Double_t *x, Double_t *par)
   {
     return Maxwell(x,&par[0])+Maxwell(x,&par[3]);
   }
   // 注意！！！！
   // a.使用自定义函数拟合时，拟合结果对参数初始化很敏感
   // b.一般需要给参数设定边界

* Fittting options:
  "Q"   Quite model,终端不输出拟合结果
  "V"   Verbose model, 详细的输出    //(默认的模式介于两者之间)
  "R"   使用函数定义时给定的区间进行拟合 (用于多区间拟合)
  "+"   在不删除前一个函数的情况下，将当前的拟合函数添加到list里面  //(默认情况是只保留最后一个拟合函数)
  "N"   不存储拟合函数，也不画图显示    //(默认情况是既保存又画图)
  "0"   不画出拟合结果
  "LL"  An Improved Log Likelihood fit for low statistics (当Bin content大于100时，不要使用这种方式)


* Set Bounds for Parameters
  func->SetParameter();    // 单独给某一个参数赋初值
  func->SetParameters();   // 同时给所有的参数赋初值
  func->SetParLimits();    // 给某一个参数设定边界
  func->FixParameter();    // 固定某个参数

* Get the associated function
  TF1 *myfunc = h->GetFunction("myfunc");  // 从直方图的拟合函数中提取

* Fit Statistics
  gStyle->SetOptFit(mode)    mode = pcev  (defaul = 0111)
  p=1   打印 probability
  c=1   打印 Chi2/NDF
  e=1   打印 errors (if e=1, v must be 1)
  v=1   打印参数 name/values

* FUMILI Minimization Package:
  (1) To minimize Chi-square function          (ROOT中默认的拟合方式是最小Chi2)
  (2) To search maximum of likelihood function

* 利用神经网络进行数据拟合

________________________________________________________________________________
----------------
TH1 (Histogram)
TH2
TH3
THStack
---------------
* 从已有root文件中读取histogram
  (1)打开root文件  ： TFile * in = new TFile();
  (2)读取需要的hist:  TH1F * h1 = (TH1F*)in->Get();
  // 在root环境: TF1F * h1 = (TH1F*)gROOT->FindObject()

* h1->GetNbinsX();          // get the number of bins in X axis
  h1->GetBinCenter(i);      // get the center of bin NO.i
  h1->GetBinContent(i);     // get the Y value of bin NO.i
  h1->GetEntries();         // get the number of entry

* 直方图有用的成员函数
  (1) 克隆:   TH1F *hist = (TH1F*)h1->Clone();
  (2) 归一化： h->Scale(1./h->Integral());


* 直方图的画图技巧
  hs->GetXaxis()->SetNdivisions(-505);    // 设置坐标值分度值
  h->SetStats(0);     // 关闭直方图右上方显示的box
  h->SetOptStat(0);   //

* 同时画出多个直方图：THStack
  THStack *hs = new THStack("hs","title");
  hs->Add(h1);
  hs->Add(h2);
________________________________________________________________________________
----------
TLegend
----------
* How to add a legend to a figure
  (1)新建一个TLegend: TLegend * legend = new TLegend();
  (2)Fit function linked to the hist: TF1 * fun = hist->GetFunction();
  (3)创建legend内容 :      sprintf(message,"#chi^{2}=%.2f", fun->GetChisquare())
  (4)AddEntry:            legend->AddEntry(fun,message);
  (5)Drawing the TLegend: legend->Draw();



________________________________________________________________________________
---------
TList
---------
TList * list = gPad->GetLIstOfPrimitives(); // List of objects in the current canvas



________________________________________________________________________________
--------
TCutG
--------
*  Int_t TCutG::IsInside(Double_t x, Double_t y) const
   (1)用法:
      if(mycut->IsInside(x,y)==1) // (x,y) is inside the cut region
      if(mycut->IsInside(x,y)==0) // (x,y) is outside the cut region

______________________________________________________________________________________
--------
TMath
-------

______________________________________________________________________________________
--------
TLine
--------

______________________________________________________________________________________
--------
TLatex
--------



______________________________________________________________________________________
----------------
TGraph
TGraph2DErrors
----------------
* I use TGraph2DErrors() to draw data(error value equal to 0), i try to fit
  with TF2 function, error happens: "fill data empty"
  // Reason: Reason: TF2 fit ignore data without an erro
