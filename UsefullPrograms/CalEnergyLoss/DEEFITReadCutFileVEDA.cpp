#include "VEDALOSS/TLoss.h"
#include "include/HiRACsICalibration.h"

//------ definition of struct MPart ---------------------
struct MPart
{
  Double_t x, y;
  Double_t Z,A;
};

// Function for DE-E identification based
// on formulas from N. Le Neindre et al. NIM A490 (2002) 251
// modified following the formula of W. Gawlikowicz
// for Light-Energy relation in CsI(Tl)
// NIM A491 (2002) 181. Adapted by Amalia Pop following
// ref.: J. Blicharska et al. LNS report 2005
// This formula needs 14 fit parameters
Double_t func14(MPart &p, Double_t *par)
{
  Double_t X = p.x;
  Double_t Z = p.Z;
  Double_t A = p.A;
  Double_t xx,exp1,exp2,res=1.0;
  Double_t reslog,ene;

  if(Z==0 && A==0)
  {
    return par[12];
  }
  xx = X-par[13];
  bool foffset=false; //this is true for fitting procedure, false for the analysis
  //if xx<0 never reached from data analysis
  if(xx<=0)
  {
    if(foffset)
    {
      xx=X;
    }
    else
    {
      return res;
    }
  }

 exp1 = par[2] + par[3] + 1;
 exp2 = 1./exp1;
 reslog = log(1.+ par[9]* Z)*(1.- exp(-par[10]*pow(Z,par[11])))/Z;
 ene = par[6] * reslog * xx ;
 ene = ene + par[7] * Z * sqrt(A) * log(1. + par[8] * reslog  * xx);
 res = pow(ene,exp1) +
       pow((par[4]* pow(Z,par[0]) * pow(A,par[1])),exp1) +
       par[5]*pow(Z,2) * pow(A,par[2]) * pow(ene,par[3]);
 res = pow(res,exp2) - ene + par[12];
 return res;
}

//------ complete macro DEEFIT ------------
void DEEFITReadCutFileVEDA()
{
  const int csi_gain_setting=170;
  int LiseModel=1; // LiseModel =1 used for low energy experiments
  double errPercentageCsIV = 0.01;
  double errPercentageCsIE = 0.01;
  double errPercentageESi = 0.01;

  ifstream FileInCut("data/DEEFITCut.dat");
  ifstream FileInPar("data/DEEFITParameters.dat");

  ofstream FileOut("data/DEEFITPointsFullInfo_VEDA.dat");
  FileOut << setw(5) <<" *tel " << setw(5) << "csi " << setw(5) << "Z" << setw(5) << "A" << setw(10) << "CsICh"<<setw(10)<< "errCsICh"
          << setw(10) << "CsIV " << setw(15) << "errCsIV"<<"  "<< setw(15) << "CsIE" << setw(15) << "errCsIE" << setw(15)<< "ESi" << setw(15) << "errESi\n";

  // ------- pulser calibration setting --------------------------
  HiRACsICalibrationManager CsICalibrationModule;
  CsICalibrationModule.LoadPulserInfo(Form("data/HiRA_CsI_Pulser_%dsetting.dat",csi_gain_setting));
  //////////////////////////////////////////////////////////////////////////////////////////////////////////

  //-------- Energy Loss Module ----------------------------------
  double TelSiThickness[12];
  TelSiThickness[0]=1537; TelSiThickness[1]=1521; TelSiThickness[2] =1500; TelSiThickness [3]=1496;
  TelSiThickness[4]=1517; TelSiThickness[5]=1512; TelSiThickness[6] =1491; TelSiThickness [7]=1460;
  TelSiThickness[8]=1537; TelSiThickness[9]=1536; TelSiThickness[10]=1471; TelSiThickness[11]=1491;
  double CsIMylarThickness=2.076;
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  int code;
  TLoss VEDAModule("VEDALOSS/",&code);

  //----------- retrieving DEEFIT parametrs -----------------------------
  double par0[12][4];
  double par1[12][4];
  double par2[12][4];
  double par3[12][4];
  double par4[12][4];
  double par5[12][4];
  double par6[12][4];
  double par7[12][4];
  double par8[12][4];
  double par9[12][4];
  double par10[12][4];
  double par11[12][4];
  double par12[12][4];
  double par13[12][4];

  while (FileInPar.is_open() && !FileInPar.eof())
  {
    std::string LineRead;
    std::getline(FileInPar, LineRead);

    LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ')==std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int numtel;
    int numcsi;

    int ntel;
    int mf;
    int npar;
    double chi2;

    LineStream >> ntel >> mf >> npar ;
    numtel = ntel/4; // take integer
    numcsi = ntel%4;

    LineStream >> par0[numtel][numcsi] >> par1[numtel][numcsi] >> par2[numtel][numcsi] >> par3[numtel][numcsi];
    LineStream >> par4[numtel][numcsi] >> par5[numtel][numcsi] >> par6[numtel][numcsi] >> par7[numtel][numcsi];
    LineStream >> par8[numtel][numcsi] >> par9[numtel][numcsi] >> par10[numtel][numcsi] >> par11[numtel][numcsi];
    LineStream >> par12[numtel][numcsi] >> par13[numtel][numcsi] >> chi2;
  }

 //----- Loading cut ranges to take DEE points ------------------
  while (FileInCut.is_open() && !FileInCut.eof())
  {
    std::string LineRead;
    std::getline(FileInCut, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    int numtel, numcsi;
    int Z, A;
    int CutStart, CutEnd, CutStep;


    LineStream >> numtel >> numcsi;
    LineStream >> Z >> A;
    LineStream >> CutStart >> CutEnd >> CutStep;

    double par[14];
    par[0] = par0[numtel][numcsi] ;
    par[1] = par1[numtel][numcsi] ;
    par[2] = par2[numtel][numcsi] ;
    par[3] = par3[numtel][numcsi] ;
    par[4] = par4[numtel][numcsi] ;
    par[5] = par5[numtel][numcsi] ;
    par[6] = par6[numtel][numcsi] ;
    par[7] = par7[numtel][numcsi] ;
    par[8] = par8[numtel][numcsi] ;
    par[9] = par9[numtel][numcsi] ;
    par[10] = par10[numtel][numcsi] ;
    par[11] = par11[numtel][numcsi] ;
    par[12] = par12[numtel][numcsi] ;
    par[13] = par13[numtel][numcsi] ;

    MPart input;
    input.Z = Z;
    input.A = A;
    for(int XChannel=CutStart; XChannel<CutEnd; XChannel+=CutStep)
    {
      input.x = XChannel;
      double CsIV = CsICalibrationModule.GetVoltageValue(XChannel, numtel, numcsi);
      double errCsIV = errPercentageCsIV *  CsIV; //add 1% error
      double ESi = func14(input, par);
      double errESi = errPercentageESi *ESi;  // add 1% error
      if(ESi<=0) continue;
      VEDAModule.SetMaterial(kSi);
      VEDAModule.SetThickness(TelSiThickness[numtel]);
      double EneLoss;
      double Eresidual;
      double EInc;
      int iter;
      double eps=0.0001; //precision?
      VEDAModule.GetEIncFromDelta(ESi, Z, A, &EInc, &Eresidual, &iter, eps);
      VEDAModule.SetMaterial(kMylar);
      VEDAModule.SetThickness(CsIMylarThickness);
      double EresidualOnCsI;
      double DEInMylar;
      VEDAModule.GetERes(Eresidual,Z,A,&DEInMylar,&EresidualOnCsI);
      double CsIE=EresidualOnCsI;
      double errCsIE = errPercentageCsIE * EresidualOnCsI;  // add 1% error
      FileOut << setw(5) << numtel << setw(5) << numcsi << setw(5) << Z << setw(5) << A << setw(10) << XChannel <<setw(10)<< 0.5 /*errCsICh*/
              << setw(15) << CsIV  << setw(15) << errCsIV <<"  "<< setw(15) << CsIE << setw(15) << errCsIE << setw(15)<< ESi << setw(15) << errESi << endl;

      printf("Tel %02d CsI %02d  Z%02d  A%02d : ESi=%.3f +- %.4f -> ECsI=%.3f +- %.4f\n",numtel, numcsi, Z, A, ESi, errESi, CsIE, errCsIE);
    }
  }
  FileOut.close();
}
