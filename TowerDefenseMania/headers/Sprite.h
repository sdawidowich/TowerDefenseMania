#pragma once
#include <SFML/Graphics.hpp>

class Sprite {
protected:
	sf::Texture* texture;
	sf::IntRect* crop;
	sf::Sprite sprite;
public:
	Sprite(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position);
	
	sf::FloatRect get_sprite_bounds();
	void draw(sf::RenderWindow& window);
};