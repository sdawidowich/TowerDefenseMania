#pragma once
#include "Enemy.h"

class Zombie : public Enemy {
private:
public:
	Zombie(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, sf::Texture* gui_textures, sf::IntRect* health_bar_crop, sf::Vector2i dir);
};