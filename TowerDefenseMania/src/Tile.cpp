#include "Tile.h"

Tile::Tile(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position) : Sprite(texture, crop, position) {}

void Tile::draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
}
