#include "Tile.h"

Tile::Tile(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position) { 
	this->texture = texture;
	this->crop = crop;

	this->sprite = sf::Sprite(*this->texture, *this->crop);
	this->sprite.setPosition(position);
}

void Tile::draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
}
