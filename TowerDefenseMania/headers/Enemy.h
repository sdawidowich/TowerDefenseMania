#pragma once
#include <SFML/Graphics.hpp>

#include "Sprite.h"

class Enemy : public Sprite {
protected:
	float speed;
	int health;
	int damage;
	sf::Vector2i dir;
public:
	Enemy(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, float speed, int health, int damage, sf::Vector2i dir);

	void move();
	void change_dir(sf::Vector2i dir);
};