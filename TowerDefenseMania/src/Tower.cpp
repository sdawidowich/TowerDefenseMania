#include "Tower.h"

Tower::Tower(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, int attack_damage, int range) : Sprite(texture, crop, position) {
	this->attack_damage = attack_damage;
	this->range = range;
}

void Tower::set_position(sf::Vector2f position) {
	this->sprite.setPosition(position);
}
