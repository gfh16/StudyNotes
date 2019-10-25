#include<iostream>
//#include "../include/math.h"
using namespace std;

extern double max(int, int);
extern double sum(int, int);

int main()
{
  int a = 20;
  int b = 30;

  cout<<"max of a and b: "<< max(a,b) << endl;
  cout<<"sum of a and b: "<< sum(a,b) << endl;

  return 0;

}
