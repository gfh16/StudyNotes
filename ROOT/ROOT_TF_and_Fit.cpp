
//Fitting with a user-defined function

// This macro gets in memory an histogram from a root file
// and fits a user defined function.
// Note that a user defined function must always be defined
// as in this example:
//  - first parameter: array of variables (in this example only 1-dimension)
//  - second parameter: array of parameters
// Note also that in case of user defined functions, one must set
// an initial value for each parameter.

//---- See more details on website : https://root.cern.ch/root/htmldoc/guides/users-guide/FittingHistograms.html

Double_t fitf(Double_t *x, Double_t *par)
{
   Double_t arg = 0;
   if (par[2] != 0) arg = (x[0] - par[1])/par[2];

   Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
   return fitval;
}
void FittingWithUserDefinedFunction.cpp()
{
   TFile *f = new TFile("hsimple.root");
   
   TCanvas *c1 = new TCanvas("c1","the fit canvas",500,400);

   TH1F *hpx = (TH1F*)f->Get("hpx");

// Creates a Root function based on function fitf above
   TF1 *func = new TF1("fitf",fitf,-2,2,3);

// Sets initial values and parameter names
   func->SetParameters(100,0,1);
   func->SetParNames("Constant","Mean_value","Sigma");

// Fit histogram in range defined by function
   hpx->Fit("fitf","r");

// Gets integral of function between fit limits
   printf("Integral of function = %g\n",func->Integral(-2,2));
}



//---------------------------------------------------------------------------------
//  *******************    My Examples     ***************************************
//  *****   Fitting with a user defined function  ********************************
//---------------------------------------------------------------------------------

// definition of the fiiting function, for 1D histograms, x[0] is used; 
// for 2D, x[0],x[1] are used; for 3D, x[0], x[1], x[2] are used

double HornFormula(Double_t *x, Double_t *par)
{
  Double_t Z = par[3];
  Double_t A = par[4];
  
  Double_t stoppingpower;
  Double_t nonlinearpart;
  Double_t lightresponse;
  
  //For Combining Functions, it's better to set several parts
  stoppingpower = par[2]*A*pow(Z,2);
  nonlinearpart = stoppingpower * log(abs((x[0] +stoppingpower)/stoppingpower)); 
  lightresponse = par[0] + par[1] * (x[0] - nonlinearpart);
  return lightresponse;
}


void FitHiRA()
{
  TF1 * fit_proton=new TF1(Form("fit_4He%02d_%02d", i,j),HornFormula, 0, 320, 5); // fitting range (0,320), 5 is parameter number
  fit_proton->SetParameters(0.01,0.007,0.1,1,1);   // user defined function must be initialed before fiting
  fit_proton->FixParameter(3, 1);   // fix par[3] to 1
  fit_proton->FixParameter(4, 1);   // fix par[4] t0 1
  graph_proton[i][j]->Fit(Form("fit_4He%02d_%02d", i,j),"RC");
  fit_proton->Draw("SAME");
  fit_proton->SetLineColor(1);

}



