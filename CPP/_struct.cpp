#include <iostream>
#include <string>

using namespace std;

//______________________________
struct node
{
  //  三种形式创建构造函数(初始化函数)
  node(): x(),str(),data() {}
  node(int a, string b, char c): x(c), str(b), data(a){}
  char   x;
  string str;
  int    data;

};

//_______________________________
int main()
{
  node aa;
  aa = {1, "hello", 'c'};
  node bb;
  bb = node(2, "python", 'D');
  cout<< aa.x <<"  "<< aa.str <<"  "<< aa.data << endl;
  cout<< bb.x <<"  "<< bb.str <<"  "<< bb.data << endl;

}
