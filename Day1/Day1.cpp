// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

void min_after(std::vector<int>& vec, int& after, int& repeat) {
	int candidate = INT_MAX;
	int count = 0;
	for (int elem : vec) {
		if (elem == after) {
			count++;
			if (repeat + 1 < count) {
				repeat = count;
				return;
			}
		}
		if (elem < candidate && elem > after) {
			candidate = elem;
			count = 1;
		}
	}
	if (count > 0) {
		after = candidate;
		repeat = 1;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "specify input file\n";
		return 1;
	}
	std::ifstream infile(argv[1]);
	std::vector<int> left;
	std::vector<int> right;
	int max = 0;
	int last_x, last_y;
	while (infile >> last_x >> last_y) {
		max += 1;
		left.push_back(last_x);
		right.push_back(last_y);
	}
	int last_left = INT_MIN, last_right = INT_MIN, repeat_left = 0, repeat_right = 0, total = 0;
	for (int i = 0; i < max; i++) {
		min_after(left, last_left, repeat_left);
		min_after(right, last_right, repeat_right);
		if (last_left < INT_MAX) {
			std::cout << total << " + " << last_right << " - " << last_left << " (" << last_right - last_left << ")  = " << total + (last_right - last_left) << '\n';
			total += last_right - last_left;
		}
	}
	std::cout << "total: " << total << '\n';
}
