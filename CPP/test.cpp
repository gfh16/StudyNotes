#include<iostream>
using namespace std;

void test()
{
   for(int i=1; i<10; i++)
   {
   	  for(int j=1; j<i+1; j++)
   	  {
   	  	cout<< i <<"x" << j <<"="<<i*j<<"\t";
   	  }
   	  cout<<endl;
   }
   
   return;
}

