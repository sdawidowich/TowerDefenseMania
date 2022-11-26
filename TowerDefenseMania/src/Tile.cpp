#include "Tile.h"

#include <iostream>

Tile::Tile(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position) : Sprite(texture, crop, position) {
	this->highlight = false;
}

void Tile::set_highlight(bool state) {
	if (!this->highlight && state) {
		sf::Uint8 lightness = 220;
		sprite.setColor(sf::Color(lightness, lightness, lightness));
	}
	else if (this->highlight and !state) {
		sf::Uint8 lightness = 255;
		sprite.setColor(sf::Color(lightness, lightness, lightness));
	}
	this->highlight = state;
}
