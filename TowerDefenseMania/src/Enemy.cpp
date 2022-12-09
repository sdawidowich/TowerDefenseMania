#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, sf::Texture* gui_textures, sf::IntRect* health_bar_crop, float speed, int health, int damage, int gold_value, sf::Vector2i dir)
	: Sprite(texture, crop, position), health_bar(HealthBar(gui_textures, health_bar_crop, sf::Vector2f(position.x, position.y - 20.f))) {
	this->speed = speed;
	this->max_health = health;
	this->health = health;
	this->damage = damage;
	this->gold_value = gold_value;
	this->path_index = 0;
	this->dir = dir;
}

int Enemy::get_health() {
	return this->health;
}

int Enemy::get_damage() {
	return this->damage;
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
	this->health_bar.move(this->dir.x * this->speed, this->dir.y * this->speed);
}

void Enemy::update_health_bar() {
	this->health_bar.update(this->health, this->max_health);
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

void Enemy::draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
	this->health_bar.draw(window);
}
