#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

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
int main(int argc, char* argv[]) {
	std::map<int, int> total;
	std::string infile = arg_infile(argc, argv);
	InputData inputData(infile);
	for (auto i = inputData.right.begin(); i != inputData.right.end(); ++i) {
		total.insert_or_assign(*i, (total.count(*i) > 0 ? total[*i] : 0) + 1);
	}
	int sum = 0;
	for (auto i = inputData.left.begin(); i != inputData.left.end(); ++i) {
		sum += (total.count(*i) > 0 ? total[*i] : 0) * *i;
	}
	std::cout << "result: " << sum << '\n';
}
