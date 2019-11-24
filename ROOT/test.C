#include "Fit/Fitter.h"
#include "Fit/BinData.h"
#include "Fit/Chi2FCN.h"
#include "TH1.h"
#include "TList.h"
#include "Math/WrappedMultiTF1.h"
#include "HFitInterface.h"
#include "TCanvas.h"
#include "TStyle.h"

//______________________________________________________________________________
// definition of shared parameter
// background functions
Int_t iparB[2] = { 0,  // exp amplitude in B histo
                   2   // exp common parameter
};

//______________________________________________________________________________
Int_t iparSB[5] = { 1, // exp amplitude in S+B histo
                    2, // exp common parameter
                    3, // gaussian amplitude
                    4, // gaussian mean
                    5  // gaussian sigma
};

//______________________________________________________________________________
struct GlobalChi2
{
  GlobalChi2( ROOT::Math::IMultiGenFunction & f1,
              ROOT::Math::IMultiGenFunction & f2):
              fChi2_1(&f1), fChi2_2(&f2) {}
  // parameter vector is first backgroud(in common 1 and 2)
  // and then is signal(only in 2)
  Double_t operator() (const Double_t *par) const
  {
    Double_t p1[2];
    for(Int_t i=0; i<2; i++) p1[i] = par[iparB[i]];

    Double_t p2[5];
    for(Int_t i=0; i<5; i++) p2[i] = par[iparSB[i]];

    return (*fChi2_1)(p1) + (*fChi2_2)(p2);
  }

  const ROOT::Math::IMultiGenFunction * fChi2_1;
  const ROOT::Math::IMultiGenFunction * fChi2_2;
};

//______________________________________________________________________________
void test()
{
  TH1D * hB  = new TH1D("hB","histo B",   100, 0, 100);
  TH1D * hSB = new TH1D("hSB","histo S+B",100, 0, 100);

  TF1 * fB = new TF1("fB","expo",0,100);
  fB->SetParameters(1, -0.05);
  hB->FillRandom("fB");
  TF1 * fS = new TF1("fS","gaus",0,100);
  fS->SetParameters(1, 30, 5);

  hSB->FillRandom("fB",2000);
  hSB->FillRandom("fS",1000);

  TF1 * fSB = new TF1("fSB","expo+gaus(2)",0,100);

//______________________________________________________________________________
// 用到的类：   ROOT::Math::WrappedMultiTF
  ROOT::Math::WrappedMultiTF1 wfB( *fB, 1);
  ROOT::Math::WrappedMultiTF1 wfSB(*fSB,1);

//______________________________________________________________________________
// 用到的类： ROOT::Fit::DataOptions
//          ROOT::Fit::DataRange
//          ROOT::Fit::BinData
//          ROOT::Fit::FillData
  // set data range and fill data
  ROOT::Fit::DataOptions opt;
  //opt.fIntegral = true;
  ROOT::Fit::DataRange rangeB(10,90);
  rangeB.SetRange(10,90);
  ROOT::Fit::BinData dataB(opt,rangeB);
  ROOT::Fit::FillData(dataB,hB);

  ROOT::Fit::DataRange rangeSB(10,50);
  rangeSB.SetRange(10,50);
  ROOT::Fit::BinData dataSB(opt,rangeSB);
  ROOT::Fit::FillData(dataSB,hSB);


//______________________________________________________________________________
// 用到的类： ROOT::Fit::Chi2Function
  ROOT::Fit::Chi2Function chi2_B(dataB,   wfB);
  ROOT::Fit::Chi2Function chi2_SB(dataSB, wfSB);

  GlobalChi2 globalChi2(chi2_B, chi2_SB);


//______________________________________________________________________________
// 用到的类： ROOT::Fit::Fitter
//          ROOT::Fit::FitResult
  const Int_t Npar = 6;
  Double_t par0[Npar] ={5, 5, -0.1, 100, 30, 10};
  // set parameters
  ROOT::Fit::Fitter fitter;
  fitter.Config().SetParamsSettings(6, par0);
  fitter.Config().ParSettings(4).Fix();
  fitter.Config().ParSettings(2).SetLimits(-10,-1.E-4);
  fitter.Config().ParSettings(3).SetLimits(0,10000);
  fitter.Config().ParSettings(3).SetStepSize(5);

  fitter.Config().MinimizerOptions().SetPrintLevel(0);
  fitter.Config().SetMinimizer("Minuit2","Migrad");

  fitter.FitFCN(6, globalChi2, 0, dataB.Size()+dataSB.Size(),true);
  ROOT::Fit::FitResult result = fitter.Result();
  result.Print(std::cout);


//______________________________________________________________________________
  //  画图
  TCanvas * c1 = new TCanvas("Simfit","Simultaneous fit of two histograms",10,10,700,700);
  c1->Divide(1,2);
  c1->cd(1);
  gStyle->SetOptFit(1111);

  fB->SetFitResult(result, iparB);
  fB->SetRange(rangeB().first, rangeB().second);
  fB->SetLineColor(kBlue);
  hB->GetListOfFunctions()->Add(fB);
  hB->Draw();

  c1->cd(2);
  fSB->SetFitResult(result, iparSB);
  fSB->SetRange(rangeSB().first, rangeSB().second);
  fSB->SetLineColor(kRed);
  hSB->GetListOfFunctions()->Add(fSB); // Draw the fit function in the same canvas
  hSB->Draw();
}
