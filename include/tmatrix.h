// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>
#include <vector>//для реализации CRS
using namespace std;

//объявление класса CRS заранее, чтобы сделать его дружественным, это понадобится для конструктора с параметром 
template<typename T>
class TDynamicMatrixCRS;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE) throw out_of_range("Too much importance");
    pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
    if (pMem == nullptr) throw domain_error("domain_error");
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    if (pMem == nullptr) throw domain_error("domain_error");
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz=v.sz;
      pMem=new T[sz];
      if (pMem == nullptr) throw domain_error("domain_error");
      copy(v.pMem, v.pMem+v.sz,pMem);
      //for (size_t i = 0; i<sz; ++i) pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0;
      pMem = nullptr;
      swap(*this,v);
  }
  ~TDynamicVector()
  {
      delete [] pMem;
      pMem = nullptr;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (v != *this){
          if (sz!=v.sz){
              delete [] pMem;
              sz=v.sz;
              pMem = new T[sz];
          }
          //copy(v.pMem, v.pMem + v.sz, pMem);
          for (size_t i = 0; i < sz; ++i) pMem[i]=v.pMem[i];
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      sz = 0;
      delete[] pMem;
      pMem = nullptr;
      swap(*this,v);
      return (*this);
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind<0 || ind>=sz) throw range_error("range error");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind<0 || ind>=sz) throw range_error("range error");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz!=v.sz) return false;
        for (size_t i=0;i<sz;++i) if (pMem[i]!=v.pMem[i]) return false;
        return true;
    }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return (!(*this == v));
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector Result(*this);
      for (size_t i = 0; i<sz;i++) Result.pMem[i]+=val;
      return Result;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector Result(*this);
      for (size_t i = 0; i<sz;i++) Result.pMem[i]-=val;
      return Result;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector Result(*this);
      for (size_t i = 0; i<sz;i++) Result.pMem[i]*=val;
      return Result;
  }
    
  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz!=v.sz) throw length_error("length error");
      TDynamicVector Result(*this);
      for (size_t i=0;i<sz;++i) Result[i] = Result[i] + v.pMem[i];
      return Result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz!=v.sz) throw length_error("length error");
      TDynamicVector Result(*this);
      for (size_t i=0;i<sz;++i) Result[i] = Result[i] - v.pMem[i];
      return Result;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz!=v.sz) throw length_error("length error");
      T sum = T(); //конструктор по умолчанию
      for (size_t i=0;i<sz;++i) sum = sum + (pMem[i]*v.pMem[i]);
      return sum;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
  friend class TDynamicMatrixCRS<T>;
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T> > //матрица хранится по строкам
{
  using TDynamicVector<TDynamicVector<T> >::pMem;
  using TDynamicVector<TDynamicVector<T> >::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T> >(s)
  {
      if (sz > MAX_MATRIX_SIZE) throw out_of_range("Too much importance");
      if (sz == 0) throw out_of_range("Greater than zero");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz); 
  }

  using TDynamicVector<TDynamicVector<T> >::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return 0; 
      else for (size_t i = 0; i < sz; ++i) if (pMem[i] != m.pMem[i]) return 0;
      return 1;
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this==m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix Res(sz);
      for (size_t i = 0; i < sz; ++i) Res.pMem[i] = pMem[i] * val;
      return Res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz) throw range_error("range_error");
      TDynamicVector<T> Res(sz);
      for (size_t i = 0; i < sz; ++i) {
          for (size_t j = 0; j < sz; ++j) {
              Res[i] += pMem[i][j] * v.[j];
          }
      }
      return Res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw range_error("range_error");
      TDynamicMatrix<T> Res(sz);
      for (size_t i = 0; i < sz; ++i) {
          Res.pMem[i] = pMem[i] + m.pMem[i];
      }
      return Res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw range_error("range_error");
      TDynamicMatrix<T> Res(sz);
      for (size_t i = 0; i < sz; ++i) {
          Res.pMem[i] = pMem[i] - m.pMem[i];
      }
      return Res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw range_error("range_error");
      TDynamicMatrix Res(sz);
      for (size_t i = 0; i < sz; ++i) {
          for (size_t k = 0; k < sz; ++k) {
              for (size_t j = 0; j < sz; ++j) {
                  Res.pMem[i][j] = Res.pMem[i][j] + pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return Res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
      for (size_t row = 0; row < m.sz; ++row) {
          istr >> m.pMem[row];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
      for (size_t row = 0; row < m.sz; ++row) cout << m.pMem[row] << endl;
      return ostr;
  }
  //для реализации CRS
  friend class TDynamicMatrixCRS<T>;
  friend TDynamicMatrix<T> operator*(const TDynamicMatrixCRS<T>& m) {
      TDynamicMatrix<T> Res(sz);
      size_t len = m.rowIndex.size() - 1;
      if (len != sz) throw logic_error("different length");
      for (size_t i = 0; i < len; ++i) {
          for (size_t j = m.rowIndex[i]; j < m.rowIndex[i + 1]; ++j) {
              for (size_t k = 0; k < len; ++k) {
                  Res[k][col[j]] = Res[k][col[j]] + m.value[j] * pMem[k][i];
              }
          }
      }
      return Res;
  }
};



//Разрежанная матрица в формате CRS
template<typename T>
class TDynamicMatrixCRS
{
    vector<T> value;//вектор значений
    vector<size_t> rowIndex;//вектор индексов строк
    vector<size_t>  col;//вектор индексов столбцов
public:
    TDynamicMatrixCRS(){}

    TDynamicMatrixCRS(TDynamicMatrixCRS& m) {
        value = m.value;
        col = m.col;
        rowIndex = m.rowIndex;
    }
    TDynamicMatrixCRS(vector<T> _value, vector<size_t> _rowIndex, vector<size_t> _col):value(_value), rowIndex(_rowIndex), col(_col) {}

    TDynamicMatrixCRS(TDynamicMatrix<T> m) {
        size_t temp = 0;
        for (size_t row = 0; row < m.sz; ++row) {
            rowIndex.push_back(temp);
            for (size_t column = 0; column < m.sz; ++column) {
                if (m[row][column] != T()) {
                    value.push_back(m[row][column]);
                    col.push_back(column);
                    temp++;
                }
            } 
        }
        rowIndex.push_back(temp);
    }

    TDynamicMatrixCRS operator*(const T& val)
    {
        TDynamicMatrixCRS Res(*this);
        for (size_t i = 0; i < value.size(), ++i) Res.value[i] = Res.value[i] * val;
        return Res;
    }

    
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
        TDynamicVector<T> Res(rowIndex.size()-1);
        if (v.sz != (rowIndex.size() - 1)) throw logic_error("different length");
        for (size_t i = 0; i < rowIndex.size() - 1; ++i) {
            for (size_t j = rowIndex[i]; j < rowIndex[i + 1]; ++j) Res[i] = Res[i] + (value[j] * v.pMem[i]);
        }
        return Res;
    }

    TDynamicMatrix<T> operator*(const TDynamicMatrix<T>& m) {
        TDynamicMatrix<T> Res(rowIndex.size() - 1);
        if (m.sz != (rowIndex.size() - 1)) throw logic_error("different length");
        for (size_t i = 0; i < rowIndex.size() - 1; ++i) {
            for (size_t j = rowIndex[i]; j < rowIndex[i + 1]; ++j) {
                for (size_t k = 0; k < rowIndex.size()-1; ++k) {
                    Res[i][k] = Res[i][k] + (value[j] * m.pMem[col[j]][k]);
                }
            }
        }
        return Res;
    }
        

    //преобразование типа
    operator TDynamicMatrix<T>() {
        TDynamicMatrix<T> Res(rowIndex.size()-1);
        for (size_t i = 0; i < rowIndex.size() - 1; ++i) {
            for (size_t j = rowIndex[i]; j < rowIndex[i + 1]; ++j) {
                Res[i][col[j]] = value[j];
            }
        }
        return Res;
    }

    TDynamicMatrixCRS operator=(const TDynamicMatrix<T>& m) {
        value.clear();
        rowIndex.clear();
        col.clear();

        size_t temp = 0;
        for (size_t row = 0; row < m.sz; ++row) {
            rowIndex.push_back(temp);
            for (size_t column = 0; column < m.sz; ++column) {
                if (m[row][column] != T()) {
                    value.push_back(m[row][column]);
                    col.push_back(column);
                    temp++;
                }
            }
        }
        rowIndex.push_back(temp);

        return *this;
    }

    TDynamicMatrixCRS operator=(const TDynamicMatrixCRS& m) {
        if (*this != m) {
            value.clear();
            rowIndex.clear();
            col.clear();
            value = m.value;
            rowIndex = m.rowIndex;
            col = m.col;
        }
        return *this
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrixCRS<T>& m)
    {
        TDynamicMatrix<T> temp;
        istr >> temp;
        m = temp;
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrixCRS<T>& m)
    {
        ostr << "value: ";
        for (size_t i = 0; i < m.value.size(); ++i) ostr<<m.value[i]<<" ";
        ostr << endl<<"row index: ";
        for (size_t i = 0; i < m.rowIndex.size(); ++i) ostr << m.rowIndex[i]<<" ";
        ostr << endl<<"columns: ";
        for (size_t i = 0; i < m.col.size(); ++i) ostr << m.col[i]<<" ";
        ostr << endl;
        return ostr;
    }
    
};
#endif