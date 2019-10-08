#include "main.hh"

int main() {
	std::cout << "Hello greedy 3301"  << std::endl;

	int money[NUMBER_OF_MONEY];
	money[0] = MONEY_10_WON;
	money[1] = MONEY_50_WON;
	money[2] = MONEY_100_WON;
	money[3] = MONEY_500_WON;
	money[4] = MONEY_1000_WON;
	money[5] = MONEY_5000_WON;
	money[6] = MONEY_10000_WON;
	money[7] = MONEY_50000_WON;

	/* user input */
	int rest;
	std::cin >> rest;
	std::cout << "input values: " << rest << std::endl;

	/* greedy algorithm */
	int min_rest_count = 0;
	bool bFlag = false;
	while (!bFlag) {
		for (int i = (NUMBER_OF_MONEY-1); 0 <= i; --i) {
			std::cout << "for loop: " << i << std::endl;

			int tmp = rest - money[i];
			if (0 < tmp) {
				rest = tmp;
				++min_rest_count;
				std::cout << "rest: " << rest << ", change: " << money[i]<< std::endl;
				break;
			} else if (0 == tmp) {
				rest = tmp;
				++min_rest_count;
				std::cout << "rest: " << rest << ", change: " << money[i]<< std::endl;

				bFlag = true;
			}
		}
	}

	std::cout << min_rest_count << std::endl;

	return 0;
}
