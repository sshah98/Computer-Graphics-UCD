#ifndef CALCULATE_H
#define CALCULATE_H

/*
 *  Maths.h
 *  Calculator
 *
 *  Copyright 2017 CSI UCD. All rights reserved.
 *
 */

#include <math.h>
#define PI 3.14159265
class calculate {

public:
  double addition(double x, double y);
  double subtraction(double x, double y);
  double multiplication(double x, double y);
  double division(double x, double y);
  double squareRoot(double value);
  double squared(double value, double power);
  double valueByPI(double value);
};

#endif // CALCULATE_H
