
//_____________________________________________________________________________
=====================
Date: October 11 2018
=====================
case 1: when I try to store data in the following vector, crash happens:
================================================================================
/*******************************************************************************
 *  Sulotion:
 *     _________________________________________________________________________
 *         LineRead.assign(LineRead.substr(0, LineRead.find('*')));
 *         if(LineRead.empty()) continue;
 *         if(LineRead.find_first_not_of(' ')==std::string::npos) continue;
 *      ________________________________________________________________________
 *  ============================================================================
 *  Reason: I retrive the data with if(LineRead.find('*')==0) continue, it does
 *  not work when ind('*') is unequal to 0. Actully I read the first comment line,
 *  which is outside the vector, giving a random number. If another unused vector
 *  is definited, this random numbers will be stored in this vector.
 ********************************************************************************/

{
  std::vector<double> CsIV_He3[12][4];
  std::vector<double> CsIE_He3[12][4];
//  std::vector<double> ZA_He3[12][4];  // when I comment this third definition, the program break !!!

  while(!FileIn_He3.eof())
  {
    std::string LineRead;
    std::getline(FileIn_He3, LineRead);
    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;

    std::istringstream LineStream(LineRead);

    int telnum;
    int csinum;
    double V;
    double errV;
    double E;
    double errE;

    LineStream >> telnum >> csinum >> V >> errV >> E >> errE;
    cout<< telnum << setw(10)<< csinum << setw(20) << V <<endl;

    CsIV_He3[telnum][csinum].push_back(V);
    CsIE_He3[telnum][csinum].push_back(E);
  }
}
//________________________________________________________________________

//________________________________________________________________________
