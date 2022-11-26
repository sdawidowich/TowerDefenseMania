#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, float speed, int health, int damage, sf::Vector2i dir) 
	: Sprite(texture, crop, position) {
	this->speed = speed;
	this->health = health;
	this->damage = damage;
	this->dir = dir;
}

void Enemy::move() {
	this->sprite.move(this->dir.x * this->speed, this->dir.y * this->speed);
}

void Enemy::change_dir(sf::Vector2i dir) {
	this->dir = dir;
}
