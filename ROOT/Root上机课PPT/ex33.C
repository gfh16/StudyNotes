void ex33(){
 TF1 *f1=new TF1("func1","sin(x)/x",0,10);
 TF1 *f2=new TF1("func2","Gaus(x,0,1)",-3,3);
 TCanvas*myC1=new TCanvas("myC1","A Canvas",10,10,800,600);
 myC1->Divide(2,1);
 myC1->cd(1);
 f1->Draw();
 myC1->cd(2);
 f2->Draw();
  myC1->SaveAs("myex33.gif");
  myC1->SaveAs("myex33.esp");
     }
