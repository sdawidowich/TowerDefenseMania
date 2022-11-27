#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include <Enemy.h>

#include "Sprite.h"

class Tower : public Sprite {
protected:
	int attack_damage;
	int range;

	sf::Clock timer;
	sf::Time attack_cooldown;
public:
	Tower(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, int attack_damage, int range, sf::Time attack_cooldown);

	int get_range();
	int get_attack_damage();

	virtual void attack(std::vector<Enemy>& enemies) = 0;
};