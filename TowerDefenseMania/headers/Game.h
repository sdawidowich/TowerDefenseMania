#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Environment.h"
#include "GUI.h"
#include "Tower.h"
#include "TowerTypes.h"
#include "Enemy.h"
#include "EnemyTypes.h"

class Game {
private:
	sf::Texture* tower_sprite_sheet;
	sf::Texture* enemy_sprite_sheet;
	sf::Texture* environment_sprite_sheet;
	sf::Texture* gui_sprite_sheet;

	Environment* environment;
	GUI* gui;

	int level;

	std::vector<Tower> towers;
	std::vector<Enemy> enemies;
public:
	Game();
	~Game();

	void update_gui(sf::RenderWindow& window, sf::Event& event);

	void draw_environment(sf::RenderWindow& window);
	void draw_gui(sf::RenderWindow& window);
	void draw_towers(sf::RenderWindow& window);
	void draw_enemies(sf::RenderWindow& window);
};