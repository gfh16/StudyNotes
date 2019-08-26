#include<iostream>
using namespace std;

class Box
{
      double width;

public:
      friend void printWidth(Box box);
      void setWidth(double wid);
    
};

//成员函数
void Box::setWidth(double wid)
{
     width = wid;
}

//请注意：printWidth()不是任何类的成员函数
void printWidth(Box box)
{
    cout << "Width of box: " << box.width <<endl;
}

//程序主函数
int main()
{
   Box box;

   box.setWidth(10.0);

   printWidth( box );

   return 0;

}
