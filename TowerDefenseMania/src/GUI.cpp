#include "GUI.h"
#include <iostream>
#include "TowerTypes.h"

GUI::GUI(sf::Texture* gui_sprite_sheet, sf::Texture* tower_sprite_sheet) {
	this->gui_sprite_sheet = gui_sprite_sheet;
	this->tower_sprite_sheet = tower_sprite_sheet;
	this->selection = nullptr;

	sf::IntRect* crop = new sf::IntRect(32 * 6, 0, 32, 32);
	Button test_button = Button(this->gui_sprite_sheet, crop, sf::Vector2f(650, 615));
	this->buttons.push_back(test_button);
}

void GUI::update_selection(sf::RenderWindow& window, sf::Event& event) {
	if (event.type == sf::Event::MouseButtonReleased) {
		for (int i = 0; i < this->buttons.size(); i++) {
			sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
			if (buttons[i].get_sprite_bounds().intersects(sf::FloatRect(mouse_pos, sf::Vector2f(1, 1)))) {
				if (!this->selection) {
					sf::IntRect* crop = new sf::IntRect(0, 0, 32, 32);
					this->selection = new ArcherTower(tower_sprite_sheet, crop, mouse_pos);
				}
			}
		}
	}
}

void GUI::move_selection() {
	if (this->selection) {
		sf::Vector2i mouse_pos = sf::Mouse::getPosition();
		this->selection->set_position(sf::Vector2f(mouse_pos));
	}
}

void GUI::draw_buttons(sf::RenderWindow& window) {
	for (int i = 0; i < this->buttons.size(); i++) {
		buttons[i].draw(window);
	}
}

void GUI::draw_selection(sf::RenderWindow& window) {
	if (this->selection) {
		selection->draw(window);
	}
}
