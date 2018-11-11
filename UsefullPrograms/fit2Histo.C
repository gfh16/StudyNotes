#include "Fit/Fitter.h"
#include "Fit/BinData.h"
#include "TH1.h"
#include "Math/WrappedTF1.h"
#include "HFitInterface.h"

// example of fitting 2 histograms with the same function

void fit2Histo() { 

  TH1D * h1 = new TH1D("h1","histo 1",100,-3,0);
  TH1D * h2 = new TH1D("h2","histo 2",100, 0,3);

  h1->FillRandom("gaus");
  h2->FillRandom("gaus");

  ROOT::Fit::BinData data; 
  ROOT::Fit::FillData(data, h1); 
  ROOT::Fit::FillData(data, h2); 

  cout << "data size is " << data.Size() << endl;

  TF1 * f1 = new TF1("f1","gaus",-3,3);
  f1->SetParameters(1,0,1);

  ROOT::Math::WrappedTF1 wf(*f1);

  ROOT::Fit::Fitter fitter;
  fitter.SetFunction(wf);

  fitter.Fit(data);
  ROOT::Fit::FitResult result = fitter.Result();
  result.Print(std::cout);
  
}
