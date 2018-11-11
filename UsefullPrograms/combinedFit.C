// combined fit of two histogram with separate functions but a common parameter
// N.B. this macro must be compiled with ACliC 

#include "Fit/Fitter.h"
#include "Fit/BinData.h"
#include "Fit/Chi2FCN.h"
#include "TH1.h"
#include "TList.h"
#include "Math/WrappedMultiTF1.h"
#include "HFitInterface.h"
#include "TCanvas.h"
#include "TStyle.h"


struct GlobalChi2 { 
   GlobalChi2(  ROOT::Math::IMultiGenFunction & f1,  ROOT::Math::IMultiGenFunction & f2) : 
      fChi2_1(&f1), fChi2_2(&f2) {}

   // parameter vector is first background (in common 1 and 2) and then is signal (only in 2)
   double operator() (const double *par) const {
      double p1[2]; 
      p1[0] = par[0]; // exp amplitude in B histo
      p1[1] = par[2]; // exp common parameter 

      double p2[5]; 
      p2[0] = par[1]; // exp amplitude in S+B histo
      p2[1] = par[2]; // exp common parameter
      p2[2] = par[3]; // gaussian amplitude
      p2[3] = par[4]; // gaussian mean
      p2[4] = par[5]; // gaussian sigma
      return (*fChi2_1)(p1) + (*fChi2_2)(p2);
   } 

   const  ROOT::Math::IMultiGenFunction * fChi2_1;
   const  ROOT::Math::IMultiGenFunction * fChi2_2;
};

void combinedFit() { 

  TH1D * hB = new TH1D("hB","histo B",100,0,100);
  TH1D * hSB = new TH1D("hSB","histo S+B",100, 0,100);

  TF1 * fB = new TF1("fB","expo",0,100);
  fB->SetParameters(1,-0.05);
  hB->FillRandom("fB");

  TF1 * fS = new TF1("fS","gaus",0,100);
  fS->SetParameters(1,30,5);

  hSB->FillRandom("fB",2000);
  hSB->FillRandom("fS",1000);

  // perform now global fit 

  TF1 * fSB = new TF1("fSB","expo + gaus(2)",0,100);

  ROOT::Math::WrappedMultiTF1 wfB(*fB,1);
  ROOT::Math::WrappedMultiTF1 wfSB(*fSB,1);

  ROOT::Fit::DataOptions opt; 
  ROOT::Fit::DataRange rangeB; 
  // set the data range
  rangeB.SetRange(10,90);
  ROOT::Fit::BinData dataB(opt,rangeB); 
  ROOT::Fit::FillData(dataB, hB);

  ROOT::Fit::DataRange rangeSB; 
  rangeSB.SetRange(10,50);
  ROOT::Fit::BinData dataSB(opt,rangeSB); 
  ROOT::Fit::FillData(dataSB, hSB);

  ROOT::Fit::Chi2Function chi2_B(dataB, wfB);
  ROOT::Fit::Chi2Function chi2_SB(dataSB, wfSB);

  GlobalChi2 globalChi2(chi2_B, chi2_SB);

  ROOT::Fit::Fitter fitter;

  const int Npar = 6; 
  double par0[Npar] = { 5,5,-0.1,100, 30,10};

  // create before the parameter settings in order to fix or set range on them
  fitter.Config().SetParamsSettings(6,par0);
  // fix 5-th parameter  
  fitter.Config().ParSettings(4).Fix();
  // set limits on the third and 4-th parameter
  fitter.Config().ParSettings(2).SetLimits(-10,-1.E-4);
  fitter.Config().ParSettings(3).SetLimits(0,10000);

  fitter.FitFCN(6,globalChi2,par0,dataB.Size()+dataSB.Size());
  ROOT::Fit::FitResult result = fitter.Result();
  result.Print(std::cout);

  TCanvas * c1 = new TCanvas("Simultaneous fit");
  c1->Divide(1,2);
  c1->cd(1);
  gStyle->SetOptFit(1111);

  fB->SetParameters(result.Parameter(0), result.Parameter(2) );
  fB->SetParError(0, result.Error(0) );
  fB->SetParError(1, result.Error(2) );
  fB->SetChisquare(result.MinFcnValue() );
  fB->SetNDF(result.Ndf() );
  hB->GetListOfFunctions()->Add(fB);
  fB->SetRange(rangeB().first, rangeB().second);   
  hB->Draw(); 

  c1->cd(2);
  fSB->SetParameters(result.GetParams()+1 );
  fSB->SetParErrors(result.GetErrors()+1 );
  fSB->SetChisquare(result.MinFcnValue() );
  fSB->SetNDF(result.Ndf() );
  fSB->SetRange(rangeSB().first, rangeSB().second);   
  hSB->GetListOfFunctions()->Add(fSB);
  hSB->Draw(); 
  
  

}
