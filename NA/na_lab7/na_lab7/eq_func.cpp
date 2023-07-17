#include "eq_func.h"

//---------------------------------------------------------

// Функції f1 і f2, їх частинні похідні
double f1(double x, double y) {
    return 2 * y - cos(x + 1);
}

double f2(double x, double y) {
    return x + sin(y) + 0.4;
}

double df1dx(double x, double y) {
    return sin(x + 1);
}

double df1dy(double x, double y) {
    return 2;
}

double df2dx(double x, double y) {
    return 1;
}

double df2dy(double x, double y) {
    return cos(y);
}

//---------------------------------------------------------

// Функції φ1 та φ2, їх частинні похідні
double phi1(double x, double y) {
    return cos(x + 1) / 2;
}
double dphi1_dx(double x, double y) {
    return -sin(x + 1) / 2;
}
double dphi1_dy(double x, double y) {
    return 0;
}

double phi2(double x, double y) {
    return -sin(y) - 0.4;
}
double dphi2_dx(double x, double y) {
    return 0;
}
double dphi2_dy(double x, double y) {
    return -cos(y);
}

//---------------------------------------------------------