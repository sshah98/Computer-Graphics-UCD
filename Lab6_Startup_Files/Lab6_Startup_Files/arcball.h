#ifndef ARCBALL_H
#define ARCBALL_H

#include "quat.h"
#include "vector.h"

class ArcBall {
public:
  ArcBall();
  ~ArcBall();

  Vector screenToPoint(int x, int y, int width, int height);
  void startBall(int x, int y, int width, int height);
  void endBall(int x, int y, int width, int height);
  void updateBall(int x, int y, int width, int height);
  void getMatrix(float *M);
  void reset();

private:
  quat q;
  Vector v;
};
#endif
