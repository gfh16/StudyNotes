#include "TH1F.h"
#include "TPad.h"

void test()
{
  TH1F *h = (TH1F*)gROOT->FindObject("h_gaus");
  if(h)
  {
	  h->Reset();
  }
  else
  {
	  h = new TH1F("h_gaus","Une gaussience",100,0.,100.);
  }
  h->Draw();
  for(Double_t x=0; x<100; x++)
  {
	  Double_t f = 20 * exp(-pow(x-50.0,2)/2./pow(10.,2));
	  h->Fill(x,f);
	  gPad->Modified();
	  gPad->Update();
      
  }
}
