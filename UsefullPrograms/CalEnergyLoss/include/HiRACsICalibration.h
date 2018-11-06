#ifndef HIRACSICalibRATION_h
#define HIRACSICalibRATION_h

#include <Math/Interpolator.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TSpline.h>
#include <math.h>
#include <cmath>

#include "EnergyLossModule.h"
#include "nuclear_masses.h"

// ASSUMPTIONS
static const int CSICALIB_NUM_TEL = 12;
static const int CSICALIB_NUM_CSI_TEL =4;
static const int CSICALIB_NUM_TOWER = 3;

// NUMBER OF MODELS FOR ENERGY LOSS CALCULATIONS
static const int NUM_MODELS_ELOSS=6;

// MAX Z DETECTED
static const int Z_MAX=20;
// MAX A DETECTED
static const int A_MAX=20;

//CSI_CRYSTAL_LENGTH (um)
static const double CsILength=1E5;
//===============================

class HiRACsISimulation
{
public :
  HiRACsISimulation();
  ~HiRACsISimulation();

  double GetSimulatedLightFromEnergy(int Z, int A, double Einc, TF1 * LightResponse, double CsIthickness_um, int model=1);

private :
  //Tools for energy loss calculations in light response simulations
  int LoadEnergyLossFile(const char *);
  void ClearEnergyLossInfo();
  std::vector <double> ParticleEnergy; //MeV/u
  std::vector <double> LiseELoss[NUM_MODELS_ELOSS];   //MeV/micron
  double Emax; //MeV/u
  double Emin; //MeV/u
  ROOT::Math::Interpolator SplineInterpolator[NUM_MODELS_ELOSS];
  ///////////////////////////////////////////////////////////////////

  //Nuclear Masses
  nuclear_masses *NucData;
  /////////////////////////////

};

class HiRACsICalibration
{
public:
  HiRACsICalibration(int Z=1, int A=1);
  ~HiRACsICalibration();

  void SetNumParameters(int);
  void SetParameter(int, double);
  void InitCalibration();

  void CheckCalibrationValidity(const char *, int numtel, int numcsi);

  double GetEnergy(double ch) const;

private:
  HiRACsISimulation *fSimulationModule;
  int fNumParameters;
  double * fParameters;
  TF1 * fCalibrationFunc;
  bool fCalibrationInitialized;
  int fZ;
  int fA;

  //Calibration sampling to speed-up calc
  std::vector<double> fCsIRawV;
  std::vector<double> fLISEEnergyMeV;
  TSpline3 * fVtoEInterpolated;
  TGraph * fVtoEExtrapolated;
  ///////////////////////////////////////

};

class HiRACsICalibrationManager
{
public:
  HiRACsICalibrationManager();
  ~HiRACsICalibrationManager();

  int LoadPulserInfo(const char *);
  int LoadEnergyCalibration(const char *);
  void Clear();

  double GetVoltageValue(double ch, int numtel, int numcsi) const;
  double GetEnergyValue(double ch, int numtel, int numcsi, int Z=1, int A=1) const;
  HiRACsICalibration * GetCalibration(int numtel, int numcsi, int Z=1, int A=1) const;

  void DrawChVoltage (int numtel, int numcsi) const;

private:

  std::vector<double> fChValues [CSICALIB_NUM_TEL*CSICALIB_NUM_CSI_TEL];
  std::vector<double> fVoltageValues [CSICALIB_NUM_TEL*CSICALIB_NUM_CSI_TEL];
  TGraph * fCsIChToVExtrapolated [CSICALIB_NUM_TEL*CSICALIB_NUM_CSI_TEL];
  TSpline3 * fCsIChToVInterpolated [CSICALIB_NUM_TEL*CSICALIB_NUM_CSI_TEL];

  HiRACsICalibration * fCalib[Z_MAX][A_MAX][CSICALIB_NUM_TEL*CSICALIB_NUM_CSI_TEL];

  bool fPulserLoaded;

};

#endif
