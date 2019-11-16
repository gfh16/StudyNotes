//////////////////////////////////////////////////////////////
//                                                          //
//     ROOT 是粒子物理与核物理数据分析的好工具！！！        //
//                                                          //
//     ROOT的学习不是一朝一夕的事情,需要反复反复再          // 
//     反复使用，才可能较好地掌握它                         //
//     这里是我学习使用ROOT的总结、感悟                     //
//     本文档的出发点是给初学者提供一种学习ROOT的思路       //     
//                                                          //
//     如果C++基础好,学习ROOT会很快上手！                   //
//     这里简单介绍ROOT里面几个最常用到的类,                //
//     以及这些类的基本操作方法                             //
//     对于一些重要的类,仔细研读源程序会有很大收获！        //
//                                                          //
//     每个类更加详细的介绍请参照下面的链接：               //
//     新版本： https://root.cern/doc/master/annotated.html //
//     旧版本： https://root.cern.ch/root/html304/          //
//                                                          //
//////////////////////////////////////////////////////////////

----------
TCanvas
----------
gROOT->GetListOfCanvas()->FindObject("c1");
gROOT->FindObject("c1");



---------
TStyle
---------

----------
TSystem
----------
gSystem->Getenv("USER")  // returns the value of the system enviroment variable 'USER'

-------
TPad
-------



--------
TTree
-------

--------
TFile
--------
TFile * file = new TFile("basic.root");
file->ls();                              // print the contents of the file
TH1F *Hist = (TH1F*)file->Get("h1");     // copy the object "h1" into the memory


-------------
rootlogon.C
------------
** This script without a function declaration is executed
automatically when ROOT is launched from the same
directory as the file

{
gStyle->SetPalette(1);
cout << "Salut " << gSystem->Getenv("USER") << "!" << endl;
gSystem->Exec("date");
}
























