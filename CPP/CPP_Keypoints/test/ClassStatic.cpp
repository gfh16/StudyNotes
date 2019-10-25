#include<iostream>
using namespace std;

class Box
{
   public:
	   static int objectCount;
	   Box(double,double,double);
	   ~Box();
	   double Volume();
   
   private:
	   double length;
	   double breadth;
	   double height;
};

Box::Box(double l=2.0, double b=2.0, double h=2.0)
{
   cout<<"Construct called."<<endl;
   length = l;
   breadth = b;
   height = h;

   //每次创建对象时增加1
   objectCount++;
}

Box::~Box()
{
   cout<<"Construct deleted."<<endl;
}

double Box::Volume()
{
    return length * breadth * height;
}

int Box::objectCount = 0;

int main()
{

   Box Box1(3.3, 1.2, 1.5);
   Box Box2(8.5, 6.0, 2.0);

   cout<<"Total objects:"<< Box::objectCount<<endl;

   return 0;


}


