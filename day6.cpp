#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>
#include<iostream>
#include<sstream>
#include <algorithm>
#include <string>

uint64_t aoc::day6::part_1(const std::vector<std::string>& data) {
	uint64_t total = 1;
	std::vector<uint64_t>times{};
	std::vector<uint64_t>distances{};

	std::istringstream issT{ data[0].substr(10) };
	std::istringstream issD{ data[1].substr(10) };
	uint64_t time,dist;
	while (issT >> time&&issD>>dist) {
		times.push_back(time);
		distances.push_back(dist);
	}

	for (int i = 0; i < times.size(); ++i) {
		int time = times[i], dist = distances[i];
		int speed = 0;
		
		double root = sqrt(time * time - 4 * dist);
		int min =std::ceil(0.5 * (time - root));
		int max = std::floor(0.5 * (time + root));
		total *= (max - min)+1;
	}
	return total;
}

uint64_t aoc::day6::part_2(const std::vector<std::string>& data) {
	uint64_t time = 0, dist = 0;

	std::string timeS = data[0].substr(data[0].find_first_of(':') + 1);
	std::string distS = data[1].substr(data[1].find_first_of(':') + 1);
	timeS.erase(remove_if(timeS.begin(), timeS.end(), isspace), timeS.end());
	distS.erase(remove_if(distS.begin(), distS.end(), isspace), distS.end());

	time = std::stoull(timeS);
	dist = std::stoull(distS);

	double root = sqrt(time * time - 4 * dist);
	uint64_t min = std::ceil(0.5 * (time - root));
	uint64_t max = std::floor(0.5 * (time + root));
	return (max - min) + 1;
}