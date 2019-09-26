#include "main.hh"

int main(int argc, char **argv) {
	std::cout << "Hello" << std::endl;

	//std::string degree;
	char input[REMOTE_MAX_INPUT];
	input[5] = ' ';

	/* User input */
	std::cin.getline(input, sizeof input);
	std::cout << input << std::endl;

	int i = 0;
	int degree[2];
	char* tok1 = strtok(input, " ");
	while(tok1 != NULL){
		std::cout<<tok1<<" count: "<<i<<std::endl;

		degree[i] = (int)atoi(tok1);
		tok1 = strtok(NULL," ");
		++i;
	}

	/* user input error */

	/* greedy algorithm */
	if (degree[1] > degree[0]) {
		/* UP */
		std::cout<< "UP" <<std::endl;
	} else if (degree[1] < degree[0]) {
		/* DOWN */
		std::cout<< "DWON" <<std::endl;
	} else {
		/* No action is needed */
		std::cout<< "NO ACTION" <<std::endl;
	}

	return 0;
}

