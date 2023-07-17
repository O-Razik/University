#pragma once
#include <iostream>
#include "eq_func.h"

// �������� ������� �� ����� ������ ��������� ��������
bool Is_Convergent(double x, double y);

// ����������� ����� 
void Iterative_Method(double x0, double y0, double eps);

// ����� �������
void Newton_Method(double x0, double y0, double eps);