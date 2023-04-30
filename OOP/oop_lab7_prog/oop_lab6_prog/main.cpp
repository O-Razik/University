#include "choose.h"
#include <vector>

int main() {

	std::cout << "Press:\n 1)Console\n 2)File\n 3)Both\n\n";
	char input = '0', mode = '0';
	
	while (input != '1' && input != '2' && input != '3' ) {
		std::cin >> input;
		if (input == '1') {
			mode = 'c';
		}
		else if (input == '2') {
			mode = 'f';
		}
		else if (input == '3')
		{
			mode = 'b';
		}
		else {
			std::cout << "\n Incorrect input. Try again\n" << std::endl;
		}
	}

	int amount = -1;
	std::cout << "\nEnter amount of parcels: ";
	while (amount < 0) {
		std::cin >> amount;
		if(amount < 0) {
		std::cout << "\n Incorrect input. Try again\n" << std::endl;
		}
	}
	std::cout << std::endl;
	
	std::vector<std::unique_ptr<CParcel>> parcels(amount);
	int iteration = 0;
	while(amount != iteration)
	{
		Choose(mode, amount, parcels, iteration);
		iteration++;
	}
	AllCoast(parcels);

	return 0;
}