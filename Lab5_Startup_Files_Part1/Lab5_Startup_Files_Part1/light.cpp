#include "light.h"

Light::Light() {
  position = Point(0.f, 0.f, 0.f);
  specular = RGBValue(255, 255, 255);
  diffuse = RGBValue(255, 255, 255);
  ambient = RGBValue(255, 255, 255);
}

Light::Light(Point position_) {
  position = position_;
  specular = RGBValue(255, 255, 255);
  diffuse = RGBValue(255, 255, 255);
  ambient = RGBValue(255, 255, 255);
}

Vector Light::directionFromPoint(Point &p) { return position - p; }
