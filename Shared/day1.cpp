#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

class InputData {
public:
	std::vector<int> left;
	std::vector<int> right;
	InputData(std::string infile_name) {
		std::ifstream infile(infile_name);
		int last_x, last_y;
		while (infile >> last_x >> last_y) {
			left.push_back(last_x);
			right.push_back(last_y);
		}
	}
};

std::string arg_infile(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "specify input file\n";
		throw 1;
	}
	return std::string(argv[1]);
}