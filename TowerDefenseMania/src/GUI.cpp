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
	this->tower_range_indicator = nullptr;

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

	this->num_tiles = (int)this->id_map.size() * (int)this->id_map[0].size();
	this->tiles = new Tile * [this->num_tiles];

	for (int i = 0; i < this->id_map.size(); i++) {
		for (int j = 0; j < this->id_map[i].size(); j++) {
			sf::Vector2f position(j * 32.f + 16.f, i * 32.f + 16.f + 608.f);
			if (i >= 3) {
				position.y = i * 32.f + 608.f;
			}
			int index = (i * (int)this->id_map[i].size()) + j;
			this->tiles[index] = new Tile(this->gui_sprite_sheet, (*this->gui_sprites_indices)[this->id_map[i][j]], position);
		}
	}
	for (int i = 0; i < this->rotation_map.size(); i++) {
		for (int j = 0; j < this->rotation_map[i].size(); j++) {
			if (this->rotation_map[i][j]) {
				int index = (i * (int)this->rotation_map[i].size()) + j;
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

void GUI::draw_text(sf::RenderWindow& window, int level, int gold, int health, int max_health) {
	if (this->font) {
		std::stringstream lvl_ss;
		lvl_ss << "Level " << level;
		std::string lvl_str = lvl_ss.str();

		sf::Text level_text;
		level_text.setFont(*this->font);
		level_text.setString(lvl_str);
		level_text.setCharacterSize(32);
		level_text.setPosition(20, 620);
		level_text.setFillColor(sf::Color::White);

		sf::Text gold_text;
		gold_text.setFont(*this->font);
		gold_text.setString(std::to_string(gold));
		gold_text.setCharacterSize(32);
		gold_text.setPosition(60, 662);
		gold_text.setFillColor(sf::Color::White);

		std::stringstream health_ss;
		health_ss << health << " / " << max_health;
		std::string health_str = health_ss.str();

		sf::Text health_text;
		health_text.setFont(*this->font);
		health_text.setString(health_str);
		health_text.setCharacterSize(32);
		health_text.setPosition(200, 662);
		health_text.setFillColor(sf::Color::White);

		window.draw(level_text);
		window.draw(gold_text);
		window.draw(health_text);
	}
}

void GUI::draw_icons(sf::RenderWindow& window) {
	Sprite gold_sprite(this->gui_sprite_sheet, (*this->gui_sprites_indices)[6], sf::Vector2f(30.f, 686.f));
	Sprite health_sprite(this->gui_sprite_sheet, (*this->gui_sprites_indices)[7], sf::Vector2f(150.f, 686.f));

	Sprite archer_tower_sprite(this->tower_sprite_sheet, (*this->tower_sprites_indices)[0], this->buttons[0].get_position());
	Sprite wizard_tower_sprite(this->tower_sprite_sheet, (*this->tower_sprites_indices)[1], this->buttons[1].get_position());

	gold_sprite.draw(window);
	health_sprite.draw(window);
	archer_tower_sprite.draw(window);
	wizard_tower_sprite.draw(window);
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

void GUI::draw_tower_range_indicator(sf::RenderWindow& window) {
	if (this->tower_range_indicator) {
		window.draw(*this->tower_range_indicator);
	}
}

std::vector<Button>* GUI::get_buttons() {
	return &this->buttons;
}

Tower* GUI::get_new_tower() {
	return this->new_tower;
}

sf::CircleShape* GUI::get_tower_range_indicator() {
	return this->tower_range_indicator;
}

void GUI::set_tower_range_indicator(sf::CircleShape* tower_range_indicator) {
	this->tower_range_indicator = tower_range_indicator;
}

