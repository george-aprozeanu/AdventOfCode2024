#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::string arg_infile(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "specify input file\n";
		throw 1;
	}
	return std::string(argv[1]);
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

enum Direction { Unknown, Stall, Sub, Add };

Direction get_direction(int value, int prev) {
	return value - prev == 0 ? Direction::Stall : sgn(value - prev) < 0 ? Direction::Sub : Direction::Add;
}
bool get_safeness(int value, int prev) {
	return std::abs(value - prev) <= 3;
}

int main(int argc, char* argv[]) {
	auto infile = arg_infile(argc, argv);
	std::ifstream instream(infile);
	std::string line;
	int total_safe = 0;
	while (std::getline(instream, line)) {
		std::stringstream str(line);
		bool safe = true;
		int value;
		int prev;
		str >> prev;
		Direction direction = Direction::Unknown;
		bool safeness = true;
		while (str >> value && safeness) {
			Direction this_direction = get_direction(value, prev);
			bool this_safeness = get_safeness(value, prev);
			if (direction == Direction::Unknown) {
				direction = this_direction;
			}
			else if (direction != this_direction || this_direction == Direction::Stall) {
				safeness = false;
				break;
			}
			safeness = safeness && this_safeness;
			prev = value;
		}
		std::cout << "line: " << line <<  " safe: " << safeness << " value: " << value << '\n';
		total_safe = total_safe + (safeness ? 1 : 0);
	}
	std::cout << "total: " << total_safe << '\n';
}
