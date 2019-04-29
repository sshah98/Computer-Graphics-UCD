#ifndef _LIGHT_H
#define _LIGHT_H

#include "RGBValue.h"
#include "point.h"
#include "vector.h"

class Light {
public: // lets make life easy
  // Constructors
  Light();        // new white (specular, diffuse and ambient) light at (0,0,0)
  Light(Point p); // new white (specular, diffuse and ambient) light at p

  Vector directionFromPoint(Point &p); // Calculate direction from p

  // Phong light model components
  RGBValue specular;
  RGBValue diffuse;
  RGBValue ambient;

  Point position; // light position
};

#endif // _LIGHT_H
