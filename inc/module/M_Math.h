#pragma once

#include <math.h>

double M_Math_ConvDegsToRads(double degs) {
    double result = degs * M_PI / 180;
    return result;
}
double M_Math_ConvRadsToDegs(double rads) {
    double result = rads * 180 / M_PI;
    return result;
}

double M_Math_CalcTargetX(double offset, double angle, double length) {
    double result = offset - sin(angle) * length;
    return result;
}
double M_Math_CalcTargetY(double offset, double angle, double length) {
    double result = offset + cos(angle) * length;
    return result;
}