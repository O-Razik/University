#pragma once
#include <iostream>
#include "eq_func.h"

// Перевірка збіжності за сумою модулів частинних похідних
bool Is_Convergent(double x, double y);

// Ітераційний метод 
void Iterative_Method(double x0, double y0, double eps);

// Метод Ньютона
void Newton_Method(double x0, double y0, double eps);