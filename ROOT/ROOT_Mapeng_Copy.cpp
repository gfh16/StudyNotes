//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
{
  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->Divide(2,3);
  c1->cd(1);
  TFile *_file0 = TFile::Open("201705090000.root");
  RawData->Draw("Mod108_TModV775.chdata[12]:Mod108_TModV775.chdata[13]",ch12&&ch13);
  c1->cd(2);
  TFile *_file0 = TFile::Open("201705090001.root");
  RawData->Draw("Mod108_TModV775.chdata[12]:Mod108_TModV775.chdata[13]",ch12&&ch13);
  c1->cd(3);
  TFile *_file0 = TFile::Open("201705090002.root");
  RawData->Draw("Mod108_TModV775.chdata[12]:Mod108_TModV775.chdata[13]",ch12&&ch13);
  c1->cd(4);
  TFile *_file0 = TFile::Open("201705090003.root");
  RawData->Draw("Mod108_TModV775.chdata[12]:Mod108_TModV775.chdata[13]",ch12&&ch13);
  c1->cd(5);
  TFile *_file0 = TFile::Open("201705090004.root");
  RawData->Draw("Mod108_TModV775.chdata[12]:Mod108_TModV775.chdata[13]",ch12&&ch13);
  c1->cd(6);
  TFile *_file0 = TFile::Open("201705090005.root");
  RawData->Draw("Mod108_TModV775.chdata[12]:Mod108_TModV775.chdata[13]",ch12&&ch13);
}

//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
{
  TCut ch0 = "Mod104_TModV785.chdata[0]>150";
  TCut ch1 = "Mod104_TModV785.chdata[1]>150";
  TCut ch2 = "Mod104_TModV785.chdata[2]>150";
  TCut ch3 = "Mod104_TModV785.chdata[3]>150";
  TCut ch4 = "Mod104_TModV785.chdata[4]>150";
  TCut ch5 = "Mod104_TModV785.chdata[5]>150";
  TCut ch6 = "Mod104_TModV785.chdata[6]>150";
  TCut ch7 = "Mod104_TModV785.chdata[7]>150";
  TCut ch8 = "Mod104_TModV785.chdata[8]>150";
  TCut ch9 = "Mod104_TModV785.chdata[9]>150";
  TCut ch10 = "Mod104_TModV785.chdata[10]>150";
  TCut ch11 = "Mod104_TModV785.chdata[11]>150";
  TCut ch12 = "Mod104_TModV785.chdata[12]>150";
  TCut ch13 = "Mod104_TModV785.chdata[13]>150";
  TCut ch14 = "Mod104_TModV785.chdata[14]>150";
  TCut ch15 = "Mod104_TModV785.chdata[15]>150";
}

//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
{

// RawData->Draw("Mod104_TModV785.chdata[4]",ch0&&ch1&&ch2&&ch3&&ch4&&ch5&&ch6&&ch7&&ch9&&ch10&&ch11&&ch12&&ch13&&ch14&&ch15);

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->Divide(2,2);

  c1->cd(1);
  RawData->Draw("Mod104_TModV785.chdata[4]",ch0&&ch1&&ch2&&ch3&&ch4&&ch5&&ch6&&ch7&&ch9&&ch10&&ch11);

  c1->cd(2);
  RawData->Draw("Mod104_TModV785.chdata[4]",ch0&&ch1&&ch2&&ch3&&ch4&&ch5&&ch6&&ch7&&ch9&&ch10);

  c1->cd(3);
  RawData->Draw("Mod104_TModV785.chdata[4]",ch0&&ch1&&ch2&&ch3&&ch4&&ch5&&ch6&&ch7&&ch9);

  c1->cd(4);
  RawData->Draw("Mod104_TModV785.chdata[4]",ch0&&ch1&&ch2&&ch3&&ch4&&ch5&&ch6&&ch7);
}

//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
{

  // RawData->Draw("Mod108_TModV775.chdata[4]",ch0&&ch1&&ch2&&ch3&&ch4&&ch5&&ch6&&ch7&&ch9&&ch10&&ch11&&ch12&&ch13&&ch14&&ch15);
  TH2F *hh9=new TH2F("xy","xy",1000.,-2000.,2000.,1000,-2000.,2000.);

  RawData->Draw("Mod108_TModV775.chdata[1]-Mod108_TModV775.chdata[2]:Mod108_TModV775.chdata[3]-Mod108_TModV775.chdata[4]>>hh9",ch1&&ch2&&ch3&&ch4);
}


//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////

void ssd()
{
  gStyle->SetOptFit(1111);
  TFile *f=new TFile("/home/mapeng/data/vme-single/vmedata/a.root");
  //TFile *f=new TFile("D:/lironghua/suquaresilicon0000.root");
  TCanvas *c1=new TCanvas("c1","c1",20,20,800,800);
  h104018->Draw();

  //定义延迟线的节点总数
  const int npeak=3;
  double par[3*npeak];
  double pos[2*npeak]={2168.,2232.,2315.,2366.,2456.,2494.};

  for(int i=0;i<npeak;++i)
  {
    h104018->Fit("gaus","R+","",pos[2*i],pos[2*i+1]);//高斯拟合，拟合函数叠加画图
    gaus->GetParameters(&par[3*i]);//取出拟合参数
  }

  cout<<"number"<<"\t\t"<<"mean"<<"\t\t"<<"sigma"<<"\t\t"<<"energyresolution"<<endl;
  for(int i=0;i<npeak;++i)
  {
    cout<<i+1<<"\t\t"<<setprecision(5)<<par[i*3+1]<<"\t\t"<<setprecision(5)<<par[i*3+2]
        <<"\t\t"<<setprecision(3)<<100*(par[i*3+2]/par[i*3+1])*2.355<<"%"<<endl;
  }
}
