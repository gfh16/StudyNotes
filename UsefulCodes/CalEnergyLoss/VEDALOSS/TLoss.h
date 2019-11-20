///////////////////////////////////////////
//  C++ Wrapping to loss of energy 
//  routines (vedaloss library)
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
#ifndef LOSS_H
#define LOSS_H

#include <iostream>
#include <cstring>


// gfortran binding 
#define loss_init loss_init_
#define set_thickness set_thickness_
#define get_thickness get_thickness_
#define range range_
#define Energy_loss param_
#define delta delta_
extern "C" {
 void loss_init(int *, char *, int * , int );
 void set_thickness(double *, double *, int *);
 void get_thickness(double *, double *, int *);
 void range(double *, double *, double *, int *, double *, double *, int *); 
 void Energy_loss(double *, double *, double *, int *, double *, double *, int *, int *);
 void delta(double *, double *, double *, int *, double *, double *, int*, 
            double *, double *, int*, double *, int *); 
}

using namespace std;

//list of materials supported by the library. The library accept input thicknesses in the 
//unity specified below (microns,mg/cm^2, mbar, cm] depending upon the material type 
//(too complex behaviour due to the old vedaloss library: to be changed)
enum ematerial {kSi=1, kMylar, kNe102, kNi, kC3F8, kC, kAg, kSn, kCsI, kAu, kU, kAl, kCa, kPb=19};
//              um     um      um    mg/cm^2 mbar  [ mg/cm^2 ...] cm   [mg/cm^2 ...            ]

class TLoss {
private:
 int fmaterial;
 double famasr;
public:
 TLoss(string dir, int *code);      //Default constructor
 ~TLoss() {}                        //Destructor 
 void SetMaterial(ematerial mat, float miso=0.0) {fmaterial = mat; famasr=miso;}  //set material 
 int GetMaterial() {return fmaterial;}                                            //get material
 void SetThickness(float thick);                   //set thickness
 float GetThickness();                             //get thickness
 int GetERes(float einc, float az, float am, double *de, double *eres);   //Get residual energy and loss of energy 
 int GetEIncFromERes(float eres, float az, float am, double *de, double *einc); //Get Einc from Eres
 int GetRange(float einc, float az, float am, double *ran);    //Get the range in mg/cm^2
 int GetEIncFromDelta(float de, float az, float am, double *einc, double *eres, int *iter, 
                      double eps);  //Get Einc from ELoss 
 int GetPunchThroughEnergy(float az, float am, float thickness, double *einc);
};

#endif
