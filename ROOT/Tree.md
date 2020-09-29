
[toc]

&emsp;
### <font color=#00BFFF> 2.4 Trees 树  </font>

#### <font color=#FF00FF>  2.4.1 什么是 Tree ? 为什么使用 Tree ? </font>
+ **ROOT 的数据存储方式** 
  >+ 当需要存储大量类型相同的数据时, ROOT 提供了 **TTree** 与 **TNtuple** 两种方式.
  >+ TTree 方式的特点是: 1)占据磁盘空间小, 2)读取速度快, 3)可以存储所有数据类型.
  >+ TNtuple 方式的特点: TNtuple 是一种特殊的 TTree, 它仅支持浮点型数据.

+ **Tree 的特点** 
  >+ TTree 的要素: branches, buffers, leafs.
  >+ When using a TTree, we fill its branch buffers with leaf data and the buffers are written to disk when it is full.
  >+ Each object is not written individually, but rather collected and written a bunch at a time.
  >+ TTree will produce a much smaller file than if the objects were written individually, since it contains many same-class objects, and the header of the objects can be compressed.

+ **TTree 特点解析**
  >+ <font color=#DC143C>  Compression. 占据磁盘空间小.</font> TTree redues the header of each object. However, the compression can be turned off. If so, we will not see these large savings.
  >+ <font color=#DC143C>  Optimize the data access. 读取速度快.</font> Tree 使用分层的 Branch 结构存储数据, 每个 Branch 可以与其他分开单独读取.

+ **TTree 特点举例说明**
  >+ 考虑 100万个事件. 每个事件 event 中, $P_X, P_Y$ 是其中两个数据成员. 对于每个事件, 现在需要计算 $P_X^2 + P_Y^2$, 并将结果填充为直方图. 
  >+ 如果没有 TTree, 我们将需要这样做:
     (1) 读取每个完整的 event
     (2) 从每个 event 中提取 $P_X, P_Y$
     (3) 计算 $P_X^2 + P_Y^2$
     (4) 填充直方图
  这样的整套操作需要进行 100 万次！
  >+ 以上的方法之所以很耗时, 主要是因为每次都要读取完整的事件! 但这实际上没有必要, 因为我们只需要其中的 $P_X, P_Y$.
  >+ TTree 的魅力所在, 是因为它提供了利用分支(Branch)存储数据的方法:
     (1) 使用 TTree, 将 $P_X, P_Y$ 存成两个不同的 Branch.
     (2) 每个事件, 我们只需要读取 $P_X, P_Y$ 这两个 Branch 即可.

+ **Tree 的数据结构**
![The TTree class](ROOT/pictures/030000F8.png)


&emsp;
#### <font color=#FF00FF>  2.4.2 查看 Tree 的基本信息 </font>

+ **TTree::Show**  
用于显示第 num 个事件的数据信息.
```C++
// 例如, 显示 staff.root 中的第 10 个事件
root[] TFile f("staff.root")
root[] f.ls()  // 查看 Tree name
root[] T->Show(10)
======> EVENT:10
 Category        = 361
 Flag            = 15
 Age             = 51
 Service         = 29
 Children        = 0
 Grade           = 7
 Step            = 13
 Hrweek          = 40
 Cost            = 7599
 Division        = PS
 Nation          = FR
```

+ **TTree::Print** 
  很有用！用于显示 tree 的结构, 包括事件的成员, branch, leaves, 和数据类型等.
```C++
// 举例
root[] T->Print()
**********************************************************************
*Tree    :T         : staff data from ascii file                     *
*Entries :3354      : Total = 245417 bytes  File  Size =        59945*
*                     Tree compression factor =   2.90               *
**********************************************************************
*Br    0 :staff     :Category/I:Flag:Age:Service:Children:Grade:...  *
*         | Cost                                                     *
*Entries :3354 : Total Size  = 154237 bytes  File Size = 32316       *
*Baskets :   3 : Basket Size =  32000 bytes  Compression= 2.97       *
```


+ **TTree::Scan** 
  用于显示选定的 leaves

```C++
//_______________________________________________________________
// root[] tree->Scan() // print the first 8 variables of the tree 
// 
root[] T->Scan("Cost:Age:Children")
************************************************
*    Row   *      Cost *       Age *  Children *
************************************************
*        0 *     11975 *        58 *         0 *
*        1 *     10228 *        63 *         0 *
*        2 *     10730 *        56 *         2 *
*        3 *      9311 *        61 *         0 *
*        4 *      9966 *        52 *         2 *
*        5 *      7599 *        60 *         0 *
*        6 *      9868 *        53 *         1 *
*        7 *      8012 *        60 *         1 *
...

//__________________________________________________
// root[] tree->Scan("var1:var2","selection")
tree->Scan("var1:var2:var3", "var1 == 0");
```


+ **Tree Viewer** 
  tree viewer 是个快速查看 tree 的方法

```C++
// 方式1: 先打开一个 .root 文件
root[] TFile f("staff.root");
root[] T->StartViewer()

// 方式2: 打开一个空的 tree viewer
root[] gSystem->Load("libTreeViewer.so); 
root[] new TTreeViewer()
```


&emsp;
#### <font color=#FF00FF>  2.4.3 Tree Branch 的存储对象 </font>
>+ The organization of branches allows the designer to optimize the data for anticipated use.
>+ Branch 的设置原则: 
   (1) 当两个变量相互独立，且不一起使用时, 应该将他们放在不同的 Branch. 
   (2) 当两个变量相互关联, 比如一个点的两个坐标, 最高效的方式是将它们放在同一个 Branch.
>+ TBranch 的变量称为 "leaf"
>+ 同一个 TTree 的不同 Branch, 可以写在不同的文件中
>+ 添加一个 Branch， 通常使用 TTree::Branch() 方法. 一般不使用 TBranch 来构造.
>+ Branch 的存储对象可以是:
   (1) A list of simple variables
   (2) An entire object
   (3) An array of objects
   (4) Contents of a folder
   (5) Contents of a TList


+ **Adding a Branch to Hold a List of Variables**
>+ 数据类型符号表示:
   C : a character string terminated by the 0 character
   B : an 8 bit signed integer
   b : an 8 bit unsigned integer
   S : a 16 bit signed integer
   s : a 16 bit unsigned integer
   I : a 32 bit signed integer
   i : a 32 bit unsigned integer
   L : a 64 bit signed integer
   l : a 64 bit unsigned integer
   F : a 32 bit floating point
   D : a 64 bit floating point
   O : [the letter 'O', not a zero] a boolean (Bool_t)

```C++
// 1.使用结构体, 包含多个变量
tree->Branch("Ev_Branch",&event,"temp/F:ntrack/I:nseg:nvtex:flag/i");
 
/*
// *第一个参数是 branch name 
// *第二个参数是 branch 的第一个变量的地址. 这里 event 是一个结构体
// *第三个参数是 leaf 列表, 每个 leaf 格式为: leaf 名字/类型, 两个 leaf 由冒号 ":" 隔开.

说明1: To avoid alignment problems, we need to use structures 
      with same length member.
说明2: If the structure does not qualify, we need to create
      one branch for each of the structire.
说明3: The leaf name is not used to pick the variable out of the 
      structure, but is only used as the name for the leaf.
说明4: structure 中的变量要与 leaf 裂变中的顺序一致.
说明5: The type can be omitted if no type is given, the same 
      type as the previous variable is assumed.
说明6: When no type is given for the very first leaf, it becomes
      a float (F).
*/


// 2.使用固定长度的数组 
Float_t f[10];
tree->Branch("fBranch",f, "f[10]/F");


// 3.使用变长度的数组
{
  Int_t nPhot;
  Float_t E[500];
  TTree* nEmcPhotos = new TTree("nEmcPhotons", "EMC Photons");
  nEmcPhotos->Branch("nPhot", &nPhot, "nPhot/I");
  nEmcPhotos->Branch("E", E, "E[nPhot]/F");
}
```

+ **Adding a TBranch to Hold an Object**

```C++
// To add a branch to hold an object
TTree* tree  = new TTree("T", "A Root Tree");
Event* event = new Event();
tree->Branch("EventBranch","Event",&event,32000,99);

/*
// "EventBranch" : branch name
// "Event" : the name of the class of the object to be stored
// &event  : the address of a pointer to the object to be stored
             (这是指针的地址, 不仅仅是一个指针, 因此需要加 "&")
// 32000 : buffer size, by default 32000 bytes. (详见2.4.4)
// 99 : split-level (详见2.4.4)
*/
```


+ **Adding a Branch to Hold a TCloneArray**
>+ ROOT has two classes to manage arrays of objects.
>+ TObjArray : manage objects of different classes
>+ TClonesArray : manage objects of the same class


+ **Adding a Branch with a Folder**
```C++
// To add a branch from a folder
// This method creates one branch for each element in the folder.
tree->Branch("/aFolder");


// 1. An alternative way to create a tree and organize it is to use folders.
// 2. You can build a folder structure and create a tree with branches for 
//    each of the sub-folders
// 3. The second argument "/MyFolder" is the top folder, and the "/" signals the 
//    TTree constructor that this is a folder not just the title。

TTree folder_tree("MyFolderTree","/MyFolder");
```


+ **Adding a Branch with a  Collection**
>+ 略


+ **Identical Branch Names**
>+ When a top-level object has two data members of the same class, 
  the sub branches end up with identical names.
>+ To distinguish the sub branch, we must associate them with the master branch
by including a "." (a dot) at the end of the master. This will force the name of sub branch to be master.sub branch instead of simply sub branch.

```C++
// To identify uniquely the sub branches we add the dot
tree->Branch("Trigger", "Trigger", &b1, 8000, 1);
tree->Branch("MuonTrigger", "Trigger", &b2, 8000, 1);

// if Trigger has three members T1, T2, T3
// the sub branch above:
// Trigger.T1, Trigger.T2, Trigger.T3
// MuonTrigger.T1, MuonTrigger.T2, MuonTrigger.T3
```
 

&emsp;
#### <font color=#FF00FF>  2.4.4 Splittng a Branch </font>
>+ To split a branch means to create a sub-branch for each data member in the object
>+ split-level = 0 - 99, indicating the depth of splitting
>+ split-level = 0, to disable splitting, means the whole object is written to one branch
>+ split-level = 1, an object data member is assigned a branch
>+ split-level = 2, the data member objects will be split also
>+ slpit-level = 3, ..., etc.
>+ As the split-level increases so does the splitting depth.
>+ The ROOT default split-level is 99, means the object will be split to the maximum.

+ **Splitting a Branch 时的内存考虑**
  >+ S.plitting a branch can quickly generate many branches, each branch has its own buffer in memory
  >+ 推荐使用的 Branch 内存大小：
  (1) 小于 50 个 branches : 推荐内存大小 32000 (bytes)
  (2) 小于 100 个 branches: 推荐内存大小 16000 (bytes)
  (3) 大于 500 个 branches: 推荐内存大小 4000  (bytes)
  以上推荐值适用于电脑内存为 32MB - 256MeV. 如果电脑内存较大, 可以给 branch 分配更大的内存. 但需要注意不同机器内存大小的兼容性.

+ **Splitting a Branch 时的性能考虑**
  >+ A split branch is faster to read, but slightly slower to write.

+ **Splitting 的规则**
  >+ If a data member is a basic type, it becomes one branch of class TBranchElement
  >+ A data member can be an array of basic types. In this case, 
     one single branch is created for the array
  >+ A data member can be a pointer to an array of basic types. The length can vary, 
     and must be specified in the comment field of the data member in the class definition.
  >+ Pointer data member are not split, except for pointers to a TCloneArray.
  >+ If a data member is an object, the data member of this object are split into branches according to the split-level.
  >+ C-structure data members are not supported in split mode.



&emsp;
#### <font color=#FF00FF>  2.4.5 Tree 的多种创建方式</font>
>+ Tree 的创建步骤:
   (1) 创建 .root 文件
   (2) 创建 TTree
   (3) 定义变量 (并初始化,推荐！)
   (4) 添加 Branch
   (5) TTree 填充
   (6) TTree 写入
>+ 根据 Branch 的创建方式不同, Tree 可以有多种创建方式.
 
+ **创建最基本的 Tree**
```C++
// 参考程序: $ROOTSYS/tutorials/tree/tree1.C
//________________________________________
void tree1w()
{
  TFile f ("tree1.root", "RECREATE");  // step1. 创建 .root 文件
  TTree t1("t1","a simple Tree");      // step2. 创建 Tree

  Float_t      px = 0.;                // step3. 定义变量
  Float_t      py = 0.;
  Float_t      pz = 0.;                 
  Double_t random = 0.;
  Int_t        ev = 0;

  t1.Branch("px", &px, "px/F");        // step4. 添加 Branch
  t1.Branch("py", &py, "py/F");
  t1.Branch("pz", &pz, "pz/F");
  t1.Branch("ev", &ev, "ev/I");

  for (Int_t i=0; i<10000; i++)
  {
    gRandom->Rannor(px,py);
    pz = px*px + py*py;
    random = gRandom->Rndm();
    ev = i;
    t1.Fill();                         // step5. Tree 填充
  }
  t1.write();                          // step6. Tree 写入
}

```


+ **A Tree with a C Structure**
>+ How to build branches from a C structure
>+ How to make a branch with a fixed length array
>+ How to make a branch with a variable length array
>+ How to read selective branches
>+ How to fill a histogram from a branch

```C++
// 参考脚本: $ROOTSYS/tutorials/tree/staff.C
//_________________________________________
{
  struct staff_t 
  {
    Int_t cat;
    Int_t division;
    Int_t flag;
    Int_t age;
    Int_t service;
    Int_t children;
    Int_t grade;
    Int_t step;
    Int_t nation;
    Int_t hrweek;
    Int_t cost;
  };
   staff_t staff;
   TFile *f = new TFile("staff.root","RECREATE");
   TTree *tree = new TTree("T","staff data from ascii file");
   tree->Branch("staff",&staff.cat,"cat/I:division:flag:age:service:children:grade:step:
                 nation:hrweek:cost");
   // staff : branch name
   // &staff.cat(或者 &staff): the address from which the first leaf to be read.
   //     here it is the address of the structure staff.
   // 第三组参数: leaf 的名字/数据类型. 前一个数据类型, 一直生效, 直到
   //     遇到下一个数据类型才停止
}


// 参考程序: $ROOTSYS/tutorials/tree/tree2.C
//__________________________________________
const Int_t MAXMEC = 30;
typedef struct {
   Float_t  vect[7];
   Float_t  getot;
   Float_t  gekin;
   Float_t  vout[7];
   Int_t    nmec;
   Int_t    lmec[MAXMEC];
   Int_t    namec[MAXMEC];
   Int_t    nstep;
   Int_t    pid;
   Float_t  destep;
   Float_t  destel;
   Float_t  safety;
   Float_t  sleng;
   Float_t  step;
   Float_t  snext;
   Float_t  sfield;
   Float_t  tofg;
   Float_t  gekrat;
   Float_t  upwght;
} Gctrak_t;


//__________________
void tree2w() {
   // write tree2 example
   //create a Tree file tree2.root
   TFile f("tree2.root","recreate");

   //create the file, the Tree
   TTree t2("t2","a Tree with data from a fake Geant3");
   // declare a variable of the C structure type
   Gctrak_t gstep;

   // add the branches for a subset of gstep
   t2.Branch("vect",gstep.vect,"vect[7]/F");
   t2.Branch("getot",&gstep.getot,"getot/F");
   t2.Branch("gekin",&gstep.gekin,"gekin/F");
   t2.Branch("nmec",&gstep.nmec,"nmec/I");
   t2.Branch("lmec",gstep.lmec,"lmec[nmec]/I");
   t2.Branch("destep",&gstep.destep,"destep/F");
   t2.Branch("pid",&gstep.pid,"pid/I");

}

//_________________________
// Branch 为固定长度的数组
// gstep.vect 不需要加 “&”
 t2.Branch("vect",gstep.vect,"vect[7]/F"); 

//________________________
// Branch 为变长度的数组
t2.Branch("nmec",&gstep.nmec,"nmec/I");
t2.Branch("lmec",gstep.lmec,"lmec[nmec]/I");

```



+ **Adding Friends to Trees**
>+ 有时候我们需要对已有的 Tree 添加新的 Branch. ROOT 里面有两种方法添加.
>+ 方法1: 添加新的 Branch - 填充 - 写入. 但是这种方法需要对文件有可写权限, 
   同时存在损坏原有 Tree 数据的风险. 不推荐使用！
>+ TTree::AddFriend 方法. 该方法的好处是不用冒损坏原有数据的风险.

```C++
// 参考程序: $ROOTSYS/tutorials/tree/tree3.C

//_____________________________
// Tree::AddFriend() 方法
// 两个参数: 参数一是friend tree name，参数二是 friend tree 所在文件
// 如果不指定文件, 则 ft1 默认与原有 Tree 在同一个文件
// Friend Tree 的 entries 必须小于等于 原有 Tree 的 entries
tree.AddFriend("ft1","friendfile1.root");


//___________________________
// 程序举例
void tree3w() 
{
   const Int_t kMaxTrack = 500;
   Int_t ntrack;
   Int_t stat[kMaxTrack];
   Int_t sign[kMaxTrack];
   Float_t px[kMaxTrack];
   Float_t py[kMaxTrack];
   Float_t pz[kMaxTrack];
   Float_t pt[kMaxTrack];
   Float_t zv[kMaxTrack];
   Float_t chi2[kMaxTrack];
   Double_t sumstat;

   // create the first root file with a tree
   TFile f("tree3.root","recreate");
   TTree *t3 = new TTree("t3","Reconst ntuple");
   t3->Branch("ntrack",&ntrack,"ntrack/I");
   t3->Branch("stat",stat,"stat[ntrack]/I");
   t3->Branch("sign",sign,"sign[ntrack]/I");
   t3->Branch("px",px,"px[ntrack]/F");
   t3->Branch("py",py,"py[ntrack]/F");
   t3->Branch("pz",pz,"pz[ntrack]/F");
   t3->Branch("zv",zv,"zv[ntrack]/F");
   t3->Branch("chi2",chi2,"chi2[ntrack]/F");

   // create the second root file with a different tree
   TFile fr("tree3f.root","recreate");
   TTree *t3f = new TTree("t3f","a friend Tree");
   t3f->Branch("ntrack",&ntrack,"ntrack/I");
   t3f->Branch("sumstat",&sumstat,"sumstat/D");
   t3f->Branch("pt",pt,"pt[ntrack]/F");

   // Fill the trees
   for (Int_t i=0;i<1000;i++) {
      Int_t nt = gRandom->Rndm()*(kMaxTrack-1);
      ntrack = nt;
      sumstat = 0;
      // set the values in each track
      for (Int_t n=0;n<nt;n++) {
         stat[n] = n%3;
         sign[n] = i%2;
         px[n]   = gRandom->Gaus(0,1);
         py[n]   = gRandom->Gaus(0,2);
         pz[n]   = gRandom->Gaus(10,5);
         zv[n]   = gRandom->Gaus(100,2);
         chi2[n] = gRandom->Gaus(0,.01);
         sumstat += chi2[n];
         pt[n]   = TMath::Sqrt(px[n]*px[n] + py[n]*py[n]);
      }
      t3->Fill();
      t3f->Fill();
   }
   // Write the two files
   t3->Print();
   f.cd();
   t3->Write();
   fr.cd();
   t3f->Write();
}

// Function to read the two files and add the friend
void tree3r()         
{
   TFile *f = new TFile("tree3.root");
   TTree *t3 = (TTree*)f->Get("t3");
   t3->AddFriend("t3f","tree3f.root");
   t3->Draw("pz","pt>3");
}

void tree3() {
   tree3w();
   tree3r();
}

```



+ **A Tree with a Class**
>+ Show the difference in splitting or not splitting a branch
>+ At the TreeViewer: the branch split expands when clicked on, the branch not 
   split is not expandable.

```C++
// 参考程序: $ROOTSYS/tutorials/tree/tree4.C
//_________________________________________
// The Event Class
class Event : public TObject {
   private:
      char                 fType[20];
      Int_t                fNtrack;
      Int_t                fNseg;
      Int_t                fNvertex;
      UInt_t               fFlag;
      Float_t              fTemperature;
      EventHeader          fEvtHdr;
      TClonesArray        *fTracks;            //->
      TH1F                *fH;                 //->
      Int_t                fMeasures[10];
      Float_t              fMatrix[4][4];
      Float_t             *fClosestDistance;   //[fNvertex]
      static TClonesArray *fgTracks;
      static TH1F         *fgHist;
      // ... list of methods
      ClassDef(Event,1)  //Event structure
};

//_______________________________________
// The EventHeader Class
class EventHeader {
   private:
      Int_t   fEvtNum;
      Int_t   fRun;
      Int_t   fDate;
      // ... list of methods
      ClassDef(EventHeader,1)      //Event Header
};

//______________________________________
// The Track Class
class Track : public TObject {
   private:
      Float_t   fPx;         //X component of the momentum
      Float_t   fPy;         //Y component of the momentum
      Float_t   fPz;         //Z component of the momentum
      Float_t   fRandom;     //A random track quantity
      Float_t   fMass2;      //The mass square of this particle
      Float_t   fBx;         //X intercept at the vertex
      Float_t   fBy;         //Y intercept at the vertex
      Float_t   fMeanCharge; //Mean charge deposition of all hits
      Float_t   fXfirst;     //X coordinate of the first point
      Float_t   fXlast;      //X coordinate of the last point
      Float_t   fYfirst;     //Y coordinate of the first point
      Float_t   fYlast;      //Y coordinate of the last point
      Float_t   fZfirst;     //Z coordinate of the first point
      Float_t   fZlast;      //Z coordinate of the last point
      Float_t   fCharge;     //Charge of this track
      Float_t   fVertex[3];  //Track vertex position
      Int_t     fNpoint;     //Number of points for this track
      Short_t   fValid;      //Validity criterion

      // method definitions ...
      ClassDef(Track,1)          //A track segment
};


//_________________________________________________
void tree4w() {
   if (!TClassTable::GetDict("Event")) {
      gSystem->Load("$ROOTSYS/test/libEvent.so");
   }

   TFile f("tree4.root","RECREATE");
   TTree t4("t4","A Tree with Events");
   Event *event = new Event();
   t4.Branch("event_branch", "Event", &event,16000,2);
   t4.Branch("event_not_split", "Event", &event,16000,0);

   // a local variable for the event type
   char etype[20];

   // fill the tree
   for (Int_t ev = 0; ev <100; ev++) {
      Float_t sigmat, sigmas;
      gRandom->Rannor(sigmat,sigmas);
      Int_t ntrack   = Int_t(600 + 600 *sigmat/120.);
      Float_t random = gRandom->Rndm(1);
      sprintf(etype,"type%d",ev%5);
      event->SetType(etype);
      event->SetHeader(ev, 200, 960312, random);
      event->SetNseg(Int_t(10*ntrack+20*sigmas));
      event->SetNvertex(Int_t(1+20*gRandom->Rndm()));
      event->SetFlag(UInt_t(random+0.5));
      event->SetTemperature(random+20.);
      for(UChar_t m = 0; m < 10; m++) {
         event->SetMeasure(m, Int_t(gRandom->Gaus(m,m+1)));
      }
                                       // continued...
      // fill the matrix
      for(UChar_t i0 = 0; i0 < 4; i0++) {
         for(UChar_t i1 = 0; i1 < 4; i1++) {
            event->SetMatrix(i0,i1,gRandom->Gaus(i0*i1,1));
         }
      }
      // create and fill the Track objects
      for (Int_t t = 0; t < ntrack; t++) event->AddTrack(random);
      t4.Fill();      // Fill the tree
      event->Clear(); // Clear before reloading event
   }
   f.Write();            // Write the file header
   t4.Print();           // Print the tree contents
}
```


+ **导入文本文件存成 Tree**
```C++
// 使用 TTree::ReadFile 方法
// Long64_t TTree::ReadFile(const char* filename, 
//                          const char* branchDescriptor)
//______________________________________________________
{
   gROOT->Reset();
   TFile *f  = new TFile("basic2.root","RECREATE");
   TH1F  *h1 = new TH1F("h1","x distribution",100,-4,4);
   TTree *T  = new TTree("ntuple","data from ascii file");
   Long64_t nlines = T->ReadFile("basic.dat","x:y:z");
   printf(" found %lld pointsn",nlines);
   T->Draw("x","z>2");
   T->Write();
}

/*
说明1: 如果不指定 'branchDescriptor', 则文本文件第一行需要有类似这样的字样:
      A/D : Table[2]/F:Ntracks/I:astring/C
说明2: 因此推荐使用 'branchDescriptor'. 如 "x:y:z"
说明3: 忽略以 "#" 开头的行
*/
```



&emsp;
#### <font color=#FF00FF>  2.4.6 Tree 的读取</font>
>+ Tree 的读取步骤
   (1) 打开 .root 文件
   (2) 读取 .root 文件中的 Tree
   (3) 定义变量
   (4) SetBranchAddress
   (5) 获取总 entry数
   (6) 逐个 entry 读取数据 

+ **Tree 读取的基本步骤**
```C++
// 参考程序: $ROOTSYS/tutorials/tree/tree1.C
//________________________________________
void tree1r()
{
   TFile* f  = new TFile("tree1.root");      // step1. 打开文件
   TTree* t1 = (TTree*)f->Get("t1");         // step2. 读取 Tree

   Float_t px, py, pz;                       // step3. 定义变量
   Double_t random;
   Int_t ev;

   t1->SetBranchAddress("px",&px);           // step4. SetBranchAddress
   t1->SetBranchAddress("py",&py);
   t1->SetBranchAddress("pz",&pz);
   t1->SetBranchAddress("random",&random);
   t1->SetBranchAddress("ev",&ev);

   TH1F* hpx   = new TH1F("hpx","px distribution",100,-3,3);
   TH2F* hpxpy = new TH2F("hpxpy","py vs px",30,-3,3,30,-3,3);

   Long64_t nentries = t1->GetEntries();    // step5. 获取总 entry 数
   for (Long64_t i=0;i<nentries;i++) {     
     t1->GetEntry(i);                       // step6. 逐个 entry 读取数据 
     hpx->Fill(px);
     hpxpy->Fill(px,py);
  }
}
```


+ **GetEntry 的不同方式**
>+ Once the branches have been given the address, a specific entry can be read into variables with method TTree::GetEntery(n).

```C++
// 方式1: 这是默认的, 也是推荐使用的方式
//_______________________________________
Event* event = 0; // event must be initialized
T->SetBranchAddress("event",&event);

Long64_t nentries = t1->GetEntries();
for (Int_t i=0; i<nentries; i++)
{
  t1->GetEntry(i);
  // the object event has been filled at this point
}


// 方式2: the option AutoDelete is set
//______________________________________
// At any iteration, the GetEntry deletes the object event and a new
// instance of Event is created and filled. 
TBranch* branch = T->GetBranch("event");
branch->SetAddress(&event);
branch->SetAutoDelete(kTRUE);
for (Int_t i=0; i<nentries; i++)
{
  T->GetEntry(i);
  // the object event has been filled at this point
}


// 方式3: 与方式1一样, 不过需要手动delete
//___________________________________
for (Int_t i=0; i<nentries; i++)
{
  delete event;
  event = 0;  //Extremely Important!
  T->GetEntry(i);
  // the object event has been filled at this point
}

```


+ **读取某些特定的 Branch**
```C++
// 数据分析时, 我们有时候没有必要读取一个 Tree 的全部 Branch,这样更加高效.

//_____________________________________________
// 方式1: branch->SetBranchStatus("*",false);
// 先关闭所有的 branch, 然后通过 SetBranchAddress() 方式打开特定的 branch
myData->SetBranchStatus("*",false);
myData->SetBranchStatus("SSD1_L1S_E",true);
myData->SetBranchAddress("SSD1_L1S_E",SSD1_L1S_E);


//___________________________________________
// 方式2: TBranch 方法
TFile* f  = new TFile("tree.root");
TTree* t2 = (TTree*)f->Get("t2");
static Float_t destep;
TBranch* b_destep = t2->GetBranch("destep");
b_destep->SetAddress(&destep); 

Int_t nentries = (Int_t)t2->GetEntries();
for (Int_t i=0; i<nentries; i++)
{
  b_destep->GetEntry(i);
  ...
}
```


+ **TTreeReader - ROOT6 中读取 Tree 的新方法**
```C++
//_______________________________________________
void TreeReaderSimple() 
{
  TH1F*  myHist = new TH1F("h1","ntuple",100,-4,4);
  TFile* myFile = TFile::Open("hsimple.root");

  TTreeReader myReader("ntuple", myFile);
  TTreeReaderValue<Float_t> myPx(myReader, "px");
  TTreeReaderValue<Float_t> myPy(myReader, "py");
   while (myReader.Next()) {
      myHist->Fill(*myPx + *myPy);
   }
   myHist->Draw();
}
```



&emsp;
#### <font color=#FF00FF>  2.4.7 TChain </font>
>+ A TChain object is a list of ROOT files containing the same tree.

+ **TChain 的用法**
```C++
// TChain 用法举例
//_____________________
{
   TChain chain("T"); 
   chain.Add("file1.root"); 
   chain.Add("file2.root");
   chain.Add("file3.root");
   TH1F *hnseg = new TH1F("hnseg",
                          "Number of segments for selected tracks",
                          5000,0,5000);
   Event *event = new Event();
   chain.SetBranchAddress("event", &event);

   // Start main loop on all events In case you want to read only a few
   // branches, use TChain::SetBranchStatus to activate a branch.
   Int_t nevent = chain.GetEntries();
   for (Int_t i=0;i<nevent;i++) {

      chain.GetEvent(i);
      hnseg->Fill(event->GetNseg());
   }
   hnseg->Draw();
}

```


+ **TChain::AddFriend**
```C++
// The original chain has access to all variables in its friends
TChain ch("t");
TChain ch1("t1");
TChain ch2("t2");
TChain ch3("t3");

ch.AddFriend("t1");
ch.AddFriend("t2");
ch.AddFriend("t3");
```

+ **文件合并**
```C++
// ROOT files containing the same data objects(e.g. histograms, Trees, etc...) 
// can be merged using line tool $ROOTSYS/bin/hadd
root[] hadd fileOut.root file1.root file2.root file3.root

```



&emsp;
#### <font color=#FF00FF>  2.4.8 Data Analysis - Tree::Draw </font>
>+ The TTree::Draw method is powerful yet look and draw the tree contents. 
It enables us to plot a variable (a leaf) with just one line of code.
>+ The TTree::MakeClass creates a class that loops over the trees entries one by one.
>+ The TTree::MakeSelector is the recommended method for ROOT data analysis. 
It is especially important for large data set in parallel processing.
>+ With MakeClass the user has control over the event loop, with MakeSelector the 
tree is in control of event loop. 
```C++
// TTree::Draw 的参数
Long64_t Draw(const char* varexp, const TCut& selection, 
              Option_t* option = "", 
              Long64_t nentries = kMaxEntries, 
              Long64_t firstentry = 0)
```

+ **TTree::Draw 参数之 "varxep(变量表达式)"**
```C++
// TTree::Draw 最基本的用法
MyTree->Draw("Age");       // Age 是 MyTree 的一个变量 (leaf)
MyTree->Draw("Cost:Age");  // 2D histogram Cost vs. Age
MyTree->Draw("e1:e2:e3");  // 最多可以到 3D histogram
```

+ **Using Selection with TTree::Draw**
```C++
MyTree->Draw("Cost:Age","Nation == "FR"");

//_________________________________
// We can use any C++ operator, and some functions defined in TFormula,
// in the selection parameter.
// If the boolean result is true, the histogram is filled with a weight.
// If the weight is not explicity
Selection = "weight *(boolean expression)"

// Add 1 to the histogram if x is less than y and sqrt(z)>3.2
"x<y && sqrt(z)>3.2"

// Add x+y to the histogram if sqrt(z)>3.2
"(x+y)*(sqrt(z)>3.2)"
```

+ **TTree::Draw 参数之 "TCut"**
```C++
root[] TCut c1 = "x<1"
root[] TCut c2 = "y<0"
root[] TCut c3 = c1 && c2;
root[] MyTree.Draw("x", c1);
root[] MyTree.Draw("x", c1 || "x>0");
root[] myTree.Draw("x", c1 && c2);
```

+ **TTree::Draw 参数之 "Draw Option"**
```C++
// The draw options are the same as for TH1::Draw.
root[] MyTree->Draw("Cost:Age", "Nation == \"FR\"", "SURF2");
```

+ **TTree::Draw 参数之 "Setting the Range"**
```C++
// There are two parameters to set the range.
// One is the number of entriess
// The second is the entry to start with
// This command draws 1000 entries starting with entry 100.
MyTree->Draw("Cost:Age","","",1000,100);
```

+ **From TTree::Draw to Histogram**
```C++
// 方法1: gPad->GetPrimitive();
//______________________________________
// The TTree::Draw method creates a histogram called 'htemp' 
// and puts it on the active pad.
nt->Draw("x", "cuts");
TH1F* htemp = (TH1F*)gPad->GetPrimitive("htemp");


// 方法2: 
nt->Draw("x>>hnew","cuts");
TH1F* hnew = (TH1F*)gDirectory->Get("hnew");
// TH1F* hnew = (TH1F*)gPad->GetPrimitive("hnew");
```

+ **Superimposing Two Histograms**
```C++
{
   TH2 *h2 = new TH2D ("h2","2D histo",100,0,70,100,0,20000);
   for (Int_t i = 0; i < 10000; i++)
   {
     h2->Fill(gRandom->Gaus(40,10),gRandom->Gaus(10000,3000));
   }
   h2->SetMarkerColor(kGreen);
   h2->Draw();

   TFile f("staff.root");
   TTree *myTree = (TTree*)f.Get("T");
   gPad->Update(); // Need to update the pad between Draw commands
   myTree->Draw("Cost:Age", "","same");
}
```

+ **TTree::Draw Examples**
  >+ 略. 详细介绍见 "ROOT User Guide"


+ **Multiple Variables Visualisation - Spider (Radar) Plots**
  >+ Used to represent multiple variables(>4) data sets.
  >+ Variables are respresented on individual axes displayed along a circle.
  >+ The minimum value sits on the circle's center, and the maximum on the circle's radius.
  >+ Spider plots are not suitable for an accurate graph, since it can be diffficult to read out
  very details values, but they give quickly a global view of an event in order to compare
  with others.
![Spider Plot](ROOT/pictures/spider2.png)


+ **Multiple Variables Visualisation - Parallel Coordinates Plots**
  >+ The Parallel Coordinates Plots are a commom way of studying and visualizing 
  multiple variables data sets.
  >+ In Parallel coordinates, all axes are parallel which allows representing data
  in much more than three dimensions.
  >+ A point in n-dimensional space is represented as a polyline with vertices on
  the parallel axes. 
  >+ 平行坐标的优点: spotting irregular events, seeing the data trend, find correlations and clusters.
  >+ 平行坐标的缺点: Difficult to see the data clusters.
![Parallel Coordinates with transparency.](ROOT/pictures/para14.png)

```C++
// 如何使用平行坐标?
// Using the plotting option "PARA" in the TTree::Draw() method.
tree->Draw("x:y:z","","PARA")

```


+ **Multiple Variables Visualisation - Box (Candle) Plots**
  >+ A Box Plot is a convenient way to describe graphically a data distribution (D) 
  with only five numbers.
  (1) The minimum value of the distribution D (Min).
  (2) The lower quartile (Q1): 25% of the data points in D are less than Q1.
  (3) The median (M): 50% of the data points in D are less than M.
  (4) The upper quartile (Q3): 75% of the data points in D are less than Q3.
  (5) The maximum value of the distribution D (Max).
  ![A box plot describes a distribution with only five numbers. ](ROOT/pictures/bp1.png)
   
```C++
// 如何使用 Box Plots(Candle Plots)
tree->Draw("x:y:z", "", "candle");
```

+ **TEventList and TEntryList**
  >+ 当 TTree::Draw 第一个参数前有 ">>" 时, ROOT 将不会画任何东西, 而是将 entries 保存在一个 list 中
  >+ 当使用 ">>" 时, list 中的所有东西将被重新覆盖.
  >+ TEventList 与 TEntryList:
     1.功能相同: both are used to store entry numbers
     2.TEntryList: uses less memory for storage, and is optimized for both very high 
     and very low selectivity pf cuts.
     3.TEntryList makes a distinction between indices from a TChain and from a TTree.

```C++
// Create a TEventList of all entries with more than 600 tracks
root[] TFile* f = new TFile("Event.root");
root[] T->Draw(">> myList", "fNtrack > 600");
root[] myList->Print("all"); 


//___________________________________
// Using an Event List
root[] TFile* f= new TFile("Event.root");
root[] TTree* T = (TTree*)f->Get("T");
root[] T->Draw("fNTrack");

root[] T->Draw(">>myList","fNtrack > 600", "entrylist");
root[] TEventList* list = (TEventList*)gDirectory->Get("myList");

root[] T->SetEntryList(list);
root[] T->Draw("fNtrack");

//____________________________________
// Operations on TEntryLists
// ** If you have entry lists that were created using different cuts, 
// ** you can comine the lists to get a new list
// ** TEntryList::Add(), TEntryList::Enter(), TEntryList::Contains()...
root[] T->Draw(">>list1", "fNtrack>600", "entrylist");
root[] TEntryList* list1 = (TEntryList*)gDirectory->Get("list1");
root[] T->Draw(">>list2", "fNtrack<590", "entrylist");
root[] TEntryList* list2 = (TEntryList*)gDirectory->Get("list2");
root[] lis1->Add(list2);
root[] T->SetEntryList(list1);
root[] T->Draw("fNtrack");


//____________________________________________
// TEntryListFromFile
// ** Used only when processing TChain objects.
// ** It is used in this case, when the entry lists, corresponding to 
// ** the trees of this chain, are stored in separate files.
// 参考程序: $ROOTSYS/test/stressEntryList.C


//____________________________________________
// Filling a Histogram
root[] TFile* f = new TFile("Event.root");
root[] T->Draw("fNtrack >> myHisto");

root[] TH1D* h1 = new TH1D("h1", "h1", 50, 0., 50.);
root[] T->Draw("fNtrack >> h1");


//___________________________________________
// Profile a Histogram
// ** Where pf is an existing TProfile histogram
root[] T->Draw("y:x >> pf");

```


+ **Tree Information**
  >+ GetV1: Returns a pointer to the float array of the first variable.
  >+ GetV2: Returns a pointer to the float array of the second variable.
  >+ GetV3: Returns a pointer to the float array of the third variable.

```C++
root[] Float_t *a;
root[] a = T->GetV1();
```


&emsp;
#### <font color=#FF00FF>  2.4.9 Data Analysis - Tree::MakeClass </font>
>+ TTree::MakeClass generates a skeleton class designed to loop over the 
   entries of the tree.
>+ TTree::MakeClass 的使用步骤:
   1.Call TTree::MakeClass
   2.Modify the myClass::Loop() method in myClass.C
   3.Load and instantiate myClass, and run myClass::Loop()
   
```C++
// 如何使用 MakeClass
//_______________________________
// Step1 : Call TTree::MakeCalss
root[] TFile* f = new TFile("staff.root");
root[] TTree* T = (TTree*)f->Get("T");
root[] T->MakeClass("myClass");

// ** MakeClass 操作将产生两个文件: myClass.h , myClass.C
// ** myClass.C 包含多个函数, myClass::Loop(), myClass::GetEntry(), ...


//_________________________________________________
// Step2 : Modify myClass::Loop() to fit your task
{
  ...
   for (Int_t jentry=0; jentry<nentries;jentry++) {
      GetEntry(jentry);
      for (Int_t j = 0; j < 100; j++) {
         myHisto->Fill(fTracks_fPx[j]);
         if (j < 100) {
            smallHisto->Fill(fTracks_fPx[j]);
         }
      }
   }
...
}

//_________________________________________________
// Step3 : Load myClass.C, and run MyClass::Loop()
root[] .L myClass.C
root[] myClass m;
root[] m.Loop();
```



&emsp;
#### <font color=#FF00FF>  2.4.10 Data Analysis - TTree::MakeSelector </font>
>+ With a TTree we can make a selector and use it to process a limited set of entries.
>+ Especially important in a parallel processing.
>+ The TTree::Process method is used to specify the selector and the entries.
>+ Before we can use TTree::Process we need to make a selector.
>+ We can call the TTree::MakeSelector method. It creates two files similar to TTree::MakeClass.

```C++
//______________________________________________
// TTree::MakeSelector 的使用步骤:
1. setup   TMySelector::Init(TTree *tree)
   // Chain = tree; fChain->SetBranchAddress()
   // initialize branches
2. start   TMySelector::SlaveBegin()
   // create histograms
3. run     TMySelector::Process(Long64_t)
   // fChain->GetTree()->GetEntry(entry);
   // analyze data, fill histograms,...
4. end     TMySelector::Terminate()
   // fit histograms, write them to files

//______________________________________________
// 如何使用 TTree::MakeSelector
root[] T->MakeSelector("MySelector");
root[] T->Process("MySelector.C", "", 1000, 100);

// With "++"/"+", the class will be compiled and dynamically loaded
root[] T->Process("MySelector.C++", "", 1000, 100);
root[] T->Process("MySelector.C+",  "", 1000, 100);


// How to create a selector with a pointer
{
  MySelector *selector = (MySelector*)TSelector::GetSelector("MySelector.C+");
  T->Process(selector);
}

```









&emsp;
#### <font color=#FF00FF>  2.4.11 Tree 的其他设置 </font>
+ **Creating a Tree from a Folder Hierarchy**
```C++
// 1. An alternative way to create a tree and organize it is to use folders.
// 2. You can build a folder structure and create a tree with branches for 
//    each of the sub-folders
// 3. The second argument "/MyFolder" is the top folder, and the "/" signals the 
//    TTree constructor that this is a folder not just the title. 

TTree folder_tree("MyFolderTree","/MyFolder");

```

+ **Autosve**
  >+ Autosave gives the option to save all the branch buffers every n byte.
  >+ <font color=#DC143C> 对于大型数据获取, 推荐使用 Autosave 方法.</font> 因为一旦获取发生崩溃, 上一次 autosave 之前的数据都能被保留下来.
  >+ Autosave 的两种使用方法:
     (1) TTree::Autosave(Long64_t n);  
     (2) Call TTree::Autosave in the acquisition loop every n entry.

+ **Tree with Circle Buffers**
```C++
// It is very useful for monitoring.
// maxEntries is the maximum number of entries to be kept in the buffers.
// When the number of entries exceeds this value, the first entries 
// in the Tree are deleted and the buffers used again
void TTree::SetCircular(Long64_t maxEntries);


// 程序举例
void circular() 
{
   gROOT->cd(); //make sure that the Tree is memory resident
   TTree *T = new TTree("T","test circular buffers");
   TRandom r;
   Float_t px,py,pz;
   Double_t random;
   UShort_t i;
   T->Branch("px",&px,"px/F");
   T->Branch("py",&py,"py/F");
   T->Branch("pz",&pz,"pz/F");
   T->Branch("random",&random,"random/D");
   T->Branch("i",&i,"i/s");
   T->SetCircular(20000);
   for (i = 0; i < 65000; i++) {
      r.Rannor(px,py);
      pz = px*px + py*py;
      random = r.Rndm();
      T->Fill();
   }
   T->Print();
}
```

+ **Size of TTree in the File**
  >+ 当将一个 tree 写入文件时, 如果文件大小超过 TTree::GetMaxTreeSize() 中存储的值时, 则关闭当前文件, 开启新的文件. 如果当前文件名为 "myfile.root", 新的文件为 "myfile_1.root", "myfile_2.root" 等.
  >+ 最大文件可以通过 TTrre::SetMaxTreeSize() 设置. 默认的 fgMaxTreeSize = 100 GB
