#include "Sprite.h"

Sprite::Sprite(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position) {
	this->texture = texture;
	this->crop = crop;

	this->sprite = sf::Sprite(*this->texture, *this->crop);
	this->sprite.setPosition(position);
	this->sprite.setOrigin(sf::Vector2f(this->sprite.getGlobalBounds().width / 2.0, this->sprite.getGlobalBounds().height / 2.0));
}

sf::FloatRect Sprite::get_sprite_bounds() {
	return this->sprite.getGlobalBounds();
}

sf::Vector2f Sprite::get_position() {
	return this->sprite.getPosition();
}

void Sprite::set_position(sf::Vector2f position) {
	this->sprite.setPosition(position);
}

void Sprite::set_rotation(float angle) {
	this->sprite.setRotation(angle);
}

void Sprite::set_scale(sf::Vector2f scale) {
	this->sprite.setScale(scale);
}

void Sprite::draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
}
