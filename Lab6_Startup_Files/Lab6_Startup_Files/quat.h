#ifndef QUAT_H
#define QUAT_H

#include "vector.h"

class quat {
public:
  quat();
  quat(float *M);
  quat(float s, float x, float y, float z);
  quat(Vector v, float w);
  quat(float w, Vector v);
  quat mult(quat q);
  quat conjugate();
  float norm2();
  quat inverse();
  Vector getImag();
  float getReal();
  void toMatrix(float *M);
  ~quat();

private:
  float s;
  Vector v;
};
#endif
