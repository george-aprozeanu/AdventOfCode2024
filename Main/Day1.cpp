#include "Day1.h"
#include <algorithm>
#include <iostream>
#include <map>


Day1Data::Day1Data(std::string infile_name) {
		std::ifstream infile(infile_name);
		int last_x, last_y;
		while (infile >> last_x >> last_y) {
			left.push_back(last_x);
			right.push_back(last_y);
		}
	}

Day1Data Day1Data::read(std::string infile) {
	return Day1Data(infile);
}

std::string arg_infile(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "specify input file\n";
		throw 1;
	}
	return std::string(argv[1]);
}

void day1p1(std::string& infile) {
	Day1Data inputData = Day1Data::read(infile);
	std::sort(inputData.left.begin(), inputData.left.end());
	std::sort(inputData.right.begin(), inputData.right.end());
	long total = 0;
	for (int i = 0; i < inputData.left.size(); i++) {
		total += std::abs(inputData.right[i] - inputData.left[i]);
	}
	std::cout << "total: " << total << " size: " << inputData.left.size() << '\n';
}

void day1p2(std::string& infile) {
	Day1Data inputData(infile);
	std::map<int, int> total;
	for (auto i = inputData.right.begin(); i != inputData.right.end(); ++i) {
		total.insert_or_assign(*i, (total.count(*i) > 0 ? total[*i] : 0) + 1);
	}
	int sum = 0;
	for (auto i = inputData.left.begin(); i != inputData.left.end(); ++i) {
		sum += (total.count(*i) > 0 ? total[*i] : 0) * *i;
	}
	std::cout << "result: " << sum << '\n';
}
