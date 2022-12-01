#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include <Enemy.h>

#include "Sprite.h"

enum class TowerCost {
	ARCHER_TOWER = 100, WIZARD_TOWER = 250
};


class Tower : public Sprite {
protected:
	int attack_damage;
	int range;
	int cost;

	sf::Clock timer;
	sf::Time attack_cooldown;
public:
	Tower(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, int attack_damage, int range, TowerCost cost, sf::Time attack_cooldown);

	int get_attack_damage();
	int get_range();
	int get_cost();

	virtual void attack(std::vector<Enemy>& enemies, int& gold) = 0;
};