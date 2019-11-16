#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TNtuple.h"

void exo_j2()
{
  ifstream in;
  in.open("exo_j2.dat",ios::in);

  Double_t x, y, z, e;
  TFile *f = new TFile("exo_j2.root","UPDATE");
  TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y:z:e");

  TH1F * h1D_z = new TH1F("h1D_z","z distribution",500,0.,10.);
  TH2F * h2D_yx  = new TH2F("h2D_yx","y vs x",500,-30.,30.,100,-30.,30.);
  TH2F * h2D_zx  = new TH2F("h2D_zx","z vs x",500,-30.,30.,100,0.,10.);
  TH2F * h2D_zy  = new TH2F("h2D_zy","z vs y",500,-30.,30.,100,0.,10.);
  TH3F * h3D_zyx = new TH3F("h3D_zyx","z vs y vs x",500,-30.,30.,500,-30.,30.,100,0.,10.);
  TH3F * h3D_eyx = new TH3F("h3D_eyx","e vs y vs x",100,-30.,30.,100,-30.,30.,100,0.,10.);
  TProfile * pro_ex = new TProfile("pro_ex","profile of <e> vs x",100,-30,30);
  TProfile * pro_ey = new TProfile("pro_ey","profile of <e> vs y",100,-30,30);
  TProfile2D * pro_exy = new TProfile2D("pro_exy","profile of <e> vs x vs y",100,-30.,30.,100,-30.,30.,0,10.);

  while(in.good())
  {
    in >> x >> y >> z >> e;
    h1D_z->Fill(z);
    h2D_yx->Fill(x,y);
    h2D_zx->Fill(x,z);
    h2D_zy->Fill(y,z);
    h3D_zyx->Fill(x,y,z);
    h3D_eyx->Fill(x,y,e);
    pro_ex->Fill(x,e);
    pro_ey->Fill(y,e);
    pro_exy->Fill(x,y,e,1);
  }

  TCanvas * c1 = new TCanvas("c1","c1",1500,1000);
  c1->Divide(2,3);
  c1->cd(1);
  h1D_z->Draw();
  c1->cd(2);
  h2D_yx->Draw();
  c1->cd(3);
  h2D_zx->Draw();
  c1->cd(4);
  h2D_zy->Draw();
  c1->cd(5);
  h3D_zyx->Draw();
  c1->cd(6);
  h3D_eyx->Draw();

  TCanvas * c2 = new TCanvas("c2","c2",1500,500);
  c2->Divide(3,1);
  c2->cd(1);
  pro_ex->Draw();
  c2->cd(2);
  pro_ey->Draw();
  c2->cd(3);
  pro_exy->Draw();
/*
  in.close();
  f->WriteTObject(h1D_z,h1D_z->GetName());
  f->WriteTObject(h2D_yx,h2D_yx->GetName());
  f->WriteTObject(h2D_zx,h2D_zx->GetName());
  f->WriteTObject(h2D_zy,h2D_zy->GetName());
  f->WriteTObject(h3D_zyx,h3D_zyx->GetName());
  f->WriteTObject(h3D_eyx,h3D_eyx->GetName());
  f->WriteTObject(pro_ex,pro_ex->GetName());
  f->WriteTObject(pro_ey,pro_ey->GetName());
  f->WriteTObject(pro_exy,pro_exy->GetName());
  delete f; */

}
