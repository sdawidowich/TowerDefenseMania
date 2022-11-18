#include "GUI.h"
#include <iostream>
#include "TowerTypes.h"

GUI::GUI(sf::Texture* gui_sprite_sheet, std::map<int, sf::IntRect*>* gui_sprites_indices, sf::Texture* tower_sprite_sheet, std::map<int, sf::IntRect*>* tower_sprites_indices) {
	this->gui_sprite_sheet = gui_sprite_sheet;
	this->gui_sprites_indices = gui_sprites_indices;
	this->tower_sprite_sheet = tower_sprite_sheet;
	this->tower_sprites_indices = tower_sprites_indices;

	this->tower_selection = Towers::NONE;
	this->new_tower = nullptr;

	Button archer_tower_select_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[0], sf::Vector2f(602, 615), "archerTowerSelector", (*this->gui_sprites_indices)[1], (*this->gui_sprites_indices)[2]);
	this->buttons.push_back(archer_tower_select_button);

	Button wizard_tower_select_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[0], sf::Vector2f(698, 615), "wizardTowerSelector", (*this->gui_sprites_indices)[1], (*this->gui_sprites_indices)[2]);
	this->buttons.push_back(wizard_tower_select_button);
}

template<typename T>
void GUI::select_tower(Button& button, sf::Vector2f& mouse_pos, Towers tower_type, int tower_sprite_index) {
	if (this->tower_selection != tower_type) {
		delete this->new_tower;
		this->new_tower = nullptr;

		this->tower_selection = tower_type;
		this->new_tower = new T(tower_sprite_sheet, (*this->tower_sprites_indices)[tower_sprite_index], mouse_pos);
		button.set_selected();
	}
	else {
		this->tower_selection = Towers::NONE;
		delete this->new_tower;
		this->new_tower = nullptr;
		button.set_unselected();
	}
}

void GUI::update_selection(sf::RenderWindow& window, sf::Event& event) {
	for (int i = 0; i < this->buttons.size(); i++) {
		sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));

		this->buttons[i].update(event, mouse_pos);
		
		if (this->buttons[i].get_state() == Button_State::BTN_CLICKED) {
			if (this->buttons[i].get_label() == "archerTowerSelector") {
				this->select_tower<ArcherTower>(this->buttons[i], mouse_pos, Towers::ARCHER_TOWER, 0);
			}
			else if (this->buttons[i].get_label() == "wizardTowerSelector") {
				this->select_tower<WizardTower>(this->buttons[i], mouse_pos, Towers::WIZARD_TOWER, 1);
			}
		}
	}
}

void GUI::move_selection(sf::RenderWindow& window) {
	if (this->new_tower) {
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		this->new_tower->set_position(sf::Vector2f(mouse_pos));
	}
}

void GUI::draw_buttons(sf::RenderWindow& window) {
	for (int i = 0; i < this->buttons.size(); i++) {
		buttons[i].draw(window);
	}
}

void GUI::draw_selection(sf::RenderWindow& window) {
	if (this->new_tower) {
		new_tower->draw(window);
	}
}
