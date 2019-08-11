#include<iostream>
#include<fstream>
using namespace std;


int main()
{

	char ch[20];

	cout<< "Enter the name of an existing text file:"<<endl;
	cin.get(ch,20);

	ifstream filein(ch);

	char c;
	while(!filein.eof())
	{
	
	   filein.get(c);
	   cout<< c << endl;
	}

	

	filein.close();

	return 0;
}
