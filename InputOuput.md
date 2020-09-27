
[toc]


&emsp;
### <font color=#00BFFF> 1.9 Input/Output  </font>
>+ Input means saving objects to ROOT files
>+ Output means reading objects from ROOT files


#### <font color=#FF00FF> 1.9.1 ROOT 文件格式</font>
+ **TFile::Map() 查看 ROOT 文件的物理输出**
```C++
root[] f.Map()
20051208/124502  At:100    N=114       TFile
20051208/124502  At:214    N=413       TH1F           CX =  2.35
20051208/124502  At:627    N=410       TH1F           CX =  2.36
20051208/124502  At:1037   N=396       TH1F           CX =  2.45
20051208/124502  At:1433   N=400       TH1F           CX =  2.42
20051208/124502  At:1833   N=402       TH1F           CX =  2.41
20051208/124502  At:2235   N=416       TH1F           CX =  2.33
20051208/124502  At:2651   N=406       TH1F           CX =  2.39
20051208/124502  At:3057   N=403       TH1F           CX =  2.40
20051208/124502  At:3460   N=411       TH1F           CX =  2.36
20051208/124502  At:3871   N=400       TH1F           CX =  2.42
20051208/124502  At:4271   N=409       TH1F           CX =  2.38
20051208/124502  At:4680   N=409       TH1F           CX =  2.38
20051208/124502  At:5089   N=420       TH1F           CX =  2.32
20051208/124502  At:5509   N=406       TH1F           CX =  2.40
20051208/124502  At:5915   N=405       TH1F           CX =  2.40
20051208/124503  At:6320   N=3052      StreamerInfo   CX =  3.16
20051208/124503  At:9372   N=732       KeysList
20051208/124503  At:10104  N=53        FreeSegments
20051208/124503  At:10157  N=1         END

第 1 列: date/time
第 2 列: start record address
第 3 列: number of bytes in the record
第 4 列: class name of the record
第 5 列: compression factor
```

+ **ROOT文件格式 - The File Header**
>+ The first 100 bytes are taken by the file header.
>+ The first four bytes of the file header contain the string "root" which identifies a file as 
a ROOT file. So, **ROOT is not dependent on the ".root" extension.** 
>+ 关于 ROOT File Header 的详细内容请参考 ROOT User Guide.


+ **ROOT文件格式 - The Top Directory Description**
```C++
20051208/124502  At:100    N=114       TFile
```

+ **ROOT文件格式 - The Histogram Records**
```C++
20051208/124502  At:214    N=413       TH1F           CX =  2.35
20051208/124502  At:627    N=410       TH1F           CX =  2.36

// The first 4 bytes of each record holding the number of bytes in this record.
// A negative number flags the record as deleted, and makes the space available
// for recycling in the next writing.

```

+ **ROOT文件格式 - The Class Description List (StreamerInfo List)**
```C++
20051208/124503  At:6320   N=3052      StreamerInfo   CX =  3.16

// The list contains the descriptionof each class that has been written to file.
// ROOT allows a class to have multiple versions, and each has its own 
// description in form of a StreamerInfo. 

root[] f.ShowStreamerInfo()  
```


+ **ROOT文件格式 - The List of Keys**
```C++
20051208/124503  At:9372   N=732       KeysList
```

+ **ROOT文件格式 - The List of Free Blocks**
```C++
20051208/124503  At:10104  N=53        FreeSegments
```

&emsp;
#### <font color=#FF00FF> 1.9.2 TFile and TKey </font>
+ **使用 TKey 读取 ROOT file 中的所有 object**
```C++
{
   TFile f("demo.root");
   TIter next(f.GetListOfKeys());
   TKey *key;
   while ((key=(TKey*)next())) {
      printf("key: %s points to an object of class: %s at %dn",
      key->GetName(),
      key->GetClassName(),key->GetSeekKey());
   }
}
```

+ **The Structure of TFile**
>+ The cycle number along with the variable name uniquely identifies the object.
>+ As follows, ObjA is on file twice with two diferent cycle numbers.

![The structure of TFile](ROOT/pictures/030000E8.png)


+ **The Current Directory**
```C++
root[] gDirectory->pwd() 
Rint:/                 // The current directory is the ROOT session(Rint)

root[] TFile f1("AFile1.root");
root[] gDirectory->pwd()
AFile1.root:/
```

+ **Objects in Memory and Objects on Disk**
```C++
// check objects in memory
root[] TFile *f = new TFile("hsimple.root");
root[] gDirectory->ls("-m")
TFile**         hsimple.root
TFile*         hsimple.root

// check objects on disk

root[] gDirectory->ls("-d")
TFile**         hsimple.root
TFile*         hsimple.root
KEY: TH1F     hpx;1    This is the px distribution
KEY: TH2F     hpxpy;1  py vs px
KEY: TProfile hprof;1  Profile of pz versus px
KEY: TNtuple  ntuple;1 Demo ntuple
```





&emsp;
#### <font color=#FF00FF> 1.9.3 Saving and Reading Objects</font>
+ **创建 ROOT 文件**
```C++
// 当 ROOT 文件包含多个 objects 时, 可以使用 TObjArray 来创建
{
   char name[10], title[20];
   TObjArray Hlist(0);      // create an array of Histograms
   TH1F* h;                 // create a pointer to a histogram
   // make and fill 15 histograms and add them to the object array
   for (Int_t i = 0; i < 15; i++) {
      sprintf(name,"h%d",i);
      sprintf(title,"histo nr:%d",i);
      h = new TH1F(name,title,100,-4,4);
      Hlist.Add(h);
      h->FillRandom("gaus",1000);
   }
   // open a file and write the array to the file
   TFile f("demo.root","recreate");
   Hlist.Write();
   f.Close();
}
```


+ **读取 ROOT 文件**
```C++
// 方式1: TFile 读取
TFile f("demo.root");
if (f.IsZombie()) {  //检查文件是否被正确打开. 等效于 (!f.IsOpen()
  cout<<"Error opening file"<<endl;
}






```