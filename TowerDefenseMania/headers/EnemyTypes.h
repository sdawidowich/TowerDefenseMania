#pragma once
#include "Enemy.h"

class Zombie : public Enemy {
private:
public:
	Zombie(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, sf::Vector2i dir);
};