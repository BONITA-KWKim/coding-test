#include "main.hh"

int main(int argc, char **argv) {
	std::cout << "Greedy" << std::endl;

	//std::string degree;
	int degree[2];
	char input[REMOTE_MAX_INPUT];
	input[5] = ' ';

	/* User input */
	while (true) {
		std::cin.getline(input, sizeof input);
		std::cout << "input values: " << input << std::endl;

		char* tok1 = strtok(input, " ");
		int i = 0;
		while(tok1 != NULL){
			degree[i] = (int)atoi(tok1);
			tok1 = strtok(NULL," ");
			++i;
		}

		/* user input error */
		if (1 > degree[0] || 40 < degree[0] || 1 > degree[1] || 40 < degree[1]) {
			std::cout << "input values have to be between 1 and 40" << std::endl;
			continue;
		} else {
			break;
		}
	}

	/* greedy algorithm */
	if (degree[1] > degree[0]) {
		/* UP */
		std::cout<< "UP" <<std::endl;

	} else if (degree[1] < degree[0]) {
		/* DOWN */
		std::cout<< "DWON" <<std::endl;
		int tmp = degree[1];
		degree[1] = degree[0];
		degree[0] = tmp;
	} else {
		/* No action is needed */
		std::cout<< "NO ACTION" <<std::endl;

		return 0;
	}

	std::cout<< degree[0] << " : " << degree[1] <<std::endl;

	int count = 0;
	while (true) {
		int gap = degree[1] - degree[0];
		if (BTN_DEGREE_10 <= gap) {
			degree[0] += BTN_DEGREE_10;
			++count;
			std::cout<< "count: " << count << " push button: " << BTN_DEGREE_10 << "    " << degree[0] << ":" << degree[1] <<std::endl;
		} else if (BTN_DEGREE_5 <= gap) {
			degree[0] += BTN_DEGREE_5;
			++count;
			std::cout<< "count: " << count << " push button: " << BTN_DEGREE_5 << "     " << degree[0] << ":" << degree[1] <<std::endl;
		} else if (BTN_DEGREE_1 <= gap) {
			degree[0] += BTN_DEGREE_1;
			++count;
			std::cout<< "count: " << count << " push button: " << BTN_DEGREE_1 << "     " << degree[0] << ":" << degree[1] <<std::endl;
		} else if (0 == gap) {
			break;
		}
	}

	std::cout << "Count: " << count << std::endl;

	return 0;
}

