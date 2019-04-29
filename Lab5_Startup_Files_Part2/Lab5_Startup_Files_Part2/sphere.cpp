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
    Vector u = p - centre;

    float a = v.dot(v);
    float b = 2.0f * u.dot(v);
    float c = u.dot(u) - radius * radius;
    return (b * b - 4.0f * a * c > 0.0f);
}

Point Sphere::intersectionPoint(Point &p, Vector &v) {
    Vector u = p - centre;

    float a = v.dot(v);
    float b = 2.0f * u.dot(v);
    float c = u.dot(u) - radius * radius;
    float delta = b * b - 4.0f * a * c;
    float t1 = (-b + sqrt(delta)) / 2.0f / a;
    float t2 = (-b - sqrt(delta)) / 2.0f / a;

    // find closest intersection point to p
    float t = 0.f;
    if (t1 > 0.f) {
        if (t2 > 0.f) {
            if (t1 < t2) {
                t = t1;
            } else {
                t = t2;
            }
        } else if (t2 > 0.f) {
            t = t2;
        }
    }

    return p + v * t;
}

Vector Sphere::normal(Point &p) { return (p - centre).normal(); }

RGBValue Sphere::getTexColour(Point &intersection) {
    RGBValue colour;
    /*
   * TO DO
   */
    float phi, theta;

    Vector temp = (intersection-centre).normal();

    phi = asinf(temp.dz);
    theta = atan2(temp.dy, temp.dx);

    float i, j;

    i = (texture->height() * ((2*phi + PI)) / (2*PI)) - 1;
    j = (texture->width() * ((theta + PI)) / (2*PI)) - 1;

    colour = texture->getPixel(i, j);


    // return the computed colour
    return colour;
}
