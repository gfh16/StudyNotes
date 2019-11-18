#include <iostream>
#include <math.h>
#include "include/Quad.h"

//______________________________________________________________________________
Quad::Quad()
{
  fA = 1.0;
  fB = 1.0;
  fC = 1.0;
}

//______________________________________________________________________________
Quad::Quad(Float_t a, Float_t b, Float_t c)
{
  fA = a;
  fB = b;
  fC = c;
}

//______________________________________________________________________________
Quad::~Quad()
{
  cout<<"deleting object with coeffts: "<< fA << "," << fB << "," << fC << endl;
}

//______________________________________________________________________________
Float_t Quad::Evaluate(Float_t x) const
{
  return fA*x*x + fB*x + fC;
}

//______________________________________________________________________________
void Quad::Solve() const
{
  Float_t delta = fB*fB - 4*fA*fC;
  Double_t x1, x2;
  if(delta > 0)
  {
    delta = sqrt(delta);
    x1 = (-fB - delta)/(2. * fA);
    x2 = (-fB + delta)/(2. * fA);
    cout<<"Three are two roots:"<< x1 << " and " << x2 << endl;
  }
  else if(delta == 0.)
  {
    x1 = -fB / (2. * fA);
    cout<<"There are two equal roots: "<< x1 << endl;
  }
  else
  {
    cout<<"There are no roots"<< endl;
  }
}
