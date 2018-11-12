////////////////////////////////////////////////////////////////////
///  how to draw nice figures? How to present the results nicer ?
///////////////////////////////////////////////////////////////////

//________________________________________________________________
//////////////////////////////////////////////////////////////////
/// ****   gPAD
  gPad->SetLogx(1);//  same as  gPad->SetLogx(true)
  gPad->SetTicky(1); // set axis grid in four axises
 

//________________________________________________________________


//________________________________________________________________
//////////////////////////////////////////////////////////////////
///   ****  Set Axis
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

  **** set display range of axis
  /// 1) normal way : 
         histogram->GetYaxis()->SetRangeUser(lower,upper);
  /// 2) Y axis of a THStack: 
         THStack *hs = new THStack("hs","test stacked histograms");
         hs->SetMinimum(0.);
         hs->SetMaximum(10.);
  /// 3) X axis of TGraph
         TGraph* myGraph = new TGraph();
         ...
         myGraph->GetXaxis()->SetLimits(lower,upper);
//__________________________________________________________________


//__________________________________________________________________
////////////////////////////////////////////////////////////////////
////  *****   TLine
  TLine * line = new TLine(double x1, double y1, double x2, double y2);
  line->SetLineColor(kRed);
  line->SetLineStyle(2);
//___________________________________________________________________


//___________________________________________________________________
/// ****** TLagend
  TLegend * legendario = new TLegend(double x1, double y1, double x2, double y2);
  legendario->AddEntry(HistZ1, "Z = 1", "F");
  legendario->AddEntry(HistZ2, "Z = 2", "F");
  legendario->AddEntry(HistZ3, "Z = 3", "F");
  legendario->AddEntry(HistZ4, "Z = 4", "F");
  legendario->AddEntry(HistZ5, "Z = 5", "F");
  legendario->SetBorderSize(0);
  legendario->Draw("SAME");
//____________________________________________________________________


//____________________________________________________________________
//////////////////////////////////////////////////////////////////////
/// TLatex
  TLatex * label_Z1_A01 = new TLatex(1.10, 2.42E6, "^{1}H");
  label_Z1_A01->SetTextColor(kRed);
  label_Z1_A01->SetTextAlign(21);
  label_Z1_A01->SetTextFont(42);
  label_Z1_A01->Draw("SAME");
  




