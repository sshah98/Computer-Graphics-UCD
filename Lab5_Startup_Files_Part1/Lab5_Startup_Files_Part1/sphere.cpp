#include "sphere.h"
#include <cmath>

#define PI 3.14159

Sphere::Sphere() {
    centre = Point(0, 0, 0);
    this->radius = 1.f;
    specular = RGBValue(128, 128, 128);
    ambient = RGBValue(128, 128, 128);
    diffuse = RGBValue(128, 128, 128);
    emissive = RGBValue(128, 128, 128);
    shininess = 32;
}

Sphere::Sphere(Point p, float r) {
    centre = p;
    this->radius = r;
    specular = RGBValue(128, 128, 128);
    ambient = RGBValue(128, 128, 128);
    diffuse = RGBValue(128, 128, 128);
    emissive = RGBValue(128, 128, 128);
    shininess = 32;
}

bool Sphere::hitTest(Point &p, Vector &v) {
    /*
   * TO DO
   * test for intersection
   */

    Vector u = p - centre;

    float A = v.dot(v);
    float B = (2*u).dot(v);
    float C = u.dot(u) - radius*radius;

    if(B*B - 4*A*C > 0) {
        return true;
    }
    return false;

}

Point Sphere::intersectionPoint(Point &p, Vector &v) {
    /*
   * TO DO
   * find closest intersection point
   */

    Vector u = p - centre;

    float A = v.dot(v);
    float B = (2*u).dot(v);
    float C = u.dot(u) - radius*radius;

    float pos_t = (-1*B + std::sqrt(B*B-4*A*C)) / (2*A);
    float neg_t = (-1*B - std::sqrt(B*B-4*A*C)) / (2*A);

    float min = std::min(pos_t, neg_t);

    Point ret = p + min*v;

    return ret;
}

Vector Sphere::normal(Point &p) { return (p - centre).normal(); }
