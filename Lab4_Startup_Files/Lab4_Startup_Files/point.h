#ifndef POINT_H
#define POINT_H

#include <ostream>

class Point {

public:          // makes life easier
  float x, y, z; // coordinates

public:
  Point();
  Point(float p_x, float p_y, float p_z);
  ~Point();

  float operator[](int i) const;
  Point &operator=(const Point &q);
};

// C++ print routine
std::ostream &operator<<(std::ostream &ostr, Point p);

// Scalar Multiplication
const Point operator*(float s, const Point &p);
const Point operator*(const Point &p, float s);

#endif
