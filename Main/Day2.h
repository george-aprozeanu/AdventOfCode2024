#pragma once
#include <vector>
#include <sstream>
#include <iostream>

int sgn(int val);

enum Direction { Unknown, Stall, Sub, Add };

Direction get_direction(int value, int prev);

bool get_safeness(int value, int prev);

void read_vec(std::string& str, std::vector<int>& vec);

std::vector<int> skip(std::vector<int>& src, size_t skip_index);

std::ostream& operator<<(std::ostream& os, std::vector<int>& that);


class Day2Sol {
public:
	Direction direction;
	int value;
	int prev;
	bool value_safe;
	bool same_dir;

	Day2Sol(int value, int prev);
	Day2Sol(int value, Day2Sol& prev_sol);
	bool good_dir();
	bool safe();
};
std::ostream& operator<<(std::ostream& os, Day2Sol& that);


const int Safe = -1;

size_t solve_day2p1(std::vector<int>& vec);
void day2p1(std::string& p1);
void day2p2(std::string& p1);
