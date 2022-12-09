#include "HealthBar.h"

HealthBar::HealthBar(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position) : Sprite(texture, crop, position) {
	this->current_health_bar.setSize(sf::Vector2f(this->sprite.getTextureRect().width, this->sprite.getTextureRect().height * (6.f / 32.f)));
	this->current_health_bar.setFillColor(sf::Color(199, 10, 10, 255));
	this->current_health_bar.setPosition(sf::Vector2f(this->sprite.getPosition().x + 1, this->sprite.getPosition().y - 1));
	this->current_health_bar.setOrigin(this->current_health_bar.getGlobalBounds().width / 2, this->current_health_bar.getGlobalBounds().height / 2);
}

void HealthBar::move(float x, float y) {
	this->sprite.move(x, y);
	this->current_health_bar.move(x, y);
}

void HealthBar::update(int health, int max_health) {
	float percentage = (float)health / (float)max_health;
	this->current_health_bar.setSize(sf::Vector2f((this->sprite.getTextureRect().width - 2) * percentage, this->sprite.getTextureRect().height * (6.f / 32.f)));
}

void HealthBar::draw(sf::RenderWindow& window) {
	window.draw(this->current_health_bar);
	window.draw(this->sprite);
}
