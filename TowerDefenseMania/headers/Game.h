#pragma once
#include <SFML/Graphics.hpp>

class Game {
private:
	sf::Texture* tower_sprite_sheet;
	sf::Texture* enemy_sprite_sheet;
	sf::Texture* environment_sprite_sheet;
public:
	Game();
	~Game();
};