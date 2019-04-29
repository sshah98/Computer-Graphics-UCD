#ifndef _SPHERE_H
#define _SPHERE_H

#include "PPMImage.h"
#include "RGBValue.h"
#include "light.h"
#include "point.h"
#include "vector.h"

class Sphere {

public: // lets make life easy
  // Constructors
  Sphere();                 // unit sphere at (0,0,0)
  Sphere(Point p, float r); // sphere of redius r centered at p

  // Hit test: true ray line described by p and v intersect sphere
  bool hitTest(Point &point, Vector &vector);

  // Assuming valid hit test, returns intersection point
  Point intersectionPoint(Point &point, Vector &vector);

  // Normal vector at intersection point
  Vector normal(Point &point);

  // returns the textured point for this intersection point
  RGBValue getTexColour(Point &intersection);

  Point centre; // sphere centre

  float radius; // sphere radius

  // material properties for Phong's light model
  RGBValue specular;
  RGBValue diffuse;
  RGBValue ambient;
  RGBValue emissive;
  unsigned int shininess;

  // ref to texture
  PPMImage *texture;
};

#endif // _SPHERE_H
