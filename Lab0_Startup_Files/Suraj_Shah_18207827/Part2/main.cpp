/*
 *  main.cpp
 *  Calculator
 *
 */

#include "calculate.h"
#include <iostream>

using namespace ::std;

int main(int argc, char *const argv[]) {

  // removes unused parameter warnings
  (void)argc;
  (void)argv;

  calculate m;
  double x = 5, y = 10;
  // calculate the following expression using m
  // sqrt((x * y) / 3 + (x ^ 2) - (y * PI));

  // each part of the equation uses a method from the calculate class to get the answer, roughly 3.2
  double answer = m.squareRoot(m.subtraction(m.addition(m.multiplication(m.multiplication(x, m.division(1, 3)), y), (m.squared(x, 2))), (m.valueByPI(y))));

  // add you code here
  cout << endl
       << endl
       << "The answer to my arithmetic problem is " << answer << endl
       << endl;
  return 0;
}
