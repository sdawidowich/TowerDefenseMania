#pragma once
#include <SFML/Graphics.hpp>

#include "Environment.h"
#include "Tower.h"
#include "Enemy.h"

class Game {
private:
	sf::Texture* tower_sprite_sheet;
	sf::Texture* enemy_sprite_sheet;
	sf::Texture* environment_sprite_sheet;

	Environment* environment;
public:
	Game();
	~Game();

	void draw_environment(sf::RenderWindow& window);
};