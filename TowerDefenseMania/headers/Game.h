#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <random>

#include "GameStats.h"
#include "Game_State.h"
#include "Environment.h"
#include "Menu.h"
#include "GUI.h"
#include "Tower.h"
#include "TowerTypes.h"
#include "Enemy.h"
#include "EnemyTypes.h"
#include "EventHandler.h"

class Game {
private:
	std::vector<GameStats>* stats_list;
	GameStats stats;
	sf::Clock timer;

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<double> distr;

	sf::Font* font;
	sf::Texture* tower_sprite_sheet;
	sf::Texture* enemy_sprite_sheet;
	sf::Texture* environment_sprite_sheet;
	sf::Texture* gui_sprite_sheet;

	std::map<int, sf::IntRect*> tower_sprites_indices;
	std::map<int, sf::IntRect*> enemy_sprites_indices;
	std::map<int, sf::IntRect*> environment_sprites_indices;
	std::map<int, sf::IntRect*> gui_sprites_indices;

	EventHandler event_handler;
	std::vector<Tower*> towers;
	std::vector<Enemy> enemies;
	Environment* environment;
	GUI* gui;

	Menu* start_menu;
	Menu* stat_menu;
	int stat_menu_page;

	int level;
	int gold;
	int max_health;
	int health;

	sf::Clock generate_timer;
	sf::Time generate_delay;
	int num_generated_enemies;

	Game_State game_state;
public:
	Game(std::string name, std::vector<GameStats>* stats_list);
	~Game();

	void set_sprite_indices(sf::Texture* sprite_sheet, std::map<int, sf::IntRect*>& sprites_indices);
	void delete_sprite_indices(std::map<int, sf::IntRect*>& sprites_indices);

	void create_start_menu();
	void create_stat_menu();

	GameStats get_stats();
	Game_State get_state();

	void update_stats();

	void check_events(sf::RenderWindow& window, sf::Event& event);
	void check_error_timer();
	void check_game_end();

	void towers_attack();
	void check_enemies();
	void generate_enemies();
	void move_enemies();
	void advance_lvl();

	void draw_start_screen(sf::RenderWindow& window);
	void draw_stat_screen(sf::RenderWindow& window);
	void draw_stats_text(sf::RenderWindow& window);
	void draw_environment(sf::RenderWindow& window);
	void draw_gui(sf::RenderWindow& window);
	void draw_towers(sf::RenderWindow& window);
	void draw_enemies(sf::RenderWindow& window);
	void draw_game_over(sf::RenderWindow& window);
};