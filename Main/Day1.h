#pragma once
#include <vector>
#include <string>
#include <fstream>

class Day1Data {
public:
	std::vector<int> left;
	std::vector<int> right;
	Day1Data(std::string infile_name);
	static Day1Data read(std::string infile);
};

std::string arg_infile(int argc, char* argv[]);

void day1p1(std::string& infile);
void day1p2(std::string& infile);