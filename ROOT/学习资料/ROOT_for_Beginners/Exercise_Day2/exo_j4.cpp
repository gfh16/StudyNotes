#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TNtuple.h"

void exo_j4()
{
  ifstream in;
  in.open("exo_j2.dat",ios::in);

  Double_t x, y, z, e;
  TFile *f = new TFile("exo_j2.root","RECREATE");
  TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y:z:e");

  TH2F * h2D_yx1  = new TH2F("h2D_yx1","y vs x for z<1",100,-30.,30.,100,-30.,30.);
  TH2F * h2D_yx2  = new TH2F("h2D_yx2","y vs x for z(3,5)",100,-30.,30.,100,-30.,30.);

  TProfile2D * pro_zyx = new TProfile2D("pro_zyx","profile of <z> vs y vs x",100,-30.,30.,100,-30.,30.,0.,10.);
  TProfile2D * pro_eyx = new TProfile2D("pro_eyx","profile of <e> vs y vs x",100,-30.,30.,100,-30.,30.,0.,10.);

  while(in.good())
  {
    in >> x >> y >> z >> e;

    if((z<1.0))          h2D_yx1->Fill(x,y);
    if((z>3.0)&&(z<5.0)) h2D_yx2->Fill(x,y);

    pro_zyx->Fill(x,y,z);
    pro_eyx->Fill(x,y,e);
  }

  TCanvas * c1 = new TCanvas("c1","c1",1500,1000);
  c1->Divide(2,2);
  c1->cd(1);
  h2D_yx1->Draw("col");
  c1->cd(2);
  h2D_yx2->Draw("box");
  c1->cd(3);
  pro_zyx->Draw("zcol");
  c1->cd(4);
  pro_eyx->Draw("surf1");

  c1->SaveAs("exp_j4.gif");
  
  in.close();
  delete c1;
  return;
}
