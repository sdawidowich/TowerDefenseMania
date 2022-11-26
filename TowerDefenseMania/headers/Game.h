#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Environment.h"
#include "GUI.h"
#include "Tower.h"
#include "TowerTypes.h"
#include "Enemy.h"
#include "EnemyTypes.h"

class Game {
private:
	sf::Font* font;
	sf::Texture* tower_sprite_sheet;
	sf::Texture* enemy_sprite_sheet;
	sf::Texture* environment_sprite_sheet;
	sf::Texture* gui_sprite_sheet;

	std::map<int, sf::IntRect*> tower_sprites_indices;
	std::map<int, sf::IntRect*> enemy_sprites_indices;
	std::map<int, sf::IntRect*> environment_sprites_indices;
	std::map<int, sf::IntRect*> gui_sprites_indices;

	std::vector<Tower*> towers;
	std::vector<Enemy> enemies;
	Environment* environment;
	GUI* gui;

	int level;
	int gold;
	int max_health;
	int health;
public:
	Game();
	~Game();

	void set_sprite_indices(sf::Texture* sprite_sheet, std::map<int, sf::IntRect*>& sprites_indices);
	void delete_sprite_indices(std::map<int, sf::IntRect*>& sprites_indices);

	void update_gui(sf::RenderWindow& window, sf::Event& event);
	void place_tower(sf::RenderWindow& window, sf::Event& event);

	void draw_environment(sf::RenderWindow& window);
	void draw_gui(sf::RenderWindow& window);
	void draw_towers(sf::RenderWindow& window);
	void draw_enemies(sf::RenderWindow& window);
};