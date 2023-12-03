#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>
#include<iostream>

bool isSymbol(int x, int y, const std::vector<std::string>& data) {
	if (x < 0 || y < 0)return false;
	if (x >= data[0].length()||y>=data.size())return false;
	if (data[y][x] == '.' || (data[y][x] >= '0' && data[y][x] <= '9'))return false;
	return true;
}

int isPartNumber(int x, int y, const std::vector<std::string>& data) {
	if (x < 0 || y < 0)return 0;
	if (x > data[0].length() || y > data.size())return 0;
	if (data[y][x] >= '0' && data[y][x] <= '9') {
		int length = data[y].find_first_not_of("0123456789", x)-x;

		bool isPart = false;
		isPart = isSymbol(x - 1, y - 1, data) || isSymbol(x - 1, y, data) || isSymbol(x - 1, y + 1, data) || isSymbol(x + length, y - 1, data) || isSymbol(x + length, y, data) || isSymbol(x +length, y + 1, data);
		for (int i = 0; i < length; ++i) {
			if (isSymbol(x + i, y - 1, data) || isSymbol(x + i, y + 1, data))
				isPart = true;
		}
		if (isPart) return length;//;
	}
	return 0;
}

uint64_t aoc::day3::part_1(const std::vector<std::string>& data) {
	int total = 0;
	for (int y = 0; y < data.size(); ++y) {
		for (int x = 0; x < data[0].length(); ++x) {
			int length = isPartNumber(x,y,data);
			if (length) {
				total += std::stoi(data[y].substr(x, length));
				x += length - 1;
			}
		}
	}
	return total;
}

int getNum(int x, int y, const std::vector<std::vector<int>>& data) {
	if (x < 0 || y < 0)return 0;
	if (x >= data[0].size() || y >= data.size())return 0;
	return data[y][x];
}

uint64_t aoc::day3::part_2(const std::vector<std::string>& data) {
	std::vector<std::vector<int>> indices(data.size(), std::vector<int>(data[0].length(), 0));
	std::vector<int>numbers(data[0].length() * data.size()*0.5);
	int count = 1;
	for (int y = 0; y < data.size(); ++y) {
		for (int x = 0; x < data[0].length(); ++x) {
			int length = isPartNumber(x, y, data);
			if (length) {
				numbers[count]= std::stoi(data[y].substr(x, length));
				for (int i = 0; i < length; ++i) {
					indices[y][x+i] = count;
				}
				x += length - 1;
				count++;
			}
		}
	}
	std::vector<std::pair<int, int>> relativeCoordinates = {
		{-1, -1},{0, -1},{1, -1},{-1, 0},{1, 0}, {-1, 1},{0, 1},{1, 1} 
	};

	int total = 0;
	for (int y = 0; y < data.size(); ++y) {
		for (int x = 0; x < data[0].length(); ++x) {
			if (data[y][x] != '*')continue;
			int firstNum = 0;
			int secondNum = 0;
			int value = 0;
			int num= 0;
			bool valid = false;
			for (int i = 0; i < relativeCoordinates.size(); ++i) {
				num = getNum(x+relativeCoordinates[i].first, y + relativeCoordinates[i].second, indices);
				if (!num)continue;
				if (secondNum > 0 && num != secondNum&& num != firstNum) {
					valid = false;
					continue;
				}
				if (firstNum == 0) {
					firstNum = num; 
					value = numbers[num]; 
				}
				if (num!=firstNum&&secondNum==0) { 
					secondNum = num;
					value *= numbers[num];
					valid = true;
				}
			}
			if (valid) {
				total += value;
				//std::cout << value << std::endl;
			}
		}
	}

	return total;
}