
#include "func.h"
#include "methods.h"

int main()
{
	std::vector<double> limits = { 0, log(2)};
	double eps = 0.0001, h;
	int n;
	
	std::cout << " Function: 3^/(thx)\n a = " << limits.front() << " , b = " << limits.back() << ", eps =" << eps << std::endl << std::endl;

	std::cout << "\n Rectangles methods: \n";
	n = calc_n_eps_rect(limits, eps);
	h = (limits.back() - limits.front()) / n;
	std::vector<double> points_rl = TableLeftRight(limits, h);

	left_rectangles(points_rl, h);
	right_rectangles(points_rl, h);

	std::vector<double> points_aver = TableAver(limits, h);
	aver_rectangles(points_aver, h);

	std::cout << "\n R(f) = " << calc_eps_rect(limits, h) << std::endl;

	std::cout << "\n Trapezium method: \n";
	n = calc_n_eps_trap(limits, eps);
	h = (limits.back() - limits.front()) / n;
	std::vector<double> points_trap = TableTrap(limits, h);
	trapezium(points_trap, h);
	std::cout << "\n R(f) = " << calc_eps_trap(limits, h) << std::endl;

	std::cout << "\n Simson method: \n n=10\n";
	n = 10;
	h = (limits.back() - limits.front()) / n;
    std::vector<double> points_sim = TableLeftRight(limits, h);
    simson(points_sim, h);

	return 0;
}


