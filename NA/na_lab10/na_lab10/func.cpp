#include "func.h"

double sh(double x) {
    return sinh(x);
}

double ch(double x) {
    return cosh(x);
}

double th(double x) {
    return sinh(x) / cosh(x);
}

double cth(double x) {
    return cosh(x) / sinh(x);
}

double f(double x) {
    return std::pow(th(x), 1.0 / 3.0);
}

double df(double x) {
    double chx = ch(x);
    return std::pow(cth(x), 2.0 / 3.0) / (3.0 * std::pow(chx, 2.0));
}

double d2f(double x) {
    double shx = sh(x);
    double chx = ch(x);
    return -1.0 * (6.0 * std::pow(shx, 2.0) + 2.0) / (9.0 * std::pow(chx, 7.0 / 3.0) * std::pow(shx, 5.0 / 3.0));
}

double d3f(double x) {
    double shx = sh(x);
    double chx = ch(x);
    double d3 = 42.0 * std::pow(shx, 4.0) + (14.0 - 6.0 * std::pow(chx, 2.0)) * std::pow(shx, 2.0) + 10.0 * std::pow(chx, 2.0);
    d3 = d3 / (27.0 * std::pow(chx, 10.0 / 3.0) * std::pow(shx, 8.0 / 3.0));
    return d3;
}

double d4f(double x) {
    double shx = sh(x);
    double chx = ch(x);
    double d4 = -(420.0 * std::pow(shx, 6.0) + (140.0 - 192.0 * std::pow(chx, 2.0)) * std::pow(shx, 4.0));
    d4 += (68.0 * std::pow(chx, 2.0) - 12.0 * std::pow(chx, 4.0)) * std::pow(chx, 2.0) + 80.0 * std::pow(chx, 2.0);
    d4 = d4 / (81.0 * std::pow(chx, 13.0 / 3.0) * std::pow(shx, 11.0 / 3.0));
    return d4;
}
