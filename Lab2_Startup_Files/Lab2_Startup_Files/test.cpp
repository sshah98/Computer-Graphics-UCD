#include "matrix.h"
#include "point.h"
#include "test.h"
#include "vector.h"

#include <cmath>

bool runTest(std::string fileName) {

  /* Points */
  Point p(3, 8, -2);
  Point q(10, -5, 0);
  Point r(0, 0, 1);
  Point s(-7, -2, 6);

  Vector v = q - p;
  Vector w = r - s;

  Point s1 = s + v;
  Point p1 = p + w;

  Vector u = v + w;

  float norm_v = v.norm();
  float norm_w = w.norm();

  Vector v_normal = v.normalised();
  Vector w_normal = w.normalised();

  float v_dot_w = v.dot(w);
  float theta = acos(v_dot_w / (norm_v * norm_w));
  Vector v_cross_w = v.cross(w);
  Vector w_cross_v = w.cross(v);

  float values_a[3][3] = {
      {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -3.0f}};

  float values_b[3][3] = {
      {3.0f, 1.0f, -9.0f}, {5.0f, 3.0f, 6.0f}, {4.0f, 0.0f, 8.0f}};

  Matrix A(values_a), B(values_b);
  Point p2 = A * p;
  Vector v1 = A * v;
  Matrix C1 = A + B;
  Matrix C2 = A - B;
  Matrix C3 = A * B;

  std::ofstream outFile(fileName.c_str(), std::ofstream::out); // open a file

  if (outFile.is_open()) {
    outFile << "------------------" << std::endl;
    outFile << "Test Code: Points:" << std::endl;
    outFile << "------------------" << std::endl;

    outFile << "P = " << p << std::endl;
    outFile << "Q = " << q << std::endl;
    outFile << "R = " << r << std::endl;
    outFile << "S = " << s << std::endl;

    outFile << "------------------" << std::endl;
    outFile << "Part 1:" << std::endl;
    outFile << "------------------" << std::endl;

    outFile << "1. v = " << v << ", w = " << w << std::endl;
    outFile << "2. S' = " << s1 << ", P' = " << p1 << std::endl;
    outFile << "3. u = " << u << std::endl;
    outFile << "4. ||v|| = " << norm_v << ", ||w|| = " << norm_w << std::endl;
    outFile << "5. v_n = " << v_normal << ", w_n = " << w_normal << std::endl;
    outFile << "6. v.w = " << v_dot_w << ", theta = " << theta << " rads ("
            << theta * (180.0f / M_PI) << " degs)" << std::endl;
    outFile << "7. vxw = " << v_cross_w << ", wxv = " << w_cross_v << std::endl;

    outFile << "------------------" << std::endl;
    outFile << "Matrices:" << std::endl;
    outFile << "------------------" << std::endl;

    outFile << "A = " << A << ", B = " << B << std::endl;

    outFile << "------------------" << std::endl;
    outFile << "Part 2:" << std::endl;
    outFile << "------------------" << std::endl;

    outFile << "8. P' = " << p2 << std::endl;
    outFile << "9. v' = " << v1 << std::endl;
    outFile << "10. C = A + B =" << A + B << std::endl;
    outFile << "11. C = A - B =" << C2 << std::endl;
    outFile << "12. C = A * B =" << C3 << std::endl;

    outFile.close();
    return true;
  } else {
    std::cerr << "Fail to open : " << fileName << std::endl;
    return false;
  }
}
