#pragma once
#include <SFML/Graphics.hpp>

#include "Game_State.h"
#include "Button.h"

class StartScreen {
private:
	sf::Font* font;
	sf::Texture* gui_sprite_sheet;
	std::map<int, sf::IntRect*>* gui_sprites_indices;
	Game_State* state;

	std::vector<Button> buttons;
public:
	StartScreen(sf::Font* font, sf::Texture* gui_sprite_sheet, std::map<int, sf::IntRect*>* gui_sprites_indices, Game_State* state);

	std::vector<Button>* get_buttons();

	void draw_buttons(sf::RenderWindow& window);
};

