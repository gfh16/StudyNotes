#include<iostream>
#include<fstream>
using namespace std;

int main()
{
   char ch;
  // ch = cin.get();

//   cin.get(ch,100);

//   char c;
   ifstream is("test.txt");

   while(is>>ch)
   {
     //ch = is.get();
     cout<< ch << endl;
   }

   return 0;

}
