#include<iostream>
using namespace std;

template <typename T>
T Max(T a, T b)
{
   return (a>b? a:b);
}

int main()
{
   int i=2;
   int j=2;
   cout<<"Max(i,j) is:"<< Max(i,j)<<endl;
   cout<<"Max<int>(i,j) is:"<<Max<int>(i,j)<<endl;

   float x=1.1;
   float y=2.2;
   cout<<"Max(x,y) is:"<<Max(x,y)<<endl;

   return 0;
}
