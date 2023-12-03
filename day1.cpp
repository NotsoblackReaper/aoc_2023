#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>
#include<iostream>
uint64_t aoc::day1::part_1(const std::vector<std::string>& data) {
	int total = 0;
	for (int i = 0; i < data.size(); ++i) {
		int firstPos = data[i].find_first_of("0123456789"), lastPos = data[i].find_last_of("0123456789");
		total += 10 * (data[i][firstPos] - '0') + (data[i][lastPos] - '0');
	}
	return total;
}

uint64_t aoc::day1::part_2(const std::vector<std::string>& data) {
	int total = 0;
	const char* digits[] = {"one", "two", "three", "four", "five", "six", "seven", "eight",  "nine"};
	for (int i = 0; i < data.size(); ++i) {
		int firstPos = data[i].find_first_of("0123456789"), lastPos= data[i].find_last_of("0123456789");
		int first = data[i][firstPos] - '0', last = data[i][lastPos] - '0';

		for (int k = 0; k < 9; ++k) {
			int pos = data[i].find(digits[k]);
			if (pos >= 0&&(pos < firstPos || firstPos < 0)) {
				first = k + 1;
				firstPos = pos;
			}
			pos = data[i].rfind(digits[k]);
			if (pos >= 0 && pos > lastPos || lastPos < 0) {
				last = k + 1;
				lastPos = pos;
			}
		}
		total += 10 * first + last;
	}
	return total;
}