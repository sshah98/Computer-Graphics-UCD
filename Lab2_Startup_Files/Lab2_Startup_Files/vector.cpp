#include "vector.h"
#include <math.h>

Vector::Vector() { dx = dy = dz = 0.0f; }

Vector::Vector(float v_dx, float v_dy, float v_dz) {
    dx = v_dx;
    dy = v_dy;
    dz = v_dz;
}

Vector::~Vector() {}

float Vector::operator[](int i) const {
    switch (i) {
    case 0:
        return dx; // dx is equivalent to index 0
    case 1:
        return dy; // dy is equivalent to index 1
    case 2:
        return dz; // dz is equivalent to index 2
    default:
        std::cout << "Error: . . . .";
        return dx;
    }
}

float Vector::norm() const {
    /**
     implemented
    */
    return sqrt(dx*dx + dy*dy + dz*dz);
}

const Vector Vector::normalised() const {
    /**
      implemented
    */
    return Vector(dx/norm(), dy/norm(), dz/norm());
}

float Vector::dot(const Vector &v) const {
    /**
      implemented
    */
    return (dx*v.dx + dy*v.dy + dz*v.dz);
}

const Vector Vector::cross(const Vector &v) const {
    /**
       implemented
    */
    return Vector((dy*v.dz)-(dz*v.dy), ((dz*v.dx)-(dx*v.dz)), ((dx*v.dy)-(dy*v.dx)));
}

// C++ print routine
std::ostream &operator<<(std::ostream &ostr, Vector v) {
    ostr << "[" << v.dx << ", " << v.dy << ", " << v.dz << "]";
    return ostr;
}

// Unary Minuse
const Vector operator-(const Vector &v) {
    /**
      implemented
    */
    return Vector(-v.dx, -v.dy, -v.dz);
}

// Addition
const Point operator+(const Point &p, const Vector &v) {
    /**
      implemented
    */
    return Point((p.x + v.dx), (p.y + v.dy), (p.z + v.dz));
}

const Vector operator+(const Vector &v, const Vector &w) {
    /**
      implemented
    */
    return Vector(v.dx + w.dx, v.dy + w.dy, v.dz + w.dz);
}

// Subtraction
const Point operator-(Point p, Vector v) {
    /**
      implemented
    */
    return Point(p.x - v.dx, p.y - v.dy, p.z - v.dz);
}

const Vector operator-(Vector v, Vector w) {
    /**
        implemented
    */
    return Vector(v.dx - w.dx, v.dy - w.dy, w.dz - w.dz);
}

const Vector operator-(const Point &tail, const Point &head) {
    /**
      implemented
    */
    return Vector(tail.x-head.x, tail.y-head.y, tail.z-head.z);
}

// Scalar Multiplication
const Vector operator*(float s, const Vector &v) {
    /**
      implemented
    */
    return Vector(s * v.dx, s * v.dy, s * v.dz);
}

const Vector operator*(const Vector &v, float s) {
    /**
      implemented
    */
    return Vector(v.dx*s, v.dy*s, v.dz*s);
}
