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
	sf::Vector2f get_position();

	void set_position(sf::Vector2f position);
	void set_rotation(float angle);
	void set_scale(sf::Vector2f scale);

	void draw(sf::RenderWindow& window);
};