#include "AOC_Solver.h"
#include <numeric>
#include <algorithm>
#include<iostream>
#include <unordered_set>
#include<sstream>

struct map_range {
	uint64_t destination;
	uint64_t source;
	uint64_t length;

	map_range(const std::string& values)
	{
		int firstSpace = values.find_first_of(' ');
		int lastSpace = values.find_last_of(' ');

		destination = std::stoull(values.substr(0, firstSpace));
		source = std::stoull(values.substr(firstSpace, lastSpace));
		length = std::stoull(values.substr(lastSpace));
	}
	const bool in_range(uint64_t source_num) {
		if (source_num<source || source_num>source + length)return false;
		return true;
	}

	const bool in_range_inverse(uint64_t destination_num) {
		if (destination_num<destination || destination_num>destination + length)return false;
		return true;
	}
	const uint64_t convert(uint64_t source_num) {
		uint64_t offset = source_num - source;
		return destination + offset;
	}
	const uint64_t convert_inverse(uint64_t destination_num) {
		uint64_t offset = destination_num - destination;
		return source + offset;
	}
};

uint64_t aoc::day5::part_1(const std::vector<std::string>& data) {
	std::vector<uint64_t>sources{};
	std::vector<map_range>maps{};

	std::istringstream iss{ data[0].substr(7) };
	uint64_t number;
	while (iss >> number) {
		sources.push_back(number);
	}
	int row = 3;
	for (int i = 0; i < 7; ++i) {
		maps.clear();
		while (row < data.size() && data[row].length() > 0) {
			maps.push_back(data[row]);
			row++;
		}
		for (int j = 0; j < sources.size(); ++j) {
			for (int k = 0; k < maps.size(); ++k) {
				if (maps[k].in_range(sources[j])) {
					sources[j] = maps[k].convert(sources[j]);
					break;
				}
			}
		}
		row += 2;
	}
	uint64_t min = UINT64_MAX;
	for (int i = 0; i < sources.size(); ++i)if (sources[i] < min)min = sources[i];
	return min;
}

uint64_t find_source(uint64_t destination, int layer, std::vector <std::vector<map_range>>& maps) {
	for (int i = 0; i < maps[layer].size(); ++i) {
		if (maps[layer][i].in_range_inverse(destination))
			if (layer == 0) {
				return maps[layer][i].convert_inverse(destination);
			}
			else {
				return find_source(maps[layer][i].convert_inverse(destination), layer - 1, maps);
			}
	}
	if (layer == 0) {
		return destination;
	}
	return find_source(destination, layer - 1, maps);
}

uint64_t find_location(uint64_t source, int layer, std::vector <std::vector<map_range>>& maps) {
	layer++;
	for (int i = 0; i < maps[layer].size(); ++i) {
		if (maps[layer][i].in_range(source))
			if (layer == 6) {
				return maps[layer][i].convert(source);
			}
			else {
				return find_location(maps[layer][i].convert(source), layer, maps);
			}
	}
	if (layer == 6) {
		return source;
	}
	return find_location(source, layer, maps);
}

bool is_valid_seed(uint64_t seed, const std::vector<uint64_t>& sources) {
	for (int i = 0; i < sources.size(); i += 2) {
		if (seed > sources[i] && seed < sources[i] + sources[i + 1])return true;
	}
	return false;
}

uint64_t aoc::day5::part_2(const std::vector<std::string>& data) {
	std::vector<uint64_t>sources{};
	std::vector <std::vector<map_range>>maps{};

	std::istringstream iss{ data[0].substr(7) };
	uint64_t number;
	while (iss >> number) {
		sources.push_back(number);
	}
	int row = 3;
	for (int i = 0; i < 7; ++i) {
		maps.push_back(std::vector<map_range>{});
		while (row < data.size() && data[row].length() > 0) {
			maps[i].push_back(data[row]);
			row++;
		}
		row += 2;
	}

	uint64_t min = UINT64_MAX;
	for (int layer = 0; layer < 7; ++layer) {
		for (int i = 0; i < maps[layer].size(); ++i) {
			uint64_t destination = maps[layer][i].destination;
			uint64_t seed = layer>0? find_source(maps[layer][i].source, layer-1, maps): maps[layer][i].source;
			if (!is_valid_seed(seed, sources))continue;
			uint64_t location = layer==6? maps[layer][i].destination:find_location(maps[layer][i].destination, layer, maps);
			if (location < min) {
				min = location;
			}
		}
	}
	return min;
}