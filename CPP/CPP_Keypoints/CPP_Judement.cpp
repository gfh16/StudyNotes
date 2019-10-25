/*******************************************************

        C++ 判断语句
  1. if 语句
  2. if...else语句
  3. switch 语句

********************************************************/
/*
  1. if 语句
       (1) 语法
            if(boolean_expression)
            {
                // 如果布尔表达式为真将执行的语句
            }

  2. if...else语句
       (1) 语法
            if(boolean_expression)
            {
              //如果布尔表达式为真将执行的
            }
            else
            {
              //如果布尔表达式为假将执行的语句

  3. if...else if...else语句
       (1)语法
         if(boolean_expression 1)
         {
           // 当布尔表达式 1 为真时执行
         }
         else if(boolean_expression 2)
         {
           // 当布尔表达式 2 为真时执行
         }
         else if(boolean_expression 3)
         {
           // 当布尔表达式 3 为真时执行
         }
         else
         {
           // 当上面条件都不为真时执行
         }

  4. switch语句
        (1) 一个 switch 语句允许测试一个变量等于多个值时的情况。每个值称为一个case。

        (2) 语法
        switch(expression)
        {
           case constant-expression :
                statement(s);
                break;   // 可选的
           case constant-expression :
                statement(s);
                break;  //可选的

          //您可以有任意数量的 case 语句
          default:   //可选的
             statement(s);
        }

   5. ?:运算符： Exp1 ? Exp2 : Exp3;




*/


////////////////////////////////////////////////////////////////////////////////

#if 1

#include <iostream>
using namespace std;

int main()
{
  // 局部变量声明
  char grade;
  cin >> grade;

  switch(grade)
  {
    case 'A':
      cout<<"很棒！"<< endl;
      break;
    case 'B':
    case 'C':
      cout<<"做得好"<< endl;
      break;
    case 'D' :
      cout<<"您通过了"<< endl;
      break;
    case 'F' :
      cout<<"最好再试一下"<< endl;
      break;
    default :
      cout<<"无效的成绩"<<endl;
  }
  cout<<"您的成绩是"<< grade << endl;

  return 0;
}

#endif
