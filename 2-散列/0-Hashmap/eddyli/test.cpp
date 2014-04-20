#include "map.h"
#include <fstream>
#include <stdint.h>
#include <ctime>

int main() {
	eddyli::Map<std::string, int> map;
	std::string s;
	std::ifstream f("inputfile.txt");
	time_t start, end;
	time(&start);

	while(std::getline(f, s)) {
        ++map[s];
    }

	time(&end);
	double dif = difftime(end,start);
	std::cout << dif<< std::endl;
	getchar();
	return 0;
}