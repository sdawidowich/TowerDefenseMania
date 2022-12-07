#pragma once
#include <SFML/Graphics.hpp>

#include "Sprite.h"

class Enemy : public Sprite {
protected:
	float speed;
	int health;
	int damage;
	int gold_value;
	int path_index;
	sf::Vector2i dir;
public:
	Enemy(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, float speed, int health, int damage, int gold_value, sf::Vector2i dir);

	int get_health();
	int get_damage();
	int get_gold_value();
	int get_path_index();
	sf::Vector2i get_dir();

	void move();
	void set_path_index(int path_index);
	void change_dir(sf::Vector2i dir);
	void take_damage(int damage);
};