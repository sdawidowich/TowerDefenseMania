#pragma once
#include "Tower.h"

class ArcherTower : public Tower {
private:
public:
	ArcherTower(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position);

	void attack(std::vector<Enemy>& enemies, int& gold, GameStats& stats) override;
};

class WizardTower : public Tower {
private:
public:
	WizardTower(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position);

	void attack(std::vector<Enemy>& enemies, int& gold, GameStats& stats) override;
};