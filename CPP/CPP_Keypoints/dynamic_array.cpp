////////////////////////////////////////////////////////////////////////////////
//
//          C 语言动态申请三维数组的三种方法
//
//   https://blog.csdn.net/qq_29545231/article/details/78662983
//
//
//
//______________________________________________________________________________
#include "stdio.h"
//#include <mallloc.h>

int*** CreateGrid(int m, int n, int t);

//______________________________________________________________________________
void dynamic_array()
{
  int*** a = CreateGrid(3,3,3);
  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
      for(int k=0; k<3; k++)
      {
        printf("a[%d][%d][%d] = %d\n", i, j, k, *(*(*(a + i) + j) + k));
      }
    }
  }
}



//______________________________________________________________________________
int*** CreateGrid(int m, int n, int t)
{
  int*** result = NULL;

  result = new int** [m];
  for(int i=0; i<m; i++)
  {
    result[i] = new int* [n];
    for(int j=0; j<n; j++)
    {
      result[i][j] = new int[t];
    }
  }
  for(int i=0; i<m; i++)
  {
    for(int j=0; j<n; j++)
    {
      for(int k=0; k<t; k++)
      {
        result[i][j][k] = 1;
      }
    }
  }
  return result;
}
