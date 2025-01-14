#include <string>
#include <fstream>
#include <iostream>
#include <vector>

enum XMAS {
	X, M, A, S
};

XMAS xmas(char c) {
	switch (c) {
	case 'X': return X;
	case 'M': return M;
	case 'A': return A;
	case 'S': return S;
	}
	throw 1;
};

XMAS xmasCheck[] = {X, M, A, S};

class Matrix2 {
	std::vector<XMAS> data;
	int width;
	int height;
public:
	Matrix2(int width, int height) : width(width), height(height) {
		data.resize(width * height);
	}
	void setColumns(int x) {
		width = x;
		data.resize(width * height);
	}
	void resizeBy(size_t x, size_t y) {
		width += x;
		height += y;
		data.resize(width * height);
	}
	void addRow(std::vector<XMAS>& row) {
		if (row.size() != width) {
			throw std::invalid_argument("Row size does not match matrix width");
		}
		data.insert(data.end(), row.begin(), row.end());
		height++;
	}
	bool checkHorizontal(int x, int y) {
		if (data[y * width + x + 0] != XMAS::X) return false;
		if (data[y * width + x + 1] != XMAS::M) return false;
		if (data[y * width + x + 2] != XMAS::A) return false;
		if (data[y * width + x + 3] != XMAS::S) return false;
		return true;
	}
	bool checkVertical(int x, int y) {
		if (data[(y + 0) * width + x] != XMAS::X) return false;
		if (data[(y + 1) * width + x] != XMAS::M) return false;
		if (data[(y + 2) * width + x] != XMAS::A) return false;
		if (data[(y + 3) * width + x] != XMAS::S) return false;
		return true;
	}
	bool checkDiagonal1(int x, int y) {
		if (data[(y + 0) * width + x + 0] != XMAS::X) return false;
		if (data[(y + 1) * width + x + 1] != XMAS::M) return false;
		if (data[(y + 2) * width + x + 2] != XMAS::A) return false;
		if (data[(y + 3) * width + x + 3] != XMAS::S) return false;
		return true;
	}
	bool checkDiagonal2(int x, int y) {
		if (data[(y + 0) * width + x + 3] != XMAS::X) return false;
		if (data[(y + 1) * width + x + 2] != XMAS::M) return false;
		if (data[(y + 2) * width + x + 1] != XMAS::A) return false;
		if (data[(y + 3) * width + x + 0] != XMAS::S) return false;
		return true;
	}
	bool reverseCheckHorizontal(int x, int y) {
		if (data[y * width + x + 3] != XMAS::X) return false;
		if (data[y * width + x + 2] != XMAS::M) return false;
		if (data[y * width + x + 1] != XMAS::A) return false;
		if (data[y * width + x + 0] != XMAS::S) return false;
		return true;
	}
	bool reverseCheckVertical(int x, int y) {
		if (data[(y + 3) * width + x] != XMAS::X) return false;
		if (data[(y + 2) * width + x] != XMAS::M) return false;
		if (data[(y + 1) * width + x] != XMAS::A) return false;
		if (data[(y + 0) * width + x] != XMAS::S) return false;
		return true;
	}
	bool reverseCheckDiagonal1(int x, int y) {
		if (data[(y + 3) * width + x + 0] != XMAS::X) return false;
		if (data[(y + 2) * width + x + 1] != XMAS::M) return false;
		if (data[(y + 1) * width + x + 2] != XMAS::A) return false;
		if (data[(y + 0) * width + x + 3] != XMAS::S) return false;
		return true;
	}
	bool reverseCheckDiagonal2(int x, int y) {
		if (data[(y + 3) * width + x + 3] != XMAS::X) return false;
		if (data[(y + 2) * width + x + 2] != XMAS::M) return false;
		if (data[(y + 1) * width + x + 1] != XMAS::A) return false;
		if (data[(y + 0) * width + x + 0] != XMAS::S) return false;
		return true;
	}
	bool checkAll(int x, int y) {
		if (checkHorizontal(x, y)) return true;
		if (checkVertical(x, y)) return true;
		if (checkDiagonal1(x, y)) return true;
		if (checkDiagonal2(x, y)) return true;
		if (reverseCheckHorizontal(x, y)) return true;
		if (reverseCheckVertical(x, y)) return true;
		if (reverseCheckDiagonal1(x, y)) return true;
		if (reverseCheckDiagonal2(x, y)) return true;
		return false;
	}
	friend std::ostream& operator<<(std::ostream& os, const Matrix2& matrix);
};

std::ostream& operator<<(std::ostream& os, const XMAS& x) {
	switch (x) {
	case X: os << 'X'; break;
	case M: os << 'M'; break;
	case A: os << 'A'; break;
	case S: os << 'S'; break;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const Matrix2& matrix) {
	for (int y = 0; y < matrix.height; ++y) {
		for (int x = 0; x < matrix.width; ++x) {
			os << matrix.data[y * matrix.width + x] << ' ';
		}
		os << '\n';
	}
	return os;
}

void day4p1(std::string& infile_name) {
	std::ifstream infile(infile_name);
	std::string line;
	Matrix2 matrix(0, 0);
	bool size_known = false;
	while (std::getline(infile, line)) {
		std::vector<XMAS> row;
		for (char c : line) row.push_back(xmas(c));
		if (!size_known) {
			matrix.setColumns(row.size());
			size_known = true;
		}
		matrix.addRow(row);
	}
	std::cout << "Matrix:\n" << matrix << std::endl;
}

void day4p2(std::string& infile_name) {

}
