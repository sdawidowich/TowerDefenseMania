#pragma once
#include "Tower.h"

class ArcherTower : public Tower {
private:
public:
	ArcherTower(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position);

	void attack() override;
};