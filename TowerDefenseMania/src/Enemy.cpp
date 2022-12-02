#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, float speed, int health, int damage, int gold_value, sf::Vector2i dir) 
	: Sprite(texture, crop, position) {
	this->speed = speed;
	this->health = health;
	this->damage = damage;
	this->gold_value = gold_value;
	this->path_index = 0;
	this->dir = dir;
}

int Enemy::get_health() {
	return this->health;
}

int Enemy::get_gold_value() {
	return this->gold_value;
}

int Enemy::get_path_index() {
	return this->path_index;
}

sf::Vector2i Enemy::get_dir() {
	return this->dir;
}

void Enemy::move() {
	this->sprite.move(this->dir.x * this->speed, this->dir.y * this->speed);
}

void Enemy::set_path_index(int path_index) {
	this->path_index = path_index;
}

void Enemy::change_dir(sf::Vector2i dir) {
	this->dir = dir;
}

void Enemy::take_damage(int damage) {
	this->health -= damage;
}
