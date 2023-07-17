#include "method.h"
#define MAX 100

// Перевірка збіжності за сумою модулів частинних похідних
bool Is_Convergent(double x, double y) {
    double sum = std::abs(dphi1_dx(x, y)) + std::abs(dphi2_dx(x, y));
    if (sum >= 1) {
        std::cout << "The convergence condition is not fulfilled\n";
        return false;
    }
	sum = std::abs(dphi1_dy(x, y)) + std::abs(dphi2_dy(x, y));
    if (sum >= 1) {
	    std::cout << "The convergence condition is not fulfilled\n";
        return false;
    }

    sum = std::abs(dphi1_dx(x, y)) + std::abs(dphi1_dy(x, y));
    if (sum >= 1) {
        std::cout << "The convergence condition is not fulfilled\n";
        return false;
    }
    sum = std::abs(dphi2_dx(x, y)) + std::abs(dphi2_dy(x, y));
    if (sum >= 1) {
        std::cout << "The convergence condition is not fulfilled\n";
        return false;
    }

    return true;
}

// Ітераційний метод 
void Iterative_Method(double x0, double y0, double eps) {
    double x = x0, y = y0, xn, yn, err_sum;
    int iter = 0;

    std::cout << "Iterative method: " << std::endl;
    // Перевірка збіжності 
    if (!Is_Convergent(x, y)) {
        return;
    }

    do {
        xn = phi2(x, y);
        yn = phi1(x, y);
        err_sum = abs(xn - x) + abs(yn - y);
        std::cout << std::endl << "Iteration #" << iter << " : \n";
        std::cout << " x = " << x << std::endl << " y = " << y << std::endl;
        x = xn;
        y = yn;
        iter++;
    	if (iter == MAX) {
    		std::cout << "\n Too many iterations. Program will stop\n";
			return;
		}
    } while (err_sum > eps);

    // Виведення результату
    std::cout << "Iteration #" << iter << " : \n";
    std::cout << " x = " << x << std::endl << " y = " << y << std::endl;
    std::cout << std::endl << "This was its final iteration.\n Result: \n";
    std::cout << " x = " << x << std::endl << " y = " << y << std::endl;
    std::cout << "Number of iterations: " << iter << std::endl;
    
}

// Метод Ньютона
void Newton_Method(double x0, double y0, double eps) {
    double x = x0, y = y0, xn = x, yn = y, detx, dety, detxy, err_sum;
    int iter = 0;

    std::cout << "Newton`s method: " << std::endl;
    // Перевірка збіжності 
    if (!Is_Convergent(x, y)) {
        return;
    }

    do {
        detxy = df1dx(x, y) * df2dy(x, y) - df1dy(x, y) * df2dx(x, y);
        detx = (-1)*(f1(x, y) * df2dy(x, y) - df1dy(x, y) * f2(x, y))/detxy;
        dety = (-1)*(df1dx(x, y) * f2(x, y) - f1(x, y) * df2dx(x, y)) / detxy;
        xn += detx;
        yn += dety;


        err_sum = abs(xn - x) + abs(yn - y);
        std::cout << std::endl << "Iteration #" << iter << " : \n";
        std::cout << " x = " << x << std::endl << " y = " << y << std::endl;
        x = xn;
        y = yn;
        iter++;
        if (iter == MAX) {
            std::cout << "\n Too many iterations. Program will stop\n";
            return;
        }
    } while (err_sum > eps);

    // Виведення результату
    std::cout << "Iteration #" << iter << " : \n";
    std::cout << " x = " << x << std::endl << " y = " << y << std::endl;
    std::cout << std::endl << "This was its final iteration.\n Result: \n";
    std::cout << " x = " << x << std::endl << " y = " << y << std::endl;
    std::cout << "Number of iterations: " << iter << std::endl;
}
