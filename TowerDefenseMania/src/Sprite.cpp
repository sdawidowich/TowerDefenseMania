#include "Sprite.h"

Sprite::Sprite(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position) {
	this->texture = texture;
	this->crop = crop;

	this->sprite = sf::Sprite(*this->texture, *this->crop);
	this->sprite.setPosition(position);
}

sf::FloatRect Sprite::get_sprite_bounds()
{
	return this->sprite.getGlobalBounds();
}

void Sprite::draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
}
