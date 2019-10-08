#include "main.hh"

int main(int argc, char **argv) {
	std::cout << "Greedy" << std::endl;

	//std::string degree;
	int degree[2];
	char input[REMOTE_MAX_INPUT];
	input[5] = ' ';
	/* buttons */
	int buttons[BTN_COUNT];
	buttons[0] = BTN_DEGREE_ADD_1;
	buttons[1] = BTN_DEGREE_ADD_5;
	buttons[2] = BTN_DEGREE_ADD_10;
	buttons[3] = BTN_DEGREE_SUB_1;
	buttons[4] = BTN_DEGREE_SUB_5;
	buttons[5] = BTN_DEGREE_SUB_10;

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
	int count = 0;

	if (degree [1] == degree[0]) {
		/* No action is needed */
		//std::cout<< "NO ACTION" <<std::endl;

		std::cout << count << std::endl;
		return 0;
	}

	while (true) {
		int gap = degree[1] - degree[0];

		if (0 == gap) {
			/* terminate */
			break;
		} else {
			/* search result */
			int button = 0;
			int distance = 0;
			for (int i = 0; BTN_COUNT > i; ++i) {
				int tmp_dis = std::abs(degree[1] - (degree[0] + buttons[i]));

				if(0 == i) {
					button = buttons[i];
					distance = tmp_dis;
				} else {
					if (distance > tmp_dis) {
						button = buttons[i];
						distance = tmp_dis;
					}
				}
			}
			++count;
			degree[0] += button;

			// std::cout << "add: " << button << ", now: " << degree[0] << ", target: " << degree[1] << count << std::endl;
		}
	}

	std::cout << count << std::endl;

	return 0;
}

