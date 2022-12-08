#include "GameStats.h"

GameStats::GameStats() {
	this->name = "";
	this->time = 0.0;
	this->level = 1;
	this->kills = 0;
	this->gold = 100;
	this->damage = 0;
	this->towers = 0;
}

GameStats::GameStats(std::string name) : GameStats() {
	this->name = name;
}

std::string GameStats::get_name() {
	return this->name;
}

double GameStats::get_time() {
	return this->time;
}

int GameStats::get_level() {
	return this->level;
}

int GameStats::get_kills() {
	return this->kills;
}

int GameStats::get_gold() {
	return this->gold;
}

int GameStats::get_damage() {
	return this->damage;
}

int GameStats::get_towers() {
	return this->towers;
}

void GameStats::set_time(double time) {
	this->time = time;
}

void GameStats::set_level(int level) {
	this->level = level;
}

void GameStats::set_kills(int kills) {
	this->kills = kills;
}

void GameStats::set_gold(int gold) {
	this->gold = gold;
}

void GameStats::set_damage(int damage) {
	this->damage = damage;
}

void GameStats::set_towers(int towers) {
	this->towers = towers;
}
