#pragma once
#include <SFML/Graphics.hpp>

#include "Sprite.h"

class Enemy : public Sprite {
protected:
	float speed;
	int health;
	sf::Vector2i dir;
public:
	Enemy(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, float speed, int health, sf::Vector2i dir);
};