#pragma once
#include <SFML/Graphics.hpp>

#include "Sprite.h"

class Tile : public Sprite {
private:
public:
	Tile(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position);

	void draw(sf::RenderWindow& window);
};