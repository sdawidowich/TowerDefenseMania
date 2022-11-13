#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, float speed, int health, sf::Vector2i dir) : Sprite(texture, crop, position) {
	this->speed = speed;
	this->health = health;
	this->dir = dir;
}

void Enemy::move() {
	this->sprite.move(this->dir.x * this->speed, this->dir.y * this->speed);
}
