#include <iostream>
#include "eq_func.h"
#include "method.h"

// �������� ��������
#define X (-0.872)
#define Y (0.492)
#define LINE(x) { std::cout << std::endl; for(int i = 0; i < x; i++) {std::cout << "-";} std::cout << "\n\n";}

// �������
#define EPS pow(10.0,-3.0) 

int main()
{
    LINE(50)

	// ����������� ����� 
    Iterative_Method(X, Y, EPS);
    LINE(50)

	// ����� �������
     Newton_Method(X, Y, EPS);
    LINE(50)

    return 0;
}
