#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <random>

#include "Environment.h"
#include "GUI.h"
#include "Tower.h"
#include "TowerTypes.h"
#include "Enemy.h"
#include "EnemyTypes.h"
#include "EventHandler.h"

enum class Game_State {
	START, PLAYING, GAME_OVER
};

class Game {
private:
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

	int level;
	int gold;
	int max_health;
	int health;

	sf::Clock timer;
	sf::Time generate_delay;
	int num_generated_enemies;

	Game_State game_over;
public:
	Game();
	~Game();

	void set_sprite_indices(sf::Texture* sprite_sheet, std::map<int, sf::IntRect*>& sprites_indices);
	void delete_sprite_indices(std::map<int, sf::IntRect*>& sprites_indices);

	Game_State get_game_over();

	void check_events(sf::RenderWindow& window, sf::Event& event);
	void check_error_timer();
	void check_game_end();

	void towers_attack();
	void check_enemies();
	void generate_enemies();
	void move_enemies();
	void advance_lvl();

	void draw_start_screen(sf::RenderWindow& window);
	void draw_environment(sf::RenderWindow& window);
	void draw_gui(sf::RenderWindow& window);
	void draw_towers(sf::RenderWindow& window);
	void draw_enemies(sf::RenderWindow& window);
	void draw_game_over(sf::RenderWindow& window);
};