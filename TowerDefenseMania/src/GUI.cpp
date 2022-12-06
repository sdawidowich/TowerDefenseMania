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
	this->button_label = sf::Text();
	this->error_text = sf::Text();
	this->error_timer.restart();
	this->error_lifespan = sf::seconds(2.f);

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

	Button archer_tower_select_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[0], sf::Vector2f(602, 670), "archerTowerSelector",
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[0]); 
		},
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[1]); 
		},
		[this](sf::RenderWindow& window, Button* btn) {
			this->select_tower<ArcherTower>(btn, sf::Vector2f(sf::Mouse::getPosition(window)), 0); 
		});
	this->buttons.push_back(archer_tower_select_button);

	Button wizard_tower_select_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[0], sf::Vector2f(698, 670), "wizardTowerSelector",
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[0]); 
		},
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[1]); 
		},
		[this](sf::RenderWindow& window, Button* btn) {
			this->select_tower<WizardTower>(btn, sf::Vector2f(sf::Mouse::getPosition(window)), 1); 
		});
	this->buttons.push_back(wizard_tower_select_button);
}

void GUI::reset_selection() {
	this->new_tower = nullptr;

	for (int i = 0; i < this->buttons.size(); i++) {
		this->buttons[i].deselect();
	}
}

void GUI::reset_button_label() {
	this->button_label = sf::Text();
}

void GUI::reset_error_text() {
	this->error_text = sf::Text();
	this->error_timer.restart();
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
		gold_text.setPosition(50, 662);
		gold_text.setFillColor(sf::Color::White);

		std::stringstream health_ss;
		health_ss << health << " / " << max_health;
		std::string health_str = health_ss.str();

		sf::Text health_text;
		health_text.setFont(*this->font);
		health_text.setString(health_str);
		health_text.setCharacterSize(32);
		health_text.setPosition(180, 662);
		health_text.setFillColor(sf::Color::White);

		window.draw(level_text);
		window.draw(gold_text);
		window.draw(health_text);
	}
}

void GUI::draw_icons(sf::RenderWindow& window) {
	Sprite gold_sprite(this->gui_sprite_sheet, (*this->gui_sprites_indices)[6], sf::Vector2f(30.f, 686.f));
	Sprite health_sprite(this->gui_sprite_sheet, (*this->gui_sprites_indices)[7], sf::Vector2f(160.f, 686.f));

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

void GUI::draw_button_label(sf::RenderWindow& window) {
	if (!this->button_label.getString().isEmpty()) {
		window.draw(this->button_label);

		sf::Vector2f icon_pos(this->button_label.getPosition().x - 35, this->button_label.getPosition().y + 12);
		Sprite icon_sprite(this->gui_sprite_sheet, (*this->gui_sprites_indices)[6], icon_pos);
		icon_sprite.set_scale(sf::Vector2f(0.9f, 0.9f));
		icon_sprite.draw(window);
	}
}

void GUI::draw_error_text(sf::RenderWindow& window) {
	if (!this->error_text.getString().isEmpty()) {
		window.draw(this->error_text);
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

sf::Text GUI::get_error_text() {
	return this->error_text;
}

sf::Clock GUI::get_error_timer() {
	return this->error_timer;
}

sf::Time GUI::get_error_lifespan() {
	return this->error_lifespan;
}

void GUI::set_tower_range_indicator(sf::CircleShape* tower_range_indicator) {
	this->tower_range_indicator = tower_range_indicator;
}

void GUI::set_button_label(Button& button, TowerCost cost) {
	sf::Vector2f button_pos = button.get_position();

	sf::Text label_text;
	label_text.setFont(*this->font);
	label_text.setString(std::to_string((int)cost));
	label_text.setCharacterSize(24);
	label_text.setPosition(button_pos.x, button_pos.y - 55);
	label_text.setFillColor(sf::Color::White);
	sf::FloatRect bounds = label_text.getGlobalBounds();
	label_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));

	this->button_label = label_text;
}

void GUI::set_error_text(std::string error_str) {
	this->reset_error_text();
	sf::Text error_text;
	error_text.setFont(*this->font);
	error_text.setString(error_str);
	error_text.setCharacterSize(24);
	error_text.setPosition(sf::Vector2f(640.f, 100.f));
	error_text.setFillColor(sf::Color::Red);
	sf::FloatRect bounds = error_text.getGlobalBounds();
	error_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));

	this->error_text = error_text;
}