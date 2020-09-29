[toc]

#### 快速创建文件目录
```C++
TString dir = gROOT->GetTutorialDir();
   dir.Append("/tree/cernstaff.C");
   FILE *fp = fopen(Form("%scernstaff.dat",dir.Data()),"r");
   if (gSystem->AccessPathName("cernstaff.root")) {
      gROOT->SetMacroPath(dir);
      gROOT->ProcessLine(".x cernbuild.C");
   }
```


#### fgets() 方法按行读取文件
```C++
FILE *fp = fopen(Form("%scernstaff.dat",dir.Data()),"r");
char line[80];
while (fgets(line,80,fp)) {
      sscanf(&line[0],"%d %d %d %d %d %d %d  %d %d %s %s",
      &Category,&Flag,&Age,&Service,&Children,&Grade,&Step,&Hrweek,&Cost,Division,Nation);
      tree->Fill();
   }
```