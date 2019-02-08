#include "calculate.h"

double calculate::addition(double x, double y) {
    return x+y;
}

double calculate::subtraction(double x, double y) {
    return x-y;
}

double calculate::multiplication(double x, double y) {
    return x*y;
}

double calculate::division(double x, double y) {
    return x/y;
}

double calculate::squareRoot(double value) {
    return sqrt(value);
}

double calculate::squared(double value, double power) {
    return pow(value, power);
}

double calculate::valueByPI(double value) {
    return value * PI;
}
