#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>

void day3p1(std::string& infile_name) {
	std::ifstream infile(infile_name);
	std::stringstream buffer;
	buffer << infile.rdbuf();
	std::string file_contents = buffer.str();

	std::regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)");
	auto words_begin = std::sregex_iterator(file_contents.begin(), file_contents.end(), pattern);
	auto words_end = std::sregex_iterator();

	int total = 0;
	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		int num1 = std::stoi(match[1].str());
		int num2 = std::stoi(match[2].str());
		total += num1 * num2;
	}
	std::cout << "total: " << total << std::endl;
}

enum DoState {
	Do, Dont
};

void day3p2(std::string& infile_name) {
	std::ifstream infile(infile_name);
	std::stringstream buffer;
	buffer << infile.rdbuf();
	std::string file_contents = buffer.str();

	std::regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)|(do|don't)\\(\\)");
	auto words_begin = std::sregex_iterator(file_contents.begin(), file_contents.end(), pattern);
	auto words_end = std::sregex_iterator();

	int total = 0;
	DoState doState = DoState::Do;
	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		if (match[3] == "do") doState = DoState::Do;
		else if (match[3] == "don't") doState = DoState::Dont;
		else {
			int num1 = std::stoi(match[1].str());
			int num2 = std::stoi(match[2].str());
			if (doState == DoState::Do) total += num1 * num2;
		}
	}
	std::cout << "total: " << total << std::endl;
}