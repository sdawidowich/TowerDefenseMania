#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Sprite.h"
#include "Tower.h"
#include "Button.h"

class GUI {
private:
	sf::Texture* gui_sprite_sheet;
	sf::Texture* tower_sprite_sheet;
	std::vector<Button> buttons;
	Tower* selection;
public:
	GUI(sf::Texture* gui_sprite_sheet, sf::Texture* tower_sprite_sheet);

	void update_selection(sf::RenderWindow& window, sf::Event& event);
	void move_selection();

	void draw_buttons(sf::RenderWindow& window);
	void draw_selection(sf::RenderWindow& window);
};