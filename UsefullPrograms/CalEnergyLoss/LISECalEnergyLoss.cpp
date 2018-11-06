#include "include/EnergyLossModule.h"

void LISECalEnergyLoss()
{
  const int Z=1;
  const int A=1;
  int LiseModel=1; // LiseModel=1 is good for low energy 

  // Input the effective thickness of silicon strip detectors, by unit: um
  double TelSiThickness[12];
  TelSiThickness[0]=1537; TelSiThickness[1]=1521; TelSiThickness[2] =1500; TelSiThickness [3]=1496;
  TelSiThickness[4]=1517; TelSiThickness[5]=1512; TelSiThickness[6] =1491; TelSiThickness [7]=1460;
  TelSiThickness[8]=1537; TelSiThickness[9]=1536; TelSiThickness[10]=1471; TelSiThickness[11]=1491;
  double CsIMylarThickness=2.076; // um

  EnergyLossModule LISEModule;

  double ESi = 5; //MeV
  for(int numtel=0; numtel<12; numtel++)
  {
    double Eresidual=LISEModule.GetResidualEnergy(Z,A,ESi,"Mylar",TelSiThickness[numtel],LiseModel);
    double EresidualOnCsI=Eresidual-LISEModule.GetEnergyLoss(Z,A,Eresidual,"Mylar",CsIMylarThickness,LiseModel);
    double CsIE=EresidualOnCsI;
//    double EresidualMax=LISEModule.GetResidualEnergy(Z,A,ESi+errESi,"Si",TelSiThickness[numtel],LiseModel);
//    double EresidualOnCsIMax=EresidualMax-LISEModule.GetEnergyLoss(Z,A,EresidualMax,"Mylar",CsIMylarThickness,LiseModel);
//    double err_CsIE=fabs(EresidualOnCsIMax-EresidualOnCsI);

    cout<< Eresidual << setw(10) << EresidualOnCsI << setw(10) << endl;
  }


}
