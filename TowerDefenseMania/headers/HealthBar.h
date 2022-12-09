#pragma once
#include <SFML/Graphics.hpp>

#include "Sprite.h"

class HealthBar : public Sprite {
private:
	sf::RectangleShape current_health_bar;
public:
	HealthBar(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position);

	void move(float x, float y);
	void update(int health, int max_health);

	void draw(sf::RenderWindow& window);
};

