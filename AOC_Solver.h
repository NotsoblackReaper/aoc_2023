#ifndef AOC_SOLVER
#define AOC_SOLVER

#include <string>
#include <vector>

namespace input {
	std::vector<std::string> data_as_string(const char*);
	std::vector<int> data_as_int(const char*);
	std::vector<int> data_as_csv_int(const char*);
}

namespace aoc
{
	namespace day1
	{
		uint64_t part_1(const std::vector<std::string>&);
		uint64_t part_2(const std::vector<std::string>&);
	}
	namespace day2
	{
		uint64_t part_1(const std::vector<std::string>&);
		uint64_t part_2(const std::vector<std::string>&);
	}
	namespace day3
	{
		uint64_t part_1(const std::vector<std::string>&);
		uint64_t part_2(const std::vector<std::string>&);
	}
	namespace day4
	{
		uint64_t part_1(const std::vector<std::string>&);
		uint64_t part_2(const std::vector<std::string>&);
	}
	namespace day5
	{
		uint64_t part_1(const std::vector<std::string>&);
		uint64_t part_2(const std::vector<std::string>&);
	}
	namespace day6
	{
		uint64_t part_1(const std::vector<std::string>&);
		uint64_t part_2(const std::vector<std::string>&);
	}
}
#endif