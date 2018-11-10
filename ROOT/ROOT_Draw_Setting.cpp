////////////////////////////////////////////////////////////////////
///  how to draw nice figures? How to present the results nicer ?
///////////////////////////////////////////////////////////////////

{
 ****  //gPAD
  gPad->SetLogx(1);//  same as  gPad->SetLogx(true)
  gPad->SetTicky(1); // set axis grid in four axises
 

}


{
  **** // Set Axis
  hs->Draw("pfc nostack");
  hs->GetXaxis()->SetTitle("E_{lab}(MeV)");
  hs->GetXaxis()->SetTitleSize(0.04);   
  hs->GetXaxis()->SetLabelSize(0.03);
  hs->GetXaxis()->CenterTitle(true);
  hs->GetXaxis()->SetRangeUser(0,EnergyCut);
  hs->GetYaxis()->SetTitle("#frac{d^{2}N}{dEd#Omega}(a.u.)");
  hs->GetYaxis()->SetTitleSize(0.04);
  hs->GetYaxis()->SetLabelSize(0.03);
  hs->GetYaxis()->CenterTitle(true);
          
}

{
 *****  // TLatex
 TLine * line = new TLine(double x1, double y1, double x2, double y2);
 line->SetLineColor(kRed);
 line->SetLineStyle(2);
   

}
