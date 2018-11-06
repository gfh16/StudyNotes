///////////////////////////////////////////////////////////////////
////////////////////// TLoss Implementation ///////////////////////
// The loss of energy class is a partial  wrapper to the fortran 
// vedaloss library. It is initialized reading the loss of 
// energy table "loss1.vedasac" generally found in the 
// directory defined by the "/general" directive in the sheet file.
// For a real c++ porting of the vedaloss library see the 
// KVedaLoss class (and others) in KaliVeda project. Anyway the 
// files loss1.vedasac here and kvloss.data in kaliveda should be 
// exactly the same (to check). 
///////////////////////////////////////////////////////////////////
#include "TLoss.h"


// Default constructor 
// gdir is the directory folder defined by the /general directive
// in the sheet file. 
TLoss::TLoss(string gdir, int *code) 
{
 fmaterial = kSi;  //default
 famasr = 0.0;
 const char* vdirc = gdir.c_str();

 int len = strlen(vdirc);
 int ffile = 45;  //fortran file number  
 loss_init(&ffile, (char *)vdirc, code, len);  //fortran bind
 if(*code == 0)
  cout<<"TLOSS>> Energy loss library: vedaloss : initialized"<<endl;
 else
  cout<<"TLOSS>> Energy loss library: vedaloss : failed"<<endl;
}


void TLoss::SetThickness(float thick)
{
 double th = thick;
 double amasr = famasr; 
 set_thickness(&th, &amasr, &fmaterial);   //fortran bind
}

float TLoss::GetThickness()
{
 double amasr = famasr;
 double thick=0;
 get_thickness(&thick,&amasr,&fmaterial);  //fortran bind
 return (float)thick;
}

//Returns residual energy and loss of energy (in MeV) of ion (Z,A) with energy Einc (MeV) 
//after thickness t. Return the error code
int TLoss::GetERes(float einc, float az, float am, double *de, double *eres)
{
 double ei = einc;
 double z=az, m=am;
 int code=0;
 int idt = 1;  // Einc-->Eres,Delta
 Energy_loss(&ei, &z, &m, &fmaterial, de, eres , &idt, &code);
 return code; 
}

//Calculates incident energy (in MeV) and loss of energy of an ion (Z,A) with residual 
//energy Eres (MeV) after thickness t. Return the error code.
int TLoss::GetEIncFromERes(float eres, float az, float am, double *de, double *einc) 
{
 double er = eres;
 double z=az, m=am; 
 int code=0;
 int idt = 2;  //Eres-->Einc, Delta
 Energy_loss(&er, &z, &m, &fmaterial, de, einc , &idt, &code);
 return code;
}

int TLoss::GetRange(float einc, float az, float am, double *ran)
{
 double ei = einc;
 double z=az, m=am; 
 double amasr = famasr;
 int code = 0;
 range(&ei, &z, &m, &fmaterial, &amasr, ran, &code); 
 return code;
}

//Calculates incident energy (in MeV) and residual energy of an ion (Z,A) from energy loss 
//Delta (MeV) in thickness t using an iterative procedure that converges on eps limit
//In some cases two solutions are possible (this part of vedaloss code is not recently verified
//and is not supported in the wrapper)
int TLoss::GetEIncFromDelta(float de, float az, float am, double *einc, double *eres, int *iter, double eps)
{
 double eloss = de;
 double z=az, m=am;  
 double einc1, eres1; 
 int iter1;
 int code = 0;
 delta(&eloss, &z, &m, &fmaterial, einc, eres, iter, &einc1, &eres1, &iter1, &eps, &code);
 return code;
}
 
int TLoss::GetPunchThroughEnergy(float az, float am, float thickness, double *einc)
{ 
 float oldthick = GetThickness();
 SetThickness(thickness);
 double eres = 0.050;
 double z=az, m=am; 
 double de, ein;
 int code = GetEIncFromERes(eres, z, m, &de, &ein);
 *einc = ein; 
 SetThickness(oldthick);
 return code;
}




 
