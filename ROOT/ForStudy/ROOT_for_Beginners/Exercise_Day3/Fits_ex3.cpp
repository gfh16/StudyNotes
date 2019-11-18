//______________________________________________________________________________
Double_t fitbackgroud(Double_t *x, Double_t *par)
{
    return par[0]*x[0] / (1 + TMath::Exp((x[0]-par[1])/par[2]));
}

//______________________________________________________________________________
Double_t fitsignal(Double_t *x, Double_t *par)
{
  Double_t Signal;

  if(x[0] <= par[1])
  {
    Signal = par[0]*TMath::Exp(-0.5*pow((x[0]-par[1])/par[2],2));
  }
  if(x[0]>par[1])
  {
    Signal = par[0]*TMath::Exp(-0.5*pow((x[0]-par[1])/par[3],2));
  }
  return Signal;
}

//______________________________________________________________________________
Double_t fitsum(Double_t *x, Double_t *par)
{
  return  fitbackgroud(x, &par[0]) + fitsignal(x, &par[3]);
}

//______________________________________________________________________________
void Fits_ex3()
{
  gStyle->SetOptFit(0);
  gStyle->SetPalette(1);

  TFile * filein = new TFile("Fits.root");
  TH1D * h1 = (TH1D*)filein->Get("hData");

  //TF1 * fit = new TF1("fit",fitsum,0.,50.,7);
  TF1 * fit = new TF1("fit",fitsum,0.,50.,7);
  fit->SetParNames("A","B","C","G","x_{0}","#sigma_{g}","#sigma_{d}");

  // 自定义函数拟合对初值非常敏感！！！需要仔细给参数赋值，同时还需要给参数设定边界
  fit->SetParameter(0, 12.);
  fit->SetParameter(1, 12.);
  fit->SetParameter(2, 1.);
  fit->SetParameter(3, 10.);
  fit->SetParameter(4, 25.);
  fit->SetParameter(5, 0.5);
  fit->SetParameter(6, 0.5);

  fit->SetParLimits(3,0.,100.);
  fit->SetParLimits(5,0.,2.);
  fit->SetParLimits(6,0.,3.);

  fit->SetLineColor(kBlack);
  h1->SetStats(0);
  h1->Draw();
  h1->Fit("fit","+");

  Double_t par[7];
  fit->GetParameters(par);

  TF1 * fb = new TF1("fb",fitbackgroud,0.,50.,3);
  TF1 * fs    = new TF1("fs",fitsignal,0.,50.,4);
  fb->SetLineColor(kBlue);
  fb->SetFillColor(kBlue);
  fb->SetFillStyle(3003);
  fs->SetLineColor(kRed);
  fs->SetFillColor(kRed);
  fs->SetFillStyle(3001);

  fb->SetParameters(par);
  fs->SetParameters(&par[3]);
  fb->Draw("same");
  fs->Draw("same");

  Double_t ratio = fs->Integral(0,50)/fb->Integral(0,50) * 100;
  TLegend * legend = new TLegend(0.6, 0.6, 0.85,0.85,"Fitting Results");
  legend->AddEntry(fb,"Fond");
  legend->AddEntry(fs,"Signal");
  legend->AddEntry(fit,"Total");
  TF1 * empty = new TF1();
  empty->SetLineColor(kWhite);
  legend->AddEntry(empty,Form("Signal/Fond: %.2f %s",ratio,"%"));
  legend->Draw();


}
