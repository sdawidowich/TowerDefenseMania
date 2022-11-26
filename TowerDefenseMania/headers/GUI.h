#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Sprite.h"
#include "Tower.h"
#include "Button.h"

class GUI {
private:
	sf::Font* font;
	sf::Texture* gui_sprite_sheet;
	sf::Texture* tower_sprite_sheet;
	std::map<int, sf::IntRect*>* gui_sprites_indices;
	std::map<int, sf::IntRect*>* tower_sprites_indices;

	std::vector<Button> buttons;
	Tower* new_tower;
public:
	GUI(sf::Font* font, sf::Texture* gui_sprite_sheet, std::map<int, sf::IntRect*>* gui_sprites_indices, sf::Texture* tower_sprite_sheet, std::map<int, sf::IntRect*>* tower_sprites_indices);

	template<typename T>
	void select_tower(Button& button, sf::Vector2f& mouse_pos, int tower_sprite_index);
	void update_selection(sf::RenderWindow& window, sf::Event& event);

	void draw_text(sf::RenderWindow& window, int level, int gold, int health);
	void draw_buttons(sf::RenderWindow& window);
	void draw_selection(sf::RenderWindow& window);

	Tower* get_new_tower();
};
