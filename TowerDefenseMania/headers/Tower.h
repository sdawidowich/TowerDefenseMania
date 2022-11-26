#pragma once
#include <SFML/Graphics.hpp>

#include "Sprite.h"

class Tower : public Sprite {
protected:
	int attack_damage;
	int range;
public:
	Tower(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, int attack_damage, int range);

	virtual void attack() = 0;
};