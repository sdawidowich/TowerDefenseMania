#include "StatsFileIO.h"

#include <iostream>
#include <fstream>
#include <sstream>

int StatsFileIO::get_num_lines(const std::string path) {
	std::ifstream input;
	input.open(path);

	if (!input.is_open()) {
		return 0;
	}

	int num_lines = 0;

	std::string line;
	while (std::getline(input, line)) {
		num_lines++;
	}

	input.close();
	return num_lines;
}

std::vector<GameStats> StatsFileIO::read_stats_from_file(const std::string path) {
	std::ifstream input;
	input.open(path);

	std::vector<GameStats> stats_list;

	if (!input.is_open()) {
		return stats_list;
	}

	std::string line;
	std::getline(input, line);

	while (std::getline(input, line)) {
		try {
			std::stringstream ss(line);

			std::string name;
			std::getline(ss, name, ',');

			std::string time_str;
			std::getline(ss, time_str, ',');
			double time = std::stod(time_str);

			std::string level_str;
			std::getline(ss, level_str, ',');
			int level = std::stoi(level_str);

			std::string kills_str;
			std::getline(ss, kills_str, ',');
			int kills = std::stoi(kills_str);

			std::string gold_str;
			std::getline(ss, gold_str, ',');
			int gold = std::stoi(gold_str);

			std::string damage_str;
			std::getline(ss, damage_str, ',');
			int damage = std::stoi(damage_str);

			std::string towers_str;
			std::getline(ss, towers_str, ',');
			int towers = std::stoi(towers_str);

			stats_list.push_back(GameStats(name, time, level, kills, gold, damage, towers));
		} catch (const std::invalid_argument&) {
			std::cout << "Error reading line in file. Line skipped." << std::endl;
		}
	}

	input.close();
	return stats_list;
}

void StatsFileIO::write_stats_to_file(const std::string path, std::vector<GameStats>& stats_list) {
	std::ofstream output;
	output.open(path);

	if (!output.is_open()) {
		return;
	}

	output << "Name,Time,Level,Kills,Gold,Damage,Towers" << std::endl;
	for (GameStats game : stats_list) {
		output << game.get_name() << ',' << game.get_time() << ',' << game.get_level() << ',' << game.get_kills() << ',' << game.get_gold() << ',' << game.get_damage() << ',' << game.get_towers() << std::endl;
	}

	output.close();
}
