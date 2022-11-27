#include "Tower.h"

Tower::Tower(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, int attack_damage, int range, sf::Time attack_cooldown) 
	: Sprite(texture, crop, position) {
	this->attack_damage = attack_damage;
	this->range = range;

	this->timer.restart();
	this->attack_cooldown = attack_cooldown;

	this->sprite.setScale(sf::Vector2f(2.f, 2.f));
}

int Tower::get_range() {
	return this->range;
}

int Tower::get_attack_damage() {
	return this->attack_damage;
}
