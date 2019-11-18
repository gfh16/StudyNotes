#include "TMath.h"

//
// 2D Gaussian fit function
//
Double_t Gaus2D(Double_t *x, Double_t *par)
{
if(par[2] > 0 && par[4] > 0)
 {
 double rx=(x[0]-par[1])/par[2];
 double ry=(x[1]-par[3])/par[4];
 return par[0]*TMath::Exp(-(rx*rx+ry*ry)/2.);
 }
else
 {
 return 0.;
 }
}
