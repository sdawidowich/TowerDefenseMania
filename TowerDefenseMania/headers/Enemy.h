#pragma once
#include <SFML/Graphics.hpp>

#include "Sprite.h"

class Enemy : public Sprite {
protected:
	float speed;
	int health;
	int damage;
	int gold_value;
	sf::Vector2i dir;
public:
	Enemy(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, float speed, int health, int damage, int gold_value, sf::Vector2i dir);

	int get_health();
	int get_gold_value();

	void move();
	void change_dir(sf::Vector2i dir);
	void take_damage(int damage);
};