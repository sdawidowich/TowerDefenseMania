#pragma once
#include <vector>

#include "GameStats.h"

class StatsFileIO {
private:
public:
	int get_num_lines(const std::string path);
	std::vector<GameStats> read_stats_from_file(const std::string path);
	void write_stats_to_file(const std::string path, std::vector<GameStats>& stats_list);
};

