#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Tile.h"
#include "Tower.h"
#include "Button.h"

class GUI {
private:
	sf::Font* font;
	sf::Texture* gui_sprite_sheet;
	sf::Texture* tower_sprite_sheet;
	std::map<int, sf::IntRect*>* gui_sprites_indices;
	std::map<int, sf::IntRect*>* tower_sprites_indices;

	std::vector< std::vector<int> > id_map;
	std::vector< std::vector<float> > rotation_map;
	Tile** tiles;
	int num_tiles;

	std::vector<Button> buttons;

	Tower* new_tower;

	sf::CircleShape* tower_range_indicator;
	sf::Text button_hover_label;
public:
	GUI(sf::Font* font, sf::Texture* gui_sprite_sheet, std::map<int, sf::IntRect*>* gui_sprites_indices, sf::Texture* tower_sprite_sheet, std::map<int, sf::IntRect*>* tower_sprites_indices);

	void reset_selection();

	void draw_text(sf::RenderWindow& window, int level, int gold, int health, int max_health);
	void draw_icons(sf::RenderWindow& window);
	void draw_background(sf::RenderWindow& window);
	void draw_buttons(sf::RenderWindow& window);
	void draw_selection(sf::RenderWindow& window);
	void draw_tower_range_indicator(sf::RenderWindow& window);
	void draw_button_hover_label(sf::RenderWindow& window);

	std::vector<Button>* get_buttons();
	Tower* get_new_tower();
	sf::CircleShape* get_tower_range_indicator();

	void set_tower_range_indicator(sf::CircleShape* tower_range_indicator);
	void set_button_hover_label(Button& button, TowerCost cost);
	void reset_button_hover_label();

	template<typename T>
	void select_tower(Button& button, sf::Vector2f& mouse_pos, int tower_sprite_index) {
		delete this->new_tower;
		this->new_tower = nullptr;

		if (!button.get_selected()) {
			this->new_tower = new T(this->tower_sprite_sheet, (*this->tower_sprites_indices)[tower_sprite_index], mouse_pos);

			for (int i = 0; i < this->buttons.size(); i++) {
				this->buttons[i].deselect();
			}
			button.select();
		}
		else {
			for (int i = 0; i < this->buttons.size(); i++) {
				this->buttons[i].deselect();
			}
		}
	}

};
