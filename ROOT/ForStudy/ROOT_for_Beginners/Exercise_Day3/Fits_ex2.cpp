
#include "TMath.h"


//______________________________________________________________________________
void Fits_ex2()
{
   gStyle->SetOptFit(1);
   TFile * filein = new TFile("Fits.root");
   TH1D * h1 = (TH1D*)filein->Get("hfsomme");

   TF1 * fit = new TF1("fit", "pol2(0)+gaus(3)+expo(6)", 0, 50);
   fit->SetParNames("p0","p1","p2","gausC","gausM","gaus#sigma","exp0","exp1");
   fit->SetParLimits(0, 5.0, 6.0);
   fit->SetParLimits(1,-1.0,-0.5);
   fit->SetParLimits(2, 0.,  0.5);
   fit->SetParLimits(3, 90., 95.);
   fit->SetParLimits(4, 20., 25.);
   fit->SetParLimits(5, 5.,  6.);
   fit->SetParLimits(6, 3.,  5.);
   fit->SetParLimits(7, -1., 0.);
   fit  ->SetLineColor(kBlack);
   h1->Draw();
   h1->Fit("fit");

   TF1 * dgaus = new TF1("dgaus","gaus", 0, 50);
   TF1 * dpol2 = new TF1("dpol2","pol2", 0, 50);
   TF1 * dexpo = new TF1("expo", "expo", 0, 50);
   dpol2->SetParameters(fit->GetParameter(0),fit->GetParameter(1),fit->GetParameter(2));
   dgaus->SetParameters(fit->GetParameter(3),fit->GetParameter(4),fit->GetParameter(5));
   dexpo->SetParameters(fit->GetParameter(6),fit->GetParameter(7));

   dgaus->SetLineColor(kBlue);
   dpol2->SetLineColor(kRed);
   dexpo->SetLineColor(kGreen);
   dgaus->Draw("same");
   dpol2->Draw("same");
   dexpo->Draw("same");

   gMinuit->Command("SCAn 1");
}
