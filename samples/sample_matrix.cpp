// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

int main()
{
  TDynamicMatrix<int> a(5), b(5), c(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами"
    << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;
  //тесты для CRS
  TDynamicMatrixCRS<int> a_CRS(a);
  cout << "Matrix a in CRS = " << endl << a_CRS << endl;
  cout << "Matrix a in CRS in the form of a dense matrix = " << endl << (TDynamicMatrix<int>)a_CRS << endl;
  TDynamicMatrix<int> d(5);
  for (i = 0; i < 5; i++)
      for (j = i; j < 5; j++)
          d[i][j] = i+1;
  cout << "Matrix d = \n"<<d << endl;
  cout << "Matrix a*d = \n" << (a * d) << endl;
  cout << "Matrix a_CRS*d = \n" << (a_CRS * d) << endl;
  cout << "Matrix d*a = \n" << (d * a) << endl;
  cout << "Matrix d*a_CRS = \n" << (d * a_CRS) << endl;
  TDynamicVector<int> A(5);
  A[1] = 1;
  A[3] = 6;
  cout << a<<endl;
  cout << A<<endl;
  cout << (TDynamicMatrixCRS<int>)a_CRS * A << endl;
  cout << a_CRS * A<<endl;
  return 0;
}
//---------------------------------------------------------------------------
