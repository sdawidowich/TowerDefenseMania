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
	sf::Text button_label;
	sf::Text error_text;

	sf::Clock error_timer;
	sf::Time error_lifespan;
public:
	GUI(sf::Font* font, sf::Texture* gui_sprite_sheet, std::map<int, sf::IntRect*>* gui_sprites_indices, sf::Texture* tower_sprite_sheet, std::map<int, sf::IntRect*>* tower_sprites_indices);

	void reset_selection();
	void reset_error_text();
	void reset_button_label();

	void draw_text(sf::RenderWindow& window, int level, int gold, int health, int max_health);
	void draw_icons(sf::RenderWindow& window);
	void draw_background(sf::RenderWindow& window);
	void draw_buttons(sf::RenderWindow& window);
	void draw_selection(sf::RenderWindow& window);
	void draw_tower_range_indicator(sf::RenderWindow& window);
	void draw_button_label(sf::RenderWindow& window);
	void draw_error_text(sf::RenderWindow& window);

	std::vector<Button>* get_buttons();
	Tower* get_new_tower();
	sf::CircleShape* get_tower_range_indicator();
	sf::Text get_error_text();
	sf::Clock get_error_timer();
	sf::Time get_error_lifespan();

	void set_tower_range_indicator(sf::CircleShape* tower_range_indicator);
	void set_button_label(Button& button, TowerCost cost);
	void set_error_text(std::string error_str);

	template<typename T>
	void select_tower(Button* button, sf::Vector2f mouse_pos, int tower_sprite_index) {
		delete this->new_tower;
		this->new_tower = nullptr;

		if (!button->is_selected()) {
			this->new_tower = new T(this->tower_sprite_sheet, (*this->tower_sprites_indices)[tower_sprite_index], mouse_pos);

			for (int i = 0; i < this->buttons.size(); i++) {
				this->buttons[i].deselect();
			}
			button->select();
			button->set_crop((*this->gui_sprites_indices)[2]);
		}
		else {
			for (int i = 0; i < this->buttons.size(); i++) {
				this->buttons[i].deselect();
			}
		}
	}

};
