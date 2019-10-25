#include<iostream>
#include "include/Box.h"

using namespace std;

int main()
{
    Box firstbox(10.0, 20.0, 30.0);
    Box secondbox(20.0, 15.0, 20.0);

    cout<<"the volume of firstbox is:"<< firstbox.volume() <<endl;
    cout<<"the volume of secondbox is:"<< secondbox.volume()<<endl;

    cout<<"fistbox is"<< (firstbox.compareVolume(secondbox) >=0 ? "":"not")
	      << "greater than secondbox."<< endl;

    cout<<"Object count is "<<firstbox.getObjectCount()<<endl;
    Box boxes[5];
    cout<<"Object count is "<<firstbox.getObjectCount()<<endl;

    const int count = sizeof boxes/ sizeof boxes[0];
    cout<<"The boxes array has"<< count <<"elements."<<endl;

    cout<<"Each element occupies"<<sizeof boxes[0]<<"bytes."<<endl;
    for(int i=0; i<count; i++)
    {
      cout<<"Volume of boxes["<< i <<"]="<< boxes[i].volume()<<endl;
    }


    return 0;

}
