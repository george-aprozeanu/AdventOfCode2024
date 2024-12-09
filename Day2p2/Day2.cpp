#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <iterator>

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

template <typename T> Direction get_direction(T value, T prev) {
	return value - prev == 0 ? Direction::Stall : sgn(value - prev) < 0 ? Direction::Sub : Direction::Add;
}
template <typename T> bool get_safeness(T value, T prev) {
	return std::abs(value - prev) <= 3;
}
template <typename T> std::vector<T> read_vec(std::stringstream& str) {
	std::vector<T> ret;
	T val;
	while (str >> val) ret.push_back(val);
	return ret;
}

template <typename T> class SkipIterator {
public:
	SkipIterator(std::vector<T>& vec, size_t skip, size_t index = 0) :
		vec(vec), skip(skip), index(index) {
		auto size = vec.size();
	}
	SkipIterator<T> begin() {
		size_t begin = this->skip == 0 ? 1 : 0;
		return SkipIterator(this->vec, this->skip, begin);
	}
	SkipIterator<T> end() {
		size_t size = this->vec.size();
		return SkipIterator(this->vec, this->skip, this->skip == size - 1 ? size - 1 : size);
	}
	bool operator !=(SkipIterator& other) {
		return this->index != other.index;
	}
	void operator ++() {
		size_t step = this->skip == this->index + 1 && this->index + 2 < this->vec.size() ? 2 : 1;
		this->index += step;
	}
	T operator*() {
		return this->vec[this->index];
	}
private:
	std::vector<T>& vec;
	size_t skip;
	size_t index;
};

int main(int argc, char* argv[]) {
	auto infile = arg_infile(argc, argv);
	std::ifstream instream(infile);
	std::string line;
	int total_safe = 0;
	while (std::getline(instream, line)) {
		std::stringstream str(line);
		std::cout << "line: " << line << '\n';
		std::vector<int> vec = read_vec<int>(str);
		for (auto i : SkipIterator<int>(vec, 0)) {
			std::cout << " " << i;
		}
		std::cout << '\n';
		/*	bool safe = true;
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
			std::cout << "line: " << line << " safe: " << safeness << " value: " << value << '\n';
			total_safe = total_safe + (safeness ? 1 : 0);*/
	}
	std::cout << "total: " << total_safe << '\n';
}
