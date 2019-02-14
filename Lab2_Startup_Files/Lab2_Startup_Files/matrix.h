#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

class Matrix {

public:              // makes life easier
  float coeff[3][3]; // treat each row as a vector

public:
  Matrix(); // default constructor
  Matrix(float m_coeff[3][3]);
  ~Matrix();

  const Matrix Identity() const;        // identity matrix
  const Vector operator[](int i) const; // row vector
  const Vector column(int j) const;     // column vector
};

// C++ print routine
std::ostream &operator<<(std::ostream &ostr, Matrix m);

// Matrix Operations
const Point operator*(const Matrix &m, const Point &p);
const Vector operator*(const Matrix &m, const Vector &v);
const Matrix operator*(const Matrix &m, const Matrix &w);
const Matrix operator+(const Matrix &m, const Matrix &w);
const Matrix operator-(const Matrix &m, const Matrix &w);

#endif
