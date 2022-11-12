#pragma once
#include <SFML/Graphics.hpp>

class Tile {
private:
	sf::Texture* texture;
	sf::IntRect* crop;
	sf::Sprite sprite;
public:
	Tile(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position);

	void draw(sf::RenderWindow& window);
};