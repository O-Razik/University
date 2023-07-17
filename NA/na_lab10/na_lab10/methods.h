#pragma once
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

#include "func.h"

std::vector<double> TableLeftRight(const std::vector<double>& limits, double h);

std::vector<double> TableAver(const std::vector<double>& limits, double h);
std::vector<double> TableTrap(const std::vector<double>& limits, double h);

void left_rectangles(const std::vector<double>& points_rl, double h);

void right_rectangles(const std::vector<double>& points_rl, double h);

void aver_rectangles(const std::vector<double>& points_aver, double h);

void trapezium(const std::vector<double>& points_trap, double h);

void simson(const std::vector<double>& points, double h);

double calc_eps_rect(const std::vector<double>& limits, double h);
double calc_n_eps_rect(const std::vector<double>& limits, double eps);

double calc_eps_trap(const std::vector<double>& limits, double h);
double calc_n_eps_trap(const std::vector<double>& limits, double eps);