#pragma once
#include "Sprite.h"

class Button : public Sprite {
private:
public:
	Button(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position);
};