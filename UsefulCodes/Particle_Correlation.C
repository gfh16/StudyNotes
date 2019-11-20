#include <stdlib.h>
#include <TH2.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <iostream>

#include "tree_MultiParticle_v20170226.h"
#include "../../Simulazioni/INDRA_Segmentazione/TIndraDetector.h"
#include "nucl_masses.h"
#include "MyConstants.h"
#include "MyVariables.h"
#include "MyStructureCorrelations.h"

using namespace std;

/* Arrange the N elements of ARRAY in random order.
 *  Only effective if N is much smaller than RAND_MAX;
 *  if this may not be the case, use a better random
 *  number generator. */
void Shuffle(Int_t *array, Int_t n)
{
  if (n > 1) {
    Int_t i;
    for (i = 0; i < n - 1; i++) {
      Int_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      Int_t t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

tree_MultiParticle_v20170226::tree_MultiParticle_v20170226(TTree *tree) : fChain(0) 
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Ar36_Ni58_32_MultiParticleTree.root");
    if (!f || !f->IsOpen()) {
      f = new TFile("Ar36_Ni58_32_MultiParticleTree.root");
    }
    f->GetObject("t",tree);
    
  }
  Init(tree);
}

tree_MultiParticle_v20170226::~tree_MultiParticle_v20170226()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t tree_MultiParticle_v20170226::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t tree_MultiParticle_v20170226::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void tree_MultiParticle_v20170226::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
  fChain->SetBranchAddress("Mult", &Mult, &b_Mult);
  fChain->SetBranchAddress("Mult_Source", &Mult_Source, &b_Mult_Source);
  fChain->SetBranchAddress("Mult_Source_p", &Mult_Source_p, &b_Mult_Source_p);
  fChain->SetBranchAddress("Mult_Source_d", &Mult_Source_d, &b_Mult_Source_d);
  fChain->SetBranchAddress("Mult_Source_t", &Mult_Source_t, &b_Mult_Source_t);
  fChain->SetBranchAddress("Mult_Source_3he", &Mult_Source_3he, &b_Mult_Source_3he);
  fChain->SetBranchAddress("Mult_Source_a", &Mult_Source_a, &b_Mult_Source_a);
  fChain->SetBranchAddress("Mult_Source_6he", &Mult_Source_6he, &b_Mult_Source_6he);
  fChain->SetBranchAddress("Mult_Source_lcp", &Mult_Source_lcp, &b_Mult_Source_lcp);
  fChain->SetBranchAddress("Mult_Source_imf", &Mult_Source_imf, &b_Mult_Source_imf);
  fChain->SetBranchAddress("Mult_Source_fra", &Mult_Source_fra, &b_Mult_Source_fra);
  fChain->SetBranchAddress("Z_Source_Rec", &Z_Source_Rec, &b_Z_Source_Rec);
  fChain->SetBranchAddress("A_Source_Rec", &A_Source_Rec, &b_A_Source_Rec);
  fChain->SetBranchAddress("MIni_Source_Rec", &MIni_Source_Rec, &b_MIni_Source_Rec);
  fChain->SetBranchAddress("Betax_SourceCM_lab", &Betax_SourceCM_lab, &b_Betax_SourceCM_lab);
  fChain->SetBranchAddress("Betay_SourceCM_lab", &Betay_SourceCM_lab, &b_Betay_SourceCM_lab);
  fChain->SetBranchAddress("Betaz_SourceCM_lab", &Betaz_SourceCM_lab, &b_Betaz_SourceCM_lab);
  fChain->SetBranchAddress("MFinDecay_Source_Rec", &MFinDecay_Source_Rec, &b_MFinDecay_Source_Rec);
  fChain->SetBranchAddress("Zmax_Source", &Zmax_Source, &b_Zmax_Source);
  fChain->SetBranchAddress("Amax_Source", &Amax_Source, &b_Amax_Source);
  fChain->SetBranchAddress("Mmax_Source", &Mmax_Source, &b_Mmax_Source);
  fChain->SetBranchAddress("Ekmax_Source_lab", &Ekmax_Source_lab, &b_Ekmax_Source_lab);
  fChain->SetBranchAddress("Thmax_Source_lab", &Thmax_Source_lab, &b_Thmax_Source_lab);
  fChain->SetBranchAddress("Phmax_Source_lab", &Phmax_Source_lab, &b_Phmax_Source_lab);
  fChain->SetBranchAddress("Ekmax_Source_soucms", &Ekmax_Source_soucms, &b_Ekmax_Source_soucms);
  fChain->SetBranchAddress("Thmax_Source_soucms", &Thmax_Source_soucms, &b_Thmax_Source_soucms);
  fChain->SetBranchAddress("Phmax_Source_soucms", &Phmax_Source_soucms, &b_Phmax_Source_soucms);
  fChain->SetBranchAddress("Zmax2_Source", &Zmax2_Source, &b_Zmax2_Source);
  fChain->SetBranchAddress("Zmax3_Source", &Zmax3_Source, &b_Zmax3_Source);
  fChain->SetBranchAddress("Z_Hit", Z_Hit, &b_Z_Hit);
  fChain->SetBranchAddress("A_Hit", A_Hit, &b_A_Hit);
  fChain->SetBranchAddress("Ek_Hit_lab", Ek_Hit_lab, &b_Ek_Hit_lab);
  fChain->SetBranchAddress("Th_Hit_lab", Th_Hit_lab, &b_Th_Hit_lab);
  fChain->SetBranchAddress("Ph_Hit_lab", Ph_Hit_lab, &b_Ph_Hit_lab);
  fChain->SetBranchAddress("Th_Hit_lab_Rand", Th_Hit_lab_Rand, &b_Th_Hit_lab_Rand);
  fChain->SetBranchAddress("Ph_Hit_lab_Rand", Ph_Hit_lab_Rand, &b_Ph_Hit_lab_Rand);
  fChain->SetBranchAddress("BetaX_Hit_lab", BetaX_Hit_lab, &b_BetaX_Hit_lab);
  fChain->SetBranchAddress("BetaY_Hit_lab", BetaY_Hit_lab, &b_BetaY_Hit_lab);
  fChain->SetBranchAddress("BetaZ_Hit_lab", BetaZ_Hit_lab, &b_BetaZ_Hit_lab);
  fChain->SetBranchAddress("Tel_Hit", Tel_Hit, &b_Tel_Hit);
  fChain->SetBranchAddress("Ek_Hit_cms", Ek_Hit_cms, &b_Ek_Hit_cms);
  fChain->SetBranchAddress("Th_Hit_cms", Th_Hit_cms, &b_Th_Hit_cms);
  fChain->SetBranchAddress("Ph_Hit_cms", Ph_Hit_cms, &b_Ph_Hit_cms);
  fChain->SetBranchAddress("BetaX_Hit_cms", BetaX_Hit_cms, &b_BetaX_Hit_cms);
  fChain->SetBranchAddress("BetaY_Hit_cms", BetaY_Hit_cms, &b_BetaY_Hit_cms);
  fChain->SetBranchAddress("BetaZ_Hit_cms", BetaZ_Hit_cms, &b_BetaZ_Hit_cms);
  fChain->SetBranchAddress("Ek_Hit_soucms", Ek_Hit_soucms, &b_Ek_Hit_soucms);
  fChain->SetBranchAddress("Th_Hit_soucms", Th_Hit_soucms, &b_Th_Hit_soucms);
  fChain->SetBranchAddress("Ph_Hit_soucms", Ph_Hit_soucms, &b_Ph_Hit_soucms);
  fChain->SetBranchAddress("BetaX_Hit_soucms", BetaX_Hit_soucms, &b_BetaX_Hit_soucms);
  fChain->SetBranchAddress("BetaY_Hit_soucms", BetaY_Hit_soucms, &b_BetaY_Hit_soucms);
  fChain->SetBranchAddress("BetaZ_Hit_soucms", BetaZ_Hit_soucms, &b_BetaZ_Hit_soucms);
  Notify();
  
  hnum_qrellab_betacmparlab= new TH2D("hnum_qrellab_betacmparlab","",500, -1, 999., 1000, -1., 1.);
  hnum_qrellab_betacmperlab= new TH2D("hnum_qrellab_betacmperlab","",500, -1, 999., 500, 0., 1.);
  hnum_qrellab_theta12cms90= new TH1D("hnum_qrellab_theta12cms90","",500, -1, 999.);
  hnum_qrellab             = new TH1D("hnum_qrellab","",500, -1, 999.);
  hnum_vredlab             = new TH1D("hnum_vredlab","",50, 0, 0.1);
  hnum_qrellab_qp          = new TH1D("hnum_qrellab_qp","",500, -1, 999.);
  hnum_qrellab_qt          = new TH1D("hnum_qrellab_qt","",500, -1, 999.);
  
  hden_qrellab_betacmparlab= new TH2D("hden_qrellab_betacmparlab","",500, -1, 999., 1000, -1., 1.);
  hden_qrellab_betacmperlab= new TH2D("hden_qrellab_betacmperlab","",500, -1, 999., 500, 0., 1.);
  hden_qrellab_theta12cms90= new TH1D("hden_qrellab_theta12cms90","",500, -1, 999.);
  hden_qrellab             = new TH1D("hden_qrellab","",500, -1, 999.);
  hden_vredlab             = new TH1D("hden_vredlab","",50, 0, 0.1);
  hden_qrellab_qp          = new TH1D("hden_qrellab_qp","",500, -1, 999.);
  hden_qrellab_qt          = new TH1D("hden_qrellab_qt","",500, -1, 999.);   
  
}

Bool_t tree_MultiParticle_v20170226::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

void tree_MultiParticle_v20170226::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t tree_MultiParticle_v20170226::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

void tree_MultiParticle_v20170226::Loop()
{
  //   In a ROOT session, you can do:
  //      root> .L tree_MultiParticle_v20170226.C
  //      root> tree_MultiParticle_v20170226 t
  //      root> t.GetEntry(12); // Fill t data members with entry number 12
  //      root> t.Show();       // Show values of entry 12
  //      root> t.Show(16);     // Read and show values of entry 16
  //      root> t.Loop();       // Loop on all entries
  //
  
  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntries();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
  }
}

void tree_MultiParticle_v20170226::CreateSourceCorrel(Int_t Z1, Int_t A1, Int_t Z2, Int_t A2)
{
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  
  
  //my detector INDRA
  TIndraDetector MyIndra;
  
  //Nuclear Masses
  nuclear_masses NucData;
  
  //Struttura dati sorgente
  Mon_Event_Correlations event;
  
  //Particelle da correlare
  Int_t PId1pick=(Z1*100)+A1;
  Int_t PId2pick=(Z2*100)+A2;
  
  //Ciclo su tutti gli eventi //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  for (Long64_t jentry=0; jentry<nentries;jentry++) 
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    
    // Print out event progress each 1000 events
    if ((jentry%10000)==0) 
    {
      printf("Progress: %.0f\%\n", double(jentry)/nentries*100);
    }
    ///////////////////////////////////////////
        
    // Calculate useful multiplicities of Li and Be isotopes (well identified in INDRA)
    Int_t Mult_Source_6li = 0;
    Int_t Mult_Source_7li = 0;
    Int_t Mult_Source_8li = 0;
    for (Int_t i=0; i<Mult_Source; i++)
    {
      if (Z_Hit[i]==3 && A_Hit[i]==6) 
      {
        Mult_Source_6li++;
      }
      if (Z_Hit[i]==3 && A_Hit[i]==7) 
      {
        Mult_Source_7li++;
      }
      if (Z_Hit[i]==3 && A_Hit[i]==8) 
      {
        Mult_Source_8li++;
      }
    }
    
    Int_t MultPId12 = 0;
    Int_t MultPId1 = 0;
    Int_t MultPId2 = 0;
    
    // Like particle correlations
    if ((PId1pick == 101) && (PId2pick == 101))  //pp
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_p;
      MultPId12 = Mult_Source_p;
    }
    if ((PId1pick == 102) && (PId2pick == 102))  //dd
    {
      MultPId1 = Mult_Source_d;
      MultPId2 = Mult_Source_d;
      MultPId12 = Mult_Source_d;
    }
    if ((PId1pick == 103) && (PId2pick == 103))  //tt
    {
      MultPId1 = Mult_Source_t;
      MultPId2 = Mult_Source_t;
      MultPId12 = Mult_Source_t;
    }
    if ((PId1pick == 203) && (PId2pick == 203))  //3He3He
    {
      MultPId1 = Mult_Source_3he;
      MultPId2 = Mult_Source_3he;
      MultPId12 = Mult_Source_3he;
    }
    if ((PId1pick == 204) && (PId2pick == 204))  //aa
    {
      MultPId1 = Mult_Source_a;
      MultPId2 = Mult_Source_a;
      MultPId12 = Mult_Source_a;
    }
    if ((PId1pick == 206) && (PId2pick == 206))  //6He6He
    {
      MultPId1 = Mult_Source_6he;
      MultPId2 = Mult_Source_6he;
      MultPId12 = Mult_Source_6he;
    }
    
    // Unlike particle correlations
    if ((PId1pick == 102) && (PId2pick == 204))  //da
    {
      MultPId1 = Mult_Source_d;
      MultPId2 = Mult_Source_a;
      MultPId12 = Mult_Source_d + Mult_Source_a;
    }
    if ((PId1pick == 102) && (PId2pick == 103))  //dt
    {
      MultPId1 = Mult_Source_d;
      MultPId2 = Mult_Source_t;
      MultPId12 = Mult_Source_d + Mult_Source_t;
    }
    if ((PId1pick == 101) && (PId2pick == 204))  //pa 
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_a;
      MultPId12 = Mult_Source_p + Mult_Source_a;
    }
    if ((PId1pick == 103) && (PId2pick == 204))  //ta 
    {
      MultPId1 = Mult_Source_t;
      MultPId2 = Mult_Source_a;
      MultPId12 = Mult_Source_t + Mult_Source_a;
    }
    if ((PId1pick == 101) && (PId2pick == 103))  //pt 
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_t;
      MultPId12 = Mult_Source_p + Mult_Source_t;
    }    
    if ((PId1pick == 101) && (PId2pick == 102))  //pd
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_d;
      MultPId12 = Mult_Source_p + Mult_Source_d;
    }
    if ((PId1pick == 101) && (PId2pick == 203))  //p3He
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_3he;
      MultPId12 = Mult_Source_p + Mult_Source_3he;
    }    
    if ((PId1pick == 102) && (PId2pick == 203))  //d3He 
    {
      MultPId1 = Mult_Source_d;
      MultPId2 = Mult_Source_3he;
      MultPId12 = Mult_Source_d + Mult_Source_3he;
    }
    if ((PId1pick == 203) && (PId2pick == 204))  //3Hea
    {
      MultPId1 = Mult_Source_3he;
      MultPId2 = Mult_Source_a;
      MultPId12 = Mult_Source_3he + Mult_Source_a;
    }
    if ((PId1pick == 204) && (PId2pick == 307))  //a7Li 
    {
      MultPId1 = Mult_Source_a;
      MultPId2 = Mult_Source_7li;
      MultPId12 = Mult_Source_a + Mult_Source_7li;
    }
    if ((PId1pick == 103) && (PId2pick == 203))  //t3He
    {
      MultPId1 = Mult_Source_t;
      MultPId2 = Mult_Source_3he;
      MultPId12 = Mult_Source_t + Mult_Source_3he;
    }
    if ((PId1pick == 101) && (PId2pick == 307))  //p7Li 
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_7li;
      MultPId12 = Mult_Source_p + Mult_Source_7li;
    }
    
    
    // Fill the hits buffer with picked particles only
    Int_t iHitPick = -1;
    
    // Recalculate multiplicities of particle 1 and 2 chosen for correlations
    Int_t MultPId1calc = 0;
    Int_t MultPId2calc = 0;
    
    // Ciclo sulla molteplicità della sorgente /////////////////////////////////////////////////////////////////////////////////////////////////////
    for (Int_t i=0; i<Mult_Source; i++) ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
      Int_t PId = (Z_Hit[i]*100) + A_Hit[i];
      //cout << i << " " << Z_Hit[i] << " " << A_Hit[i] << " " << PId << endl;
      if (PId==PId1pick) MultPId1calc++;  // Calculated multiplicity of particle 1
      if (PId==PId2pick) MultPId2calc++;  // Calculated multiplicity of particle 2
      if (PId==PId1pick || PId==PId2pick) {
        iHitPick++;
        //cout << iHitPick << endl;
        bufpick_PId[iHitPick] = PId;
        bufpick_Z[iHitPick] = Z_Hit[i];
        bufpick_A[iHitPick] = A_Hit[i];
        bufpick_N[iHitPick] = A_Hit[i] - Z_Hit[i];
        bufpick_Mass[iHitPick] = NucData.get_mass_Z_A(Z_Hit[i],A_Hit[i]);
        bufpick_Tel[iHitPick] = Tel_Hit[i];
        bufpick_Ekin_lab[iHitPick] = (Double_t) Ek_Hit_lab[i];
        bufpick_Theta_lab[iHitPick] = (Double_t) Th_Hit_lab[i];
        bufpick_Phi_lab[iHitPick] = (Double_t) Ph_Hit_lab[i];
        bufpick_Theta_lab_Rand[iHitPick] = (Double_t) Th_Hit_lab_Rand[i];
        bufpick_Phi_lab_Rand[iHitPick] = (Double_t) Ph_Hit_lab_Rand[i];
        bufpick_Betapar_lab[iHitPick] = (Double_t) BetaZ_Hit_lab[i];
        bufpick_Betaper_lab[iHitPick] = (Double_t) TMath::Sqrt(BetaX_Hit_lab[i]*BetaX_Hit_lab[i]+BetaY_Hit_lab[i]*BetaY_Hit_lab[i]);
        bufpick_Ekin_syscms[iHitPick] = (Double_t) Ek_Hit_cms[i];
        bufpick_Theta_syscms[iHitPick] = (Double_t) Th_Hit_cms[i];
        bufpick_Phi_syscms[iHitPick] = (Double_t) Ph_Hit_cms[i];
        bufpick_Betapar_syscms[iHitPick] = (Double_t) BetaZ_Hit_cms[i];
        bufpick_Betaper_syscms[iHitPick] = (Double_t) TMath::Sqrt(BetaX_Hit_cms[i]*BetaX_Hit_cms[i]+BetaY_Hit_cms[i]*BetaY_Hit_cms[i]);
        bufpick_Ekin_soucms[iHitPick] = (Double_t) Ek_Hit_soucms[i];
        bufpick_Theta_soucms[iHitPick] = (Double_t) Th_Hit_soucms[i];
        bufpick_Phi_soucms[iHitPick] = (Double_t) Ph_Hit_soucms[i];
        bufpick_Betapar_soucms[iHitPick] = (Double_t) BetaZ_Hit_soucms[i];
        bufpick_Betaper_soucms[iHitPick] = (Double_t) TMath::Sqrt(BetaX_Hit_soucms[i]*BetaX_Hit_soucms[i]+BetaY_Hit_soucms[i]*BetaY_Hit_soucms[i]);
        
      } // if (PId==PId1pick || PId==PId2pick)
      
    } // for (Int_t i=0; i<Mult_Source; i++) ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //cout << " ---------- End of Buffer Filling ---------- " << endl;
    
    if ((iHitPick+1) != MultPId12) 
    {
      cout << iHitPick << " " << MultPId12 << " " << PId1pick << " " << PId2pick << " " << jentry << " " << iEvt << endl;
      cout << "Something must be wrong...! " << endl;
      exit(0);
    } else 
    {
      MultPId12 = iHitPick+1;
    } // if ((iHitPick+1) != MultPId12 && (PId1pick<300 && PId2pick<300))
    
    Int_t Hits[MultPId12];
    for (Int_t i=0; i<MultPId12; i++)
    {
      Hits[i] = i;
    }
    
    // Assign the Buffer number ipBuffer = 0, 1, ..., BUFFER_LENGTH
    // This is necessary to fill up buffers of size BUFFER_LENGTH and stop (for example one can start doing coincidence and event mixing before going into filling the next buffer)
    Int_t ipBuffer = (jentry%BUFFER_LENGTH);
    
    // Eseguo questo blocco indipendentemente da quanto è la molteplicità delle particelle coinvolte ///////////////////////////////////////////////
    buf_EvtNum[ipBuffer] = EvtNum;
    buf_Mult[ipBuffer] = Mult_Source;
    buf_MultPId12[ipBuffer] = MultPId12;
    buf_MultPId1[ipBuffer] = MultPId1;
    buf_MultPId2[ipBuffer] = MultPId2;
    buf_MultPId1calc[ipBuffer] = MultPId1calc;
    buf_MultPId2calc[ipBuffer] = MultPId2calc;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Eseguito se ci sono anche solo singole //////////////////////////////////////////////////////////////////////////////////////////////////////
    if (MultPId12 > 0) /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
      buf_IndraMult[ipBuffer] = Mult;
      buf_MultZ1[ipBuffer] = Mult_Source_p + Mult_Source_d + Mult_Source_t;
      buf_MultZ2[ipBuffer] = Mult_Source_3he + Mult_Source_a + Mult_Source_6he;
      buf_MultFrag[ipBuffer] = Mult_Source_fra;
      buf_MultIMF[ipBuffer] = Mult_Source_imf;
      buf_Mult_p[ipBuffer] = Mult_Source_p;
      buf_Mult_d[ipBuffer] = Mult_Source_d;
      buf_Mult_t[ipBuffer] = Mult_Source_t;
      buf_Mult_3he[ipBuffer] = Mult_Source_3he;
      buf_Mult_a[ipBuffer] = Mult_Source_a;
      buf_Mult_6he[ipBuffer] = Mult_Source_6he;
      buf_ZSourceRec[ipBuffer] = Z_Source_Rec;
      buf_ASourceRec[ipBuffer] = A_Source_Rec;
      buf_MIniSourceRec[ipBuffer] = (Double_t) MIni_Source_Rec;
      buf_MFinDecaySourceRec[ipBuffer] = (Double_t) MFinDecay_Source_Rec;
      buf_BetaxSourceCM_lab[ipBuffer] = (Double_t) Betax_SourceCM_lab;
      buf_BetaySourceCM_lab[ipBuffer] = (Double_t) Betay_SourceCM_lab;
      buf_BetazSourceCM_lab[ipBuffer] = (Double_t) Betaz_SourceCM_lab;
      buf_Zmax_Source[ipBuffer] = Zmax_Source;
      buf_Amax_Source[ipBuffer] = Amax_Source;
      buf_Mmax_Source[ipBuffer] = Mmax_Source;
      buf_Zmax2_Source[ipBuffer] = Zmax2_Source;
      buf_Zmax3_Source[ipBuffer] = Zmax3_Source;
      buf_Ekmax_Source_lab[ipBuffer] = (Double_t) Ekmax_Source_lab;
      buf_Thmax_Source_lab[ipBuffer] = (Double_t) Thmax_Source_lab;
      buf_Phmax_Source_lab[ipBuffer] = (Double_t) Phmax_Source_lab;
      buf_Ekmax_Source_soucms[ipBuffer] = (Double_t) Ekmax_Source_soucms;
      buf_Thmax_Source_soucms[ipBuffer] = (Double_t) Thmax_Source_soucms;
      buf_Phmax_Source_soucms[ipBuffer] = (Double_t) Phmax_Source_soucms;
      
      // Shuffle the order of the hits in the event
      if (MultPId12 > 1)
      {
        Shuffle(Hits, MultPId12);
      } // if (MultPId12 > 1)
      
      // Shuffle hits in each event of the buffer by using the shuffled array Hits[MultPId12]
      for (Int_t i=0; i<MultPId12; i++) 
      {
        Int_t ishuffle = Hits[i];
        buf_Tel[i][ipBuffer] = bufpick_Tel[ishuffle];
        buf_PId[i][ipBuffer] = bufpick_PId[ishuffle];
        buf_Z[i][ipBuffer] = bufpick_Z[ishuffle];
        buf_A[i][ipBuffer] = bufpick_A[ishuffle];
        buf_N[i][ipBuffer] = bufpick_A[ishuffle] - bufpick_Z[ishuffle];
        buf_Mass[i][ipBuffer] = bufpick_Mass[ishuffle];
        buf_Ekin_lab[i][ipBuffer] = bufpick_Ekin_lab[ishuffle];
        buf_Theta_lab[i][ipBuffer] = bufpick_Theta_lab[ishuffle];
        buf_Phi_lab[i][ipBuffer] = bufpick_Phi_lab[ishuffle];
        buf_Theta_lab_Rand[i][ipBuffer] = bufpick_Theta_lab_Rand[ishuffle];
        buf_Phi_lab_Rand[i][ipBuffer] = bufpick_Phi_lab_Rand[ishuffle];
        buf_Betapar_lab[i][ipBuffer] = bufpick_Betapar_lab[ishuffle];
        buf_Betaper_lab[i][ipBuffer] = bufpick_Betaper_lab[ishuffle];
        buf_Ekin_syscms[i][ipBuffer] = bufpick_Ekin_syscms[ishuffle];
        buf_Theta_syscms[i][ipBuffer] = bufpick_Theta_syscms[ishuffle];
        buf_Phi_syscms[i][ipBuffer] = bufpick_Phi_syscms[ishuffle];
        buf_Betapar_syscms[i][ipBuffer] = bufpick_Betapar_syscms[ishuffle];
        buf_Betaper_syscms[i][ipBuffer] = bufpick_Betaper_syscms[ishuffle];
        buf_Ekin_soucms[i][ipBuffer] = bufpick_Ekin_soucms[ishuffle];
        buf_Theta_soucms[i][ipBuffer] = bufpick_Theta_soucms[ishuffle];
        buf_Phi_soucms[i][ipBuffer] = bufpick_Phi_soucms[ishuffle];
        buf_Betapar_soucms[i][ipBuffer] = bufpick_Betapar_soucms[ishuffle];
        buf_Betaper_soucms[i][ipBuffer] = bufpick_Betaper_soucms[ishuffle];
      } // for (Int_t i=0; i<MultPId12; i++)
      
      
    } // if (MultPId12 > 0) ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    // Now we do coincident and event mixing pairs /////////////////////////////////////////////////////////////////////////////////////////////////
    if (ipBuffer == BUFFER_LENGTH-1) ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
      //cout << " LET US BUILD COINCIDENT PAIRS *********" << endl;
      
      for (Int_t iBuf=0; iBuf<BUFFER_LENGTH; iBuf++) 
      {
        Int_t EvtNum1 = buf_EvtNum[iBuf];
        Int_t EvtNum2 = buf_EvtNum[iBuf];
        
        Int_t MultEvent = buf_Mult[iBuf];
        Int_t MultEvent1 = buf_Mult[iBuf];
        Int_t MultEvent2 = buf_Mult[iBuf];
        Int_t DeltaMultEvt12 = TMath::Abs(MultEvent1 - MultEvent2);
        
        Int_t MultPId1Evt1 = buf_MultPId1calc[iBuf];
        Int_t MultPId1Evt2 = buf_MultPId1calc[iBuf];
        Int_t DeltaMultPId1Evt12 = TMath::Abs(MultPId1Evt1-MultPId1Evt2);
        
        Int_t MultPId2Evt1 = buf_MultPId2calc[iBuf];
        Int_t MultPId2Evt2 = buf_MultPId2calc[iBuf];
        Int_t DeltaMultPId2Evt12 = TMath::Abs(MultPId2Evt1-MultPId2Evt2);
        
        //cout << " Coincidence pairs in event buffer: " << iBuf << endl;
        //cout << "Buffer: " << iBuf << " MultPId12: " << buf_MultPId12[iBuf] << endl;
        
        Int_t iPairCoinc = -1;
        
        
        for (Int_t hit1=0; hit1<buf_MultPId12[iBuf]-1; hit1++)
        {
          for (Int_t hit2=hit1+1; hit2<buf_MultPId12[iBuf]; hit2++)
          {
            
            Int_t Tel2 = buf_Tel[hit2][iBuf];
            Int_t Tel1 = buf_Tel[hit1][iBuf];
            
            Int_t Coinc_OK = 1;     // Coincident pair selected (1) or not selected (0): check for pile-up on same Tel
            
            if (Tel1 == Tel2) 
            {
              Coinc_OK = 0;	// Skip pile-up of pairs in the same telescope (impossible in the case of coincident pairs in Indra or Chimera)
            }
            
            if (Coinc_OK == 1) // Pile-up control
            { 
              
              // Particle IDs
              Int_t PId2 = buf_PId[hit2][iBuf];
              Int_t PId1 = buf_PId[hit1][iBuf];
              
              if ((PId1 == PId1pick && PId2 == PId2pick)||(PId1 == PId2pick && PId2 == PId1pick)) //only the selected pairs of particles
              {
                                
                Double_t M2=buf_Mass[hit2][iBuf]; // Mass of particle 1
                Double_t M1=buf_Mass[hit1][iBuf]; // Mass of particle 1
                
                Int_t Z1 = buf_Z[hit1][iBuf];
                Int_t Z2 = buf_Z[hit2][iBuf];
                
                // Reduced mass
                Double_t Mu = (M1*M2)/(M1+M2);
                
                // ----------- KINEMATICS OF PARTICLE 1 -----------------
                
                // Kinematics of particle 1 in LAB frame
                
                //////////
                
                // basic in lab
                Double_t Ekin1_lab=buf_Ekin_lab[hit1][iBuf]; // Kin energy of part 1 in lab
                Double_t Etot1_lab = Ekin1_lab + M1; // Tot energy of part 1 in lab
                Double_t Theta1_lab = buf_Theta_lab[hit1][iBuf]; // Theta of part 1 in lab
                Double_t Phi1_lab = buf_Phi_lab[hit1][iBuf]; // Phi of part 1 in lab
                Double_t Theta1_lab_Rand = buf_Theta_lab_Rand[hit1][iBuf]; // Theta of part 1 in lab
                Double_t Phi1_lab_Rand = buf_Phi_lab_Rand[hit1][iBuf]; // Phi of part 1 in lab
                Double_t beta1par_lab = buf_Betapar_lab[hit1][iBuf];
                Double_t beta1per_lab = buf_Betaper_lab[hit1][iBuf];
                
                // Convert angles in lab from Deg to Rad in lab
                Double_t Theta1_lab_rad = Theta1_lab * TMath::DegToRad();	// Theta in radians
                Double_t Phi1_lab_rad = Phi1_lab * TMath::DegToRad();       // Phi in radians
                
                // momentum in lab
                Double_t p01_lab = sqrt((Etot1_lab*Etot1_lab)-(M1*M1));    // Momentum of part 1 in lab
                Double_t p01x_lab = p01_lab*sin(Theta1_lab_rad)*cos(Phi1_lab_rad); // momentum px component in lab
                Double_t p01y_lab = p01_lab*sin(Theta1_lab_rad)*sin(Phi1_lab_rad); // momentum py component in lab
                Double_t p01z_lab = p01_lab*cos(Theta1_lab_rad);           // momentum pz component in lab
                Double_t e01_lab = Etot1_lab;							   // total energy in lab
                TLorentzVector p1_lab(p01x_lab,p01y_lab,p01z_lab,e01_lab); // Four-momentum vector of part 1 in the lab frame
                TVector3 p1v_lab = p1_lab.Vect();						   // 3-Momentum vector of part 1 in lab frame
                Double_t p01t_lab = p1v_lab.Perp();						   // Transverse momentum of part 1 in lab
                Double_t p01l_lab = p1v_lab.Z();                           // Longitudinal momentum of part 1 along beam axis in lab
                // TVector3 p1v_lab(p01x_lab, p01y_lab, p01z_lab);         // 3-Momentum vector of part 1 in lab frame
                // Double_t p01t_lab = p01_lab * sin(Theta1_lab);          // Transverse momentum of part 1 in lab frame
                
                // beta in lab
                Double_t Beta01_lab = p01_lab/Etot1_lab;                   // Beta of part 1 in lab
                Double_t Beta01x_lab = p01x_lab/Etot1_lab;				   // Beta x of part 1 in lab
                Double_t Beta01y_lab = p01y_lab/Etot1_lab;				   // Beta y of part 1 in lab
                Double_t Beta01z_lab = p01z_lab/Etot1_lab;				   // Beta z of part 1 in lab
                TVector3 Beta1v_lab(Beta01x_lab, Beta01y_lab, Beta01z_lab);// TVector3 vector beta of part 1 in lab
                Double_t Beta01_par_lab = Beta1v_lab.Z();				   // longitudinal beta of part 1 along beam axis in lab
                Double_t Beta01_per_lab = Beta1v_lab.Perp();			   // transverse beta of part 1 perpendicular to beam axis in lab
                // Rapidity in lab
                Double_t Y01_lab = (0.5 * TMath::Log((1.+Beta01_par_lab)/(1.-Beta01_par_lab)));  // rapidity in lab
                
                
                // Kinematics of particle 1 in Source cms frame
                
                // basic in Source cms frame
                Double_t Ekin1_soucms=buf_Ekin_soucms[hit1][iBuf]; // Kin energy of part 1 in QP
                Double_t Etot1_soucms = Ekin1_soucms + M1; // Tot energy of part 1 in QP
                Double_t Theta1_soucms = buf_Theta_soucms[hit1][iBuf]; // Theta of part 1 in QP
                Double_t Phi1_soucms = buf_Phi_soucms[hit1][iBuf]; // Phi of part 1 in QP
                Double_t beta1par_soucms = buf_Betapar_soucms[hit1][iBuf];
                Double_t beta1per_soucms = buf_Betaper_soucms[hit1][iBuf];
                
                // Convert angles in lab from Deg to Rad in Source
                Double_t Theta1_soucms_rad = Theta1_soucms * TMath::DegToRad();	// Theta in radians
                Double_t Phi1_soucms_rad = Phi1_soucms * TMath::DegToRad();		// Phi in radians
                
                // momentum in Source cms frame
                Double_t p01_soucms = sqrt((Etot1_soucms*Etot1_soucms)-(M1*M1));    // Momentum of part 1 in Source cms
                Double_t p01x_soucms = p01_soucms*sin(Theta1_soucms_rad)*cos(Phi1_soucms_rad); // momentum px component in Source cms
                Double_t p01y_soucms = p01_soucms*sin(Theta1_soucms_rad)*sin(Phi1_soucms_rad); // momentum py component in Source cms
                Double_t p01z_soucms = p01_soucms*cos(Theta1_soucms_rad);			   // momentum pz component in Source cms
                Double_t e01_soucms = Etot1_soucms;							   // total energy in Source cms
                TLorentzVector p1_soucms(p01x_soucms,p01y_soucms,p01z_soucms,e01_soucms); // Four-momentum vector of part 1 in the Source cms frame
                TVector3 p1v_soucms = p1_soucms.Vect();						   // 3-Momentum vector of part 1 in Source cms frame
                Double_t p01t_soucms = p1v_soucms.Perp();						   // Transverse momentum of part 1 in Source cms
                Double_t p01l_soucms = p1v_soucms.Z();						   // Longitudinal momentum of part 1 along beam axis in Source cms
                // TVector3 p1v_qp(p01x_qp, p01y_qp, p01z_qp);         // 3-Momentum vector of part 1 in Source cms frame
                // Double_t p01t_qp = p01_qp * sin(Theta1_qp);          // Transverse momentum of part 1 in Source cms frame
                
                // beta in Source cms frame
                Double_t Beta01_soucms = p01_soucms/Etot1_soucms;                   // Beta of part 1 in Source cms frame
                Double_t Beta01x_soucms = p01x_soucms/Etot1_soucms;				   // Beta x of part 1 in Source cms frame
                Double_t Beta01y_soucms = p01y_soucms/Etot1_soucms;				   // Beta y of part 1 in Source cms frame
                Double_t Beta01z_soucms = p01z_soucms/Etot1_soucms;				   // Beta z of part 1 in Source cms frame
                TVector3 Beta1v_soucms(Beta01x_soucms, Beta01y_soucms, Beta01z_soucms);// TVector3 vector beta of part 1 in Source cms frame
                Double_t Beta01_par_soucms = Beta1v_soucms.Z();				   // longitudinal beta of part 1 along beam axis in Source cms frame
                Double_t Beta01_per_soucms = Beta1v_soucms.Perp();			   // transverse beta of part 1 perpendicular to beam axis in Source cms frame
                // Rapidity in Source cms frame
                Double_t Y01_soucms = (0.5 * TMath::Log((1.+Beta01_par_soucms)/(1.-Beta01_par_soucms)));  // rapidity in Source cms frame
                
                
                // Kinematics of particle 1 in Reaction System cms frame: _syscms
                
                Double_t Ekin1_syscms=buf_Ekin_syscms[hit1][iBuf]; // Kin energy of part 1 in cms
                Double_t Etot1_syscms = Ekin1_syscms + M1; // Tot energy of part 1 in cms
                Double_t Theta1_syscms = buf_Theta_syscms[hit1][iBuf]; // Theta of part 1 in cms
                Double_t Phi1_syscms = buf_Phi_syscms[hit1][iBuf]; // Phi of part 1 in cms
                Double_t beta1par_syscms = buf_Betapar_syscms[hit1][iBuf];
                Double_t beta1per_syscms = buf_Betaper_syscms[hit1][iBuf];
                
                // Convert angles from Deg to Rad in system cms
                Double_t Theta1_syscms_rad = Theta1_syscms * TMath::DegToRad();	// Theta in radians
                Double_t Phi1_syscms_rad = Phi1_syscms * TMath::DegToRad();		// Phi in radians
                
                // momentum in rreaction system cms frame
                Double_t p01_syscms = sqrt((Etot1_syscms*Etot1_syscms)-(M1*M1));    // Momentum of part 1 in raction cms
                Double_t p01x_syscms = p01_syscms*sin(Theta1_syscms_rad)*cos(Phi1_syscms_rad); // momentum px component in reaction cms
                Double_t p01y_syscms = p01_syscms*sin(Theta1_syscms_rad)*sin(Phi1_syscms_rad); // momentum py component in reaction cms
                Double_t p01z_syscms = p01_syscms*cos(Theta1_syscms_rad);			   // momentum pz component in reaction cms
                Double_t e01_syscms = Etot1_syscms;							   // total energy in reaction cms
                TLorentzVector p1_syscms(p01x_syscms,p01y_syscms,p01z_syscms,e01_syscms); // Four-momentum vector of part 1 in the reaction cms frame
                TVector3 p1v_syscms = p1_syscms.Vect();						   // 3-Momentum vector of part 1 in reaction cms frame
                Double_t p01t_syscms = p1v_syscms.Perp();						   // Transverse momentum of part 1 in reaction cms
                Double_t p01l_syscms = p1v_syscms.Z();						   // Longitudinal momentum of part 1 along beam axis in reaction cms
                // TVector3 p1v_qp(p01x_qp, p01y_qp, p01z_qp);         // 3-Momentum vector of part 1 in reaction cms frame
                // Double_t p01t_qp = p01_qp * sin(Theta1_qp);          // Transverse momentum of part 1 in reaction cms frame
                
                // beta in reaction cms frame
                Double_t Beta01_syscms = p01_syscms/Etot1_syscms;                   // Beta of part 1 in reaction cms frame
                Double_t Beta01x_syscms = p01x_syscms/Etot1_syscms;				   // Beta x of part 1 in reaction cms frame
                Double_t Beta01y_syscms = p01y_syscms/Etot1_syscms;				   // Beta y of part 1 in reaction cms frame
                Double_t Beta01z_syscms = p01z_syscms/Etot1_syscms;				   // Beta z of part 1 in reaction cms frame
                TVector3 Beta1v_syscms(Beta01x_syscms, Beta01y_syscms, Beta01z_syscms);// TVector3 vector beta of part 1 in reaction cms frame
                Double_t Beta01_par_syscms = Beta1v_syscms.Z();				   // longitudinal beta of part 1 along beam axis in reaction cms frame
                Double_t Beta01_per_syscms = Beta1v_syscms.Perp();			   // transverse beta of part 1 perpendicular to beam axis in reaction cms frame
                // Rapidity in reaction cms frame
                Double_t Y01_syscms = (0.5 * TMath::Log((1.+Beta01_par_syscms)/(1.-Beta01_par_syscms)));  // rapidity in reaction cms frame
                
                //cout << "Coinc -- Tel1, Tel2: " << Tel1 << " " << Tel2 << "    and PId1, PId2: " << PId1 << " " << PId2 << endl;
                
                
                // ----------- KINEMATICS OF PARTICLE 2 -----------------
                
                // Kinematics of particle 2 in LAB frame
                
                // basic in lab
                Double_t Ekin2_lab=buf_Ekin_lab[hit2][iBuf]; // Kin energy of part 2 in lab
                Double_t Etot2_lab = Ekin2_lab + M2; // Tot energy of part 2 in lab
                Double_t Theta2_lab = buf_Theta_lab[hit2][iBuf]; // Theta of part 2 in lab
                Double_t Phi2_lab = buf_Phi_lab[hit2][iBuf]; // Phi of part 2 in lab
                Double_t Theta2_lab_Rand = buf_Theta_lab_Rand[hit2][iBuf]; // Theta of part 1 in lab
                Double_t Phi2_lab_Rand = buf_Phi_lab_Rand[hit2][iBuf]; // Phi of part 1 in lab
                Double_t beta2par_lab = buf_Betapar_lab[hit2][iBuf];
                Double_t beta2per_lab = buf_Betaper_lab[hit2][iBuf];
                
                // Convert angles in lab from Deg to Rad in lab
                Double_t Theta2_lab_rad = Theta2_lab * TMath::DegToRad();	// Theta in radians
                Double_t Phi2_lab_rad = Phi2_lab * TMath::DegToRad();		// Phi in radians
                
                // momentum in lab
                Double_t p02_lab = sqrt((Etot2_lab*Etot2_lab)-(M2*M2));    // Momentum of part 2 in lab
                Double_t p02x_lab = p02_lab*sin(Theta2_lab_rad)*cos(Phi2_lab_rad); // momentum px component in lab
                Double_t p02y_lab = p02_lab*sin(Theta2_lab_rad)*sin(Phi2_lab_rad); // momentum py component in lab
                Double_t p02z_lab = p02_lab*cos(Theta2_lab_rad);           // momentum pz component in lab
                Double_t e02_lab = Etot2_lab;							   // total energy in lab
                TLorentzVector p2_lab(p02x_lab,p02y_lab,p02z_lab,e02_lab); // Four-momentum vector of part 1 in the lab frame
                TVector3 p2v_lab = p2_lab.Vect();						   // 3-Momentum vector of part 2 in lab frame
                Double_t p02t_lab = p2v_lab.Perp();						   // Transverse momentum of part 2 in lab
                Double_t p02l_lab = p2v_lab.Z();                           // Longitudinal momentum of part 2 along beam axis in lab
                // TVector3 p2v_lab(p02x_lab, p02y_lab, p02z_lab);         // 3-Momentum vector of part 2 in lab frame
                // Double_t p02t_lab = p02_lab * sin(Theta2_lab);          // Transverse momentum of part 2 in lab frame
                
                // beta in lab
                Double_t Beta02_lab = p02_lab/Etot2_lab;                   // Beta of part 2 in lab
                Double_t Beta02x_lab = p02x_lab/Etot2_lab;				   // Beta x of part 2 in lab
                Double_t Beta02y_lab = p02y_lab/Etot2_lab;				   // Beta y of part 2 in lab
                Double_t Beta02z_lab = p02z_lab/Etot2_lab;				   // Beta z of part 2 in lab
                TVector3 Beta2v_lab(Beta02x_lab, Beta02y_lab, Beta02z_lab);// TVector3 vector beta of part 2 in lab
                Double_t Beta02_par_lab = Beta2v_lab.Z();				   // longitudinal beta of part 2 along beam axis in lab
                Double_t Beta02_per_lab = Beta2v_lab.Perp();			   // transverse beta of part 2 perpendicular to beam axis in lab
                // Rapidity in lab
                Double_t Y02_lab = (0.5 * TMath::Log((1.+Beta02_par_lab)/(1.-Beta02_par_lab)));  // rapidity in lab
                
                
                // Kinematics of particle 2 in Source cms cms frame
                
                // basic in Source cms cms frame
                Double_t Ekin2_soucms=buf_Ekin_soucms[hit2][iBuf]; // Kin energy of part 2 in Source cms
                Double_t Etot2_soucms = Ekin2_soucms + M2; // Tot energy of part 2 in Source cms
                Double_t Theta2_soucms = buf_Theta_soucms[hit2][iBuf]; // Theta of part 2 in Source cms
                Double_t Phi2_soucms = buf_Phi_soucms[hit2][iBuf]; // Phi of part 2 in Source cms
                Double_t beta2par_soucms = buf_Betapar_soucms[hit2][iBuf];
                Double_t beta2per_soucms = buf_Betaper_soucms[hit2][iBuf];
                
                // Convert angles in lab from Deg to Rad in Source cms
                Double_t Theta2_soucms_rad = Theta2_soucms * TMath::DegToRad();	// Theta in radians
                Double_t Phi2_soucms_rad = Phi2_soucms * TMath::DegToRad();		// Phi in radians
                
                // momentum in source cms frame
                Double_t p02_soucms = sqrt((Etot2_soucms*Etot2_soucms)-(M2*M2));    // Momentum of part 2 in Source cms
                Double_t p02x_soucms = p02_soucms*sin(Theta2_soucms_rad)*cos(Phi2_soucms_rad); // momentum px component in Source cms
                Double_t p02y_soucms = p02_soucms*sin(Theta2_soucms_rad)*sin(Phi2_soucms_rad); // momentum py component in Source cms
                Double_t p02z_soucms = p02_soucms*cos(Theta2_soucms_rad);			   // momentum pz component in Source cms
                Double_t e02_soucms = Etot2_soucms;							   // total energy in Source cms
                TLorentzVector p2_soucms(p02x_soucms,p02y_soucms,p02z_soucms,e02_soucms); // Four-momentum vector of part 2 in the Source cms frame
                TVector3 p2v_soucms = p2_soucms.Vect();						   // 3-Momentum vector of part 2 in Source cms frame
                Double_t p02t_soucms = p2v_soucms.Perp();						   // Transverse momentum of part 2 in Source cms
                Double_t p02l_soucms = p2v_soucms.Z();						   // Longitudinal momentum of part 2 along beam axis in Source cms
                // TVector3 p2v_qp(p02x_qp, p02y_qp, p02z_qp);         // 3-Momentum vector of part 2 in Source cms frame
                // Double_t p02t_qp = p02_qp * sin(Theta2_qp);          // Transverse momentum of part 2 in Source cms frame
                
                // beta in Source cms frame
                Double_t Beta02_soucms = p02_soucms/Etot2_soucms;                   // Beta of part 2 in Source cms frame
                Double_t Beta02x_soucms = p02x_soucms/Etot2_soucms;				   // Beta x of part 2 in Source cms frame
                Double_t Beta02y_soucms = p02y_soucms/Etot2_soucms;				   // Beta y of part 2 in Source cms frame
                Double_t Beta02z_soucms = p02z_soucms/Etot2_soucms;				   // Beta z of part 2 in Source cms frame
                TVector3 Beta2v_soucms(Beta02x_soucms, Beta02y_soucms, Beta02z_soucms);// TVector3 vector beta of part 2 in Source cms frame
                Double_t Beta02_par_soucms = Beta2v_soucms.Z();				   // longitudinal beta of part 2 along beam axis in Source cms frame
                Double_t Beta02_per_soucms = Beta2v_soucms.Perp();			   // transverse beta of part 2 perpendicular to beam axis in Source cms frame
                // Rapidity in Source cms frame
                Double_t Y02_soucms = (0.5 * TMath::Log((1.+Beta02_par_soucms)/(1.-Beta02_par_soucms)));  // rapidity in Source cms frame
                
                //cout << "Particle 1 : Beta velocities along Z axis: " << Beta01z_lab << " " << Beta01z_qp << endl;
                //cout << "Particle 2 : Beta velocities along Z axis: " << Beta02z_lab << " " << Beta02z_qp << endl;
                
                // Kinematics of particle 2 in Reaction System cms frame: _syscms
                
                Double_t Ekin2_syscms=buf_Ekin_syscms[hit2][iBuf]; // Kin energy of part 2 in cms
                Double_t Etot2_syscms = Ekin2_syscms + M2; // Tot energy of part 2 in cms
                Double_t Theta2_syscms = buf_Theta_syscms[hit2][iBuf]; // Theta of part 2 in cms
                Double_t Phi2_syscms = buf_Phi_syscms[hit2][iBuf]; // Phi of part 2 in cms
                Double_t beta2par_syscms = buf_Betapar_syscms[hit2][iBuf];
                Double_t beta2per_syscms = buf_Betaper_syscms[hit2][iBuf];
                
                // Convert angles in lab from Deg to Rad in system cms
                Double_t Theta2_syscms_rad = Theta2_syscms * TMath::DegToRad();	// Theta in radians
                Double_t Phi2_syscms_rad = Phi2_syscms * TMath::DegToRad();		// Phi in radians
                
                // momentum in Source cms frame
                Double_t p02_syscms = sqrt((Etot2_syscms*Etot2_syscms)-(M2*M2));    // Momentum of part 2 in raction cms
                Double_t p02x_syscms = p02_syscms*sin(Theta2_syscms_rad)*cos(Phi2_syscms_rad); // momentum px component in reaction cms
                Double_t p02y_syscms = p02_syscms*sin(Theta2_syscms_rad)*sin(Phi2_syscms_rad); // momentum py component in reaction cms
                Double_t p02z_syscms = p02_syscms*cos(Theta2_syscms_rad);			   // momentum pz component in reaction cms
                Double_t e02_syscms = Etot2_syscms;							   // total energy in reaction cms
                TLorentzVector p2_syscms(p02x_syscms,p02y_syscms,p02z_syscms,e02_syscms); // Four-momentum vector of part 2 in the reaction cms frame
                TVector3 p2v_syscms = p2_syscms.Vect();						   // 3-Momentum vector of part 2 in reaction cms frame
                Double_t p02t_syscms = p2v_syscms.Perp();						   // Transverse momentum of part 2 in reaction cms
                Double_t p02l_syscms = p2v_syscms.Z();						   // Longitudinal momentum of part 2 along beam axis in reaction cms
                
                // beta in reaction cms frame
                Double_t Beta02_syscms = p02_syscms/Etot2_syscms;                   // Beta of part 2 in reaction cms frame
                Double_t Beta02x_syscms = p02x_syscms/Etot2_syscms;				   // Beta x of part 2 in reaction cms frame
                Double_t Beta02y_syscms = p02y_syscms/Etot2_syscms;				   // Beta y of part 2 in reaction cms frame
                Double_t Beta02z_syscms = p02z_syscms/Etot2_syscms;				   // Beta z of part 2 in reaction cms frame
                TVector3 Beta2v_syscms(Beta02x_syscms, Beta02y_syscms, Beta02z_syscms);// TVector3 vector beta of part 2 in reaction cms frame
                Double_t Beta02_par_syscms = Beta2v_syscms.Z();				   // longitudinal beta of part 2 along beam axis in reaction cms frame
                Double_t Beta02_per_syscms = Beta2v_syscms.Perp();			   // transverse beta of part 2 perpendicular to beam axis in reaction cms frame
                // Rapidity in reaction cms frame
                Double_t Y02_syscms = (0.5 * TMath::Log((1.+Beta02_par_syscms)/(1.-Beta02_par_syscms)));  // rapidity in reaction cms frame
                
                // CALCULATE COINCIDENCE PAIR VARIABLES: using theta and phi at center of telescopes for all pair variables
                
                // Coincident Pair quantities in lab
                TVector3 Ptotv_lab = p1v_lab + p2v_lab; // Total TVector3 momentum of pair in lab
                TLorentzVector Ptot_lab = p1_lab + p2_lab; // Total momentum of pair in lab - Four-momentum
                Double_t Ptot_lab_x = Ptot_lab.Px();
                Double_t Ptot_lab_y = Ptot_lab.Py();
                Double_t Ptot_lab_z = Ptot_lab.Pz();
                Double_t Ptotlab = Ptot_lab.Rho();
                // Double_t Ptotlab = sqrt((Ptot_lab_x*Ptot_lab_x)+(Ptot_lab_y*Ptot_lab_y)+(Ptot_lab_z*Ptot_lab_z));
                TVector3 PtotTransv_lab;
                PtotTransv_lab.SetX(Ptot_lab_x);
                PtotTransv_lab.SetY(Ptot_lab_y);
                PtotTransv_lab.SetZ(0.);
                Double_t PtotTransvlab = PtotTransv_lab.Mag();
                // Double_t PtotTransvlab = sqrt((Ptot_lab_x*Ptot_lab_x)+(Ptot_lab_y*Ptot_lab_y));
                Double_t PtotLonglab = Ptot_lab_z;
                Double_t Ekintot_lab = Ekin1_lab + Ekin2_lab; // Tot kinetic energy of pair in lab
                Double_t Etot_lab = Etot1_lab + Etot2_lab; // Tot energy of pair in lab
                // Beta of pair CMS in lab
                TVector3 PairBeta_lab = Ptotv_lab * (1./Etot_lab);		// Beta of pair CMS in lab
                Double_t PairBetalab = PairBeta_lab.Mag();				// Magnitude of Beta of pair CMS in lab
                // Double_t PairBetalab = sqrt((PairBeta_lab.X()*PairBeta_lab.X())+(PairBeta_lab.Y()*PairBeta_lab.Y())+(PairBeta_lab.Z()*PairBeta_lab.Z()));
                Double_t PairBetaPar_lab = PairBeta_lab.Z();		// Long component of Beta of pair CMS in lab
                Double_t PairBetaPer_lab = PairBeta_lab.Perp();	// Transverse beta of pair CMS in lab
                // Double_t PairBetaPer_lab = sqrt((PairBeta_lab.X()*PairBeta_lab.X())+(PairBeta_lab.Y()*PairBeta_lab.Y()));
                Double_t PairY_lab =  (0.5 * TMath::Log((1.+PairBetaPar_lab)/(1.-PairBetaPar_lab)));  //Rapidity of pair CMS in lab
                Double_t PairTheta_lab = PairBeta_lab.Theta() * TMath::RadToDeg(); // Theta of pair CMS in lab	(degrees)
                Double_t PairPhi_lab = PairBeta_lab.Phi() * TMath::RadToDeg() + 180.; // Phi of pair CMS in lab (degrees) (the method Phi() uses -180:180)
                
                // Boost momenta of particles from the LAB (lab) to the pair CMS frame (pcms)
                TLorentzVector p1_Paircms_lab = p1_lab;	// p1_Paircms momentum of part 1 in the Pair CMS before boosting
                TLorentzVector p2_Paircms_lab = p2_lab;	// p2_Paircms momentum of part 2 in the Pair CMS before boosting
                p1_Paircms_lab.Boost(-PairBeta_lab);	// perform boosting in Pair cms for part 1
                p2_Paircms_lab.Boost(-PairBeta_lab);      // perform boosting in Pair cms for part 2
                
                // Momenta pf particle 1 and 2 in pair frame as TVector3 objects
                TVector3 p1v_Paircms_lab = p1_Paircms_lab.Vect();	// TVector3 of part 1 momentum in pair cms frame
                TVector3 p2v_Paircms_lab = p2_Paircms_lab.Vect();	// TVector3 of part 2 momentum in pair cms frame
                // TVector3 p1v_Paircms_lab(p1_Paircms_lab.Px(), p1_Paircms_lab.Py(), p1_Paircms_lab.Pz());
                // TVector3 p2v_Paircms_lab(p2_Paircms_lab.Px(), p2_Paircms_lab.Py(), p2_Paircms_lab.Pz());
                // Momentum of relative motion in pair frame as a TVector3 object: \vec{q} = 1/2 * ( \vec{p1} - \vec{p2} )
                TVector3 qv_Paircms_lab = 0.5 * (p1v_Paircms_lab - p2v_Paircms_lab);
                
                // Relative angle between momentum of relative motion and Total momentum in LAB frame
                Double_t PsiRelLAB = Ptotv_lab.Angle(qv_Paircms_lab);
                
                // Relative angle between momenta of particle 1 and 2 in the LAB frame
                Double_t Theta12RelLAB = p1v_lab.Angle(p2v_lab) * TMath::RadToDeg();
                
                // Calculate relative momentum q = |momentum of one of the particles in the Pair CMS|=|tmp11|=|tmp12| in LAB frame
                // Double_t q = sqrt((p1_Paircms_lab.Px()*p1_Paircms_lab.Px()) + (p1_Paircms_lab.Py()*p1_Paircms_lab.Py()) +      (p1_Paircms_lab.Pz()*p1_Paircms_lab.Pz()));
                Double_t q_LAB = qv_Paircms_lab.Mag();
                
                // Calculate relative velocities in LAB frame and vred = vrel/sqrt(Z1+Z2)
                Double_t vrel_LAB = q_LAB/Mu;             // Magnitude of relative velocity vector
                Double_t vred_LAB = vrel_LAB / TMath::Sqrt(Z1+Z2);  // reduced velocity to put different charges on the same correlation function
                
                
                // Coincident Pair quantities in Source cms
                TVector3 Ptotv_soucms = p1v_soucms + p2v_soucms; // Total momentum of pair in qp - Three-vector
                TLorentzVector Ptot_soucms = p1_soucms + p2_soucms; // Total momentum of pair in qp - Four-momentum
                Double_t Ptot_soucms_x = Ptot_soucms.Px();
                Double_t Ptot_soucms_y = Ptot_soucms.Py();
                Double_t Ptot_soucms_z = Ptot_soucms.Pz();
                Double_t Ptotsoucms = Ptot_soucms.Rho();
                // Double_t Ptotqp = sqrt((Ptot_soucms_x*Ptot_qp_x)+(Ptot_qp_y*Ptot_qp_y)+(Ptot_qp_z*Ptot_qp_z));
                TVector3 PtotTransv_soucms;
                PtotTransv_soucms.SetX(Ptot_soucms_x);
                PtotTransv_soucms.SetY(Ptot_soucms_y);
                PtotTransv_soucms.SetZ(0.);
                Double_t PtotTransvsoucms = PtotTransv_soucms.Mag();
                // Double_t PtotTransvqp = sqrt((Ptot_qp_x*Ptot_qp_x)+(Ptot_qp_y*Ptot_qp_y));
                Double_t PtotLongsoucms = Ptot_soucms_z;
                Double_t Ekintot_soucms = Ekin1_soucms + Ekin2_soucms; // Tot kinetic energy of pair in qp
                Double_t Etot_soucms = Etot1_soucms + Etot2_soucms; // Tot energy of pair in qp
                // Beta of pair CMS in qp
                TVector3 PairBeta_soucms = Ptotv_soucms * (1./Etot_soucms);		// Beta of pair CMS in qp frame
                Double_t PairBetasoucms = PairBeta_soucms.Mag();				// Magnitude of Beta of pair CMS in qp frame
                // Double_t PairBetaqp = sqrt((PairBeta_qp.X()*PairBeta_qp.X())+(PairBeta_qp.Y()*PairBeta_qp.Y())+(PairBeta_qp.Z()*PairBeta_qp.Z()));
                Double_t PairBetaPar_soucms = PairBeta_soucms.Z();
                Double_t PairBetaPer_soucms = PairBeta_soucms.Perp();			// Transverse beta of pair CMS in qp frame
                // Double_t PairBetaPer_qp = sqrt((PairBeta_qp.X()*PairBeta_qp.X())+(PairBeta_qp.Y()*PairBeta_qp.Y()));
                Double_t PairY_soucms =  (0.5 * TMath::Log((1.+PairBetaPar_soucms)/(1.-PairBetaPar_soucms)));  // Rapidity of pair CMS in qp frame
                Double_t PairTheta_soucms = PairBeta_soucms.Theta() * TMath::RadToDeg();				// Theta of pair CMS in qp frame (degrees)
                Double_t PairPhi_soucms = PairBeta_soucms.Phi() * TMath::RadToDeg() + 180.;             // Phi of pair CMS in qp frame (degrees) (the method Phi() uses -180:180)
                
                // Boost momenta of particles from the QP (qp) to the pair CMS frame (pcms)
                TLorentzVector p1_Paircms_soucms = p1_soucms;	// p1_Paircms momentum of part 1 in the Pair CMS before boosting
                TLorentzVector p2_Paircms_soucms = p2_soucms;	// p2_Paircms momentum of part 2 in the Pair CMS before boosting
                p1_Paircms_soucms.Boost(-PairBeta_soucms);	// perform boosting in Pair cms for part 1
                p2_Paircms_soucms.Boost(-PairBeta_soucms);      // perform boosting in Pair cms for part 2
                
                // Momenta pf particle 1 and 2 in pair frame as TVector3 objects
                TVector3 p1v_Paircms_soucms = p1_Paircms_soucms.Vect();	// TVector3 of part 1 momentum in pair cms frame
                TVector3 p2v_Paircms_soucms = p2_Paircms_soucms.Vect();	// TVector3 of part 2 momentum in pair cms frame
                // TVector3 p1v_Paircms_qp(p1_Paircms_qp.Px(), p1_Paircms_qp.Py(), p1_Paircms_qp.Pz());
                // TVector3 p2v_Paircms_qp(p2_Paircms_qp.Px(), p2_Paircms_qp.Py(), p2_Paircms_qp.Pz());
                // Momentum of relative motion in pair frame as a TVector3 object: \vec{q} = 1/2 * ( \vec{p1} - \vec{p2} )
                TVector3 qv_Paircms_soucms = 0.5 * (p1v_Paircms_soucms - p2v_Paircms_soucms);
                
                // Relative angle between momentum of relative motion and Total momentum in QP frame
                Double_t PsiRelSouCMS = Ptotv_soucms.Angle(qv_Paircms_soucms);
                
                // Relative angle between momenta of particle 1 and 2 in the QP frame
                Double_t Theta12RelSouCMS = p1v_soucms.Angle(p2v_soucms) * TMath::RadToDeg();
                
                // Calculate relative momentum q = |momentum of one of the particles in the Pair CMS|=|tmp11|=|tmp12| in QP frame
                // Double_t q = sqrt((p1_Paircms_qp.Px()*p1_Paircms_qp.Px()) + (p1_Paircms_qp.Py()*p1_Paircms_qp.Py()) +      (p1_Paircms_qp.Pz()*p1_Paircms_qp.Pz()));
                Double_t q_SouCMS = qv_Paircms_soucms.Mag();
                
                // Calculate relative velocities in Source CMS frame and vred = vrel/sqrt(Z1+Z2)
                Double_t vrel_SouCMS = q_SouCMS/Mu;             // Magnitude of relative velocity vector
                Double_t vred_SouCMS = vrel_SouCMS / TMath::Sqrt(Z1+Z2);  // reduced velocity to put different charges on the same correlation function
                
                
                // Coincident Pair quantities in reaction System cms in lab frame: syscms
                TVector3 Ptotv_syscms = p1v_syscms + p2v_syscms; // Total momentum of pair - Three-vector
                TLorentzVector Ptot_syscms = p1_syscms + p2_syscms; // Total momentum of pair - Four-momentum
                Double_t Ptot_syscms_x = Ptot_syscms.Px();
                Double_t Ptot_syscms_y = Ptot_syscms.Py();
                Double_t Ptot_syscms_z = Ptot_syscms.Pz();
                Double_t Ptotsyscms = Ptot_syscms.Rho();
                
                TVector3 PtotTransv_syscms;
                PtotTransv_syscms.SetX(Ptot_syscms_x);
                PtotTransv_syscms.SetY(Ptot_syscms_y);
                PtotTransv_syscms.SetZ(0.);
                Double_t PtotTransvsyscms = PtotTransv_syscms.Mag();
                
                Double_t PtotLongsyscms = Ptot_syscms_z;
                Double_t Ekintot_syscms = Ekin1_syscms + Ekin2_syscms; // Tot kinetic energy of pair in reaction system cms
                Double_t Etot_syscms = Etot1_syscms + Etot2_syscms; // Tot energy of pair in reaction system cms
                // Beta of pair CMS in System cms frame
                TVector3 PairBeta_syscms = Ptotv_syscms * (1./Etot_syscms);		// Beta of pair CMS in system cms frame
                Double_t PairBetasyscms = PairBeta_syscms.Mag();				// Magnitude of Beta of pair CMS in system smc frame
                
                Double_t PairBetaPar_syscms = PairBeta_syscms.Z();
                Double_t PairBetaPer_syscms = PairBeta_syscms.Perp();			// Transverse beta of pair CMS in system cms frame
                
                Double_t PairY_syscms =  (0.5 * TMath::Log((1.+PairBetaPar_syscms)/(1.-PairBetaPar_syscms)));  // Rapidity of pair CMS in system cms frame
                Double_t PairTheta_syscms = PairBeta_syscms.Theta() * TMath::RadToDeg();				// Theta of pair CMS in system cms frame (degrees)
                Double_t PairPhi_syscms = PairBeta_syscms.Phi() * TMath::RadToDeg() + 180.;             // Phi of pair CMS in system cms frame (degrees) (the method Phi() uses -180:180)
                
                // Boost momenta of particles from the Source CMS frame (soucms) to the pair CMS frame (Paircms)
                TLorentzVector p1_Paircms_syscms = p1_soucms;	// p1_Paircms momentum of part 1 in the Pair CMS before boosting
                TLorentzVector p2_Paircms_syscms = p2_soucms;	// p2_Paircms momentum of part 2 in the Pair CMS before boosting
                p1_Paircms_syscms.Boost(-PairBeta_syscms);      // perform boosting in Pair cms for part 1
                p2_Paircms_syscms.Boost(-PairBeta_syscms);      // perform boosting in Pair cms for part 2
                
                // Momenta pf particle 1 and 2 in pair frame as TVector3 objects
                TVector3 p1v_Paircms_syscms = p1_Paircms_syscms.Vect();	// TVector3 of part 1 momentum in pair cms frame
                TVector3 p2v_Paircms_syscms = p2_Paircms_syscms.Vect();	// TVector3 of part 2 momentum in pair cms frame
                // TVector3 p1v_Paircms_qp(p1_Paircms_qp.Px(), p1_Paircms_qp.Py(), p1_Paircms_qp.Pz());
                // TVector3 p2v_Paircms_qp(p2_Paircms_qp.Px(), p2_Paircms_qp.Py(), p2_Paircms_qp.Pz());
                // Momentum of relative motion in pair frame as a TVector3 object: \vec{q} = 1/2 * ( \vec{p1} - \vec{p2} )
                TVector3 qv_Paircms_syscms = 0.5 * (p1v_Paircms_syscms - p2v_Paircms_syscms);
                
                // Relative angle between momentum of relative motion and Total momentum in QP frame
                Double_t PsiRelSysCMS = Ptotv_syscms.Angle(qv_Paircms_syscms);
                
                // Relative angle between momenta of particle 1 and 2 in the QP frame
                Double_t Theta12RelSysCMS = p1v_syscms.Angle(p2v_syscms) * TMath::RadToDeg();
                
                // Calculate relative momentum q = |momentum of one of the particles in the Pair CMS|=|tmp11|=|tmp12| in QP frame
                // Double_t q = sqrt((p1_Paircms_qp.Px()*p1_Paircms_qp.Px()) + (p1_Paircms_qp.Py()*p1_Paircms_qp.Py()) +      (p1_Paircms_qp.Pz()*p1_Paircms_qp.Pz()));
                Double_t q_SysCMS = qv_Paircms_syscms.Mag();
                
                // Calculate relative velocities in Source CMS frame and vred = vrel/sqrt(Z1+Z2)
                Double_t vrel_SysCMS = q_SysCMS/Mu;             // Magnitude of relative velocity vector
                Double_t vred_SysCMS = vrel_SysCMS / TMath::Sqrt(Z1+Z2);  // reduced velocity to put different charges on the same correlation function
                
                //cout << "qrel, vrel, vred: " << q_LAB << " " << vrel_LAB << " " << vred_LAB << endl;
                
                NCoincPair++;
                
                iPairCoinc++;
                
                event.Evt1 = EvtNum1;
                event.Evt2 = EvtNum2;
                
                event.MultPId1Evt1 = MultPId1Evt1;
                event.MultPId2Evt1 = MultPId2Evt1;
                event.MultPId1Evt2 = MultPId1Evt2;
                event.MultPId2Evt2 = MultPId2Evt2;
                
                event.PId1 = PId1;
                event.PId2 = PId2;
                
                // Ring numbers
                Double_t temp1 = ((Double_t)Tel1)/100.;
                Int_t iring1 = (Int_t)temp1;
                Double_t temp2 = ((Double_t)Tel2)/100.;
                Int_t iring2 = (Int_t)temp2;
                
                event.tel1 = Tel1;
                event.tel2 = Tel2;
                event.ring1 = iring1;
                event.ring2 = iring2;
                
                event.ekin1_lab = Ekin1_lab;
                event.ekin2_lab = Ekin2_lab;
                event.ekin1_cms = Ekin1_syscms;
                event.ekin2_cms = Ekin2_syscms;
                event.ekin1_sou = Ekin1_soucms;
                event.ekin2_sou = Ekin2_soucms;
                
                event.th1_lab = Theta1_lab;
                event.th2_lab = Theta2_lab;
                event.th1_lab_Rand = Theta1_lab_Rand;
                event.th2_lab_Rand = Theta2_lab_Rand;
                event.th1_cms = Theta1_syscms;
                event.th2_cms = Theta2_syscms;
                event.th1_sou = Theta1_soucms;
                event.th2_sou = Theta2_soucms;
                
                event.ph1_lab = Phi1_lab;
                event.ph2_lab = Phi2_lab;
                event.ph1_lab_Rand = Phi1_lab_Rand;
                event.ph2_lab_Rand = Phi2_lab_Rand;
                event.ph1_cms = Phi1_syscms;
                event.ph2_cms = Phi2_syscms;
                event.ph1_sou = Phi1_soucms;
                event.ph2_sou = Phi2_soucms;
                
                event.Beta1par_lab = beta1par_lab;
                event.Beta1per_lab = beta1per_lab;
                event.Beta2par_lab = beta2par_lab;
                event.Beta2per_lab = beta2per_lab;
                
                event.Beta1par_cms = beta1par_syscms;
                event.Beta1per_cms = beta1per_syscms;
                event.Beta2par_cms = beta2par_syscms;
                event.Beta2per_cms = beta2per_syscms;
                
                event.Beta1par_sou = beta1par_soucms;
                event.Beta1per_sou = beta1per_soucms;
                event.Beta2par_sou = beta2par_soucms;
                event.Beta2per_sou = beta2per_soucms;
                
                event.betapairpar_lab = PairBetaPar_lab;
                event.betapairper_lab = PairBetaPer_lab;
                event.betapairpar_sou = PairBetaPar_soucms;
                event.betapairper_sou = PairBetaPer_soucms;
                event.betapairpar_cms = PairBetaPar_syscms;
                event.betapairper_cms = PairBetaPer_syscms;
                
                event.ptot_lab = Ptotlab;
                event.ptot_sou = Ptotsoucms;
                event.ptot_cms = Ptotsyscms;
                
                event.ypair_lab = PairY_lab;
                event.ypair_sou = PairY_soucms;
                event.ypair_cms = PairY_syscms;
                
                event.threl_lab = (p1v_lab.Angle(p2v_lab))*TMath::RadToDeg();
                event.threl_sou = (p1v_soucms.Angle(p2v_soucms))*TMath::RadToDeg();
                event.threl_cms = (p1v_syscms.Angle(p2v_syscms))*TMath::RadToDeg();
                
                // for qrel, vrel and vred it is not important what reference frame we use
                event.qrel_lab = q_LAB;
                event.Vrel_lab = vrel_LAB;
                event.Vred_lab = vred_LAB;
                
                // Fill Histograms /////////////////////////////////////////////////////////////////////////
                hnum_qrellab_betacmparlab->Fill(event.qrel_lab,event.betapairpar_lab);
                hnum_qrellab_betacmperlab->Fill(event.qrel_lab,event.betapairper_lab);
                hnum_qrellab->Fill(event.qrel_lab);
                hnum_vredlab->Fill(event.Vred_lab);
                if ((event.th1_cms>=70 && event.th1_cms<=110) && (event.th2_cms>=70 && event.th2_cms<=110)) 
                {
                  hnum_qrellab_theta12cms90->Fill(event.qrel_lab);
                }
                if ((event.Beta1par_lab>=BETA_CMS_LAB && event.Beta2par_lab>=BETA_CMS_LAB))
                {
                  hnum_qrellab_qp->Fill(event.qrel_lab);
                }
                if ((event.Beta1par_lab<BETA_CMS_LAB && event.Beta2par_lab<BETA_CMS_LAB)) 
                {
                  hnum_qrellab_qt->Fill(event.qrel_lab);
                }
                ////////////////////////////////////////////////////////////////////////////////////////////
                
              } // ((PId1 == PId1pick && PId2 == PId2pick)||(PId1 == PId2pick && PId2 == PId1pick))
              
            } 
            else 
            { // else of if (Coinc_OK == 1)
              NSkipCoincPair++;
            } // if (Coinc_OK == 1)
            
          } // (Int_t hit2=hit1+1; hit2<buf_MultPId12[iBuf]; hit2++)
          
        } // for (Int_t hit1=0; hit1<buf_MultPId12[iBuf]-1; hit1++)
        
      } // for (Int_t iBuf=0; iBuf<BUFFER_LENGTH; iBuf++)
      
    } // if (ipBuffer == BUFFER_LENGTH-1) //////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
    
  }   //Ciclo su tutti gli eventi //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  return;
}

void tree_MultiParticle_v20170226::CreateSourceUnCorrel(Int_t Z1, Int_t A1, Int_t Z2, Int_t A2)
{
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  
  
  //my detector INDRA
  TIndraDetector MyIndra;
  
  //Nuclear Masses
  nuclear_masses NucData;
  
  //Struttura dati sorgente
  Mon_Event_Correlations event;
  
  //Particelle da correlare
  Int_t PId1pick=(Z1*100)+A1;
  Int_t PId2pick=(Z2*100)+A2;  
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) 
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    
    // Print out event progress each 10000 events
    if ((jentry%10000)==0) 
    {
      printf("Progress: %.0f\%\n", double(jentry)/nentries*100);
    }
    ///////////////////////////////////////////
    
    // Calculate useful multiplicities of Li and Be isotopes (well identified in INDRA)
    Int_t Mult_Source_6li = 0;
    Int_t Mult_Source_7li = 0;
    Int_t Mult_Source_8li = 0;
    for (Int_t i=0; i<Mult_Source; i++)
    {
      if (Z_Hit[i]==3 && A_Hit[i]==6) 
      {
        Mult_Source_6li++;
      }
      if (Z_Hit[i]==3 && A_Hit[i]==7) 
      {
        Mult_Source_7li++;
      }
      if (Z_Hit[i]==3 && A_Hit[i]==8) 
      {
        Mult_Source_8li++;
      }
    }
    
    Int_t MultPId12 = 0;
    Int_t MultPId1 = 0;
    Int_t MultPId2 = 0;
    
    // Like particle correlations
    if ((PId1pick == 101) && (PId2pick == 101))  //pp
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_p;
      MultPId12 = Mult_Source_p;
    }
    if ((PId1pick == 102) && (PId2pick == 102))  //dd
    {
      MultPId1 = Mult_Source_d;
      MultPId2 = Mult_Source_d;
      MultPId12 = Mult_Source_d;
    }
    if ((PId1pick == 103) && (PId2pick == 103))  //tt
    {
      MultPId1 = Mult_Source_t;
      MultPId2 = Mult_Source_t;
      MultPId12 = Mult_Source_t;
    }
    if ((PId1pick == 203) && (PId2pick == 203))  //3He3He
    {
      MultPId1 = Mult_Source_3he;
      MultPId2 = Mult_Source_3he;
      MultPId12 = Mult_Source_3he;
    }
    if ((PId1pick == 204) && (PId2pick == 204))  //aa
    {
      MultPId1 = Mult_Source_a;
      MultPId2 = Mult_Source_a;
      MultPId12 = Mult_Source_a;
    }
    if ((PId1pick == 206) && (PId2pick == 206))  //6He6He
    {
      MultPId1 = Mult_Source_6he;
      MultPId2 = Mult_Source_6he;
      MultPId12 = Mult_Source_6he;
    }
    
    // Unlike particle correlations
    if ((PId1pick == 102) && (PId2pick == 204))  //da
    {
      MultPId1 = Mult_Source_d;
      MultPId2 = Mult_Source_a;
      MultPId12 = Mult_Source_d + Mult_Source_a;
    }
    if ((PId1pick == 102) && (PId2pick == 103))  //dt
    {
      MultPId1 = Mult_Source_d;
      MultPId2 = Mult_Source_t;
      MultPId12 = Mult_Source_d + Mult_Source_t;
    }
    if ((PId1pick == 101) && (PId2pick == 204))  //pa 
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_a;
      MultPId12 = Mult_Source_p + Mult_Source_a;
    }
    if ((PId1pick == 103) && (PId2pick == 204))  //ta 
    {
      MultPId1 = Mult_Source_t;
      MultPId2 = Mult_Source_a;
      MultPId12 = Mult_Source_t + Mult_Source_a;
    }
    if ((PId1pick == 101) && (PId2pick == 103))  //pt 
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_t;
      MultPId12 = Mult_Source_p + Mult_Source_t;
    }    
    if ((PId1pick == 101) && (PId2pick == 102))  //pd
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_d;
      MultPId12 = Mult_Source_p + Mult_Source_d;
    }
    if ((PId1pick == 101) && (PId2pick == 203))  //p3He
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_3he;
      MultPId12 = Mult_Source_p + Mult_Source_3he;
    }
    if ((PId1pick == 102) && (PId2pick == 203))  //d3He 
    {
      MultPId1 = Mult_Source_d;
      MultPId2 = Mult_Source_3he;
      MultPId12 = Mult_Source_d + Mult_Source_3he;
    }
    if ((PId1pick == 203) && (PId2pick == 204))  //3Hea
    {
      MultPId1 = Mult_Source_3he;
      MultPId2 = Mult_Source_a;
      MultPId12 = Mult_Source_3he + Mult_Source_a;
    }
    if ((PId1pick == 204) && (PId2pick == 307))  //a7Li 
    {
      MultPId1 = Mult_Source_a;
      MultPId2 = Mult_Source_7li;
      MultPId12 = Mult_Source_a + Mult_Source_7li;
    }
    if ((PId1pick == 103) && (PId2pick == 203))  //t3He
    {
      MultPId1 = Mult_Source_t;
      MultPId2 = Mult_Source_3he;
      MultPId12 = Mult_Source_t + Mult_Source_3he;
    }
    if ((PId1pick == 101) && (PId2pick == 307))  //p7Li 
    {
      MultPId1 = Mult_Source_p;
      MultPId2 = Mult_Source_7li;
      MultPId12 = Mult_Source_p + Mult_Source_7li;
    }
    
    
    // Fill the hits buffer with picked particles only
    Int_t iHitPick = -1;
    
    // Recalculate multiplicities of particle 1 and 2 chosen for correlations
    Int_t MultPId1calc = 0;
    Int_t MultPId2calc = 0;
    
    // Ciclo sulla molteplicità della sorgente /////////////////////////////////////////////////////////////////////////////////////////////////////
    for (Int_t i=0; i<Mult_Source; i++) ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
      Int_t PId = (Z_Hit[i]*100) + A_Hit[i];
      //cout << i << " " << Z_Hit[i] << " " << A_Hit[i] << " " << PId << endl;
      if (PId==PId1pick) MultPId1calc++;  // Calculated multiplicity of particle 1
      if (PId==PId2pick) MultPId2calc++;  // Calculated multiplicity of particle 2
      if (PId==PId1pick || PId==PId2pick) {
        iHitPick++;
        //cout << iHitPick << endl;
        bufpick_PId[iHitPick] = PId;
        bufpick_Z[iHitPick] = Z_Hit[i];
        bufpick_A[iHitPick] = A_Hit[i];
        bufpick_N[iHitPick] = A_Hit[i] - Z_Hit[i];
        bufpick_Mass[iHitPick] = NucData.get_mass_Z_A(Z_Hit[i],A_Hit[i]);
        bufpick_Tel[iHitPick] = Tel_Hit[i];
        bufpick_Ekin_lab[iHitPick] = (Double_t) Ek_Hit_lab[i];
        bufpick_Theta_lab[iHitPick] = (Double_t) Th_Hit_lab[i];
        bufpick_Phi_lab[iHitPick] = (Double_t) Ph_Hit_lab[i];
        bufpick_Theta_lab_Rand[iHitPick] = (Double_t) Th_Hit_lab_Rand[i];
        bufpick_Phi_lab_Rand[iHitPick] = (Double_t) Ph_Hit_lab_Rand[i];
        bufpick_Betapar_lab[iHitPick] = (Double_t) BetaZ_Hit_lab[i];
        bufpick_Betaper_lab[iHitPick] = (Double_t) TMath::Sqrt(BetaX_Hit_lab[i]*BetaX_Hit_lab[i]+BetaY_Hit_lab[i]*BetaY_Hit_lab[i]);
        bufpick_Ekin_syscms[iHitPick] = (Double_t) Ek_Hit_cms[i];
        bufpick_Theta_syscms[iHitPick] = (Double_t) Th_Hit_cms[i];
        bufpick_Phi_syscms[iHitPick] = (Double_t) Ph_Hit_cms[i];
        bufpick_Betapar_syscms[iHitPick] = (Double_t) BetaZ_Hit_cms[i];
        bufpick_Betaper_syscms[iHitPick] = (Double_t) TMath::Sqrt(BetaX_Hit_cms[i]*BetaX_Hit_cms[i]+BetaY_Hit_cms[i]*BetaY_Hit_cms[i]);
        bufpick_Ekin_soucms[iHitPick] = (Double_t) Ek_Hit_soucms[i];
        bufpick_Theta_soucms[iHitPick] = (Double_t) Th_Hit_soucms[i];
        bufpick_Phi_soucms[iHitPick] = (Double_t) Ph_Hit_soucms[i];
        bufpick_Betapar_soucms[iHitPick] = (Double_t) BetaZ_Hit_soucms[i];
        bufpick_Betaper_soucms[iHitPick] = (Double_t) TMath::Sqrt(BetaX_Hit_soucms[i]*BetaX_Hit_soucms[i]+BetaY_Hit_soucms[i]*BetaY_Hit_soucms[i]);
        
      } // if (PId==PId1pick || PId==PId2pick)
      
    } // for (Int_t i=0; i<Mult_Source; i++) ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //cout << " ---------- End of Buffer Filling ---------- " << endl;
    
    if ((iHitPick+1) != MultPId12) 
    {
      cout << iHitPick << " " << MultPId12 << " " << PId1pick << " " << PId2pick << " " << jentry << " " << iEvt << endl;
      cout << "Something must be wrong...! " << endl;
      exit(0);
    } else 
    {
      MultPId12 = iHitPick+1;
    } // if ((iHitPick+1) != MultPId12 && (PId1pick<300 && PId2pick<300))
    
    Int_t Hits[MultPId12];
    for (Int_t i=0; i<MultPId12; i++)
    {
      Hits[i] = i;
    }
    
    // Assign the Buffer number ipBuffer = 0, 1, ..., BUFFER_LENGTH
    // This is necessary to fill up buffers of size BUFFER_LENGTH and stop (for example one can start doing coincidence and event mixing before going into filling the next buffer)
    Int_t ipBuffer = (jentry%BUFFER_LENGTH);
    
    // Eseguo questo blocco indipendentemente da quanto è la molteplicità delle particelle coinvolte ///////////////////////////////////////////////
    buf_EvtNum[ipBuffer] = EvtNum;
    buf_Mult[ipBuffer] = Mult_Source;
    buf_MultPId12[ipBuffer] = MultPId12;
    buf_MultPId1[ipBuffer] = MultPId1;
    buf_MultPId2[ipBuffer] = MultPId2;
    buf_MultPId1calc[ipBuffer] = MultPId1calc;
    buf_MultPId2calc[ipBuffer] = MultPId2calc;    
    // Eseguito se ci sono anche solo singole //////////////////////////////////////////////////////////////////////////////////////////////////////
    if (MultPId12 > 0) /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
      buf_MultZ1[ipBuffer] = Mult_Source_p + Mult_Source_d + Mult_Source_t;
      buf_MultZ2[ipBuffer] = Mult_Source_3he + Mult_Source_a + Mult_Source_6he;
      buf_MultFrag[ipBuffer] = Mult_Source_fra;
      buf_MultIMF[ipBuffer] = Mult_Source_imf;
      buf_Mult_p[ipBuffer] = Mult_Source_p;
      buf_Mult_d[ipBuffer] = Mult_Source_d;
      buf_Mult_t[ipBuffer] = Mult_Source_t;
      buf_Mult_3he[ipBuffer] = Mult_Source_3he;
      buf_Mult_a[ipBuffer] = Mult_Source_a;
      buf_Mult_6he[ipBuffer] = Mult_Source_6he;
      buf_ZSourceRec[ipBuffer] = Z_Source_Rec;
      buf_ASourceRec[ipBuffer] = A_Source_Rec;
      buf_MIniSourceRec[ipBuffer] = (Double_t) MIni_Source_Rec;
      buf_MFinDecaySourceRec[ipBuffer] = (Double_t) MFinDecay_Source_Rec;
      buf_BetaxSourceCM_lab[ipBuffer] = (Double_t) Betax_SourceCM_lab;
      buf_BetaySourceCM_lab[ipBuffer] = (Double_t) Betay_SourceCM_lab;
      buf_BetazSourceCM_lab[ipBuffer] = (Double_t) Betaz_SourceCM_lab;
      buf_Zmax_Source[ipBuffer] = Zmax_Source;
      buf_Amax_Source[ipBuffer] = Amax_Source;
      buf_Mmax_Source[ipBuffer] = Mmax_Source;
      buf_Zmax2_Source[ipBuffer] = Zmax2_Source;
      buf_Zmax3_Source[ipBuffer] = Zmax3_Source;
      buf_Ekmax_Source_lab[ipBuffer] = (Double_t) Ekmax_Source_lab;
      buf_Thmax_Source_lab[ipBuffer] = (Double_t) Thmax_Source_lab;
      buf_Phmax_Source_lab[ipBuffer] = (Double_t) Phmax_Source_lab;
      buf_Ekmax_Source_soucms[ipBuffer] = (Double_t) Ekmax_Source_soucms;
      buf_Thmax_Source_soucms[ipBuffer] = (Double_t) Thmax_Source_soucms;
      buf_Phmax_Source_soucms[ipBuffer] = (Double_t) Phmax_Source_soucms;
      
      // Shuffle the order of the hits in the event
      if (MultPId12 > 1)
      {
        Shuffle(Hits, MultPId12);
      } // if (MultPId12 > 1)
      
      // Shuffle hits in each event of the buffer by using the shuffled array Hits[MultPId12]
      for (Int_t i=0; i<MultPId12; i++) 
      {
        Int_t ishuffle = Hits[i];
        buf_Tel[i][ipBuffer] = bufpick_Tel[ishuffle];
        buf_PId[i][ipBuffer] = bufpick_PId[ishuffle];
        buf_Z[i][ipBuffer] = bufpick_Z[ishuffle];
        buf_A[i][ipBuffer] = bufpick_A[ishuffle];
        buf_N[i][ipBuffer] = bufpick_A[ishuffle] - bufpick_Z[ishuffle];
        buf_Mass[i][ipBuffer] = bufpick_Mass[ishuffle];
        buf_Ekin_lab[i][ipBuffer] = bufpick_Ekin_lab[ishuffle];
        buf_Theta_lab[i][ipBuffer] = bufpick_Theta_lab[ishuffle];
        buf_Phi_lab[i][ipBuffer] = bufpick_Phi_lab[ishuffle];
        buf_Theta_lab_Rand[i][ipBuffer] = bufpick_Theta_lab_Rand[ishuffle];
        buf_Phi_lab_Rand[i][ipBuffer] = bufpick_Phi_lab_Rand[ishuffle];
        buf_Betapar_lab[i][ipBuffer] = bufpick_Betapar_lab[ishuffle];
        buf_Betaper_lab[i][ipBuffer] = bufpick_Betaper_lab[ishuffle];
        buf_Ekin_syscms[i][ipBuffer] = bufpick_Ekin_syscms[ishuffle];
        buf_Theta_syscms[i][ipBuffer] = bufpick_Theta_syscms[ishuffle];
        buf_Phi_syscms[i][ipBuffer] = bufpick_Phi_syscms[ishuffle];
        buf_Betapar_syscms[i][ipBuffer] = bufpick_Betapar_syscms[ishuffle];
        buf_Betaper_syscms[i][ipBuffer] = bufpick_Betaper_syscms[ishuffle];
        buf_Ekin_soucms[i][ipBuffer] = bufpick_Ekin_soucms[ishuffle];
        buf_Theta_soucms[i][ipBuffer] = bufpick_Theta_soucms[ishuffle];
        buf_Phi_soucms[i][ipBuffer] = bufpick_Phi_soucms[ishuffle];
        buf_Betapar_soucms[i][ipBuffer] = bufpick_Betapar_soucms[ishuffle];
        buf_Betaper_soucms[i][ipBuffer] = bufpick_Betaper_soucms[ishuffle];
      } // for (Int_t i=0; i<MultPId12; i++)
      
      
    } // if (MultPId12 > 0) ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Now we do event mixing pairs  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (ipBuffer == BUFFER_LENGTH-1) ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {   
      for (Int_t iBuf1=0; iBuf1<BUFFER_LENGTH-1; iBuf1++) 
      {
        for (Int_t iBuf2=iBuf1+1; iBuf2<BUFFER_LENGTH; iBuf2++) 
        {
          Int_t EvtNum1 = buf_EvtNum[iBuf1];
          Int_t EvtNum2 = buf_EvtNum[iBuf2];
          
          Int_t MultEvent1 = buf_Mult[iBuf1];
          Int_t MultEvent2 = buf_Mult[iBuf2];
          Int_t DeltaMultEvt12 = TMath::Abs(MultEvent1 - MultEvent2);
          
          Int_t MultPId1Evt1 = buf_MultPId1calc[iBuf1];
          Int_t MultPId1Evt2 = buf_MultPId1calc[iBuf2];
          Int_t DeltaMultPId1Evt12 = TMath::Abs(MultPId1Evt1-MultPId1Evt2);
          
          Int_t MultPId2Evt1 = buf_MultPId2calc[iBuf1];
          Int_t MultPId2Evt2 = buf_MultPId2calc[iBuf2];
          Int_t DeltaMultPId2Evt12 = TMath::Abs(MultPId2Evt1-MultPId2Evt2);
          
          
          for (Int_t hit1=0; hit1<buf_MultPId12[iBuf1]; hit1++)
          {
            for (Int_t hit2=0; hit2<buf_MultPId12[iBuf2]; hit2++)
            {
              // Telescope numbers
              Int_t Tel1 = buf_Tel[hit1][iBuf1];
              Int_t Tel2 = buf_Tel[hit2][iBuf2];
              
              // Ring numbers
              Double_t temp1 = ((Double_t)Tel1)/100.;
              Int_t iring1 = (Int_t)temp1;
              Double_t temp2 = ((Double_t)Tel2)/100.;
              Int_t iring2 = (Int_t)temp2;
              
              Int_t Uncor_OK = 1;     // Coincident pair selected (1) or not selected (0): check for pile-up on same Tel
              
              if (Tel1 == Tel2) 
              {
                Uncor_OK = 0;	// Skip pile-up of pairs in the same telescope (impossible in the case of coincident pairs in Indra or Chimera)
              }
              
              if (Uncor_OK == 1) // Pile-up control
              {
                
                // Particle IDs
                Int_t PId1 = buf_PId[hit1][iBuf1];
                Int_t PId2 = buf_PId[hit2][iBuf2];
                
                
                if ((PId1 == PId1pick && PId2 == PId2pick)||(PId1 == PId2pick && PId2 == PId1pick)) //only selected pairs of particles
                {
                  if (DeltaMultPId1Evt12>=0 && DeltaMultPId2Evt12>=0) 
                  {
                    
                    Double_t M1=buf_Mass[hit1][iBuf1]; // Mass of particle 1
                    Double_t M2=buf_Mass[hit2][iBuf2]; // Mass of particle 1
                    
                    Int_t Z1 = buf_Z[hit1][iBuf1];
                    Int_t Z2 = buf_Z[hit2][iBuf2];
                    
                    // Reduced mass
                    Double_t Mu = (M1*M2)/(M1+M2);
                    
                    
                    // ----------- KINEMATICS OF PARTICLE 1 -----------------
                    
                    // Kinematics of particle 1 in LAB frame
                    
                    //////////
                    
                    // basic in lab
                    Double_t Ekin1_lab=buf_Ekin_lab[hit1][iBuf1]; // Kin energy of part 1 in lab
                    Double_t Etot1_lab = Ekin1_lab + M1; // Tot energy of part 1 in lab
                    Double_t Theta1_lab = buf_Theta_lab[hit1][iBuf1]; // Theta of part 1 in lab
                    Double_t Phi1_lab = buf_Phi_lab[hit1][iBuf1]; // Phi of part 1 in lab
                    Double_t Theta1_lab_Rand = buf_Theta_lab_Rand[hit1][iBuf1]; // Theta of part 1 in lab
                    Double_t Phi1_lab_Rand = buf_Phi_lab_Rand[hit1][iBuf1]; // Phi of part 1 in lab
                    Double_t beta1par_lab = buf_Betapar_lab[hit1][iBuf1];
                    Double_t beta1per_lab = buf_Betaper_lab[hit1][iBuf1];
                    
                    // Convert angles in lab from Deg to Rad in lab
                    Double_t Theta1_lab_rad = Theta1_lab * TMath::DegToRad();	// Theta in radians
                    Double_t Phi1_lab_rad = Phi1_lab * TMath::DegToRad();		// Phi in radians
                    
                    // momentum in lab
                    Double_t p01_lab = sqrt((Etot1_lab*Etot1_lab)-(M1*M1));    // Momentum of part 1 in lab
                    Double_t p01x_lab = p01_lab*sin(Theta1_lab_rad)*cos(Phi1_lab_rad); // momentum px component in lab
                    Double_t p01y_lab = p01_lab*sin(Theta1_lab_rad)*sin(Phi1_lab_rad); // momentum py component in lab
                    Double_t p01z_lab = p01_lab*cos(Theta1_lab_rad);           // momentum pz component in lab
                    Double_t e01_lab = Etot1_lab;							   // total energy in lab
                    TLorentzVector p1_lab(p01x_lab,p01y_lab,p01z_lab,e01_lab); // Four-momentum vector of part 1 in the lab frame
                    TVector3 p1v_lab = p1_lab.Vect();						   // 3-Momentum vector of part 1 in lab frame
                    Double_t p01t_lab = p1v_lab.Perp();						   // Transverse momentum of part 1 in lab
                    Double_t p01l_lab = p1v_lab.Z();                           // Longitudinal momentum of part 1 along beam axis in lab
                    // TVector3 p1v_lab(p01x_lab, p01y_lab, p01z_lab);         // 3-Momentum vector of part 1 in lab frame
                    // Double_t p01t_lab = p01_lab * sin(Theta1_lab);          // Transverse momentum of part 1 in lab frame
                    
                    // beta in lab
                    Double_t Beta01_lab = p01_lab/Etot1_lab;                   // Beta of part 1 in lab
                    Double_t Beta01x_lab = p01x_lab/Etot1_lab;				   // Beta x of part 1 in lab
                    Double_t Beta01y_lab = p01y_lab/Etot1_lab;				   // Beta y of part 1 in lab
                    Double_t Beta01z_lab = p01z_lab/Etot1_lab;				   // Beta z of part 1 in lab
                    TVector3 Beta1v_lab(Beta01x_lab, Beta01y_lab, Beta01z_lab);// TVector3 vector beta of part 1 in lab
                    Double_t Beta01_par_lab = Beta1v_lab.Z();				   // longitudinal beta of part 1 along beam axis in lab
                    Double_t Beta01_per_lab = Beta1v_lab.Perp();			   // transverse beta of part 1 perpendicular to beam axis in lab
                    // Rapidity in lab
                    Double_t Y01_lab = (0.5 * TMath::Log((1.+Beta01_par_lab)/(1.-Beta01_par_lab)));  // rapidity in lab
                    
                    
                    // Kinematics of particle 1 in Source cms frame
                    
                    // basic in Source cms frame
                    Double_t Ekin1_soucms=buf_Ekin_soucms[hit1][iBuf1]; // Kin energy of part 1 in QP
                    Double_t Etot1_soucms = Ekin1_soucms + M1; // Tot energy of part 1 in QP
                    Double_t Theta1_soucms = buf_Theta_soucms[hit1][iBuf1]; // Theta of part 1 in QP
                    Double_t Phi1_soucms = buf_Phi_soucms[hit1][iBuf1]; // Phi of part 1 in QP
                    Double_t beta1par_soucms = buf_Betapar_soucms[hit1][iBuf1];
                    Double_t beta1per_soucms = buf_Betaper_soucms[hit1][iBuf1];
                    
                    // Convert angles in lab from Deg to Rad in Source
                    Double_t Theta1_soucms_rad = Theta1_soucms * TMath::DegToRad();	// Theta in radians
                    Double_t Phi1_soucms_rad = Phi1_soucms * TMath::DegToRad();		// Phi in radians
                    
                    // momentum in Source cms frame
                    Double_t p01_soucms = sqrt((Etot1_soucms*Etot1_soucms)-(M1*M1));    // Momentum of part 1 in Source cms
                    Double_t p01x_soucms = p01_soucms*sin(Theta1_soucms_rad)*cos(Phi1_soucms_rad); // momentum px component in Source cms
                    Double_t p01y_soucms = p01_soucms*sin(Theta1_soucms_rad)*sin(Phi1_soucms_rad); // momentum py component in Source cms
                    Double_t p01z_soucms = p01_soucms*cos(Theta1_soucms_rad);			   // momentum pz component in Source cms
                    Double_t e01_soucms = Etot1_soucms;							   // total energy in Source cms
                    TLorentzVector p1_soucms(p01x_soucms,p01y_soucms,p01z_soucms,e01_soucms); // Four-momentum vector of part 1 in the Source cms frame
                    TVector3 p1v_soucms = p1_soucms.Vect();						   // 3-Momentum vector of part 1 in Source cms frame
                    Double_t p01t_soucms = p1v_soucms.Perp();						   // Transverse momentum of part 1 in Source cms
                    Double_t p01l_soucms = p1v_soucms.Z();						   // Longitudinal momentum of part 1 along beam axis in Source cms
                    // TVector3 p1v_qp(p01x_qp, p01y_qp, p01z_qp);         // 3-Momentum vector of part 1 in Source cms frame
                    // Double_t p01t_qp = p01_qp * sin(Theta1_qp);          // Transverse momentum of part 1 in Source cms frame
                    
                    // beta in Source cms frame
                    Double_t Beta01_soucms = p01_soucms/Etot1_soucms;                   // Beta of part 1 in Source cms frame
                    Double_t Beta01x_soucms = p01x_soucms/Etot1_soucms;				   // Beta x of part 1 in Source cms frame
                    Double_t Beta01y_soucms = p01y_soucms/Etot1_soucms;				   // Beta y of part 1 in Source cms frame
                    Double_t Beta01z_soucms = p01z_soucms/Etot1_soucms;				   // Beta z of part 1 in Source cms frame
                    TVector3 Beta1v_soucms(Beta01x_soucms, Beta01y_soucms, Beta01z_soucms);// TVector3 vector beta of part 1 in Source cms frame
                    Double_t Beta01_par_soucms = Beta1v_soucms.Z();				   // longitudinal beta of part 1 along beam axis in Source cms frame
                    Double_t Beta01_per_soucms = Beta1v_soucms.Perp();			   // transverse beta of part 1 perpendicular to beam axis in Source cms frame
                    // Rapidity in Source cms frame
                    Double_t Y01_soucms = (0.5 * TMath::Log((1.+Beta01_par_soucms)/(1.-Beta01_par_soucms)));  // rapidity in Source cms frame
                    
                    
                    // Kinematics of particle 1 in Reaction System cms frame: _syscms
                    
                    Double_t Ekin1_syscms=buf_Ekin_syscms[hit1][iBuf1]; // Kin energy of part 1 in cms
                    Double_t Etot1_syscms = Ekin1_syscms + M1; // Tot energy of part 1 in cms
                    Double_t Theta1_syscms = buf_Theta_syscms[hit1][iBuf1]; // Theta of part 1 in cms
                    Double_t Phi1_syscms = buf_Phi_syscms[hit1][iBuf1]; // Phi of part 1 in cms
                    Double_t beta1par_syscms = buf_Betapar_syscms[hit1][iBuf1];
                    Double_t beta1per_syscms = buf_Betaper_syscms[hit1][iBuf1];
                    
                    // Convert angles from Deg to Rad in system cms
                    Double_t Theta1_syscms_rad = Theta1_syscms * TMath::DegToRad();	// Theta in radians
                    Double_t Phi1_syscms_rad = Phi1_syscms * TMath::DegToRad();		// Phi in radians
                    
                    // momentum in rreaction system cms frame
                    Double_t p01_syscms = sqrt((Etot1_syscms*Etot1_syscms)-(M1*M1));    // Momentum of part 1 in raction cms
                    Double_t p01x_syscms = p01_syscms*sin(Theta1_syscms_rad)*cos(Phi1_syscms_rad); // momentum px component in reaction cms
                    Double_t p01y_syscms = p01_syscms*sin(Theta1_syscms_rad)*sin(Phi1_syscms_rad); // momentum py component in reaction cms
                    Double_t p01z_syscms = p01_syscms*cos(Theta1_syscms_rad);			   // momentum pz component in reaction cms
                    Double_t e01_syscms = Etot1_syscms;							   // total energy in reaction cms
                    TLorentzVector p1_syscms(p01x_syscms,p01y_syscms,p01z_syscms,e01_syscms); // Four-momentum vector of part 1 in the reaction cms frame
                    TVector3 p1v_syscms = p1_syscms.Vect();						   // 3-Momentum vector of part 1 in reaction cms frame
                    Double_t p01t_syscms = p1v_syscms.Perp();						   // Transverse momentum of part 1 in reaction cms
                    Double_t p01l_syscms = p1v_syscms.Z();						   // Longitudinal momentum of part 1 along beam axis in reaction cms
                    // TVector3 p1v_qp(p01x_qp, p01y_qp, p01z_qp);         // 3-Momentum vector of part 1 in reaction cms frame
                    // Double_t p01t_qp = p01_qp * sin(Theta1_qp);          // Transverse momentum of part 1 in reaction cms frame
                    
                    // beta in reaction cms frame
                    Double_t Beta01_syscms = p01_syscms/Etot1_syscms;                   // Beta of part 1 in reaction cms frame
                    Double_t Beta01x_syscms = p01x_syscms/Etot1_syscms;				   // Beta x of part 1 in reaction cms frame
                    Double_t Beta01y_syscms = p01y_syscms/Etot1_syscms;				   // Beta y of part 1 in reaction cms frame
                    Double_t Beta01z_syscms = p01z_syscms/Etot1_syscms;				   // Beta z of part 1 in reaction cms frame
                    TVector3 Beta1v_syscms(Beta01x_syscms, Beta01y_syscms, Beta01z_syscms);// TVector3 vector beta of part 1 in reaction cms frame
                    Double_t Beta01_par_syscms = Beta1v_syscms.Z();				   // longitudinal beta of part 1 along beam axis in reaction cms frame
                    Double_t Beta01_per_syscms = Beta1v_syscms.Perp();			   // transverse beta of part 1 perpendicular to beam axis in reaction cms frame
                    // Rapidity in reaction cms frame
                    Double_t Y01_syscms = (0.5 * TMath::Log((1.+Beta01_par_syscms)/(1.-Beta01_par_syscms)));  // rapidity in reaction cms frame
                    
                    //cout << "Coinc -- Tel1, Tel2: " << Tel1 << " " << Tel2 << "    and PId1, PId2: " << PId1 << " " << PId2 << endl;
                    
                    
                    
                    
                    // ----------- KINEMATICS OF PARTICLE 2 -----------------
                    
                    // Kinematics of particle 2 in LAB frame
                    
                    // basic in lab
                    Double_t Ekin2_lab=buf_Ekin_lab[hit2][iBuf2]; // Kin energy of part 2 in lab
                    Double_t Etot2_lab = Ekin2_lab + M2; // Tot energy of part 2 in lab
                    Double_t Theta2_lab = buf_Theta_lab[hit2][iBuf2]; // Theta of part 2 in lab
                    Double_t Phi2_lab = buf_Phi_lab[hit2][iBuf2]; // Phi of part 2 in lab
                    Double_t Theta2_lab_Rand = buf_Theta_lab_Rand[hit2][iBuf2]; // Theta of part 1 in lab
                    Double_t Phi2_lab_Rand = buf_Phi_lab_Rand[hit2][iBuf2]; // Phi of part 1 in lab
                    Double_t beta2par_lab = buf_Betapar_lab[hit2][iBuf2];
                    Double_t beta2per_lab = buf_Betaper_lab[hit2][iBuf2];
                    
                    // Convert angles in lab from Deg to Rad in lab
                    Double_t Theta2_lab_rad = Theta2_lab * TMath::DegToRad();	// Theta in radians
                    Double_t Phi2_lab_rad = Phi2_lab * TMath::DegToRad();		// Phi in radians
                    
                    // momentum in lab
                    Double_t p02_lab = sqrt((Etot2_lab*Etot2_lab)-(M2*M2));    // Momentum of part 2 in lab
                    Double_t p02x_lab = p02_lab*sin(Theta2_lab_rad)*cos(Phi2_lab_rad); // momentum px component in lab
                    Double_t p02y_lab = p02_lab*sin(Theta2_lab_rad)*sin(Phi2_lab_rad); // momentum py component in lab
                    Double_t p02z_lab = p02_lab*cos(Theta2_lab_rad);           // momentum pz component in lab
                    Double_t e02_lab = Etot2_lab;							   // total energy in lab
                    TLorentzVector p2_lab(p02x_lab,p02y_lab,p02z_lab,e02_lab); // Four-momentum vector of part 1 in the lab frame
                    TVector3 p2v_lab = p2_lab.Vect();						   // 3-Momentum vector of part 2 in lab frame
                    Double_t p02t_lab = p2v_lab.Perp();						   // Transverse momentum of part 2 in lab
                    Double_t p02l_lab = p2v_lab.Z();                           // Longitudinal momentum of part 2 along beam axis in lab
                    // TVector3 p2v_lab(p02x_lab, p02y_lab, p02z_lab);         // 3-Momentum vector of part 2 in lab frame
                    // Double_t p02t_lab = p02_lab * sin(Theta2_lab);          // Transverse momentum of part 2 in lab frame
                    
                    // beta in lab
                    Double_t Beta02_lab = p02_lab/Etot2_lab;                   // Beta of part 2 in lab
                    Double_t Beta02x_lab = p02x_lab/Etot2_lab;				   // Beta x of part 2 in lab
                    Double_t Beta02y_lab = p02y_lab/Etot2_lab;				   // Beta y of part 2 in lab
                    Double_t Beta02z_lab = p02z_lab/Etot2_lab;				   // Beta z of part 2 in lab
                    TVector3 Beta2v_lab(Beta02x_lab, Beta02y_lab, Beta02z_lab);// TVector3 vector beta of part 2 in lab
                    Double_t Beta02_par_lab = Beta2v_lab.Z();				   // longitudinal beta of part 2 along beam axis in lab
                    Double_t Beta02_per_lab = Beta2v_lab.Perp();			   // transverse beta of part 2 perpendicular to beam axis in lab
                    // Rapidity in lab
                    Double_t Y02_lab = (0.5 * TMath::Log((1.+Beta02_par_lab)/(1.-Beta02_par_lab)));  // rapidity in lab
                    
                    
                    // Kinematics of particle 2 in Source cms cms frame
                    
                    // basic in Source cms cms frame
                    Double_t Ekin2_soucms=buf_Ekin_soucms[hit2][iBuf2]; // Kin energy of part 2 in Source cms
                    Double_t Etot2_soucms = Ekin2_soucms + M2; // Tot energy of part 2 in Source cms
                    Double_t Theta2_soucms = buf_Theta_soucms[hit2][iBuf2]; // Theta of part 2 in Source cms
                    Double_t Phi2_soucms = buf_Phi_soucms[hit2][iBuf2]; // Phi of part 2 in Source cms
                    Double_t beta2par_soucms = buf_Betapar_soucms[hit2][iBuf2];
                    Double_t beta2per_soucms = buf_Betaper_soucms[hit2][iBuf2];
                    
                    // Convert angles in lab from Deg to Rad in Source cms
                    Double_t Theta2_soucms_rad = Theta2_soucms * TMath::DegToRad();	// Theta in radians
                    Double_t Phi2_soucms_rad = Phi2_soucms * TMath::DegToRad();		// Phi in radians
                    
                    // momentum in source cms frame
                    Double_t p02_soucms = sqrt((Etot2_soucms*Etot2_soucms)-(M2*M2));    // Momentum of part 2 in Source cms
                    Double_t p02x_soucms = p02_soucms*sin(Theta2_soucms_rad)*cos(Phi2_soucms_rad); // momentum px component in Source cms
                    Double_t p02y_soucms = p02_soucms*sin(Theta2_soucms_rad)*sin(Phi2_soucms_rad); // momentum py component in Source cms
                    Double_t p02z_soucms = p02_soucms*cos(Theta2_soucms_rad);			   // momentum pz component in Source cms
                    Double_t e02_soucms = Etot2_soucms;							   // total energy in Source cms
                    TLorentzVector p2_soucms(p02x_soucms,p02y_soucms,p02z_soucms,e02_soucms); // Four-momentum vector of part 2 in the Source cms frame
                    TVector3 p2v_soucms = p2_soucms.Vect();						   // 3-Momentum vector of part 2 in Source cms frame
                    Double_t p02t_soucms = p2v_soucms.Perp();						   // Transverse momentum of part 2 in Source cms
                    Double_t p02l_soucms = p2v_soucms.Z();						   // Longitudinal momentum of part 2 along beam axis in Source cms
                    // TVector3 p2v_qp(p02x_qp, p02y_qp, p02z_qp);         // 3-Momentum vector of part 2 in Source cms frame
                    // Double_t p02t_qp = p02_qp * sin(Theta2_qp);          // Transverse momentum of part 2 in Source cms frame
                    
                    // beta in Source cms frame
                    Double_t Beta02_soucms = p02_soucms/Etot2_soucms;                   // Beta of part 2 in Source cms frame
                    Double_t Beta02x_soucms = p02x_soucms/Etot2_soucms;				   // Beta x of part 2 in Source cms frame
                    Double_t Beta02y_soucms = p02y_soucms/Etot2_soucms;				   // Beta y of part 2 in Source cms frame
                    Double_t Beta02z_soucms = p02z_soucms/Etot2_soucms;				   // Beta z of part 2 in Source cms frame
                    TVector3 Beta2v_soucms(Beta02x_soucms, Beta02y_soucms, Beta02z_soucms);// TVector3 vector beta of part 2 in Source cms frame
                    Double_t Beta02_par_soucms = Beta2v_soucms.Z();				   // longitudinal beta of part 2 along beam axis in Source cms frame
                    Double_t Beta02_per_soucms = Beta2v_soucms.Perp();			   // transverse beta of part 2 perpendicular to beam axis in Source cms frame
                    // Rapidity in Source cms frame
                    Double_t Y02_soucms = (0.5 * TMath::Log((1.+Beta02_par_soucms)/(1.-Beta02_par_soucms)));  // rapidity in Source cms frame
                    
                    //cout << "Particle 1 : Beta velocities along Z axis: " << Beta01z_lab << " " << Beta01z_qp << endl;
                    //cout << "Particle 2 : Beta velocities along Z axis: " << Beta02z_lab << " " << Beta02z_qp << endl;
                    
                    
                    // Kinematics of particle 2 in Reaction System cms frame: _syscms
                    
                    Double_t Ekin2_syscms=buf_Ekin_syscms[hit2][iBuf2]; // Kin energy of part 2 in cms
                    Double_t Etot2_syscms = Ekin2_syscms + M2; // Tot energy of part 2 in cms
                    Double_t Theta2_syscms = buf_Theta_syscms[hit2][iBuf2]; // Theta of part 2 in cms
                    Double_t Phi2_syscms = buf_Phi_syscms[hit2][iBuf2]; // Phi of part 2 in cms
                    Double_t beta2par_syscms = buf_Betapar_syscms[hit2][iBuf2];
                    Double_t beta2per_syscms = buf_Betaper_syscms[hit2][iBuf2];
                    
                    // Convert angles in lab from Deg to Rad in system cms
                    Double_t Theta2_syscms_rad = Theta2_syscms * TMath::DegToRad();	// Theta in radians
                    Double_t Phi2_syscms_rad = Phi2_syscms * TMath::DegToRad();		// Phi in radians
                    
                    // momentum in Source cms frame
                    Double_t p02_syscms = sqrt((Etot2_syscms*Etot2_syscms)-(M2*M2));    // Momentum of part 2 in raction cms
                    Double_t p02x_syscms = p02_syscms*sin(Theta2_syscms_rad)*cos(Phi2_syscms_rad); // momentum px component in reaction cms
                    Double_t p02y_syscms = p02_syscms*sin(Theta2_syscms_rad)*sin(Phi2_syscms_rad); // momentum py component in reaction cms
                    Double_t p02z_syscms = p02_syscms*cos(Theta2_syscms_rad);			   // momentum pz component in reaction cms
                    Double_t e02_syscms = Etot2_syscms;							   // total energy in reaction cms
                    TLorentzVector p2_syscms(p02x_syscms,p02y_syscms,p02z_syscms,e02_syscms); // Four-momentum vector of part 2 in the reaction cms frame
                    TVector3 p2v_syscms = p2_syscms.Vect();						   // 3-Momentum vector of part 2 in reaction cms frame
                    Double_t p02t_syscms = p2v_syscms.Perp();						   // Transverse momentum of part 2 in reaction cms
                    Double_t p02l_syscms = p2v_syscms.Z();						   // Longitudinal momentum of part 2 along beam axis in reaction cms
                    
                    // beta in reaction cms frame
                    Double_t Beta02_syscms = p02_syscms/Etot2_syscms;                   // Beta of part 2 in reaction cms frame
                    Double_t Beta02x_syscms = p02x_syscms/Etot2_syscms;				   // Beta x of part 2 in reaction cms frame
                    Double_t Beta02y_syscms = p02y_syscms/Etot2_syscms;				   // Beta y of part 2 in reaction cms frame
                    Double_t Beta02z_syscms = p02z_syscms/Etot2_syscms;				   // Beta z of part 2 in reaction cms frame
                    TVector3 Beta2v_syscms(Beta02x_syscms, Beta02y_syscms, Beta02z_syscms);// TVector3 vector beta of part 2 in reaction cms frame
                    Double_t Beta02_par_syscms = Beta2v_syscms.Z();				   // longitudinal beta of part 2 along beam axis in reaction cms frame
                    Double_t Beta02_per_syscms = Beta2v_syscms.Perp();			   // transverse beta of part 2 perpendicular to beam axis in reaction cms frame
                    // Rapidity in reaction cms frame
                    Double_t Y02_syscms = (0.5 * TMath::Log((1.+Beta02_par_syscms)/(1.-Beta02_par_syscms)));  // rapidity in reaction cms frame
                    
                    // CALCULATE COINCIDENCE PAIR VARIABLES
                    
                    // Coincident Pair quantities in lab
                    TVector3 Ptotv_lab = p1v_lab + p2v_lab; // Total TVector3 momentum of pair in lab
                    TLorentzVector Ptot_lab = p1_lab + p2_lab; // Total momentum of pair in lab - Four-momentum
                    Double_t Ptot_lab_x = Ptot_lab.Px();
                    Double_t Ptot_lab_y = Ptot_lab.Py();
                    Double_t Ptot_lab_z = Ptot_lab.Pz();
                    Double_t Ptotlab = Ptot_lab.Rho();
                    // Double_t Ptotlab = sqrt((Ptot_lab_x*Ptot_lab_x)+(Ptot_lab_y*Ptot_lab_y)+(Ptot_lab_z*Ptot_lab_z));
                    TVector3 PtotTransv_lab;
                    PtotTransv_lab.SetX(Ptot_lab_x);
                    PtotTransv_lab.SetY(Ptot_lab_y);
                    PtotTransv_lab.SetZ(0.);
                    Double_t PtotTransvlab = PtotTransv_lab.Mag();
                    // Double_t PtotTransvlab = sqrt((Ptot_lab_x*Ptot_lab_x)+(Ptot_lab_y*Ptot_lab_y));
                    Double_t PtotLonglab = Ptot_lab_z;
                    Double_t Ekintot_lab = Ekin1_lab + Ekin2_lab; // Tot kinetic energy of pair in lab
                    Double_t Etot_lab = Etot1_lab + Etot2_lab; // Tot energy of pair in lab
                    // Beta of pair CMS in lab
                    TVector3 PairBeta_lab = Ptotv_lab * (1./Etot_lab);		// Beta of pair CMS in lab
                    Double_t PairBetalab = PairBeta_lab.Mag();				// Magnitude of Beta of pair CMS in lab
                    // Double_t PairBetalab = sqrt((PairBeta_lab.X()*PairBeta_lab.X())+(PairBeta_lab.Y()*PairBeta_lab.Y())+(PairBeta_lab.Z()*PairBeta_lab.Z()));
                    Double_t PairBetaPar_lab = PairBeta_lab.Z();		// Long component of Beta of pair CMS in lab
                    Double_t PairBetaPer_lab = PairBeta_lab.Perp();	// Transverse beta of pair CMS in lab
                    // Double_t PairBetaPer_lab = sqrt((PairBeta_lab.X()*PairBeta_lab.X())+(PairBeta_lab.Y()*PairBeta_lab.Y()));
                    Double_t PairY_lab =  (0.5 * TMath::Log((1.+PairBetaPar_lab)/(1.-PairBetaPar_lab)));  //Rapidity of pair CMS in lab
                    Double_t PairTheta_lab = PairBeta_lab.Theta() * TMath::RadToDeg(); // Theta of pair CMS in lab	(degrees)
                    Double_t PairPhi_lab = PairBeta_lab.Phi() * TMath::RadToDeg() + 180.; // Phi of pair CMS in lab (degrees) (the method Phi() uses -180:180)
                    
                    // Boost momenta of particles from the LAB (lab) to the pair CMS frame (pcms)
                    TLorentzVector p1_Paircms_lab = p1_lab;	// p1_Paircms momentum of part 1 in the Pair CMS before boosting
                    TLorentzVector p2_Paircms_lab = p2_lab;	// p2_Paircms momentum of part 2 in the Pair CMS before boosting
                    p1_Paircms_lab.Boost(-PairBeta_lab);	// perform boosting in Pair cms for part 1
                    p2_Paircms_lab.Boost(-PairBeta_lab);      // perform boosting in Pair cms for part 2
                    
                    // Momenta pf particle 1 and 2 in pair frame as TVector3 objects
                    TVector3 p1v_Paircms_lab = p1_Paircms_lab.Vect();	// TVector3 of part 1 momentum in pair cms frame
                    TVector3 p2v_Paircms_lab = p2_Paircms_lab.Vect();	// TVector3 of part 2 momentum in pair cms frame
                    // TVector3 p1v_Paircms_lab(p1_Paircms_lab.Px(), p1_Paircms_lab.Py(), p1_Paircms_lab.Pz());
                    // TVector3 p2v_Paircms_lab(p2_Paircms_lab.Px(), p2_Paircms_lab.Py(), p2_Paircms_lab.Pz());
                    // Momentum of relative motion in pair frame as a TVector3 object: \vec{q} = 1/2 * ( \vec{p1} - \vec{p2} )
                    TVector3 qv_Paircms_lab = 0.5 * (p1v_Paircms_lab - p2v_Paircms_lab);
                    
                    // Relative angle between momentum of relative motion and Total momentum in LAB frame
                    Double_t PsiRelLAB = Ptotv_lab.Angle(qv_Paircms_lab);
                    
                    // Relative angle between momenta of particle 1 and 2 in the LAB frame
                    Double_t Theta12RelLAB = p1v_lab.Angle(p2v_lab) * TMath::RadToDeg();
                    
                    // Calculate relative momentum q = |momentum of one of the particles in the Pair CMS|=|tmp11|=|tmp12| in LAB frame
                    // Double_t q = sqrt((p1_Paircms_lab.Px()*p1_Paircms_lab.Px()) + (p1_Paircms_lab.Py()*p1_Paircms_lab.Py()) +      (p1_Paircms_lab.Pz()*p1_Paircms_lab.Pz()));
                    Double_t q_LAB = qv_Paircms_lab.Mag();
                    
                    // Calculate relative velocities in LAB frame and vred = vrel/sqrt(Z1+Z2)
                    Double_t vrel_LAB = q_LAB/Mu;             // Magnitude of relative velocity vector
                    Double_t vred_LAB = vrel_LAB / TMath::Sqrt(Z1+Z2);  // reduced velocity to put different charges on the same correlation function
                    
                    
                    // Coincident Pair quantities in Source cms
                    TVector3 Ptotv_soucms = p1v_soucms + p2v_soucms; // Total momentum of pair in qp - Three-vector
                    TLorentzVector Ptot_soucms = p1_soucms + p2_soucms; // Total momentum of pair in qp - Four-momentum
                    Double_t Ptot_soucms_x = Ptot_soucms.Px();
                    Double_t Ptot_soucms_y = Ptot_soucms.Py();
                    Double_t Ptot_soucms_z = Ptot_soucms.Pz();
                    Double_t Ptotsoucms = Ptot_soucms.Rho();
                    // Double_t Ptotqp = sqrt((Ptot_soucms_x*Ptot_qp_x)+(Ptot_qp_y*Ptot_qp_y)+(Ptot_qp_z*Ptot_qp_z));
                    TVector3 PtotTransv_soucms;
                    PtotTransv_soucms.SetX(Ptot_soucms_x);
                    PtotTransv_soucms.SetY(Ptot_soucms_y);
                    PtotTransv_soucms.SetZ(0.);
                    Double_t PtotTransvsoucms = PtotTransv_soucms.Mag();
                    // Double_t PtotTransvqp = sqrt((Ptot_qp_x*Ptot_qp_x)+(Ptot_qp_y*Ptot_qp_y));
                    Double_t PtotLongsoucms = Ptot_soucms_z;
                    Double_t Ekintot_soucms = Ekin1_soucms + Ekin2_soucms; // Tot kinetic energy of pair in qp
                    Double_t Etot_soucms = Etot1_soucms + Etot2_soucms; // Tot energy of pair in qp
                    // Beta of pair CMS in qp
                    TVector3 PairBeta_soucms = Ptotv_soucms * (1./Etot_soucms);		// Beta of pair CMS in qp frame
                    Double_t PairBetasoucms = PairBeta_soucms.Mag();				// Magnitude of Beta of pair CMS in qp frame
                    // Double_t PairBetaqp = sqrt((PairBeta_qp.X()*PairBeta_qp.X())+(PairBeta_qp.Y()*PairBeta_qp.Y())+(PairBeta_qp.Z()*PairBeta_qp.Z()));
                    Double_t PairBetaPar_soucms = PairBeta_soucms.Z();
                    Double_t PairBetaPer_soucms = PairBeta_soucms.Perp();			// Transverse beta of pair CMS in qp frame
                    // Double_t PairBetaPer_qp = sqrt((PairBeta_qp.X()*PairBeta_qp.X())+(PairBeta_qp.Y()*PairBeta_qp.Y()));
                    Double_t PairY_soucms =  (0.5 * TMath::Log((1.+PairBetaPar_soucms)/(1.-PairBetaPar_soucms)));  // Rapidity of pair CMS in qp frame
                    Double_t PairTheta_soucms = PairBeta_soucms.Theta() * TMath::RadToDeg();				// Theta of pair CMS in qp frame (degrees)
                    Double_t PairPhi_soucms = PairBeta_soucms.Phi() * TMath::RadToDeg() + 180.;             // Phi of pair CMS in qp frame (degrees) (the method Phi() uses -180:180)
                    
                    // Boost momenta of particles from the QP (qp) to the pair CMS frame (pcms)
                    TLorentzVector p1_Paircms_soucms = p1_soucms;	// p1_Paircms momentum of part 1 in the Pair CMS before boosting
                    TLorentzVector p2_Paircms_soucms = p2_soucms;	// p2_Paircms momentum of part 2 in the Pair CMS before boosting
                    p1_Paircms_soucms.Boost(-PairBeta_soucms);	// perform boosting in Pair cms for part 1
                    p2_Paircms_soucms.Boost(-PairBeta_soucms);      // perform boosting in Pair cms for part 2
                    
                    // Momenta pf particle 1 and 2 in pair frame as TVector3 objects
                    TVector3 p1v_Paircms_soucms = p1_Paircms_soucms.Vect();	// TVector3 of part 1 momentum in pair cms frame
                    TVector3 p2v_Paircms_soucms = p2_Paircms_soucms.Vect();	// TVector3 of part 2 momentum in pair cms frame
                    // TVector3 p1v_Paircms_qp(p1_Paircms_qp.Px(), p1_Paircms_qp.Py(), p1_Paircms_qp.Pz());
                    // TVector3 p2v_Paircms_qp(p2_Paircms_qp.Px(), p2_Paircms_qp.Py(), p2_Paircms_qp.Pz());
                    // Momentum of relative motion in pair frame as a TVector3 object: \vec{q} = 1/2 * ( \vec{p1} - \vec{p2} )
                    TVector3 qv_Paircms_soucms = 0.5 * (p1v_Paircms_soucms - p2v_Paircms_soucms);
                    
                    // Relative angle between momentum of relative motion and Total momentum in QP frame
                    Double_t PsiRelSouCMS = Ptotv_soucms.Angle(qv_Paircms_soucms);
                    
                    // Relative angle between momenta of particle 1 and 2 in the QP frame
                    Double_t Theta12RelSouCMS = p1v_soucms.Angle(p2v_soucms) * TMath::RadToDeg();
                    
                    // Calculate relative momentum q = |momentum of one of the particles in the Pair CMS|=|tmp11|=|tmp12| in QP frame
                    // Double_t q = sqrt((p1_Paircms_qp.Px()*p1_Paircms_qp.Px()) + (p1_Paircms_qp.Py()*p1_Paircms_qp.Py()) +      (p1_Paircms_qp.Pz()*p1_Paircms_qp.Pz()));
                    Double_t q_SouCMS = qv_Paircms_soucms.Mag();
                    
                    // Calculate relative velocities in Source CMS frame and vred = vrel/sqrt(Z1+Z2)
                    Double_t vrel_SouCMS = q_SouCMS/Mu;             // Magnitude of relative velocity vector
                    Double_t vred_SouCMS = vrel_SouCMS / TMath::Sqrt(Z1+Z2);  // reduced velocity to put different charges on the same correlation function
                    
                    
                    // Coincident Pair quantities in reaction System cms in lab frame: syscms
                    TVector3 Ptotv_syscms = p1v_syscms + p2v_syscms; // Total momentum of pair - Three-vector
                    TLorentzVector Ptot_syscms = p1_syscms + p2_syscms; // Total momentum of pair - Four-momentum
                    Double_t Ptot_syscms_x = Ptot_syscms.Px();
                    Double_t Ptot_syscms_y = Ptot_syscms.Py();
                    Double_t Ptot_syscms_z = Ptot_syscms.Pz();
                    Double_t Ptotsyscms = Ptot_syscms.Rho();
                    
                    TVector3 PtotTransv_syscms;
                    PtotTransv_syscms.SetX(Ptot_syscms_x);
                    PtotTransv_syscms.SetY(Ptot_syscms_y);
                    PtotTransv_syscms.SetZ(0.);
                    Double_t PtotTransvsyscms = PtotTransv_syscms.Mag();
                    
                    Double_t PtotLongsyscms = Ptot_syscms_z;
                    Double_t Ekintot_syscms = Ekin1_syscms + Ekin2_syscms; // Tot kinetic energy of pair in reaction system cms
                    Double_t Etot_syscms = Etot1_syscms + Etot2_syscms; // Tot energy of pair in reaction system cms
                    // Beta of pair CMS in System cms frame
                    TVector3 PairBeta_syscms = Ptotv_syscms * (1./Etot_syscms);		// Beta of pair CMS in system cms frame
                    Double_t PairBetasyscms = PairBeta_syscms.Mag();				// Magnitude of Beta of pair CMS in system smc frame
                    
                    Double_t PairBetaPar_syscms = PairBeta_syscms.Z();
                    Double_t PairBetaPer_syscms = PairBeta_syscms.Perp();			// Transverse beta of pair CMS in system cms frame
                    
                    Double_t PairY_syscms =  (0.5 * TMath::Log((1.+PairBetaPar_syscms)/(1.-PairBetaPar_syscms)));  // Rapidity of pair CMS in system cms frame
                    Double_t PairTheta_syscms = PairBeta_syscms.Theta() * TMath::RadToDeg();				// Theta of pair CMS in system cms frame (degrees)
                    Double_t PairPhi_syscms = PairBeta_syscms.Phi() * TMath::RadToDeg() + 180.;             // Phi of pair CMS in system cms frame (degrees) (the method Phi() uses -180:180)
                    
                    // Boost momenta of particles from the Source CMS frame (soucms) to the pair CMS frame (Paircms)
                    TLorentzVector p1_Paircms_syscms = p1_soucms;	// p1_Paircms momentum of part 1 in the Pair CMS before boosting
                    TLorentzVector p2_Paircms_syscms = p2_soucms;	// p2_Paircms momentum of part 2 in the Pair CMS before boosting
                    p1_Paircms_syscms.Boost(-PairBeta_syscms);      // perform boosting in Pair cms for part 1
                    p2_Paircms_syscms.Boost(-PairBeta_syscms);      // perform boosting in Pair cms for part 2
                    
                    // Momenta pf particle 1 and 2 in pair frame as TVector3 objects
                    TVector3 p1v_Paircms_syscms = p1_Paircms_syscms.Vect();	// TVector3 of part 1 momentum in pair cms frame
                    TVector3 p2v_Paircms_syscms = p2_Paircms_syscms.Vect();	// TVector3 of part 2 momentum in pair cms frame
                    // TVector3 p1v_Paircms_qp(p1_Paircms_qp.Px(), p1_Paircms_qp.Py(), p1_Paircms_qp.Pz());
                    // TVector3 p2v_Paircms_qp(p2_Paircms_qp.Px(), p2_Paircms_qp.Py(), p2_Paircms_qp.Pz());
                    // Momentum of relative motion in pair frame as a TVector3 object: \vec{q} = 1/2 * ( \vec{p1} - \vec{p2} )
                    TVector3 qv_Paircms_syscms = 0.5 * (p1v_Paircms_syscms - p2v_Paircms_syscms);
                    
                    // Relative angle between momentum of relative motion and Total momentum in QP frame
                    Double_t PsiRelSysCMS = Ptotv_syscms.Angle(qv_Paircms_syscms);
                    
                    // Relative angle between momenta of particle 1 and 2 in the QP frame
                    Double_t Theta12RelSysCMS = p1v_syscms.Angle(p2v_syscms) * TMath::RadToDeg();
                    
                    // Calculate relative momentum q = |momentum of one of the particles in the Pair CMS|=|tmp11|=|tmp12| in QP frame
                    // Double_t q = sqrt((p1_Paircms_qp.Px()*p1_Paircms_qp.Px()) + (p1_Paircms_qp.Py()*p1_Paircms_qp.Py()) +      (p1_Paircms_qp.Pz()*p1_Paircms_qp.Pz()));
                    Double_t q_SysCMS = qv_Paircms_syscms.Mag();
                    
                    // Calculate relative velocities in Source CMS frame and vred = vrel/sqrt(Z1+Z2)
                    Double_t vrel_SysCMS = q_SysCMS/Mu;             // Magnitude of relative velocity vector
                    Double_t vred_SysCMS = vrel_SysCMS / TMath::Sqrt(Z1+Z2);  // reduced velocity to put different charges on the same correlation function
                    
                    
                    /*
                     *                                    cout << "Coinc PId1, PId2: " << PId1 << " " << PId2 << endl;
                     *                                    cout << "    Energies E1lab, E2lab: " << Ekin1_lab << " " << Ekin2_lab << endl;
                     *                                    //cout << "    Relative momentum in lab and PLF: " << q_LAB << " " << q_QP << endl;
                     */
                    
                    NUncorPair++;
                    
                    event.Evt1 = EvtNum1;
                    event.Evt2 = EvtNum2;
                    
                    event.MultPId1Evt1 = MultPId1Evt1;
                    event.MultPId2Evt1 = MultPId2Evt1;
                    event.MultPId1Evt2 = MultPId1Evt2;
                    event.MultPId2Evt2 = MultPId2Evt2;
                    
                    event.PId1 = PId1;
                    event.PId2 = PId2;
                    
                    // Ring numbers
                    Double_t temp1 = ((Double_t)Tel1)/100.;
                    Int_t iring1 = (Int_t)temp1;
                    Double_t temp2 = ((Double_t)Tel2)/100.;
                    Int_t iring2 = (Int_t)temp2;
                    
                    event.tel1 = Tel1;
                    event.tel2 = Tel2;
                    event.ring1 = iring1;
                    event.ring2 = iring2;
                    
                    event.ekin1_lab = Ekin1_lab;
                    event.ekin2_lab = Ekin2_lab;
                    event.ekin1_cms = Ekin1_syscms;
                    event.ekin2_cms = Ekin2_syscms;
                    event.ekin1_sou = Ekin1_soucms;
                    event.ekin2_sou = Ekin2_soucms;
                    
                    event.th1_lab = Theta1_lab;
                    event.th2_lab = Theta2_lab;
                    event.th1_lab_Rand = Theta1_lab_Rand;
                    event.th2_lab_Rand = Theta2_lab_Rand;
                    event.th1_cms = Theta1_syscms;
                    event.th2_cms = Theta2_syscms;
                    event.th1_sou = Theta1_soucms;
                    event.th2_sou = Theta2_soucms;
                    
                    event.ph1_lab = Phi1_lab;
                    event.ph2_lab = Phi2_lab;
                    event.ph1_lab_Rand = Phi1_lab_Rand;
                    event.ph2_lab_Rand = Phi2_lab_Rand;
                    event.ph1_cms = Phi1_syscms;
                    event.ph2_cms = Phi2_syscms;
                    event.ph1_sou = Phi1_soucms;
                    event.ph2_sou = Phi2_soucms;
                    
                    event.Beta1par_lab = beta1par_lab;
                    event.Beta1per_lab = beta1per_lab;
                    event.Beta2par_lab = beta2par_lab;
                    event.Beta2per_lab = beta2per_lab;
                    
                    event.Beta1par_cms = beta1par_syscms;
                    event.Beta1per_cms = beta1per_syscms;
                    event.Beta2par_cms = beta2par_syscms;
                    event.Beta2per_cms = beta2per_syscms;
                    
                    event.Beta1par_sou = beta1par_soucms;
                    event.Beta1per_sou = beta1per_soucms;
                    event.Beta2par_sou = beta2par_soucms;
                    event.Beta2per_sou = beta2per_soucms;
                    
                    event.betapairpar_lab = PairBetaPar_lab;
                    event.betapairper_lab = PairBetaPer_lab;
                    event.betapairpar_sou = PairBetaPar_soucms;
                    event.betapairper_sou = PairBetaPer_soucms;
                    event.betapairpar_cms = PairBetaPar_syscms;
                    event.betapairper_cms = PairBetaPer_syscms;
                    
                    event.ptot_lab = Ptotlab;
                    event.ptot_sou = Ptotsoucms;
                    event.ptot_cms = Ptotsyscms;
                    
                    event.ypair_lab = PairY_lab;
                    event.ypair_sou = PairY_soucms;
                    event.ypair_cms = PairY_syscms;
                    
                    event.threl_lab = (p1v_lab.Angle(p2v_lab))*TMath::RadToDeg();
                    event.threl_sou = (p1v_soucms.Angle(p2v_soucms))*TMath::RadToDeg();
                    event.threl_cms = (p1v_syscms.Angle(p2v_syscms))*TMath::RadToDeg();
                    
                    // for qrel, vrel and vred it is not important what reference frame we use
                    event.qrel_lab = q_LAB;
                    event.Vrel_lab = vrel_LAB;
                    event.Vred_lab = vred_LAB;
                    event.qrel_sou = q_SouCMS;
                    event.Vrel_sou = vrel_SouCMS;
                    event.Vred_sou = vred_SouCMS;
                    
                    // Fill Histograms ////////////////////////////////////////////////////////////////////////
                    hden_qrellab_betacmparlab->Fill(event.qrel_lab,event.betapairpar_lab);
                    hden_qrellab_betacmperlab->Fill(event.qrel_lab,event.betapairper_lab);
                    hden_qrellab->Fill(event.qrel_lab);
                    hden_vredlab->Fill(event.Vred_lab);
                    if ((event.th1_cms>=70 && event.th1_cms<=110) && (event.th2_cms>=70 && event.th2_cms<=110))
                    {
                      hden_qrellab_theta12cms90->Fill(event.qrel_lab);
                    }
                    if ((event.Beta1par_lab>=BETA_CMS_LAB && event.Beta2par_lab>=BETA_CMS_LAB)) 
                    {
                      hden_qrellab_qp->Fill(event.qrel_lab);
                    }
                    if ((event.Beta1par_lab<BETA_CMS_LAB && event.Beta2par_lab<BETA_CMS_LAB))
                    {
                      hden_qrellab_qt->Fill(event.qrel_lab);
                    }
                    ///////////////////////////////////////////////////////////////////////////////////////////
                    
                  } // if (DeltaMultPId1Evt12==0 && DeltaMultPId2Evt12==0)
                  
                } // ((PId1 == PId1pick && PId2 == PId2pick)||(PId1 == PId2pick && PId2 == PId1pick))
                
              } else 
              { // else of if (Coinc_OK == 1)
                
                NSkipUncorPair++;
                //cout << "Skipping Coincidence pair " << endl;
                //cout << "Tels: " << Tel1 << " " << Tel2 << endl;
                
              } // if (Coinc_OK == 1)
              
              
            } // for (Int_t hit2=0; hit2<buf_MultPair[iBuf2]; hit2++)
            
          } // for (Int_t hit1=0; hit1<buf_MultPair[iBuf1]; hit1++)
          
          
          
        } // for (Int_t iBuf2=iBuf1+1; iBuf2<BUFFER_LENGTH; iBuf2++)
        
      } // for (Int_t iBuf1=0; iBuf1<BUFFER_LENGTH-1; iBuf1++) ///////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
    } // if (ipBuffer == BUFFER_LENGTH-1) //////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
    
  }   //Ciclo su tutti gli eventi //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  return;
}

void tree_MultiParticle_v20170226::SaveAllHistograms(const char * nomefile)
{
  TFile * fileout = new TFile(nomefile, "RECREATE");
  
  fileout->WriteTObject(hnum_qrellab_betacmparlab);
  fileout->WriteTObject(hnum_qrellab_betacmperlab);
  fileout->WriteTObject(hnum_qrellab_theta12cms90);
  fileout->WriteTObject(hnum_qrellab);
  fileout->WriteTObject(hnum_qrellab_qp          );
  fileout->WriteTObject(hnum_qrellab_qt          );
  
  fileout->WriteTObject(hden_qrellab_betacmparlab);
  fileout->WriteTObject(hden_qrellab_betacmperlab);
  fileout->WriteTObject(hden_qrellab_theta12cms90);  
  fileout->WriteTObject(hden_qrellab);
  fileout->WriteTObject(hden_qrellab_qp          );
  fileout->WriteTObject(hden_qrellab_qt          );
  
  if(CorrFunc)
  {
    fileout->WriteTObject(CorrFunc  );
    fileout->WriteTObject(CorrFunc_n);
    fileout->WriteTObject(CorrFunc_qp);
    fileout->WriteTObject(CorrFunc_qp_n);
    fileout->WriteTObject(CorrFunc_qt);
    fileout->WriteTObject(CorrFunc_qt_n);
    fileout->WriteTObject(CorrFunc_Vred);
    fileout->WriteTObject(CorrFunc_Vred_n);
  }
  
  fileout->Close();
  return;
}

void tree_MultiParticle_v20170226::BuildCorrelationFunction()
{ 
  Double_t knorm ;
  Double_t dknorm;
  TF1 *gfit; 
  
  // Correlation function Q relative
  TH1D * hnum_Q = new TH1D(*hnum_qrellab);
  TH1D * hden_Q = new TH1D(*hden_qrellab);
  
  hnum_Q->Sumw2();
  hden_Q->Sumw2();
  
  hnum_Q->Divide(hden_Q);
  hnum_Q->Fit("pol0","V0","E1",180.,220.);
  gfit = (TF1*)hnum_Q->GetFunction("pol0");
  
  CorrFunc = (TH1D*) new TH1D(*hnum_Q);
  CorrFunc->SetName("CorrFunc");
  
  CorrFunc_n = (TH1D*) new TH1D(*hnum_Q);  
  CorrFunc_n->SetName("CorrFunc_n");
  knorm  = gfit->GetParameter(0);
  dknorm = gfit->GetParError(0);
  CorrFunc_n->Scale(1./knorm);
  
  hden_qrellab->Scale(knorm);
  /////////////////////////////////////////////////////
  
  // Correlation function Q relative QT
  TH1D * hnum_Q_qp = new TH1D(*hnum_qrellab_qp);
  TH1D * hden_Q_qp = new TH1D(*hden_qrellab_qp);
  
  hnum_Q_qp->Sumw2();
  hden_Q_qp->Sumw2();
  
  hnum_Q_qp->Divide(hden_Q_qp);
  hnum_Q_qp->Fit("pol0","V0","E1",180.,220.);
  gfit = (TF1*)hnum_Q_qp->GetFunction("pol0");
  
  CorrFunc_qp = (TH1D*) new TH1D(*hnum_Q_qp);
  CorrFunc_qp->SetName("CorrFunc_qp");
  
  CorrFunc_qp_n = (TH1D*) new TH1D(*hnum_Q_qp);  
  CorrFunc_qp_n->SetName("CorrFunc_qp_n");
  knorm  = gfit->GetParameter(0);
  dknorm = gfit->GetParError(0);
  CorrFunc_qp_n->Scale(1./knorm);
  
  hden_qrellab_qp->Scale(knorm);
  /////////////////////////////////////////////////////
  
  // Correlation function Q relative QP
  TH1D * hnum_Q_qt = new TH1D(*hnum_qrellab_qt);
  TH1D * hden_Q_qt = new TH1D(*hden_qrellab_qt);
  
  hnum_Q_qt->Sumw2();
  hden_Q_qt->Sumw2();
  
  hnum_Q_qt->Divide(hden_Q_qt);
  hnum_Q_qt->Fit("pol0","V0","E1",180.,220.);
  gfit = (TF1*)hnum_Q_qt->GetFunction("pol0");
  
  CorrFunc_qt = (TH1D*) new TH1D(*hnum_Q_qt);
  CorrFunc_qt->SetName("CorrFunc_qt");
  
  CorrFunc_qt_n = (TH1D*) new TH1D(*hnum_Q_qt);  
  CorrFunc_qt_n->SetName("CorrFunc_qt_n");
  knorm = gfit->GetParameter(0);
  dknorm = gfit->GetParError(0);
  CorrFunc_qt_n->Scale(1./knorm);
  
  hden_qrellab_qt->Scale(knorm);  
  /////////////////////////////////////////////////////
  
  // Correlation function Vreduced
  TH1D * hnum_Vred = new TH1D(*hnum_vredlab);
  TH1D * hden_Vred = new TH1D(*hden_vredlab);
  
  hnum_Vred->Sumw2();
  hden_Vred->Sumw2();
  
  hnum_Vred->Divide(hden_Vred);
  hnum_Vred->Fit("pol0","V0","E1",0.05,0.1);
  gfit = (TF1*)hnum_Vred->GetFunction("pol0");
  
  CorrFunc_Vred = (TH1D*) new TH1D(*hnum_Vred);
  CorrFunc_Vred->SetName("CorrFunc_Vred");
  
  CorrFunc_Vred_n = (TH1D*) new TH1D(*hnum_Vred);  
  CorrFunc_Vred_n->SetName("CorrFunc_Vred_n");
  knorm = gfit->GetParameter(0);
  dknorm = gfit->GetParError(0);
  CorrFunc_Vred_n->Scale(1./knorm);
  
  hden_vredlab->Scale(knorm);    
  /////////////////////////////////////////////////////
  
  CorrFunc       ->SetMarkerStyle(20);
  CorrFunc_n     ->SetMarkerStyle(20);
  CorrFunc_qp    ->SetMarkerStyle(20);
  CorrFunc_qp_n  ->SetMarkerStyle(20);
  CorrFunc_qt    ->SetMarkerStyle(20);
  CorrFunc_qt_n  ->SetMarkerStyle(20);
  CorrFunc_Vred  ->SetMarkerStyle(20);
  CorrFunc_Vred_n->SetMarkerStyle(20); 
  CorrFunc       ->SetMarkerSize(0.8);
  CorrFunc_n     ->SetMarkerSize(0.8);
  CorrFunc_qp    ->SetMarkerSize(0.8);
  CorrFunc_qp_n  ->SetMarkerSize(0.8);
  CorrFunc_qt    ->SetMarkerSize(0.8);
  CorrFunc_qt_n  ->SetMarkerSize(0.8);
  CorrFunc_Vred  ->SetMarkerSize(0.8);
  CorrFunc_Vred_n->SetMarkerSize(0.8); 
  CorrFunc       ->SetLineColor(kBlack);
  CorrFunc_n     ->SetLineColor(kBlack);
  CorrFunc_qp    ->SetLineColor(kBlack);
  CorrFunc_qp_n  ->SetLineColor(kBlack);
  CorrFunc_qt    ->SetLineColor(kBlack);
  CorrFunc_qt_n  ->SetLineColor(kBlack);
  CorrFunc_Vred  ->SetLineColor(kBlack);
  CorrFunc_Vred_n->SetLineColor(kBlack); 
  
  return;
}
