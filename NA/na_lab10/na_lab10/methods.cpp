#include "methods.h"

std::vector<double> TableLeftRight(const std::vector<double>& limits, double h)
{
    std::vector<double> result;
    int i = 0;
    std::cout << std::endl << "  i  |  xi    | f(xi)  " << std::endl << " ====+========+========" << std::endl;
    for (double x = limits.front(); x <= limits.back(); x += h)
    {
        std::cout << "  " << i << "  | " << std::setprecision(4) << std::fixed << x << " | " << f(x) << " \n";
        result.emplace_back(x);
        i++;
    }
    std::cout << std::endl;
    return result;
}

std::vector<double> TableAver(const std::vector<double>& limits, double h)
{
    std::vector<double> result;
    int i = 0;
    std::cout << std::endl << "  i  | xi+h/2 | f(xi+h/2)  " << std::endl << " ====+========+===========" << std::endl;
    for (double x = limits.front(); x < limits.back(); x += h)
    {
        std::cout << "  " << i << "  | " << std::setprecision(4) << std::fixed << (x + (h / 2)) << " | " << f(x + (h / 2)) << " \n";
        result.emplace_back(x + (h / 2));
        i++;
    }
    std::cout << std::endl;
    return result;
}

std::vector<double> TableTrap(const std::vector<double>& limits, double h)
{
    std::vector<double> result;
    int i = 0;
    std::cout << std::endl << "  i  |  xi    | (f(xi)+f(x[i+1]))/2 " << std::endl << " ====+========+==============" << std::endl;
    for (double x = limits.front(); x < limits.back(); x += h)
    {
        std::cout << "  " << i << "  | " << std::setprecision(4) << std::fixed << x << " | " << (f(x) + f(x + h)) / 2 << " \n";
        result.emplace_back(x);
        i++;
    }
    std::cout << "  " << i << "  | " << std::setprecision(4) << std::fixed << limits.back() << " | " << "  -  " << " \n";
    result.emplace_back(limits.back());
    std::cout << std::endl;
    return result;
}

void left_rectangles(const std::vector<double>& points_rl, double h)
{
    std::cout << " Approximation of the integral using the left rectangles method: " << std::endl;
    double I = 0;
    std::cout << "  I = " << h << " * ( ";
    for (std::size_t i = 0; i < points_rl.size() - 1; ++i)
    {
        double x = points_rl[i];
        I += f(x) * h;
        std::cout << std::setprecision(4) << std::fixed << f(x) << " ";
        if ((i + 1) < (points_rl.size() - 1))
            std::cout << "+ ";
    }
    std::cout << ") = " << std::setprecision(4) << std::fixed << I << std::endl;
}

void right_rectangles(const std::vector<double>& points_rl, double h)
{
    std::cout << " Approximation of the integral using the right rectangles method: " << std::endl;
    double I = 0;
    std::cout << "  I = " << h << " * ( ";
    for (std::size_t i = 1; i < points_rl.size(); i++)
    {
        double x = points_rl[i];
        I += f(x) * h;
        std::cout << std::setprecision(4) << std::fixed << f(x) << " ";
        if ((i + 1) < points_rl.size())
            std::cout << "+ ";
    }
    std::cout << ") = " << std::setprecision(4) << std::fixed << I << std::endl;
}

void aver_rectangles(const std::vector<double>& points_aver, double h)
{
    std::cout << " Approximation of the integral using the average rectangles method: " << std::endl;
    double I = 0;
    std::cout << "  I = " << h << " * ( ";
    for (std::size_t i = 0; i < points_aver.size(); ++i)
    {
        double x_ = points_aver[i];
        I += f(x_) * h;
        std::cout << std::setprecision(4) << std::fixed << f(x_) << " ";
        if ((i + 1) < points_aver.size())
            std::cout << "+ ";
    }
    std::cout << ") = " << std::setprecision(4) << std::fixed << I << std::endl;
}

void trapezium(const std::vector<double>& points_trap, double h)
{
    std::cout << "\n Approximation of the integral using the trapezium method: " << std::endl;
    double I = 0;
    std::cout << "  I = " << h << " * ( ";
    for (std::size_t i = 0; i < points_trap.size() - 1; ++i)
    {
        double x = points_trap[i];
        I += (f(x) + f(x + h)) / 2 * h;
        std::cout << std::setprecision(4) << std::fixed << (f(x) + f(x + h)) / 2 << " ";
        if ((i + 1) < (points_trap.size() - 1))
            std::cout << "+ ";
    }
    std::cout << ") = " << std::setprecision(4) << std::fixed << I << std::endl;
}

void simson(const std::vector<double>& points, double h)
{
    std::cout << "\n Approximation of the integral using Simpson's rule: " << std::endl;
    double I = 0;
    std::cout << "  I = " << h/3 << " * ( ";

    I += f(points[0]);
    std::cout << std::setprecision(4) << std::fixed << f(points[0]) << " + ";
    for (std::size_t i = 1; i < points.size() - 1; ++i)
    {
        double x = points[i];
        if (i % 2 == 0)
        {
            I += 2 * f(x);
            std::cout << std::setprecision(4) << std::fixed << 2 * f(x) << " + ";
        }
        else
        {
            I += 4 * f(x);
            std::cout << std::setprecision(4) << std::fixed << 4 * f(x) << " + ";
        }

    }
    I += f(points[points.size() - 1]);
    std::cout << std::setprecision(4) << std::fixed << f(points[points.size() - 1]) << " ";

    I = I * h / 3;
    std::cout << ") = " << std::setprecision(4) << std::fixed << I << std::endl;
}

double calc_eps_rect(const std::vector<double>& limits, double h)
{
    double R;
    R = d2f(limits[1]) / 24 * (limits[1] - limits[0]) * h * h;
    return R;
}

double calc_n_eps_rect(const std::vector<double>& limits, double eps)
{
    int n = 1;
    double h;
    while(1)
    {
        h = (limits[1] - limits[0]) / n;
        if (fabs(calc_eps_rect(limits, h)) < eps) break;
        else n++;
    }

    return n;
}

double calc_eps_trap(const std::vector<double>& limits, double h)
{
    double R;
    R = -1 * d2f(limits[1]) / 12 * (limits[1] - limits[0]) * h * h;
    return R;
}

double calc_n_eps_trap(const std::vector<double>& limits, double eps)
{
    int n = 1;
    double h;
    while (1)
    {
        h = (limits[1] - limits[0]) / n;
        if (fabs(calc_eps_trap(limits, h)) < eps) break;
        else n++;
    }

    return n;
}

double calc_eps_sim(const std::vector<double>& limits, double n, double Maxd4f)
{
    double R;
    R = -1 * pow(limits[1]-limits[0], 5) * fabs(Maxd4f) / (180 * pow(n,4));
    return R;
}

