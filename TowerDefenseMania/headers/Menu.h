#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Game_State.h"
#include "GameStats.h"
#include "Button.h"

class Menu {
private:
	std::vector<Button> buttons;
	std::vector<sf::Text> text;
	std::vector<Sprite> sprites;
public:
	Menu();

	void add_button(Button btn);
	void add_text(sf::Text text);
	void add_sprite(Sprite sprite);

	std::vector<Button>* get_buttons();

	void draw(sf::RenderWindow& window);
};
