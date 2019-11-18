#include "TMath.h"

//_____________________________________________________________________________
Double_t Maxwell(Double_t *x, Double_t *par)
{
  if(x[0] > par[1] && par[2] > 0 && par[0] > 0)
  {
    return par[0]*(x[0]-par[1])/par[2]*TMath::Exp(-(x[0]-par[1])/par[2]);
  }
  else
  {
    return 0;
  }
}

//______________________________________________________________________________
Double_t DeuxMaxwell(Double_t *x, Double_t *par)
{
  return Maxwell(x,par) + Maxwell(x,&par[3]);
}
