#include "main.hh"

int main() {
	std::cout << "Hello greedy 3321" << std::endl;

	int number_of_topping = 0;
	char tmpPrice[9];
	int price[2];
	int dough_price = 0;
	int topping_price = 0;
	int dough_kcal = 0;
	std::vector<int> topping_kcals;

	//memset(tmpPrice, 0, sizeof tmpPrice);

	/* user input */
	std::cin >> number_of_topping; // 1 <= x <= 1000
	std::cin.getline(tmpPrice, sizeof tmpPrice);

	/*
	char* tok1 = strtok(tmpPrice, " ");
	int i = 0;
	while(tok1 != NULL){
		price[i] = (int)atoi(tok1);
		tok1 = strtok(NULL, " ");
		++i;
	}

	std::cin >> dough_kcal;

	for (int i = 0; number_of_topping > i; ++i) {
		std::cout << "i: " << i << std::endl;
		int tmp = 0;
		std::cin >> tmp;
		std::cout << "tmp: " << tmp <<std::endl;
		topping_kcals.push_back(tmp);
	}
	*/

	//std::cout << "number of Topping: " << number_of_topping << std::endl;
	//std::cout << "Price: " << tmpPrice << std::endl;
	//std::cout << "dough_kcal: " << dough_kcal << std::endl;

	return 0;
}
