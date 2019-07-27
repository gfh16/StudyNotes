/*******************************************************************************

                        C++ 循环语句
    1. while 循环
    2. for 循环
    3. do...while循环

*******************************************************************************/

1. while循环
  (1)语法
    while(condition)
    {
      statement(s);
    }
  (2)说明：condition可以是任意表达式。当任意非零值时都是真，当条件为真时执行循环。
  (3)举例：
     while(a<20)
     {
       cout<<"a 的值："<< a <<endl;
       a++；
     }


2. for 循环
   (1)语法
      for (init; condition; increment)
      {
        statement(s);
      }
   (2)说明：condition为真时，执行循环主体；为假时，不执行循环主体。
   (3)举例
      for(int a=0; a<20; a++)
      {
        cout<< "a 的值： "<< a << endl;
      }

3. do...while循环
   (1)语法
      do
      {
        statement(s);
      } while(condition);

4.无限循环
   for( ; ; )
   {
     statement(s);
   }
