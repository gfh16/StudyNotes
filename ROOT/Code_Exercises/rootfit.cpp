#include "Riostream"

using namespace tsd;

void rootfit()
{
  // Using Binned Data
  ROOT::Fit::DataOptions opt;
  opt.fIntegral = true;
  ROOT::Fit::BinData data(opt);
  auto * h1 = (TH1*)gDirectory->Get("myHistogram");
  ROOT::Fit::FillData(data, h1);

  // Using unbined Data
  Double_t buffer = histogram->GetBuffer();
  Int_t n = buffer[0];
  ROOT::Fit::UnBinData data1(n);
  for(Int_t i=0; i<n; i++)
  {
    data.add(buffer[2*i+1]);
  }


}
