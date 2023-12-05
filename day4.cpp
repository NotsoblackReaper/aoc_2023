#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>
#include<iostream>
#include <unordered_set>

uint64_t aoc::day4::part_1(const std::vector<std::string>& data) {
	int total = 0;
	std::unordered_set<int> winning_numbers{};
	for (int i = 0; i < data.size(); ++i) {
		int score = 0;
		int offset = data[i].find_first_of(':')+2;
		while (data[i][offset] !='|') {
			int number = (data[i][offset] == ' ' ? 0 : data[i][offset] - '0') * 10 + data[i][offset + 1]-'0';
			winning_numbers.insert(number);
			offset += 3;
		}
		offset+= 2;
		while (offset < data[i].length()) {
			int number = (data[i][offset] == ' ' ? 0 : data[i][offset] - '0') * 10 + data[i][offset + 1]-'0';
			if (winning_numbers.contains(number)) {
				if (score == 0)score = 1;
				else score*= 2;
			}
			offset += 3;
		}
		winning_numbers.clear();
		total += score;
	}
	return total;
}

uint64_t aoc::day4::part_2(const std::vector<std::string>& data) {
	int total = 0;
	std::unordered_set<int> winning_numbers{};
	std::vector<int>win_count(data.size() + 1);
	std::vector<int>card_count(data.size() + 1);
	for (int i = 0; i < data.size() + 1; ++i)
		card_count[i] = 1;

	for (int i = 0; i < data.size(); ++i) {
		int score = 0;
		int offset = data[i].find_first_of(':') + 2;
		while (data[i][offset] != '|') {
			int number = (data[i][offset] == ' ' ? 0 : data[i][offset] - '0') * 10 + data[i][offset + 1] - '0';
			winning_numbers.insert(number);
			offset += 3;
		}
		offset += 2;
		while (offset < data[i].length()) {
			int number = (data[i][offset] == ' ' ? 0 : data[i][offset] - '0') * 10 + data[i][offset + 1] - '0';
			score += winning_numbers.contains(number);
			offset += 3;
		}
		winning_numbers.clear();
		win_count[i]=score;
	}
	for (int i = 0; i < data.size() + 1; ++i) {
		if (!card_count[i])card_count[i] = 1;
		for (int j = 0; j < win_count[i]; ++j) {
			if (!card_count[i + 1 + j])card_count[i + 1 + j] = 1;
			card_count[i + 1 + j] += card_count[i];
		}
		total += win_count[i]* card_count[i];
	}
	return total+data.size();
}