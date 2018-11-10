//////////////////////////////////////////////////////////////
///  Notes of Histograms
/////////////////////////////////////////////////////////////
{

   ***  //cloning a histogram
        TH1* hc = (TH1*)h1->Clone();  
   
   ***  // Normalizing histograms
        Double_t scale = norm/h->Integral();
        h->Scale(scale);
   
        h->Scale(1./h->Integral());
   
   ***  // No show statistics box of a histogram
        h->SetStats(0); 
   
   ***  // Muliti Histograms Drawing
         THStack *hs = new THStack("hs","title");
         hs->Add(h1);
         hs->Add(h2);
         hs->Draw();
}
