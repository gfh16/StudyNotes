#include "../include/Box.h"
#include<iostream>

using namespace std;

int Box::objectCount = 0;

Box::Box()
{
  cout<<"default constrcutor callled."<<endl;
  ++objectCount;
  length = width = height = 1.0;
}

Box::Box(double LenValue, double WidValue, double HeiValue)
{
  length = LenValue;


  width  = WidValue;
  height = HeiValue;

  cout<<"Box constructor called."<<endl;
  ++ objectCount;

  if(length<=0) length = 1.0;
  if(width<=0)  width  = 1.0;
  if(height<=0) height = 1.0;
}

double Box::volume() const
{
  return length * width * height;
}

int Box::compareVolume(const Box& box2) const
{
   double vol1 = this->volume();
   double vol2 = box2.volume();
   return (vol1 > vol2 ? 1 : (vol1 < vol2 ? -1 : 0));
}

int Box::getObjectCount() const
{
  return objectCount;
}
