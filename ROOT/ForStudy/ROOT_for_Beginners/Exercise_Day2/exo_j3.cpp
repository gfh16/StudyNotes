#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TNtuple.h"

void exo_j3()
{
  ifstream in;
  in.open("exo_j2.dat",ios::in);

  Double_t x, y, z, e;
  TFile *f = new TFile("exo_j2.root","RECREATE");
  TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y:z:e");

  TH1F * h1D_de = new TH1F("h1D_de","z distribution",1000,-1000.,1000.);
  TH2F * h2D_yx1  = new TH2F("h2D_yx1","y vs x for z(0,1)",100,-30.,30.,100,-30.,30.);
  TH2F * h2D_yx2  = new TH2F("h2D_yx2","y vs x for z(1,2)",100,-30.,30.,100,-30.,30.);
  TH2F * h2D_yx3  = new TH2F("h2D_yx3","y vs x for z(2,3)",100,-30.,30.,100,-30.,30.);

  TProfile2D * pro_zyx = new TProfile2D("pro_zyx","profile of <z> vs y vs x",100,-30.,30.,100,-30.,30.,0.,10.);
  TProfile2D * pro_eyx = new TProfile2D("pro_eyx","profile of <e> vs y vs x",100,-30.,30.,100,-30.,30.,0.,10.);

  while(in.good())
  {
    in >> x >> y >> z >> e;
    float de = e - e*x - e*x*x - e*y - e*y*y - e*y*y*y;
    h1D_de->Fill(de);

    if((z>0.0)&&(z<=1.0)) h2D_yx1->Fill(x,y);
    if((z>1.0)&&(z<=2.0)) h2D_yx2->Fill(x,y);
    if((z>2.0)&&(z<=3.0)) h2D_yx3->Fill(x,y);

    pro_zyx->Fill(x,y,z);
    pro_eyx->Fill(x,y,e);
  }

  TCanvas * c1 = new TCanvas("c1","c1",1500,1000);
  c1->Divide(2,3);
  c1->cd(1);
  h1D_de->Draw();
  c1->cd(2);
  h2D_yx1->Draw();
  c1->cd(3);
  h2D_yx2->Draw();
  c1->cd(4);
  h2D_yx3->Draw();
  c1->cd(5);
  pro_zyx->Draw();
  c1->cd(6);
  pro_eyx->Draw();

  f->WriteTObject(h1D_de,h1D_de->GetName());
  f->WriteTObject(h2D_yx1,h2D_yx1->GetName());
  f->WriteTObject(h2D_yx2,h2D_yx2->GetName());
  f->WriteTObject(h2D_yx3,h2D_yx3->GetName());
  f->WriteTObject(pro_zyx,pro_zyx->GetName());
  f->WriteTObject(pro_eyx,pro_eyx->GetName());

  in.close();
  //delete f;
  //delete c1;
  return;
}
