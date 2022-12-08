#pragma once
#include <string>

class GameStats {
private:
	std::string name;
	double time;
	int level;
	int kills;
	int gold;
	int damage;
	int towers;
public:
	GameStats();
	GameStats(std::string name);

	// Getters
	std::string get_name();
	double get_time();
	int get_level();
	int get_kills();
	int get_gold();
	int get_damage();
	int get_towers();

	// Setters
	void set_time(double time);
	void set_level(int level);
	void set_kills(int kills);
	void set_gold(int gold);
	void set_damage(int damage);
	void set_towers(int towers);
};

