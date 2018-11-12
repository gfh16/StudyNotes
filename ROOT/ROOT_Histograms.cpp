///////////////////////////////////////////////////////////////////////
///  Notes of Histograms
///////////////////////////////////////////////////////////////////////
**** 填充直方图后，所有的信息都保存下来了吗？能否找到任意entry的内容？

{

  ***  //cloning a histogram
  TH1* hc = (TH1*)h1->Clone();  
   
  ***  // Normalizing histograms
  Double_t scale = norm/h->Integral();
  h->Scale(scale);
   
  h->Scale(1./h->Integral());
   
  ***  // No show statistics box of a histogram
  h->SetStats(0); 
  h->SetOptStat(0);
   
  ***  // Muliti Histograms Drawing
  THStack *hs = new THStack("hs","title");
  hs->Add(h1);
  hs->Add(h2);
  hs->Draw();
  hs->Draw("pfc nostack");
  hs->GetXaxis()->SetTitle("E_{Lab}(MeV)");
  hs->GetXaxis()->SetTitleSize(0.04);
  hs->GetXaxis()->SetLabelSize(0.03);
  hs->GetXaxis()->CenterTitle(true);
  hs->GetXaxis()->SetRangeUser(0,EnergyCut);
  hs->GetYaxis()->SetTitle("#frac{d^{2}N}{dEd#Omega}(a.u.)");
  hs->GetYaxis()->SetTitleSize(0.04);
  hs->GetYaxis()->SetLabelSize(0.03);
  hs->GetYaxis()->CenterTitle(true);
  
  *** // Fill histograms
  h1->Fill(x);
  h1->Fill(x,w); // with weight
  h2->Fill(x,y);
  h2->Fill(x,y,w);
  h3->Fill(x,y,z);
  h3->Fill(x,y,z,w);
 
  h1->SetBinContent(Int_t binx, Double_t content);
  
  *** // Several ways to create histograms
  /// 1) clone form existing histogram
         TH1* hc = (TH1*)h1->Clone();
  
  /// 2) make a projection from a 2D or 3D histogram
         TH1* hx = h2-ProjectionX();
  
  
  *** // binning
  h1->GetNbinsX();          // get the number of bins in X axis
  h1->GetBinCenter(i);      // get the center of bin NO.i
  h1->GetBinContent(i);     // get the Y value of bin NO.i 
  h1->GetEntries();         // get the number of entry
    
  
  
   
  
}
