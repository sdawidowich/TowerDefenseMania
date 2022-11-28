#include "GUI.h"

#include <iostream>
#include <sstream>

#include "TowerTypes.h"

GUI::GUI(sf::Font* font, sf::Texture* gui_sprite_sheet, std::map<int, sf::IntRect*>* gui_sprites_indices, sf::Texture* tower_sprite_sheet, std::map<int, sf::IntRect*>* tower_sprites_indices) {
	this->font = font;
	this->gui_sprite_sheet = gui_sprite_sheet;
	this->gui_sprites_indices = gui_sprites_indices;
	this->tower_sprite_sheet = tower_sprite_sheet;
	this->tower_sprites_indices = tower_sprites_indices;
	this->new_tower = nullptr;

	this->id_map = {
		{3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4},
		{4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4},
		{3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3}
	};

	this->rotation_map = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90},
		{270, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90},
		{270, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90},
		{270, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180}
	};

	this->num_tiles = this->id_map.size() * this->id_map[0].size();
	this->tiles = new Tile * [this->num_tiles];

	for (int i = 0; i < this->id_map.size(); i++) {
		for (int j = 0; j < this->id_map[i].size(); j++) {
			sf::Vector2f position(j * 32.f + 16.f, i * 32.f + 16.f + 608.f);
			int index = (i * this->id_map[i].size()) + j;
			this->tiles[index] = new Tile(this->gui_sprite_sheet, (*this->gui_sprites_indices)[this->id_map[i][j]], position);
		}
	}
	for (int i = 0; i < this->rotation_map.size(); i++) {
		for (int j = 0; j < this->rotation_map[i].size(); j++) {
			if (this->rotation_map[i][j]) {
				int index = (i * this->rotation_map[i].size()) + j;
				this->tiles[index]->set_rotation(this->rotation_map[i][j]);
			}
		}
	}

	Button archer_tower_select_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[0], sf::Vector2f(602, 670), "archerTowerSelector", (*this->gui_sprites_indices)[1], (*this->gui_sprites_indices)[2]);
	this->buttons.push_back(archer_tower_select_button);

	Button wizard_tower_select_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[0], sf::Vector2f(698, 670), "wizardTowerSelector", (*this->gui_sprites_indices)[1], (*this->gui_sprites_indices)[2]);
	this->buttons.push_back(wizard_tower_select_button);
}

void GUI::reset_selection() {
	this->new_tower = nullptr;

	for (int i = 0; i < this->buttons.size(); i++) {
		this->buttons[i].deselect();
	}
}

void GUI::draw_text(sf::RenderWindow& window, int level, int gold, int health) {
	if (this->font) {
		std::stringstream lvl_str;
		lvl_str << "Level " << level;
		std::string time_str = lvl_str.str();

		sf::Text level_text;
		level_text.setFont(*this->font);
		level_text.setString(time_str);
		level_text.setCharacterSize(32);
		level_text.setPosition(20, 45);
		level_text.setFillColor(sf::Color::White);

		window.draw(level_text);
	}
}

void GUI::draw_background(sf::RenderWindow& window) {
	for (int i = 0; i < this->num_tiles; i++) {
		this->tiles[i]->draw(window);
	}
}

void GUI::draw_buttons(sf::RenderWindow& window) {
	for (int i = 0; i < this->buttons.size(); i++) {
		this->buttons[i].draw(window);
	}
}

void GUI::draw_selection(sf::RenderWindow& window) {
	if (this->new_tower) {
		this->new_tower->draw(window);
	}
}

Tower* GUI::get_new_tower() {
	return this->new_tower;
}

std::vector<Button>* GUI::get_buttons() {
	return &this->buttons;
}
