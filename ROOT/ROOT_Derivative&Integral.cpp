//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
//// are in ROOT only two classes to perform numerical derivation
=====================
Derivative (导数)
=====================

**************************************************
* 1. Interpolator/ Function Interpolation (插值法)
**************************************************
{
  ROOT::Math::Interpolator SplineInterpolator[12][4];

  for(int i=0; i<12; i++) {
    for(int j=0; j<4; j++) {
      SplineInterpolator[i][j].SetData(EnergyValues[i][j],VoltageValues[i][j]);
      double Energy = EnergyValues[i][j][0]+ (EnergyValues[i][j][EnergyValues[i][j].size()-1]-EnergyValues[i][j][0])*(k+1)/NumSteps - (EnergyValues[i][j][EnergyValues[i][j].size()-1]-EnergyValues[i][j][0])*0.5/NumSteps;
      SplineInterpolator[i][j].Deriv(Energy)
    }
  }

}
//______________________________________________________________________________


//______________________________________________________________________________
**************************
* 2. RichardsonDerivator *
**************************
// See the details: https://root.cern.ch/function-derivation
//Implements the Richardson method for numerical integration.
//It can calculate up to the third derivative of a function.
{
  double x0 = 2;
  ROOT::Math::Functor1D f1D(&myfunc);
  ROOT::Math::RichardsonDerivator rd;
  rd.SetFunction(f1D);

  rd.Derivative1(x0);// first order
  rd.Derivative2(x0);// second order
  rd.Derivative3(x0);//third order
}
//______________________________________________________________________________



//______________________________________________________________________________
*************************
* 3. Derivator
*************************
// See the details: https://root.cern.ch/function-derivation
{
  ROOT::Math::Function1D f1D(&myfunc);
  ROOT::Math::Derivator der(f1D);

  double x0;
  der.SetFunction(f1D);
  double result = der.Eval(x0);
  double err = der.Error();
}
//______________________________________________________________________________
