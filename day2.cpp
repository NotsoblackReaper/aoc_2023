#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>
#include<iostream>

bool game_possible(std::string text, int red, int green, int blue) {
	text = text.substr(text.find_first_of(':') +2);
	int semicolon = -1;
	while ((semicolon = text.find_first_of(';')) && text.length()){
		std::string game = semicolon>0?text.substr(0, semicolon):text;
		text = semicolon > 0 ? text.substr(semicolon+2):"";

		int comma = -1;
		while ((comma = game.find_first_of(',')) && game.length()) {
			std::string color = comma > 0 ? game.substr(0, comma) : game;
			game = comma > 0 ? game.substr(comma + 2) : "";

			int spaceIdx = 1+(color[2]==' ');
			int value = spaceIdx == 1 ? color[0] - '0' : (color[0] - '0') * 10+ (color[1] - '0');
			if (color[spaceIdx + 1] == 'g' && value > green)return false;
			if (color[spaceIdx + 1] == 'b' && value > blue)return false;
			if (color[spaceIdx + 1] == 'r' &&value > red)return false;
		} 
	}
	return true;
}

uint64_t aoc::day2::part_1(const std::vector<std::string>& data) {
	int total = 0;
	for (int i = 0; i < data.size(); ++i) {
		if (game_possible(data[i], 12, 13, 14))total += i+1;
	}
	return total;
}


int min_cubes(std::string text) {
	int colorVals[] = { 0,0,0 };
	text = text.substr(text.find_first_of(':') + 2);
	int semicolon = text.find_first_of(';');
	while ((semicolon = text.find_first_of(';')) && text.length()) {
		std::string game = semicolon > 0 ? text.substr(0, semicolon) : text;
		text = semicolon > 0 ? text.substr(semicolon + 2) : "";

		int comma = -1;
		while ((comma = game.find_first_of(',')) && game.length()) {
			std::string color = comma > 0 ? game.substr(0, comma) : game;
			game = comma > 0 ? game.substr(comma + 2) : "";

			int spaceIdx = 1 + (color[2] == ' ');
			int value = spaceIdx == 1 ? color[0] - '0' : (color[0] - '0') * 10 + (color[1] - '0');
			int valIdx = color[spaceIdx + 1] == 'r' ? 0 : color[spaceIdx + 1] == 'g' ? 1 : 2;
			if (value > colorVals[valIdx])colorVals[valIdx] = value;
		}
	}
	return(colorVals[0]* colorVals[1]* colorVals[2]);
}


uint64_t aoc::day2::part_2(const std::vector<std::string>& data) {
	uint64_t total = 0;
	for (int i = 0; i < data.size(); ++i) {
		total+=min_cubes(data[i]);
	}
	return total;
}