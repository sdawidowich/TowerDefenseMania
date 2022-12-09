#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Game_State.h"
#include "GameStats.h"
#include "Button.h"

class StatScreen {
private:
	sf::Font* font;
	sf::Texture* gui_sprite_sheet;
	std::map<int, sf::IntRect*>* gui_sprites_indices;
	Game_State* state;

	std::vector<Button> buttons;

	int page;
public:
	StatScreen(sf::Font* font, sf::Texture* gui_sprite_sheet, std::map<int, sf::IntRect*>* gui_sprites_indices, Game_State* state);

	std::vector<Button>* get_buttons();

	void draw_buttons(sf::RenderWindow& window);
	void draw_stats(sf::RenderWindow& window, std::vector<GameStats>* stats_list);
};

