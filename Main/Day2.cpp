#include "Day2.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

int sgn(int val) {
	return val < 0 ? -1 : val > 0 ? 1 : 0;
}

Direction get_direction(int value, int prev) {
	return value - prev == 0 ? Direction::Stall : sgn(value - prev) < 0 ? Direction::Sub : Direction::Add;
}

bool get_safeness(int value, int prev) {
	return std::abs(value - prev) <= 3;
}

void read_vec(std::string& str, std::vector<int>& vec) {
	std::stringstream stream(str);
	int val;
	while (stream >> val) vec.push_back(val);
}

std::vector<int> skip(std::vector<int>& src, size_t skip_index) {
	size_t index = 0;
	std::vector<int> ret;
	for (auto it = src.begin(); it != src.end(); it++, index++) {
		if (index != skip_index) ret.push_back(*it);
	}
	return ret;
}

std::ostream& operator<<(std::ostream& os, std::vector<int>& that) {
	auto end = that.end();
	for (auto i = that.begin(); i != end; i++) {
		os << *i << " ";
	}
	return os;
}

Day2Sol::Day2Sol(int value, int prev) {
	this->value = value;
	this->prev = prev;
	this->value_safe = get_safeness(value, prev);
	this->direction = get_direction(value, prev);
	this->same_dir = true;
}
Day2Sol::Day2Sol(int value, Day2Sol& prev_sol) {
	this->value = value;
	this->prev = prev_sol.value;
	this->value_safe = get_safeness(value, prev_sol.value);
	this->direction = get_direction(value, prev_sol.value);
	this->same_dir = this->direction == prev_sol.direction;
}

bool Day2Sol::good_dir() {
	return this->direction != Direction::Stall;
}

bool Day2Sol::safe() {
	return this->good_dir() && this->same_dir && this->value_safe;
}

size_t solve_day2p1(std::vector<int>& vec) {
	auto i = vec.begin();
	auto end = vec.end();
	int prev = *i++;
	int value = *i++;
	Day2Sol prev_sol(value, prev);
	if (!prev_sol.safe()) return 0;
	size_t index = 1;
	for (; i != end; i++, index++) {
		value = *i;
		Day2Sol sol(value, prev_sol);
		std::cout << "Index: " << index << " " << sol << '\n';
		if (!sol.safe()) return index;
		prev_sol = sol;
	}
	return -1;
}


void day2p1(std::string& infile_name) {
	std::ifstream infile(infile_name);
	std::string line;
	std::cout << "in: " << infile_name << '\n';
	int safe_count = 0;
	while (std::getline(infile, line)) {
		std::vector<int> in;
		read_vec(line, in);
		bool safe = solve_day2p1(in) == Safe;
		if (safe) safe_count++;
	}
	std::cout << " total: " << safe_count << '\n';
}

std::ostream& operator<<(std::ostream& os, Day2Sol& that) {
	return os << "dir: " << that.direction << " value= " << that.value << " prev= " << that.prev << " value_safe= " << that.value_safe << " same_dir= " << that.same_dir << " good_dir: " << that.good_dir();
};

void day2p2(std::string& infile_name) {
	std::ifstream infile(infile_name);
	std::string line;
	std::cout << "in: " << infile_name << '\n';
	int safe_count = 0;
	while (std::getline(infile, line)) {
		std::vector<int> in;
		read_vec(line, in);
		std::cout << "\n\n";
		int fail_index = solve_day2p1(in);
		if (fail_index == Safe) {
			std::cout << "Safe: " << in << '\n';
			safe_count++;
		}
		else {
			auto a = skip(in, fail_index);
			std::cout << "Test A: " << a << '\n';
			int safe_a = solve_day2p1(a);
			std::cout << "fail at: " << fail_index << "\nsafe_a= " << safe_a << " vec: " << in << " a: " << a << '\n';
			if (safe_a == Safe) {
				std::cout << "Safe A: " << a << '\n';
				safe_count++;
			}
			else {
				auto b = skip(in, fail_index + 1);
				std::cout << "Test B: " << b << '\n';
				int safe_b = solve_day2p1(b);
				std::cout << "safe_b= " << safe_b << " vec: " << in << " b: " << b << '\n' << '\n';
				if (safe_b == Safe) {
					std::cout << "Safe B: " << b << '\n';
					safe_count++;
				}
			}
		};
	}
	std::cout << " p2 total: " << safe_count << '\n';
}