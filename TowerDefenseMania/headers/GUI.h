#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Sprite.h"
#include "Tower.h"
#include "Button.h"

enum class Towers {
	NONE, ARCHER_TOWER, WIZARD_TOWER
};

class GUI {
private:
	sf::Texture* gui_sprite_sheet;
	sf::Texture* tower_sprite_sheet;
	std::map<int, sf::IntRect*>* gui_sprites_indices;
	std::map<int, sf::IntRect*>* tower_sprites_indices;

	std::vector<Button> buttons;

	Towers tower_selection;
	Tower* new_tower;
public:
	GUI(sf::Texture* gui_sprite_sheet, std::map<int, sf::IntRect*>* gui_sprites_indices, sf::Texture* tower_sprite_sheet, std::map<int, sf::IntRect*>* tower_sprites_indices);

	template<typename T>
	void select_tower(Button& button, sf::Vector2f& mouse_pos, Towers tower_type, int tower_sprite_index);
	void update_selection(sf::RenderWindow& window, sf::Event& event);
	void move_selection(sf::RenderWindow& window);

	void draw_buttons(sf::RenderWindow& window);
	void draw_selection(sf::RenderWindow& window);
};
